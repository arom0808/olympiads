import sys


class Node:
    def __init__(self, pc=False, parent=None, is_suflink_tree_has_finish='-', is_finish=False):
        self.pc, self.parent, self.is_suflink_tree_has_finish, self.is_finish = pc, parent, is_suflink_tree_has_finish, is_finish
        self.go = dict()
        self.suflink = None
        self.color = '0'


class Nodes:
    def __init__(self, n):
        self.root = Node()
        self.total_size = 0
        for i in range(n):
            node = self.root
            for temp_ch in sys.stdin.readline().rstrip('\n'):
                c = temp_ch == '1'
                if c in node.go:
                    node = node.go[c]
                else:
                    new_node = Node(c, node)
                    node.go[c] = new_node
                    node = new_node
                self.total_size += 1
            node.is_finish = True

    def GetSuflink(self, node):
        if node is None:
            return self.root
        if node.suflink is not None:
            return node.suflink
        if node == self.root or node.parent == self.root:
            node.suflink = self.root
        else:
            node.suflink = self.GetGo(self.GetSuflink(node.parent), node.pc)
        return node.suflink

    def GetGo(self, node, c):
        if node is None:
            return self.root
        if c in node.go:
            return node.go[c]
        if node == self.root:
            node.go[c] = self.root
        else:
            node.go[c] = self.GetGo(self.GetSuflink(node), c)
        return node.go[c]

    def GetIsSuflinkHasFinish(self, node):
        if node is None:
            return False
        if node.is_suflink_tree_has_finish != '-':
            return node.is_suflink_tree_has_finish == '1'
        t_n = node
        while t_n != self.root:
            if t_n.is_suflink_tree_has_finish == '1' or t_n.is_finish:
                node.is_suflink_tree_has_finish = '1'
                return True
            t_n = self.GetSuflink(t_n)
        node.is_suflink_tree_has_finish = '0'
        return False


class StackEl:
    def __init__(self, node, c):
        self.node, self.c = node, c


def GetResult():
    nodes = Nodes(int(sys.stdin.readline().rstrip('\n')))
    stack = [StackEl(nodes.root, '0') for _ in range(nodes.total_size + 1)]
    now_depth = 1
    while now_depth > 0:
        act = stack[now_depth - 1]
        if act.c == '0':
            if act.node.color == '1':
                return True
            act.node.color = '1'
            if not nodes.GetIsSuflinkHasFinish(act.node):
                stack[now_depth].node = nodes.GetGo(act.node, False)
                stack[now_depth].c = '0'
                now_depth += 1
            act.c = '1'
        elif act.c == '1':
            if not nodes.GetIsSuflinkHasFinish(act.node):
                stack[now_depth].node = nodes.GetGo(act.node, True)
                stack[now_depth].c = '0'
                now_depth += 1
            act.c = '2'
        else:
            act.node.color = '2'
            now_depth -= 1
    return False


def main():
    res = GetResult()
    if res:
        print("TAK")
    else:
        print("NIE")


main()
