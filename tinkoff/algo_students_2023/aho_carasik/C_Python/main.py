# import random
from sys import stdin, stdout
from typing import TextIO, Optional


class Node:
    def __init__(self, point_value: int, go: dict[str, 'Node'], parent: Optional['Node']):
        self.point_value: int = point_value
        self.go: dict[str, 'Node'] = go
        self.parent: Optional['Node'] = parent


class Nodes:
    def __init__(self, n: int, in_stream: TextIO):
        self.root = Node(0, dict(), None)
        for i in range(0, n):
            node = self.root
            node.point_value += 1
            for c in in_stream.readline().rstrip('\n'):
                if c in node.go:
                    node.go[c].point_value += 1
                else:
                    node.go[c] = Node(1, dict(), node)
                node = node.go[c]


class NewSolution:
    def __init__(self, k: int, m: int, a: list[int], nodes: Nodes):
        self.k: int = k
        self.qe: list[str] = ['0'] * m
        self.now_res: list[str] = ['0'] * m
        self.a: list[int] = a
        self.nodes: Nodes = nodes
        self.now_min_sum: int = 99999999999999999999999
        self.now_sum: int = 0
        self.cur_node: Node = nodes.root
        self.symbols = [chr(i) for i in range(ord('0'), ord('0') + k)]

    def RecursionSolution(self, cur_i=0):
        if self.now_sum >= self.now_min_sum:
            return
        if cur_i == 0:
            self.now_sum, self.cur_node = 0, self.nodes.root
        if cur_i < len(self.qe):
            for self.qe[cur_i] in self.symbols:
                if self.qe[cur_i] in self.cur_node.go:
                    next_node = self.cur_node.go[self.qe[cur_i]]
                    self.now_sum += (self.cur_node.point_value - next_node.point_value) * self.a[cur_i]
                    self.cur_node = next_node
                    if cur_i == len(self.qe) - 1:
                        self.now_sum += self.cur_node.point_value * self.a[cur_i + 1]
                    self.RecursionSolution(cur_i + 1)
                    if cur_i == len(self.qe) - 1:
                        self.now_sum -= self.cur_node.point_value * self.a[cur_i + 1]
                    self.cur_node = self.cur_node.parent
                    self.now_sum -= (self.cur_node.point_value - next_node.point_value) * self.a[cur_i]
                else:
                    self.now_sum += self.cur_node.point_value * self.a[cur_i]
                    for s in range(cur_i + 1, len(self.qe)):
                        self.qe[s] = '0'
                    self.RecursionSolution(len(self.qe))
                    self.now_sum -= self.cur_node.point_value * self.a[cur_i]
        else:
            if self.now_sum < self.now_min_sum or (self.now_sum == self.now_min_sum and self.qe < self.now_res):
                self.now_res = self.qe[:]
                self.now_min_sum = self.now_sum

    def GetResult(self) -> tuple[int, str]:
        return self.now_min_sum, ''.join(self.now_res)


# def GenerateRandom(out_stream: TextIO):
#     n, m, k = random.randint(100_000, 100_000), random.randint(10, 10), random.randint(10, 10)
#     symbol_variants = [chr(s) for s in range(ord('0'), ord('0') + k)]
#     a = [random.randint(1_000_000, 1_000_000) for _ in range(m)]
#     bids = [''.join([random.choice(symbol_variants) for __ in range(m)]) for _ in range(n)]
#     out_stream.write(str(n) + " " + str(m) + " " + str(k) + "\n")
#     out_stream.write(' '.join([str(s) for s in a]) + '\n')
#     for bid in bids:
#         out_stream.write(bid + '\n')


def solute_for_this_input(in_stream: TextIO):
    [n, m, k] = [int(s) for s in in_stream.readline().rstrip('\n').split(' ')]
    a = [0] + [int(s) for s in in_stream.readline().rstrip('\n').split(' ')]
    nodes = Nodes(n, in_stream)
    new_solution = NewSolution(k, m, a, nodes)
    new_solution.RecursionSolution()
    return new_solution.GetResult()


def main():
    results = solute_for_this_input(stdin)
    print(results[1])
    print(results[0])
    # while True:
    #     with open('input.txt', 'w') as wr_in:
    #         GenerateRandom(wr_in)
    #     with open('input.txt', 'r') as read_in:
    #         results = solute_for_this_input(read_in)
    #         stdout.write(results[1])
    #         stdout.write('\n')
    #         stdout.write(str(results[0]))
    #         stdout.write('\n')


main()
