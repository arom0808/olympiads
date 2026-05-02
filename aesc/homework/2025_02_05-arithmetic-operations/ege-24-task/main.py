def main():
    f = open("input.txt", "r")
    k = int(f.readline().rstrip("\n"))
    n = int(f.readline().rstrip("\n"))
    arr = [int(x.rstrip("\n")) for x in f.readlines()]
    r = 0
    ans = 0
    for i in range(n):
        while r != n and arr[r] - arr[i] <= k:
            r += 1
        ans += n - r
    print(ans * 2)


main()
