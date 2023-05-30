from collections import deque


def generate_support_data(n: int, graph: dict[int, list[int]], time_to_do: list[int]):
    used = [False for _ in range(n)]
    counter, result_detail_cnt, result_time = 0, 0, 0
    counters_on_ids = [0 for _ in range(n)]
    stack: deque[tuple[int, int]] = deque()
    stack.append((0, 0))
    while len(stack) != 0:
        now_act = stack.pop()
        counter += 1
        counters_on_ids[now_act[0]] = counter
        if not used[now_act[0]]:
            result_time += time_to_do[now_act[0]]
            result_detail_cnt += 1
        used[now_act[0]] = True
        sons = graph[now_act[0]]
        if now_act[1] >= len(sons):
            continue
        stack.append((now_act[0], now_act[1] + 1))
        next_son_id = sons[now_act[1]]
        if counters_on_ids[next_son_id] == 0:
            stack.append((next_son_id, 0))
    id_on_count: dict[int, int] = dict()
    for i in range(n):
        if counters_on_ids[i] != 0:
            id_on_count[counters_on_ids[i]] = i
    return result_time, result_detail_cnt, id_on_count


def main():
    n = int(input())
    time_to_do = [int(s) for s in input().split(' ')]
    graph: dict[int, list[int]] = {}
    for i in range(n):
        graph[i] = [int(s) - 1 for s in input().split(' ')][1:]
    sup = generate_support_data(n, graph, time_to_do)
    print(sup[0], sup[1])
    print(' '.join([str(i[1] + 1) for i in sorted(sup[2].items())]))


main()
