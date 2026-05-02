from sys import stdin, stdout

n, k, p = 0, 0, 0
a, c = [], []
ps = []


def main():
    global n, k, p, a, c, ps
    n, k, p = map(int, stdin.readline().rstrip('\n').split())
    a = list(map(int, stdin.readline().rstrip('\n').split()))
    c = list(map(int, stdin.readline().rstrip('\n').split()))
    ps = [(a[i], c[i]) for i in range(n)]
    ps.sort(key=lambda x: x[0])
    clp = 0
    for i in range(n):
        if a[i] <= p:
            clp += c[i]
    sac = sum(c)
    t = min(clp, sac // (k + 1))
    ans = 0
    for i in range(n):
        ans += c[i] * a[i]
    li = 0
    for i in range(n):
        if ps[i][0] <= p:
            li = i
    for i in range(li, -1, -1):
        ans -= ps[i][0] * min(t, ps[i][1])
        t -= min(t, ps[i][1])
        if t == 0:
            break
    stdout.write(str(ans) + "\n")


main()
