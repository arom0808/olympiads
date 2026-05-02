n, k, a, m, t = [int(input()) for _ in range(5)]
flag=False
for i in range(n,0,-1):
    if (t-m-i*a>=0):
        flag=True
        break
    t-=(m*k)
if (flag):
    print("Yes")
else:
    print("No")