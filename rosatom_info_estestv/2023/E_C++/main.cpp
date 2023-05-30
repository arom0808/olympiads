#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

enum class Dir {
    left = 0,
    top = 1,
    right = 2,
    bottom = 3
};

class MapArr : public std::vector<bool> {
public:
    explicit MapArr(std::uint32_t N) : N(N), std::vector<bool>(N * N, false) {}

    void SetTrue(std::uint32_t x, std::uint32_t y) {
        this->operator[](x * N + y) = true;
    }

    bool GetValue(std::uint32_t x, std::uint32_t y) const {
        return this->operator[](x * N + y);
    }

private:
    std::uint32_t N;
};

class MapArrDir : public std::vector<bool> {
public:
    explicit MapArrDir(std::uint32_t N) : N(N), std::vector<bool>(N * N * 4, false) {}

    bool SetTrueOrReturn(std::uint32_t x, std::uint32_t y, Dir dir) {
        auto i = this->operator[](x * N + y * 4 + static_cast<std::uint32_t>(dir));
        if (i) return true;
        i = true;
        return false;
    }

private:
    std::uint32_t N;
};

enum class Sol {
    left = 0,
    top = 1,
    right = 2,
    bottom = 3,
    loop = 4
};

Dir Rotate90(Dir dir) { return static_cast<Dir>((static_cast<std::uint32_t>(dir) + 1) % 4); }

bool IsDirVert(Dir dir) { return dir == Dir::top || dir == Dir::bottom; }

//bool IsDirPositive(Dir dir) { return dir == Dir::bottom || dir == Dir::right; }

//template<typename F, typename S>
//void AddToMap(std::map<F, std::set<S>> &map, F first, S second) {
//    auto it = map.find(first);
//    if (it == map.end()) map.emplace(first, std::set<S>{second});
//    else it->second.insert(second);
//}

Sol GetSolution(std::uint32_t N, const MapArr &map, std::pair<std::uint32_t, std::uint32_t> start_pos) {
    MapArrDir visited(N);
    Dir dir = Dir::top;
    auto pos = start_pos;
    while (true) {
        if (visited.SetTrueOrReturn(pos.first, pos.second, dir)) return Sol::loop;
        bool did_X_found = false;
        auto vert_func = [&dir, &pos, &did_X_found, &map, N]() {
            if ((dir == Dir::top ? (pos.first > 0) : (pos.first < N - 1))) {
                std::uint32_t i = pos.first;
                do {
                    if (dir == Dir::top) --i;
                    else ++i;
                    if (map.GetValue(i, pos.second)) {
                        pos.first = i;
                        did_X_found = true;
                        break;
                    }
                } while ((dir == Dir::top ? (i > 0) : (i < N)));
            }
        };
        auto hor_func = [&dir, &pos, &did_X_found, &map, N]() {
            if ((dir == Dir::left ? (pos.second > 0) : (pos.second < N - 1))) {
                std::uint32_t j = pos.second;
                do {
                    if (dir == Dir::left) --j;
                    else ++j;
                    if (map.GetValue(pos.first, j)) {
                        pos.second = j;
                        did_X_found = true;
                        break;
                    }
                } while ((dir == Dir::left ? (j > 0) : (j < N)));
            }
        };
        if (IsDirVert(dir)) vert_func();
        else hor_func();
        if (!did_X_found) return static_cast<Sol>(static_cast<std::uint32_t>(dir));
        dir = Rotate90(dir);
    }
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    MapArr map(N);
    std::string temp;
    std::pair<std::uint32_t, std::uint32_t> start_pos;
    for (std::uint32_t i = 0; i < N; ++i) {
        std::cin >> temp;
        for (std::uint32_t j = 0; j < N; ++j) {
            if (temp[j] == '.') continue;
            if (temp[j] == 'I') {
                start_pos = {i, j};
                continue;
            }
            map.SetTrue(i, j);
        }
    }
    auto sol = GetSolution(N, map, start_pos);
    if (sol == Sol::left) std::cout << "OUT MINUS_X";
    else if (sol == Sol::top) std::cout << "OUT MINUS_Y";
    else if (sol == Sol::right) std::cout << "OUT PLUS_X";
    else if (sol == Sol::bottom) std::cout << "OUT PLUS_Y";
    else std::cout << "LOOP";
    return 0;
}
