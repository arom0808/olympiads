#include <iostream>

using namespace std;

int32_t n;

struct Coord {
    int32_t x, y;

    explicit Coord(int32_t x = 0, int32_t y = 0) : x(x), y(y) {}

    Coord operator+(const Coord &other) const {
        return Coord(x + other.x, y + other.y);
    }

    [[nodiscard]] bool is_ok() const {
        return x >= 0 && x < n && y >= 0 && y < n;
    }
};

const Coord moves[8] = {Coord(-2, 1), Coord(-1, 2), Coord(1, 2), Coord(2, 1), Coord(2, -1), Coord(1, -2),
                        Coord(-1, -2), Coord(-2, -1)};
int32_t ans[64];

bool dfs(Coord coord, int32_t level) {
    if (ans[coord.x * n + coord.y] != -1) return false;
    ans[coord.x * n + coord.y] = level;
    if (level + 1 == n * n) return true;
    for (auto mv: moves) if ((coord + mv).is_ok() && dfs(coord + mv, level + 1)) return true;
    ans[coord.x * n + coord.y] = -1;
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (auto &el: ans) el = -1;
    if (dfs(Coord(0, 0), 0)) {
        cout << "1\n";
        for (int32_t i = 0; i < n; ++i) {
            for (int32_t j = 0; j < n; ++j) cout << ans[i * n + j] + 1 << " ";
            cout << "\n";
        }
    } else {
        cout << "0\n";
    }
    return 0;
}
