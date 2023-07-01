#!/usr/bin/python3

running = "r\n"
over = "o\n"

import subprocess
import os
import sys

n = 0
m = 0
k = 0

a = []

log = open("log.txt", "w")
moves = open("steps.txt", "w")

lastmove = ""

def Terminate():
    global prog1
    global prog2
    global validator
    global log
    log.write("-1 -1 -1\n")
    print("sending over information to programs")
    prog1.stdin.write(bytes(over, "utf-8"))
    prog1.stdin.flush()
    prog2.stdin.write(bytes(over, "utf-8"))
    prog2.stdin.flush()
    print("Terminating...")
    prog1.terminate()
    prog2.terminate()
    validator.terminate()
    print("Terminated, exiting")
    exit(0)

def validate(validator: subprocess.Popen[bytes], steps: list, curplayer: int):
    print("Player", curplayer, "is making turn:", steps, file=moves)
    if (len(steps) < 2):
        print("Player", curplayer, "gave an array of wrong length")
        Terminate()
    playerid = steps[0]
    if (playerid != curplayer):
        print("Player", curplayer, "gave incorrect player number")
        Terminate()
    steps = steps[1:]
    clen = steps[0]
    if (clen < 0 or clen > 3):
        print("Player", curplayer, "gave incorrect length of sequence")
        Terminate()
    steps = steps[1:]
    if (len(steps) != clen * 2):
        print("Player", curplayer, "gave different array length num and array length")
        Terminate()
    validInp = str(curplayer) + " " + str(clen)
    for el in steps:
        validInp += " " + str(el)
    validInp += "\n"
    validator.stdin.write(bytes(validInp, "utf-8"))
    validator.stdin.flush()
    validOut = validator.stdout.readline().decode("utf-8")
    validOut = list(map(int, validOut.strip().split()))
    if (validOut[0] == -1):
        print("Number of players' own cells are equal. Pleare rerun on different test.")
        if (len(validOut) >= 2):
            if validOut[1] == 0 and len(validOut) >= 5:
                print("Additional info: scores of player1, player2, and number of neutral cells:", validOut[2], validOut[3], validOut[4])
        Terminate()
    if (validOut[0] == 1 or validOut[0] == 2):
        print("After move of", curplayer, "the game was terminated. Player", validOut[0], "won")
        if (len(validOut) >= 2):
            if (validOut[1] == 0):
                print("Additional info: all moves were correct, but number of cells differ")
                if (len(validOut) >= 2):
                    if validOut[1] == 0 and len(validOut) >= 5:
                        print("Additional info: scores of player1, player2, and number of neutral cells:", validOut[2], validOut[3], validOut[4])

            elif (validOut[1] == 1):
                print("Additional info: the last move of player", 3 - validOut[0], "was invalid")
        Terminate()

def initInteract():
    global n, m, k, lastmove, a
    prefix = os.getcwd() + '/'

    argv = sys.argv
    argv = argv[1:]
    if (len(argv) < 4):
        argv.append("help")
    if ("help" in argv or "--help" in argv or "-help" in argv or "-h" in argv):
        print("interactor.py sol_1 sol_2 validate input\n\n\
Provide relative path to solutions binary files as first and second arguments,\n\
relative path to validator binary as third argument,\n\
relative path to the text file with input as the fourth argument.\n")
        exit(0)

    prog1 = prefix + argv[0]
    prog2 = prefix + argv[1]
    interactor = prefix + argv[2]
    inputfile = prefix + argv[3]

    proc1 = subprocess.Popen([prog1], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc2 = subprocess.Popen([prog2], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    validator = subprocess.Popen([interactor], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    with open(inputfile) as f:
        n, m, k = map(int, f.readline().split())
        a = [[] for _ in range(n)]
        for i in range(n):
            crow = f.readline()
            a[i] = list(map(int, crow.split()))
    

    log.write(str(n) + " " + str(m) + "\n")
    for i in range(n):
        for j in range(m):
            log.write(str(a[i][j]) + " \n"[j == m - 1])
    
    cstr = str(n) + " " + str(m) + " " + str(k) + " 1\n"
    valstr = str(n) + " " + str(m) + " " + str(k) + "\n"
    for i in range(n):
        for j in range(m):
            cstr += str(a[i][j]) + " \n"[j == m - 1]
            valstr += str(a[i][j]) + " \n"[j == m - 1]
    proc1.stdin.write(bytes(cstr, "utf-8"))
    proc1.stdin.flush()
    firstOut = proc1.stdout.readline().decode("utf-8")
    validator.stdin.write(bytes(valstr, "utf-8"))
    validator.stdin.flush()
    lastmove = firstOut
    try:
        firstOut = list(map(int, firstOut.strip().split()))
    except ValueError:
        print("The first solution output format is incorrect")
        Terminate()

    validate(validator, firstOut.copy(), 1)
    firstOut = firstOut[2:]
    for i in range(0, len(firstOut), 2):
        x = firstOut[i]
        y = firstOut[i + 1]
        x -= 1
        y -= 1
        if (a[x][y] == 2):
            a[x][y] = -1
            print("Player 1 moved to the cell of player 2 by first move. The game is finishing")
            Terminate()
        else:
            a[x][y] = 1
        log.write(str(x) + " " + str(y) + " " + str(a[x][y]) + "\n")
    
    cstr = str(n) + " " + str(m) + " " + str(k) + " 2\n"
    for i in range(n):
        for j in range(m):
            cstr += str(a[i][j]) + " \n"[j == m - 1]
    proc2.stdin.write(bytes(cstr, "utf-8"))
    proc2.stdin.flush()
    secondOut = proc2.stdout.readline().decode("utf-8")
    lastmove = secondOut
    try:
        secondOut = list(map(int, secondOut.strip().split()))
    except ValueError:
        print("The second solution output format is incorrect")
        Terminate()
    validate(validator, secondOut.copy(), 2)
    secondOut = secondOut[2:]
    for i in range(0, len(secondOut), 2):
        x = secondOut[i]
        y = secondOut[i + 1]
        x -= 1
        y -= 1
        if (a[x][y] == 0):
            a[x][y] = 2
        else:
            a[x][y] = -2
        log.write(str(x) + " " + str(y) + " " + str(a[x][y]) + "\n")
    
    return (proc1, proc2, validator)

def movep(prog: subprocess.Popen[bytes], validator: subprocess.Popen[bytes], cnum: int):
    global lastmove
    prog.stdin.write(bytes(running + lastmove, "utf-8"))
    prog.stdin.flush()
    cmove = prog.stdout.readline().decode("utf-8")
    lastmove = cmove
    try:
        cmove = list(map(int, cmove.strip().split()))
    except ValueError:
        print("The first solution output format is incorrect")
        Terminate()

    validate(validator, cmove.copy(), cnum)

    cmove = cmove[2:]
    for i in range(0, len(cmove), 2):
        x = cmove[i]
        y = cmove[i + 1]
        x -= 1
        y -= 1
        if (a[x][y] == 0):
            a[x][y] = cnum
        else:
            a[x][y] = -cnum
        log.write(str(x) + " " + str(y) + " " + str(a[x][y]) + "\n")

prog1, prog2, validator = initInteract()

curp = 1
cntmoves = 0
while True:
    movep(prog1, validator, curp)
    curp += 1
    movep(prog2, validator, curp)
    curp -= 1
    cntmoves += 1
