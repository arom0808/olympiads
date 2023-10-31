def main():
    non_period, period = input()[2:].split('(')
    period = period[:-1]
    print(non_period, period)


main()
