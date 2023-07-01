#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <list>
#include <set>

struct Node {
    Node *parent = nullptr;
    std::set<Node *> childs;
    std::int64_t level = 0;
    std::list<Node *>::iterator pos;

    void DeleteThis() {
        for (auto child: childs) {
            child->parent = parent;
            child->level = level;
        }
        if (parent != nullptr) {
            parent->childs.erase(this);
            parent->childs.merge(this->childs);
        }
    }
};

int main() {
    std::int64_t n, k;
    std::cin >> n >> k;
    std::vector<Node *> vec_nodes(n);
    for (auto &node: vec_nodes) node = new Node();
    for (std::int64_t i = 1, temp; i < n; ++i) {
        std::cin >> temp;
        vec_nodes[i]->parent = vec_nodes[temp - 1];
        vec_nodes[temp - 1]->childs.emplace(vec_nodes[i]);
        vec_nodes[i]->level = vec_nodes[temp - 1]->level + 1;
    }
    std::list<Node *> nodes(vec_nodes.begin(), vec_nodes.end());
    for (auto it = nodes.begin(); it != nodes.end(); ++it) (*it)->pos = it;
    std::int64_t installed = 0, deleted = 0;
    while (installed < k) {
        auto to_del = nodes.end();
        std::int64_t max_level = std::numeric_limits<std::int64_t>::min();
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->level > max_level) {
                to_del = it;
                max_level = (*it)->level;
            }
        }
        if (to_del == nodes.end()) break;
        while (to_del != nodes.end()) {
            auto parent = (*to_del)->parent;
            (*to_del)->DeleteThis();
            nodes.erase(to_del);
            ++deleted;
            if (parent != nullptr) to_del = parent->pos;
            else to_del = nodes.end();
        }
        ++installed;
    }
    std::cout << deleted;
    return 0;
}
