#include <iostream>
#include <algorithm>
#include <functional>
#include <random>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

std::int64_t gcd(std::int64_t a, std::int64_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

std::int64_t multiply(std::int64_t a, std::int64_t b, std::int64_t m) {
    if (b == 1) return a;
    if (b % 2 == 0) return (2 * multiply(a, b / 2, m)) % m;
    return (multiply(a, b - 1, m) + a) % m;
}

std::int64_t pows(std::int64_t a, std::int64_t b, std::int64_t m) {
    if (b == 0) return 1;
    if (b % 2 == 0) {
        std::int64_t temp = pows(a, b / 2, m);
        return multiply(temp, temp, m) % m;
    }
    return (multiply(pows(a, b - 1, m), a, m)) % m;
}

bool check_by_ferma(std::int64_t x) {
    if (x == 1 || x == 2 || x == 3) return true;
    std::uniform_int_distribution<std::int64_t> dist_a(2, x - 1);
    for (int i = 0; i < 100; i++) {
        std::int64_t a = dist_a(rng);
        if (gcd(a, x) != 1) return false;
        if (pows(a, x - 1, x) != 1) return false;
    }
    return true;
}

struct Node {
    std::uint16_t num;
    Node *parent;
    std::vector<Node> nodes;

    explicit Node(std::uint16_t num, Node *parent = nullptr) : num(num), parent(parent) {}
};

void BuildOneLevel(Node &root, std::uint64_t start_num = 0) {
    for (std::uint16_t i = 1; i < 10; i += 2)
        if (check_by_ferma(start_num * 10 + i)) root.nodes.emplace_back(Node(i, &root));
}

void BuildNLevels(std::uint16_t N, Node &root, std::uint64_t start_num) {
    if (N == 0) return;
    if (root.nodes.empty()) BuildOneLevel(root, start_num);
    for (auto &node: root.nodes) BuildNLevels(N - 1, node, start_num * 10 + node.num);
}

std::uint16_t GetNextDigit(Node &now_root, std::uint64_t start_value) {
    BuildNLevels(3, now_root, start_value);
    std::uint16_t first_var = 100, second_var = 100;
    for (const auto &p: now_root.nodes) {
        bool is_third_exists = false;
        if (p.nodes.empty()) {
            first_var = p.num;
            break;
        }
        for (const auto &s: p.nodes) {
            for (const auto &t: s.nodes) {
                is_third_exists = true;
                break;
            }
            if (is_third_exists) break;
        }
        if (is_third_exists) second_var = p.num;
    }
    if (first_var < 10) return first_var;
    if (second_var < 10) return second_var;
    return 5;
//    std::vector<std::pair<std::uint16_t, std::vector<std::pair<std::uint16_t, std::vector<std::uint16_t>>>>> after_is_first_prime;
//    after_is_first_prime.reserve(5);
//    for (std::uint16_t i = 1; i < 10; i += 2) {
//        std::uint64_t cur_first_num = now_num * 10 + i;
//        if (check_by_ferma(cur_first_num)) {
//            after_is_first_prime.emplace_back(i, std::vector<std::pair<std::uint16_t, std::vector<std::uint16_t>>>{});
//            auto now_first_it = std::prev(after_is_first_prime.end());
//            now_first_it->second.reserve(5);
//            for (std::uint16_t j = 1; j < 10; j += 2) {
//                std::uint64_t cur_second_num = cur_first_num * 10 + j;
//                if (check_by_ferma(cur_second_num)) {
//                    now_first_it->second.emplace_back(j, std::vector<std::uint16_t>{});
//                    auto now_second_it = std::prev(now_first_it->second.end());
//                    now_second_it->second.reserve(5);
//                    for (std::uint16_t k = 1; k < 10; k += 2) {
//                        std::uint64_t cur_third_num = cur_second_num * 10 + k;
//                        if (check_by_ferma(cur_third_num)) {
//                            now_second_it->second.emplace_back(k);
//                        }
//                    }
//                }
//            }
//            if (now_first_it->second.empty()) return now_first_it->first;
//        }
//    }
//    for (const auto &p: after_is_first_prime) {
//        bool is_third_exists = false;
//        for (const auto &s: p.second) {
//            for (const auto &t: s.second) {
//                is_third_exists = true;
//                break;
//            }
//            if (is_third_exists) break;
//        }
//        if (is_third_exists) return p.first;
//    }
//    return 5;
}

int main() {
    std::uint64_t now_num;
    std::cin >> now_num;
    Node root(now_num);
    auto now_node = std::ref(root);
    while (true) {
        std::int16_t next_digit = GetNextDigit(now_node.get(), now_num);
        now_node = std::ref(*std::find_if(now_node.get().nodes.begin(), now_node.get().nodes.end(),
                                          [next_digit](const Node &node) { return node.num == next_digit; }));
        now_num = now_num * 10 + next_digit;
        std::cout << next_digit << "\n";
        std::cout.flush();
        std::cin >> next_digit;
        if (next_digit == -1) return 0;
        else {
            now_node = std::ref(*std::find_if(now_node.get().nodes.begin(), now_node.get().nodes.end(),
                                              [next_digit](const Node &node) { return node.num == next_digit; }));
            now_num = now_num * 10 + next_digit;
        }
    }
    return 0;
}
