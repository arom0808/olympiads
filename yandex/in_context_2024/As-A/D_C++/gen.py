from random import randint

n, x = randint(int(1), int(1000)), randint(int(0), int(1e7))
print(n, x)
print(" ".join([str(randint(0, int(1e7))) for _ in range(n)]))
print(" ".join([str(randint(0, int(1e5))) for _ in range(n)]))
