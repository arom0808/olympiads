import random

arr = [random.randint(0, 10) for _ in range(10)]
results = []
print(len(arr))
print(" ".join(map(str, arr)))
ops = random.randint(5, 20)
print(ops)
for i in range(ops):
    l = random.randint(1, len(arr))
    r = random.randint(l, len(arr))
    if random.randint(0, 1):
        print(f"m {l} {r}")
        results.append(max(arr[l - 1:r]))
    else:
        add = random.randint(0, 100)
        print(f"a {l} {r} {add}")
        for j in range(l - 1, r):
            arr[j] += add

print()
print("\n".join(map(str, results)))
