#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <map>

std::uint32_t gcd(std::uint32_t a, std::uint32_t b) {
    if (a % b == 0) return b;
    if (b % a == 0) return a;
    if (a > b) return gcd(a % b, b);
    return gcd(a, b % a);
}

//std::uint32_t ltm(std::uint32_t a, std::uint32_t b) {
//    return (a * b) / gcd(a, b);
//}

class Fraction {
public:
    std::uint32_t numerator, denominator;
    double real_value;

    explicit Fraction(std::uint32_t numerator = 0, std::uint32_t denominator = 1)
            : numerator(numerator), denominator(denominator),
              real_value(static_cast<double>(numerator) / static_cast<double>(denominator)) {
        Simplify();
    }

    bool operator<(const Fraction &other) const {
        return real_value < other.real_value;
    }

    bool operator>=(const Fraction &other) const {
        return real_value >= other.real_value;
    }

    void Simplify() {
        auto n_g = gcd(numerator, denominator);
        numerator /= n_g;
        denominator /= n_g;
    }
};

//void AddToCollisions(std::map<Fraction, std::map<std::uint32_t, std::set<std::uint32_t>>> &collisions,
//                     const Fraction &n_time, std::uint32_t i, std::uint32_t j) {
//    auto it1 = collisions.find(n_time);
//    if (it1 == collisions.end())
//        it1 = collisions.emplace(n_time, std::map<std::uint32_t, std::set<std::uint32_t>>{}).first;
//    auto it2 = it1->second.find(i);
//    if (it2 == it1->second.end()) it2 = it1->second.emplace(i, std::set<std::uint32_t>{}).first;
//    it2->second.emplace(j);
//}

void
AddToGraphEdges(std::vector<std::map<Fraction, std::vector<std::uint32_t>>> &graph_edges, const Fraction &n_time,
                std::uint32_t i, std::uint32_t j) {
    auto it1 = graph_edges[i].find(n_time);
    if (it1 == graph_edges[i].end()) graph_edges[i].emplace(n_time, std::vector<std::uint32_t>{j});
    else it1->second.emplace_back(j);
}

//std::optional<Fraction>
//GooseDFS(const std::vector<std::map<Fraction, std::set<std::uint32_t>>> &graph_edges, std::vector<bool> &visited,
//         std::uint32_t now_id, const Fraction &now_time, std::uint32_t q) {
//    if()
//}

int main() {
    std::int32_t n;
    std::cin >> n;
    std::vector<std::int32_t> stars(n);
    for (auto &&star: stars) std::cin >> star;
    std::vector<std::map<Fraction, std::vector<std::uint32_t>>> graph_edges(n);
    for (std::int32_t i = 0; i < n - 1; ++i) {
        for (std::int32_t j = i + 1; j < n; ++j) {
            std::int32_t a = stars[i] - stars[j], b = i - j;
            if ((a < 0 && b > 0) || (a > 0 && b < 0) || b == 0) continue;
            Fraction n_time(std::abs(a), std::abs(b));
            AddToGraphEdges(graph_edges, n_time, i, j);
            AddToGraphEdges(graph_edges, n_time, j, i);
        }
    }
    for (std::int32_t i = 0; i < n - 1; ++i) {

    }
    std::vector<std::uint32_t> q(n);
    for (auto &&ee: q) {
        std::cin >> ee;
        --ee;
    }

//    for (std::int32_t i = 0; i < n; ++i) {
//        if (is_answed[i]) std::cout << answers[i].numerator << "/" << answers[i].denominator << "\n";
//        else std::cout << "-1\n";
//    }
    return 0;
}
