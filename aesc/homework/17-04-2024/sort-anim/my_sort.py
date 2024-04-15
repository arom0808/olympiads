


def insert_sort(arr):
    for i in range(1, len(arr)):
        l, r = 0, i #0
        while l != r: #1
            m = (l + r) #2
            if arr[m] < arr[i]:
                l = m + 1
            elif arr[m] > arr[i]:
                r = m
            else:
                l = r = m
        for j in range(i, l, -1): #2
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
