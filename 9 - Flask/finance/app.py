import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]

    symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ?", user_id)

    for symbol in symbols:
        stock = lookup(symbol["symbol"])
        currentprice = stock["price"]
        db.execute("UPDATE transactions SET currentprice = ? WHERE symbol = ?", currentprice, symbol["symbol"])

    transactions_db = db.execute("SELECT symbol, SUM(shares) AS shares, currentprice FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users where id = ?", user_id)
    cash = cash_db[0]["cash"]

    return render_template("index.html", transactions = transactions_db, cash = float(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Must give symbol")

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be a integer number")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Invalid Symbol")

        if not shares:
            return apology("Must give a share")

        if shares<0:
            return apology("Share must be greater than 0")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < transaction_value:
            return apology("Cash is not enough")

        updt_cash = user_cash - transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updt_cash, user_id)

        date = datetime.datetime.now()

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date, currentprice, type) VALUES (?, ?, ?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], date, stock["price"], "Purchase")

        flash("Purchase Completed")

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]

    transactions_db = db.execute("SELECT symbol, shares, price, date, type FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions = transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must Give Symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("This symbol doesn't exist")

        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        try:
            if not username:
                return apology("Blank username is invalid")
            elif not password:
                return apology("Blank password is invalid")
            elif not confirmation:
                return apology("Blank confirmation is invalid")
            elif password != confirmation:
                return apology("Passwords Do Not Match")
            else:
                hash = generate_password_hash(password)

                new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
                session["user_id"] = new_user

                return redirect("/registers")

        except ValueError:
            return apology("Username already exists")

    return render_template("register.html")


@app.route("/registers")
def registerok():
    return render_template("registersuc.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Must give symbol")

        if shares<0:
            return apology("Share must be greater than 0")

        stock = lookup(symbol.upper())

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        shares_db = db.execute("SELECT SUM(shares) FROM transactions WHERE symbol = ? AND user_id = ? GROUP BY symbol", symbol, user_id)
        print(shares_db)
        user_shares = shares_db[0]["SUM(shares)"]

        if shares > user_shares:
            return apology("Amount of share is not enough")

        updt_cash = user_cash + transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updt_cash, user_id)

        date = datetime.datetime.now()

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, currentprice, date, type) VALUES (?, ?, ?, ?, ?, ?, ?)", user_id, stock["symbol"], (-1)*shares, stock["price"], stock["price"], date, "Sale")

        flash("Sale Completed")

        return redirect("/")


    user_id = session["user_id"]
    symbols_user = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
    print(symbols_user)

    return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])
