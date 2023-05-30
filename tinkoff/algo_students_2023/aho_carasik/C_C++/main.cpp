#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

//#include <fstream>
//#include <random>
//
//namespace Generating {
//    std::random_device dev;
//    std::uint32_t seed = dev();
////    std::uint32_t seed = 1081499123;
//    std::mt19937 rng(seed);
//    std::uniform_int_distribution dist_10_20(10, 20);
//    std::uniform_int_distribution dist_2_9(2, 9);
//    std::uniform_int_distribution dist_1_6(1, 6);
//    std::uniform_int_distribution dist_1_1000(1, 1000);
//
//
//    void Generate() {
//        std::cout << "seed: " << seed << "\n\n";
//        std::uint32_t N = dist_1_1000(rng), M = dist_1_6(rng), K = dist_2_9(rng);
//        std::uniform_int_distribution<char> dist_char('0', '0' + K - 1);
//        std::vector<std::uint32_t> A(M);
//        for (auto &&a: A) a = dist_1_1000(rng);
//        std::sort(A.begin(), A.end());
//        std::vector<std::string> nums(N);
//        for (auto &&n: nums) {
//            n.resize(M, '0');
//            for (auto &&ch: n) ch = dist_char(rng);
//        }
//        std::ofstream o_f("input.txt");
//        o_f << N << " " << M << " " << K << "\n";
//        for (const auto &a: A) o_f << a << " ";
//        o_f << "\n";
//        for (const auto &n: nums) o_f << n << "\n";
//        o_f.close();
//    }
//}
//
//class OldSolution {
//public:
//    std::uint32_t k;
//    std::uint32_t m, min_sum = std::numeric_limits<std::uint32_t>::max();
//    std::vector<char> cur_num, min_num;
//    std::vector<std::uint32_t> a;
//    std::vector<std::string> strs;
//
//    explicit OldSolution(std::istream &in_stream) {
//        std::uint32_t n;
//        in_stream >> n >> m >> k;
//        a.resize(m + 1);
//        for (std::uint32_t i = 1; i < a.size(); ++i) in_stream >> a[i];
//        a[0] = 0;
//        strs.resize(n);
//        for (auto &&el: strs) in_stream >> el;
//        cur_num.resize(m, '0');
//        min_num.resize(m, '0');
//    }
//
//    std::uint32_t GetLevelOfEqual(const std::string &str) {
//        std::uint32_t eq_level = 0;
//        while (str[eq_level] == cur_num[eq_level] && eq_level < cur_num.size()) ++eq_level;
//        return eq_level;
//    }
//
//    void RecursionSolution(std::uint32_t cur_level = 0) {
//        if (cur_level < m) {
//            for (cur_num[cur_level] = '0'; cur_num[cur_level] < '0' + k; ++cur_num[cur_level]) {
//                RecursionSolution(cur_level + 1);
//            }
//        } else {
//            std::uint32_t sum = 0;
//            for (const auto &str: strs) sum += a[GetLevelOfEqual(str)];
//            if (sum < min_sum) {
//                min_sum = sum;
//                min_num = cur_num;
//            }
//        }
//    }
//
//    std::pair<std::string, std::uint32_t> GetResults() {
//        return {std::string(min_num.begin(), min_num.end()), min_sum};
//    }
//};

class Bor {
public:
    class BorNode {
    public:
        std::uint64_t this_count;
        BorNode *parent;
        char pc;
        std::map<char, BorNode *> childs;

        explicit BorNode(BorNode *parent = nullptr, char pc = '\0', std::uint64_t this_count = 1)
                : parent(parent), pc(pc), this_count(this_count) {}

        BorNode(BorNode &other) : this_count(other.this_count), parent(other.parent), pc(other.pc) {
            for (const auto &ch: other.childs)
                childs.emplace(ch.first, new BorNode(*ch.second));
        }

        BorNode(BorNode &&other) noexcept: this_count(other.this_count), parent(other.parent), pc(other.pc),
                                           childs(std::move(other.childs)) {}

        ~BorNode() { for (auto &child: childs) delete child.second; }
    };

    BorNode *root;

    Bor() : root(new BorNode(nullptr, '\0', 0)) {}

    Bor(std::uint64_t n, std::istream &in_stream) : Bor() {
        std::string temp;
        for (std::uint64_t i = 0; i < n; ++i) {
            in_stream >> temp;
            auto cur_node = root;
            ++cur_node->this_count;
            for (auto c: temp) {
                auto it = cur_node->childs.find(c);
                if (it != cur_node->childs.end()) {
                    cur_node = it->second;
                    ++cur_node->this_count;
                } else cur_node = cur_node->childs.emplace(c, new BorNode(cur_node, c)).first->second;
            }
        }
    }

    ~Bor() { delete root; }
};


class NewSolution {
public:
    char k;
    std::uint64_t m, min_sum = std::numeric_limits<std::uint64_t>::max();
    std::vector<char> cur_num, min_num;
    std::vector<std::uint64_t> &a;
    Bor &bor;

    NewSolution(std::uint64_t k, std::uint64_t m, std::vector<std::uint64_t> &a, Bor &bor)
            : k(static_cast<char>(k)), m(m), a(a), bor(bor),
              cur_num(m, '0'), min_num(m, '0') {}

    void
    RecursionSolution(std::uint64_t cur_level = 0, std::uint64_t cur_sum = 0, Bor::BorNode *cur_bor_node = nullptr) {
        if (cur_sum > min_sum) return;
        if (cur_bor_node == nullptr) cur_bor_node = bor.root;
        if (cur_level < m) {
            for (cur_num[cur_level] = '0'; cur_num[cur_level] < '0' + k; ++cur_num[cur_level]) {
                auto it = cur_bor_node->childs.find(cur_num[cur_level]);
                if (it != cur_bor_node->childs.end()) {
                    std::uint64_t next_sum =
                            cur_sum + a[cur_level] * (cur_bor_node->this_count - it->second->this_count);
                    if (cur_level == m - 1) next_sum += a[cur_level + 1] * it->second->this_count;
                    RecursionSolution(cur_level + 1, next_sum, it->second);
                } else {
                    for (std::uint64_t i = cur_level + 1; i < m; ++i) cur_num[i] = '0';
                    RecursionSolution(m, cur_sum + a[cur_level] * cur_bor_node->this_count, cur_bor_node);
                }
            }
        } else {
            if (cur_sum < min_sum) {
                min_sum = cur_sum;
                min_num = cur_num;
            }
        }
    }

    std::pair<std::string, std::uint64_t> GetResults() {
        return {std::string(min_num.begin(), min_num.end()), min_sum};
    }
};

std::pair<std::string, std::uint64_t> NewSoluteForThisInput(std::istream &in_stream) {
    std::uint64_t n, m, k;
    in_stream >> n >> m >> k;
    std::vector<std::uint64_t> a(m + 1);
    a[0] = 0;
    for (std::uint64_t i = 1; i < a.size(); ++i) in_stream >> a[i];
    Bor bor(n, in_stream);
    NewSolution new_solution(k, m, a, bor);
    new_solution.RecursionSolution();
    return new_solution.GetResults();
}

//std::pair<std::string, std::uint64_t> OldSoluteForThisInput(std::istream &in_stream) {
//    OldSolution old_sol(in_stream);
//    old_sol.RecursionSolution();
//    return old_sol.GetResults();
//}

int main() {
    auto results = NewSoluteForThisInput(std::cin);
    std::cout << results.first << "\n" << results.second;
    return 0;
//    std::uint64_t ff = 0;
//    while (true) {
//        Generating::Generate();
//        std::ifstream i_f_1("input.txt");
//        auto new_sol = NewSoluteForThisInput(i_f_1);
//        i_f_1.close();
//        std::ifstream i_f_2("input.txt");
//        auto old_sol = OldSoluteForThisInput(i_f_2);
//        i_f_2.close();
//        if (new_sol != old_sol) {
//            std::cout << "NOT EQUAL!!!";
//            break;
//        }
//        std::cout << ff++;
//    }
    return 0;
}
