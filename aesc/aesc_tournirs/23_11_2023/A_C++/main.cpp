#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    std::set<uint64_t> island, border;
    char c;
    for (std::uint32_t i = 0; i < n; ++i) {
        for (std::uint32_t j = 0; j < m; ++j) {
            cin >> c;
            if (c == '#') island.insert((static_cast<uint64_t>(i) << 32) | j);
        }
    }
    for (auto &pos: island) {
        int32_t x = pos >> 32, y = pos & ((1ull << 32) - 1);
        for (int32_t dx = -1; dx <= 1; ++dx) {
            for (int32_t dy = -1; dy <= 1; ++dy) {
                int32_t nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && static_cast<uint32_t>(nx) < n && static_cast<uint32_t>(ny) < m) {
                    uint64_t now_coords = (static_cast<uint64_t>(nx) << 32) | ny;
                    if (island.find(now_coords) == island.end()) border.insert(now_coords);
                }
            }
        }
    }
    auto pos = border.begin();
    while (!border.empty()) {
        int32_t x = (*pos) >> 32, y = (*pos) & ((1ull << 32) - 1);
        cout << x + 1 << " " << y + 1 << "\n";
        cout.flush();
        border.erase(pos);
        if (border.empty()) return 0;
        bool found = false;
        for (int32_t dx = -1; dx <= 1; ++dx) {
            for (int32_t dy = -1; dy <= 1; ++dy) {
                if (dx != 0 && dy != 0) continue;
                int32_t nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && static_cast<uint32_t>(nx) < n && static_cast<uint32_t>(ny) < m) {
                    uint64_t now_coords = (static_cast<uint64_t>(nx) << 32) | ny;
                    auto it = border.find(now_coords);
                    if (it != border.end()) {
                        pos = it;
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
        }
    }
    return 0;
}
