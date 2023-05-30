from collections import deque


def add_way_to_graph(graph: dict[int, list[int]], a: int, b: int):
    if a in graph:
        graph[a].append(b)
    else:
        graph[a] = [b]


def in_first_dfs(graph: dict[int, list[int]], counters_on_ids: list[int], counter: int, start_id: int) -> int:
    stack: deque[tuple[int, int]] = deque([(start_id, 0)])
    while len(stack) != 0:
        now_act = stack.pop()
        counter += 1
        counters_on_ids[now_act[0]] = counter
        sons = graph[now_act[0]]
        if now_act[1] >= len(sons):
            continue
        stack.append((now_act[0], now_act[1] + 1))
        next_son_id = sons[now_act[1]]
        if counters_on_ids[next_son_id] == 0:
            stack.append((next_son_id, 0))
    return counter


def first_dfs(n: int, graph: dict[int, list[int]]) -> dict[int, int]:
    counters_on_ids = [0] * n
    counter = 0
    for i in range(n):
        if counters_on_ids[i] == 0:
            counter = in_first_dfs(graph, counters_on_ids, counter, i) + 1
    ids_on_counters: dict[int, int] = {}
    for i in range(n):
        ids_on_counters[counters_on_ids[i]] = i
    return ids_on_counters


def in_second_dfs(n: int, now_comp: int, reversed_graph: dict[int, list[int]], comp_on_id: list[int], start_id: int):
    stack: deque[tuple[int, int]] = deque([(start_id, 0)])
    while len(stack) != 0:
        now_act = stack.pop()
        comp_on_id[now_act[0]] = now_comp
        sons = reversed_graph[now_act[0]]
        if now_act[1] >= len(sons):
            continue
        stack.append((now_act[0], now_act[1] + 1))
        next_son_id = sons[now_act[1]]
        if comp_on_id[next_son_id] == n + 1:
            stack.append((next_son_id, 0))


def second_dfs(n: int, reversed_graph: dict[int, list[int]], ids_on_counters: dict[int, int]) -> tuple[int, list[int]]:
    now_comp = 0
    comp_on_id = [n + 1] * n
    for it in sorted(ids_on_counters.items(), reverse=True):
        if comp_on_id[it[1]] == n + 1:
            in_second_dfs(n, now_comp, reversed_graph, comp_on_id, it[1])
            now_comp += 1
    return now_comp, comp_on_id


def get_reversed_graph(n: int, graph: dict[int, list[int]]) -> dict[int, list[int]]:
    reversed_graph: dict[int, list[int]] = {}
    for i in graph.items():
        for j in i[1]:
            add_way_to_graph(reversed_graph, j, i[0])
    for i in range(n):
        if not (i in reversed_graph):
            reversed_graph[i] = []
    return reversed_graph


def get_condensed_graph(n: int, graph: dict[int, list[int]]) -> tuple[int, dict[int, list[int]], list[int]]:
    ids_on_counters = first_dfs(n, graph)
    reversed_graph = get_reversed_graph(n, graph)
    comps_count, comp_on_id = second_dfs(n, reversed_graph, ids_on_counters)
    condensed_graph: dict[int, list[int]] = {}
    for i in range(n):
        for linked_id in graph[i]:
            if comp_on_id[i] != comp_on_id[linked_id]:
                add_way_to_graph(condensed_graph, comp_on_id[i], comp_on_id[linked_id])
    for i in range(n):
        if not (i in condensed_graph):
            condensed_graph[i] = []
    return comps_count, condensed_graph, comp_on_id


def main():
    [n, m] = [int(s) for s in input().split(' ')]
    graph: dict[int, list[int]] = dict()
    for i in range(m):
        add_way_to_graph(graph, *[int(s) - 1 for s in input().split(' ')])
    for i in range(n):
        if not (i in graph):
            graph[i] = []
    comps_count, condensed_graph, comp_on_id = get_condensed_graph(n, graph)
    c_ids_on_counters = first_dfs(comps_count, condensed_graph)
    t_c = 0
    d_s = {}
    for it in sorted(c_ids_on_counters.items(), reverse=True):
        d_s[it[1]] = t_c
        t_c += 1
    print(comps_count)
    print(' '.join([str(d_s[comp_on_id[i]] + 1) for i in range(n)]))


main()
