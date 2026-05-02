from random import randint, choice, shuffle
from string import ascii_lowercase

n = randint(2, 7)
k = randint(2, min(n, 5))

o_f = open("input.txt", "w")
o_f.write(str(n) + " " + str(k) + "\n")
s = ''.join(choice(ascii_lowercase[:5]) for i in range(n))
arr = [s[i:i + k] for i in range(n - k + 1)]
shuffle(arr)
o_f.write("\n".join(arr))
o_f.write("\n")
o_f.write(s)