height = 0

while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        pass

for i in range(1, height+1):
    blank = height - i
    for j in range(blank):
        print(' ', end='')
    for j in range(height - blank):
        print('#', end='')
    print('  ', end='')
    for j in range(height - blank):
        print('#', end='')
    print()
