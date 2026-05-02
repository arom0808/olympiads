from random import randint

n = randint(1, 5)
print(n)

print(" ".join([str(randint(1, 10)) for _ in range(n)]))

print("\n".join([str(randint(i + 1, n - 1) + 1) + " " + str(i + 1) for i in range(n - 1)]))
k = randint(1, 4)
print(k)
for _ in range(k):
    if randint(0, 1):
        print("! " + str(randint(1, n)) + " " + str(randint(1, 10)))
    else:
        print("? " + str(randint(1, n)) + " " + str(randint(1, n)))
