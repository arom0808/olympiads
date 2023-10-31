#include <iostream>
#include <vector>
#include <set>
#include <map>

class GraphNode {
public:
    std::uint32_t id = 0;
    std::set<GraphNode *> conn;
};

class TreeNode {
public:
    std::uint32_t id = 0, level = 0;
    TreeNode *parent = nullptr;
    std::set<TreeNode *> childs;
    std::map<std::uint32_t, TreeNode *> pre_mega_parents;
    TreeNode *mega_parent = nullptr;
};

const std::uint32_t save_level = 100;

void make_tree_node(std::vector<GraphNode> &graph, std::vector<TreeNode> &tree, std::uint32_t id,
                    std::uint32_t level = 0, TreeNode *parent = nullptr, TreeNode *mega_parent = nullptr) {
    auto graph_node = &graph[id];
    auto tree_node = &tree[id];
    tree_node->id = graph_node->id;
    tree_node->level = level;
    tree_node->parent = parent;
    tree_node->mega_parent = mega_parent;
    for (auto gr_ch: graph_node->conn) {
        gr_ch->conn.erase(graph_node);
        make_tree_node(graph, tree, gr_ch->id, level + 1, tree_node,
                       (level % save_level == 0 ? tree_node : mega_parent));
        tree_node->childs.emplace(&tree[gr_ch->id]);
    }
    if (level % save_level == 0 && level != 0) {
        auto parent_node = tree_node->parent;
        for (; parent_node->level % save_level != 0; parent_node = parent_node->parent)
            tree_node->pre_mega_parents.emplace(parent_node->level, parent_node);
        tree_node->pre_mega_parents.emplace(parent_node->level, parent_node);
    }
}

std::uint32_t nearest_node_on_way(std::vector<TreeNode> &tree, std::uint32_t s, std::uint32_t t) {
    auto start_node = &tree[s], target_node = &tree[t];
    if (target_node->level <= start_node->level) return start_node->parent->id;
    auto parent_node = target_node;
    for (; parent_node->parent->level % save_level != 0; parent_node = parent_node->parent)
        if (parent_node->parent == start_node) return parent_node->id;
    if (parent_node->parent == start_node) return parent_node->id;
    parent_node = parent_node->parent;
    if (parent_node->parent != nullptr && parent_node->parent == start_node) return parent_node->id;
    if (parent_node->level <= start_node->level) return start_node->parent->id;
    while (parent_node->pre_mega_parents.begin()->first > start_node->level)
        parent_node = parent_node->mega_parent;
    if (parent_node->pre_mega_parents[start_node->level] == start_node) {
        if (parent_node->level - start_node->level > 1)
            return parent_node->pre_mega_parents[start_node->level + 1]->id;
        else return parent_node->id;
    }
    return start_node->parent->id;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<GraphNode> graph(n);
    for (std::uint32_t i = 0; i < n; ++i) graph[i].id = i;
    for (std::uint32_t i = 0, a, b; i < n - 1; ++i) {
        std::cin >> a >> b;
        graph[--a].conn.emplace(&graph[--b]);
        graph[b].conn.emplace(&graph[a]);
    }
    std::vector<TreeNode> tree(n);
    make_tree_node(graph, tree, 0);
    std::uint32_t m;
    std::cin >> m;
    for (std::uint32_t i = 0, s, t; i < m; ++i) {
        std::cin >> s >> t;
        std::cout << nearest_node_on_way(tree, s - 1, t - 1) + 1 << "\n";
    }
    return 0;
}