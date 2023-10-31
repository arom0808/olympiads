f = 1
for i in range(1, 100):
    print(i, str(f).rstrip('0')[-1])
    f *= i
