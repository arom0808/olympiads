[k, T] = [int(x) for x in input().split(' ')]
[a, b] = list(zip(*[[int(x) for x in input().split(' ')] for _ in range(k)]))

f = [[0] * k for _ in range(T)]

for i in range(T):
    for j in range(k):
        f[i][j] = f[i][j - 1]
        if i >= a[j - 1] and f[i - a[j - 1]][j - 1] + 1 > f[i][j]:
            f[i][j] = f[i - a[j - 1]][j - 1] + 1

print(f)

# print("Список задач, которые следует решить:", tasks)
# print("Максимальное количество баллов:", f[T][k])
