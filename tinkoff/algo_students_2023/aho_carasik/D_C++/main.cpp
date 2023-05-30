#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <bitset>
#include <chrono>
#include <deque>
#include <sstream>
#include <fstream>

#include <random>

//namespace Generate {
//    std::random_device dev;
//    std::mt19937 rng(dev());
//    std::uniform_int_distribution<std::uint32_t> dist_0_30000(0, 30000);
//    std::bernoulli_distribution dist_bool_05(0.5), dist_bool_001(0.01);
//
//    std::string Generate() {
//        std::stringstream now_str_stream;
//        std::uint32_t n = 1;
//        std::uint32_t size = dist_0_30000(rng);
//        for (std::uint32_t i = 0; i < size; ++i) {
//            now_str_stream << dist_bool_05(rng);
//            if (dist_bool_001(rng)) {
//                if (i < size - 1) ++n;
//                now_str_stream << "\n";
//            }
//        }
//        return std::to_string(n) + "\n" + now_str_stream.str();
//    }
//
//    std::string GenerateFee() {
//        std::string result = std::to_string(1) + "\n";
//        for (std::uint16_t i = 0; i < 1875; ++i) {
//            result += std::bitset<16>(i).to_string();
//        }
//        return result + "\n";
//    }
//}

class Node {
public:
    bool pc, is_finish;
    std::map<bool, Node *> go;
    Node *suflink = nullptr, *parent = nullptr;
    char is_suflink_tree_has_finish;
    char color = '0';

    explicit Node(bool pc = false, Node *parent = nullptr, char is_suflink_tree_has_finish = '-',
                  bool is_finish = false)
            : pc(pc), parent(parent), is_suflink_tree_has_finish(is_suflink_tree_has_finish), is_finish(is_finish) {}

    Node(const Node &other) = default;

    Node(Node &&other) noexcept: pc(other.pc), is_finish(other.is_finish), suflink(other.suflink), parent(other.parent),
                                 is_suflink_tree_has_finish(other.is_suflink_tree_has_finish),
                                 go(std::move(other.go)) {}
};

class Nodes {
public:
    Node *root;

    Node *GetSufLink(Node *node) {
        if (node == nullptr) return root;
        if (node->suflink != nullptr) return node->suflink;
        if (node == root || node->parent == root) node->suflink = root;
        else node->suflink = GetGo(GetSufLink(node->parent), node->pc);
        return node->suflink;
    }

    Node *GetGo(Node *node, bool c) {
        if (node == nullptr) return root;
        auto it = node->go.find(c);
        if (it != node->go.end()) return it->second;
        if (node == root) node->go.emplace(c, root);
        else node->go.emplace(c, GetGo(GetSufLink(node), c));
        return node->go[c];
    }

    bool GetIsSuflinkHasFinish(Node *node) {
        if (node == nullptr) return false;
        if (node->is_suflink_tree_has_finish != '-') return node->is_suflink_tree_has_finish == '1';
        auto t_n = node;
        while (t_n != root) {
            if (t_n->is_suflink_tree_has_finish == '1' || t_n->is_finish) {
                node->is_suflink_tree_has_finish = '1';
                return true;
            }
            t_n = GetSufLink(t_n);
        }
        node->is_suflink_tree_has_finish = '0';
        return false;
    }

    explicit Nodes(std::uint64_t n, std::uint64_t &total_size) : root(new Node()) {
        total_size = 0;
        for (std::uint64_t i = 0; i < n; ++i) {
            Node *node = root;
            for (char temp_ch = getchar(); temp_ch != '\n'; temp_ch = getchar()) {
                bool c = temp_ch == '1';
                auto it = node->go.find(c);
                if (it != node->go.end()) node = it->second;
                else {
                    auto new_node = new Node(c, node);
                    node->go.emplace(c, new_node);
                    node = new_node;
                }
                ++total_size;
            }
            node->is_finish = true;
        }
    }
};

bool RecSol(Nodes &nodes, Node *node) {
    if (nodes.GetIsSuflinkHasFinish(node)) return false;
    if (node->color == '1') return true;
    if (node->color == '2') return false;
    node->color = '1';
    if (RecSol(nodes, nodes.GetGo(node, false))) return true;
    if (RecSol(nodes, nodes.GetGo(node, true))) return true;
    node->color = '2';
    return false;
}

bool GetResultWithThisInput() {
    auto start_time = std::chrono::steady_clock::now();
    std::string str_N;
    str_N.reserve(10);
    char temp_ch = getchar();
    do {
        str_N += temp_ch;
        temp_ch = getchar();
    } while (temp_ch != '\n');
    std::uint64_t N = std::stoi(str_N);
    std::uint64_t total_size = 0;
    Nodes nodes(N, total_size);
    return RecSol(nodes, nodes.root);
//    std::unordered_set<Node *> visited;
//    std::vector<std::pair<Node *, char>> stack(total_size + 1);
//    std::vector<std::uint32_t> count_visited(total_size + 1, 0);
//    std::uint64_t now_depth = 1;
//    stack[now_depth - 1] = {nodes.root, '0'};
//    while (now_depth > 0) {
//        auto &act = stack[now_depth - 1];
//        nodes.GetSufLink(act.first);
//        nodes.GetGo(act.first, false);
//        nodes.GetGo(act.first, true);
//        if (act.second == '0') {
//            if (act.first->color == '1') return true;
////            if (visited.find(act.first) != visited.end()) return true;
////            visited.insert(act.first);
//            act.first->color = '1';
//            if (!nodes.GetIsSuflinkHasFinish(act.first))
//                stack[now_depth++] = {nodes.GetGo(act.first, false), '0'};
//            act.second = '1';
//        } else if (act.second == '1') {
//            if (!nodes.GetIsSuflinkHasFinish(act.first))
//                stack[now_depth++] = {nodes.GetGo(act.first, true), '0'};
//            act.second = '2';
//        } else {
//            act.first->color = '2';
////            visited.erase(act.first);
//            --now_depth;
//        }
//    }
    return false;
}

int main() {
//    std::ofstream in("input.txt");
//    in << Generate::GenerateFee();
    auto res = GetResultWithThisInput();
    if (res) std::cout << "TAK";
    else std::cout << "NIE";
    return 0;
}