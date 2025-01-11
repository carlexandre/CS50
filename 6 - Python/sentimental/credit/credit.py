def main():
    while True:
        try:
            number = int(input("Number: "))
        except ValueError:
            pass
        else:
            break

    leng = lenght(number)

    if leng not in [13, 15, 16]:
        print("INVALID")

    elif leng == 15 and initnumber(number, False) in [34, 37]:
        print("AMEX")

    elif leng == 16 and initnumber(number, False) in [51, 52, 53, 54, 55]:
        print("MASTERCARD")

    elif (leng == 16 or leng == 13) and initnumber(number, True) == 4:
        if verify(number):
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")


def initnumber(num, firstorboth):
    save = num
    if firstorboth:
        while save > 0:
            rest = save%10
            save = save//10
    else:
        while save > 10:
            rest = save%100
            save = save//10

    return rest


def lenght(num):
    counter = 0

    while num > 0:
        counter += 1
        num = num//10

    return counter


def verify(num):
    num1 = num//10
    s1 = 0
    s0 = 0

    while num > 0:
        s0 += num%10
        num = num//100

    while num1 > 0:
        m = (num1%10)*2
        if m > 9:
            m -= 9
        s1 += m
        num1= num1//100

    return (s0+s1) % 10 == 0


main()
