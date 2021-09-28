# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

def isCorrect(date):
    date = [int(s) for s in date]
    if date[2] > 0:
        date[2] += 2000
    else:
        date[2] += 2100
    if date[1] > 12:
        return False
    if date[1] == 2:
        if (date[2] % 4 == 0 and date[2] % 100 != 0) or date[2] % 400 == 0:
            if date[0] > 29:
                return False
        else:
            if date[0] > 28:
                return False
    elif date[1] == 1 or date[1] == 3 or date[1] == 5 or date[1] == 7 or date[1] == 8 or date[1] == 10 or date[1] == 12:
        if date[0] > 31:
            return False
    else:
        if date[0] > 30:
            return False
    return True


def main():
    fr = open("chronicle.in", "r")
    dates = fr.read().split('/')
    dates = [[dates[0], dates[1], dates[2]], [dates[0], dates[2], dates[1]], [dates[1], dates[0], dates[2]],
             [dates[1], dates[2], dates[0]], [dates[2], dates[1], dates[0]], [dates[2], dates[0], dates[1]]]
    fr.close()
    correct_dates = []
    [correct_dates.append(date) for date in dates if isCorrect(date) and date not in correct_dates]
    fw = open("chronicle.out", "w")
    fw.write("No such date"
             if len(correct_dates) == 0 else
             ''.join(("0" if len(s[0]) == 1 else "") + s[0] + '/' + ("0" if len(s[1]) == 1 else "") + s[1] + '/' + (
                 "0" if len(s[2]) == 1 else "") + s[2] + '\n' for s in correct_dates)[:-1])
    fw.close()


# Press the green button in the gutter to run the script.
main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
