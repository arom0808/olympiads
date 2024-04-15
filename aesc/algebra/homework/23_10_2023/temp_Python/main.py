a = 1000
x_1, x_2 = a / 4, a / 2
x = (x_1 + x_2) / 2
for i in range(1000):
    print(x)
    x, x_1, x_2 = (x + x_1) / 2, x, x_1
 /