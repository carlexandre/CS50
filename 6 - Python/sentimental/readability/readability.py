from math import ceil, floor

def main():
    text = input("Text: ")

    w = words(text)

    l = (letters(text)/w) * 100
    s = (sentences(text)/w) * 100

    grade = 0.0588 * l - 0.296 * s - 15.8

    if grade%1 < 0.5:
        grade = floor(grade)
    else:
        grade = ceil(grade)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def letters(string):
    countletters = 0

    for i in string:
        if i.lower() in "abcdefghijklmnopqrstuvwxyz":
            countletters += 1

    return countletters


def words(string):
    return string.count(' ') + 1


def sentences(string):
    return string.count('.') + string.count('!') + string.count('?')


main()
