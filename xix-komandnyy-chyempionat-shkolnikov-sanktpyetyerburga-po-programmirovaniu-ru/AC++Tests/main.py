import datetime


def addZero(integer):
    if integer < 10:
        return "0" + str(integer)
    else:
        return str(integer)


def generateIn():
    infile = open("pyin.in", "w")
    for i in range(0, 100):
        for j in range(0, 100):
            for k in range(0, 100):
                infile.write(addZero(i))
                infile.write('/')
                infile.write(addZero(j))
                infile.write('/')
                infile.write(addZero(k))
                infile.write('\n')
    infile.close()


def permutations(arr) -> list:
    return [
        (arr[0], arr[1], arr[2]),
        (arr[0], arr[2], arr[1]),
        (arr[1], arr[0], arr[2]),
        (arr[1], arr[2], arr[0]),
        (arr[2], arr[0], arr[1]),
        (arr[2], arr[1], arr[0])
    ]


def main():
    infile = open("pyin.in", "r")
    outfile = open("pyout.out", "w")
    i = 0
    for line in infile:
        dates = list(dict.fromkeys(permutations([int(i) for i in line.split('/')])))
        isn = False
        for date in dates:
            try:
                datetime.datetime(date[2] + 2000, date[1], date[0])
                outfile.write(addZero(date[0]))
                outfile.write('/')
                outfile.write(addZero(date[1]))
                outfile.write('/')
                outfile.write(addZero(date[2]))
                outfile.write('\n')
                isn = True
            except ValueError:
                continue
        if not isn:
            outfile.write("No such date\n")
        outfile.write('\n')
    infile.close()
    outfile.close()


main()
