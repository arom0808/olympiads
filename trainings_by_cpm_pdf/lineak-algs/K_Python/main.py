from collections import deque

[N, K] = [int(i) for i in input().split(' ')]
nums = [int(i) for i in input().split(' ')]
com = deque(maxlen=K)
for i in range(len(nums)):
    if i >= K and len(com) > 0 and com[0] == i - K:
        com.popleft()
    while len(com) > 0 and nums[com[-1]] >= nums[i]:
        com.pop()
    com.append(i)
    if i >= K - 1:
        print(nums[com[0]])
