from collections import deque


def UpdateMinMax(min_i: int, min_j: int, max_i: int, max_j: int, new_min_max_ij: ((int, int), (int, int))):
    min_i = min(min_i, new_min_max_ij[0][0])
    min_j = min(min_j, new_min_max_ij[0][1])
    max_i = max(max_i, new_min_max_ij[1][0])
    max_j = max(max_j, new_min_max_ij[1][1])
    return min_i, min_j, max_i, max_j


def GetMinIJAndMaxIJ(main_table: [[bool]], is_visited_table: [[bool]], i: int, j: int, min_i: int, min_j: int,
                     max_i: int, max_j: int):
    visit_queue = deque()
    visit_queue.append((i, j))
    while len(visit_queue) > 0:
        i, j = visit_queue.popleft()
        if is_visited_table[i][j]:
            continue
        is_visited_table[i][j] = True
        min_i, min_j, max_i, max_j = UpdateMinMax(min_i, min_j, max_i, max_j, ((i, j), (i, j)))
        if i > 0:
            if main_table[i - 1][j] and (not is_visited_table[i - 1][j]):
                visit_queue.append((i - 1, j))
        if i > 0 and j < len(main_table[i]) - 1:
            if main_table[i - 1][j + 1] and (not is_visited_table[i - 1][j + 1]):
                visit_queue.append((i - 1, j + 1))
        if j < len(main_table[i]) - 1:
            if main_table[i][j + 1] and (not is_visited_table[i][j + 1]):
                visit_queue.append((i, j + 1))
        if i < len(main_table) - 1 and j < len(main_table[i]) - 1:
            if main_table[i + 1][j + 1] and (not is_visited_table[i + 1][j + 1]):
                visit_queue.append((i + 1, j + 1))
        if i < len(main_table) - 1:
            if main_table[i + 1][j] and (not is_visited_table[i + 1][j]):
                visit_queue.append((i + 1, j))
        if i < len(main_table) - 1 and j > 0:
            if main_table[i + 1][j - 1] and (not is_visited_table[i + 1][j - 1]):
                visit_queue.append((i + 1, j - 1))
        if j > 0:
            if main_table[i][j - 1] and (not is_visited_table[i][j - 1]):
                visit_queue.append((i, j - 1))
        if i > 0 and j > 0:
            if main_table[i - 1][j - 1] and (not is_visited_table[i - 1][j - 1]):
                visit_queue.append((i - 1, j - 1))
    return (min_i, min_j), (max_i, max_j)


def FertileCount(min_i: int, min_j: int, max_i: int, max_j: int, main_table: [[bool]]):
    count = 0
    for i in range(min_i, max_i + 1):
        for j in range(min_j, max_j + 1):
            if main_table[i][j]:
                count += 1
    return count


def EfficiencyToNumbers(eff_0: (int, int), eff_1: (int, int)):
    return eff_0[0] * eff_1[1], eff_1[0] * eff_0[1]


def main():
    [n, m] = [int(num) for num in input().split(' ')]
    main_table = [[False if b == '0' else True for b in input().split(' ') if b == '1' or b == '0'] for i in range(m)]
    is_visited_table = [[False for i in range(n)] for i in range(m)]
    max_efficiency = (0, 1)
    max_square = 0
    for i in range(m):
        for j in range(n):
            if main_table[i][j] and (not is_visited_table[i][j]):
                min_i, min_j, max_i, max_j = UpdateMinMax(1000, 1000, 0, 0,
                                                          GetMinIJAndMaxIJ(main_table, is_visited_table, i, j,
                                                                           1000, 1000, 0, 0))
                square = (max_i - min_i + 1) * (max_j - min_j + 1)
                fertile_count = FertileCount(min_i, min_j, max_i, max_j, main_table)
                if fertile_count < 2:
                    continue
                eff_in_nums = EfficiencyToNumbers((fertile_count, square), max_efficiency)
                if eff_in_nums[0] > eff_in_nums[1]:
                    max_efficiency = (fertile_count, square)
                    max_square = square
                elif eff_in_nums[0] == eff_in_nums[1] and square > max_square:
                    max_square = square
    print(max_square)


main()
