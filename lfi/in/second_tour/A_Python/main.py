first, second = int(round(float(input()) * 2)), int(round(float(input()) * 2))
nobody_count = 0
while first > 0 and second > 0:
    nobody_count += 1
    first -= 1
    second -= 1

matches_count = nobody_count + (max(first, second) // 2)
print(matches_count)
if nobody_count % 2 != 0:
    print(1)
else:
    print(0)
print(nobody_count)
