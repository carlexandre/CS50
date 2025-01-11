import csv

books = []

with open("books.csv") as file:
    text = csv.DictReader(file)
    for row in text:
        books.append(row)

for book in books:
    print(f"{book['title']} - {book['author']}")
