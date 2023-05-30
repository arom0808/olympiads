#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

//template<typename CoordsT, typename LengthT = double>
//class Point {
//public:
//    CoordsT x, y;
//
//    explicit Point(const CoordsT &x = 0, const CoordsT &y = 0) : x(x), y(y) {}
//
//    Point(const std::initializer_list<CoordsT> &init_list) : x(*init_list.begin()), y(*std::next(init_list.begin())) {}
//
//    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
//
//    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
//
//    friend Point operator*(const CoordsT &a, const Point &b) { return {b.x * a, b.y * a}; }
//
//    Point operator*(const CoordsT &a) const { return {x * a, y * a}; }
//
//    bool operator==(const Point &other) const { return x == other.x && y == other.y; }
//
//    bool operator!=(const Point &other) const { return !(operator==(other)); }
//
//    bool operator<(const Point &other) const { return (x < other.x) || (x == other.x && (y < other.y)); }
//
//    bool operator>(const Point &other) const { return (x > other.x) || (x == other.x && (y > other.y)); }
//
//    LengthT length() const { return std::sqrt(x * x + y * y); }
//
//    LengthT distanceTo(const Point &other) const {
//        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
//    }
//};
//
//enum class OrientationOfPoints {
//    Collinear = 0,
//    Clockwise = 1,
//    Counterclockwise = 2
//};
//
//template<typename CoordsT, typename LengthT = double>
//OrientationOfPoints GetOrientationOfTriplePoints(const Point<CoordsT, LengthT> &p, const Point<CoordsT, LengthT> &q,
//                                                 const Point<CoordsT, LengthT> &r) {
//    CoordsT val = (q.y - p.y) * (r.x - q.x) -
//                  (q.x - p.x) * (r.y - q.y);
//    if (val == 0) return OrientationOfPoints::Collinear;
//    return (val > 0) ? OrientationOfPoints::Clockwise
//                     : OrientationOfPoints::Counterclockwise;
//}
//
//template<typename CoordsT, typename LengthT = double>
//typename std::vector<Point<CoordsT, LengthT>>::iterator
//RemoveAngleEquals(const Point<CoordsT, LengthT> &first_point,
//                  typename std::vector<Point<CoordsT, LengthT>>::iterator begin,
//                  typename std::vector<Point<CoordsT, LengthT>>::iterator end) {
//    auto m_point = begin;
//    for (auto it = begin; it < end; ++it) {
//        while (it < std::prev(end) &&
//               GetOrientationOfTriplePoints(first_point, *it, *std::next(it)) == OrientationOfPoints::Collinear)
//            ++it;
//        *m_point = *it;
//        ++m_point;
//    }
//    return m_point;
//}
//
//template<typename CoordsT, typename LengthT = double>
//void GetConvexHull(std::vector<Point<CoordsT, LengthT>> &points, std::vector<Point<CoordsT, LengthT>> &results) {
//    results.clear();
//    auto BottomLeftSortF = [](const Point<CoordsT, LengthT> &a, const Point<CoordsT, LengthT> &b) {
//        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
//    };
//    std::iter_swap(points.begin(), std::min_element(points.begin(), points.end(), BottomLeftSortF));
//    auto PolarCoordsSortF = [&first_point = points.front()]
//            (const Point<CoordsT, LengthT> &a, const Point<CoordsT, LengthT> &b) {
//        OrientationOfPoints orientation = GetOrientationOfTriplePoints(first_point, a, b);
//        if (orientation == OrientationOfPoints::Collinear)
//            return (first_point.distanceTo(b) > first_point.distanceTo(a));
//        return (orientation == OrientationOfPoints::Counterclockwise);
//    };
//    std::sort(std::next(points.begin()), points.end(), PolarCoordsSortF);
//    points.erase(RemoveAngleEquals(points.front(), std::next(points.begin()), points.end()), points.end());
//    if (points.size() < 3) return;
//    results.resize(3);
//    std::copy(points.begin(), std::next(points.begin(), 3), results.begin());
//    results.reserve(points.size());
//    for (auto it = std::next(points.begin(), 3); it != points.end(); ++it) {
//        while (GetOrientationOfTriplePoints(*std::prev(results.end(), 2), results.back(), *it) !=
//               OrientationOfPoints::Counterclockwise)
//            results.erase(std::prev(results.end()));
//        results.push_back(*it);
//    }
//}

//template<typename VertexT, typename EdgeT>
//class GraphAdjMat {
//public:
//    std::vector<VertexT> vertexes;
//    std::vector<std::vector<EdgeT>> adjacency_matrix;

//    explicit GraphAdjMat(std::uint32_t vertexes_count) : vertexes(vertexes_count), adjacency_matrix(vertexes_count) {
//        for (std::uint32_t i = 0; i < vertexes_count; ++i)
//            adjacency_matrix[i].resize(vertexes_count - i);
//    };
//
//    typename std::vector<EdgeT>::reference EdgeRef(std::uint32_t i, std::uint32_t j) {
//        auto row_id = std::min(i, j);
//        return adjacency_matrix[row_id][std::max(i, j) - row_id];
//    }
//
//    typename std::vector<EdgeT>::const_reference
//    EdgeRef(std::uint32_t i, std::uint32_t j) const {
//        auto row_id = std::min(i, j);
//        return adjacency_matrix[row_id][std::max(i, j) - row_id];
//    }
//};

//template<typename VertexT, typename EdgeT>
//class GraphAdjArr {
//public:
//    struct Vertex {
//    public:
//        std::vector<std::pair<std::uint32_t, EdgeT>> connected_vertexes_ids_and_edges;
//        VertexT value;
//    };
//    std::vector<Vertex> vertexes;
//
//    GraphAdjArr() = default;
//
//    GraphAdjArr(const std::vector<VertexT> &vertex_values,
//                const std::vector<std::pair<std::pair<std::uint32_t, std::uint32_t>, EdgeT>> &edges) {
//        vertexes.resize(vertex_values.size());
//        for (std::uint32_t i = 0; i < vertexes.size(); ++i)
//            vertexes[i].value = vertex_values[i];
//        for (const auto &edge: edges) {
//            vertexes[edge.first.first].connected_vertexes_ids_and_edges.emplace_back(edge.first.second, edge.second);
//        }
//    }
//};
//
//void FordBellmanAlgorithm(const GraphAdjArr<std::uint32_t, std::int32_t> &graph, std::uint32_t start_point_id,
//                          std::vector<std::int32_t> &result) {
//    std::int32_t inf = std::numeric_limits<std::int32_t>::max(), endless_negative_cycle = std::numeric_limits<std::int32_t>::min();
//    result.clear();
//    result.resize(graph.vertexes.size(), inf);
//    result[start_point_id] = 0;
//    for (std::uint32_t i = 0; i < graph.vertexes.size() - 1; ++i) {
//        for (std::uint32_t from = 0; from < graph.vertexes.size(); ++from) {
//            for (const auto &edge: graph.vertexes[from].connected_vertexes_ids_and_edges) {
//                if (result[from] == inf) continue;
//                if (result[edge.first] == inf || result[edge.first] > result[from] + edge.second)
//                    result[edge.first] = result[from] + edge.second;
//            }
//        }
//    }
//    std::vector<std::uint32_t> vertexes_in_endless_cycle;
//    vertexes_in_endless_cycle.reserve(graph.vertexes.size());
//    for (std::uint32_t from = 0; from < graph.vertexes.size(); ++from) {
//        for (const auto &edge: graph.vertexes[from].connected_vertexes_ids_and_edges) {
//            if (result[from] == inf) continue;
//            if (result[edge.first] > result[from] + edge.second) {
//                vertexes_in_endless_cycle.push_back(from);
//                vertexes_in_endless_cycle.push_back(edge.first);
//            }
//        }
//    }
//    for (const auto &e_c: vertexes_in_endless_cycle) result[e_c] = endless_negative_cycle;
//}
//
//int main() {
//    GraphAdjArr<std::uint32_t, std::int32_t> graph({0, 0, 0, 0, 0}, {{{0, 1}, -1},
//                                                                     {{0, 2}, 4},
//                                                                     {{1, 2}, 3},
//                                                                     {{1, 3}, 2},
//                                                                     {{1, 4}, 2},
//                                                                     {{3, 1}, 1},
//                                                                     {{4, 3}, -3}});
//    std::vector<std::int32_t> result;
//    FordBellmanAlgorithm(graph, 1, result);
//    for (const auto &res: result) {
//        std::cout << res << std::endl;
//    }
//    return 0;
//}

std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
    while (a && b) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}


std::vector<std::uint64_t> multiplier{1, 3, 5, 7, 11, 3 * 5, 3 * 7, 3 * 11, 5 * 7, 5 * 11, 7 * 11, 3 * 5 * 7,
                                      3 * 5 * 11, 3 * 7 * 11, 5 * 7 * 11, 3 * 5 * 7 * 11};
std::set<std::uint64_t> small_easy_nums{2, 3, 5, 7, 11};
const std::uint64_t uint64_max = std::numeric_limits<std::uint64_t>::max();

std::uint64_t SQUFOF(std::uint64_t N) {
    if (small_easy_nums.find(N) != small_easy_nums.end()) return 0;
    std::uint64_t D, Po, P, Pprev, Q, Qprev, q, b, r, s;
    std::uint32_t L, B, i;
    s = static_cast<std::uint64_t>(std::sqrt(static_cast<long double>(N)) + 0.5);
    if (s * s == N) return s;
    for (int k = 0; k < multiplier.size() && N <= uint64_max / multiplier[k]; k++) {
        D = multiplier[k] * N;
        Po = Pprev = P = static_cast<std::uint64_t>(std::sqrt(static_cast<long double>(D)));
        Qprev = 1;
        Q = D - Po * Po;
        L = static_cast<std::uint32_t>(2 * std::sqrt(static_cast<long double>(2 * s)));
        B = 3 * L;
        for (i = 2; i < B; i++) {
            b = static_cast<std::uint64_t>((Po + P) / Q);
            P = b * Q - P;
            q = Q;
            Q = Qprev + b * (Pprev - P);
            r = static_cast<std::uint64_t>(std::sqrt(static_cast<long double>(Q)) + 0.5);
            if (!(i & 1) && r * r == Q) break;
            Qprev = q;
            Pprev = P;
        };
        if (i >= B) continue;
        b = static_cast<std::uint64_t> ((Po - P) / r);
        Pprev = P = b * r + P;
        Qprev = r;
        Q = (D - Pprev * Pprev) / Qprev;
        i = 0;
        do {
            b = static_cast<std::uint64_t>((Po + P) / Q);
            Pprev = P;
            P = b * Q - P;
            q = Q;
            Q = Qprev + b * (Pprev - P);
            Qprev = q;
            i++;
        } while (P != Pprev);
        r = gcd(N, Qprev);
        if (r != 1 && r != N) return r;
    }
    return 0;
}

int main() {
    std::cout << SQUFOF(23556656566656);
    return 0;
}