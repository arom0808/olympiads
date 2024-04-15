l = 15
r = 87
k = 0b0101

print('l:', bin(l)[2:])
print('r:', bin(r)[2:])
print('k:', bin(k)[2:])

for i in range(l, r):
    a = bin(i ^ k)[2:]
    print('0' * (7 - len(a)) + a, ':', i ^ k)
