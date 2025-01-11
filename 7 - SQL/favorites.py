import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}

    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

    for favorite in sorted(counts, key=counts.get,reverse = True):
         #counts.get is used to make the sort in dictionaries with the right side, the values

         print(f"{favorite}: {counts[favorite]}")
