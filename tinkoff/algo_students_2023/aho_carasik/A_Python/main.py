class Node:
    def __init__(self):
        self.pc = '\0'
        self.parent = None
        self.suf_link = None
        self.go = dict()
        self.terminal = False


def BuildBOR(s) -> Node:
    nodes = [Node() for _ in range(len(s) + 1)]
    for i in range(1, len(s) + 1):
        nodes[i - 1].go[s[i - 1]] = nodes[i]
        nodes[i].parent = nodes[i - 1]
        nodes[i].pc = s[i - 1]
    nodes[len(s)].terminal = True
    return nodes[0]


def GetSufLink(root, node):
    if (root is None) or (node is None):
        return None
    if node.suf_link is not None:
        return node.suf_link
    if node == root or node.parent == root:
        node.suf_link = root
    else:
        node.suf_link = GetGo(root, GetSufLink(root, node.parent), node.pc)
    return node.suf_link


def GetGo(root, node, c):
    if (root is None) or (node is None):
        return None
    if c in node.go:
        return node.go[c]
    if node == root:
        node.go[c] = root
    else:
        node.go[c] = GetGo(root, GetSufLink(root, node), c)
    return node.go[c]


def GetAllEquals(root, s, res):
    node = root
    for i in range(0, len(s)):
        node = GetGo(root, node, s[i])
        v = node
        while v != root:
            if v.terminal:
                res.add(i)
            v = GetSufLink(root, v)


def main():
    S, T = input(), input()
    root = BuildBOR(T)
    results = set()
    GetAllEquals(root, S, results)
    if len(results) > 0:
        print(" ".join([str(j) for j in sorted([i + 1 - len(T) for i in results])]), end='')


main()
