n = int(input())
l = 2
r = 3
temp = 1
while (not (l <= n <= r)):
    if (temp == 1):
        l = r + 1
        r = l * 2 - 1
        temp = 2
    else:
        temp = 1
        l = r + 1
        r = (l - 1) * 3
if temp == 1:
    print("Yvonne")
else:
    print("Zara")
