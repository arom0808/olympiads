#include <iostream>
#include <random>
#include <set>

using namespace std;

uint32_t seed = 423859;
mt19937 rng(seed);
int32_t n;

template<typename T>
T randint(T a, T b) {
    return uniform_int_distribution(a, b)(rng);
}

struct Line {
    int32_t axis, id;

    bool operator<(const Line &other) const {
        if (axis != other.axis) return axis < other.axis;
        return id < other.id;
    }
};

bool ask(Line line, int32_t last_ch = n - 1) {
    if (line.axis == 0) cout << "? 1 " << line.id + 1 << " " << last_ch + 1 << " " << line.id + 1 << endl;
    else cout << "? " << line.id + 1 << " 1 " << line.id + 1 << " " << last_ch + 1 << endl;
    int32_t r;
    cin >> r;
    if (r == -1) exit(0);
    return r % 2;
}

int32_t lb_l(Line line) {
    int32_t l = 0, r = n - 1;
    while (l != r) {
        int32_t m = (l + r) / 2;
        if (ask(line, m)) r = m;
        else l = m + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    set<Line> lines_to_check;
    for (int32_t i = 0; i < n; ++i) lines_to_check.emplace(0, i), lines_to_check.emplace(1, i);
    vector<Line> found_ls;
    while (found_ls.empty()) {
        auto it = next(lines_to_check.begin(), randint<int32_t>(0, lines_to_check.size() - 1));
        if (ask(*it)) found_ls.push_back(*it);
        lines_to_check.erase(it);
    }
    for (int32_t i = 0; i < n; ++i) lines_to_check.erase(Line(1 - found_ls.front().axis, i));
    while (found_ls.size() < 2) {
        auto it = next(lines_to_check.begin(), randint<int32_t>(0, lines_to_check.size() - 1));
        if (ask(*it)) found_ls.push_back(*it);
        lines_to_check.erase(it);
    }
    int32_t fr = lb_l(found_ls[0]), sr = lb_l(found_ls[1]);
    if (found_ls[0].axis == 0)
        cout << "! " << fr + 1 << " " << found_ls[0].id + 1 << " " << sr + 1 << " " << found_ls[1].id + 1 << endl;
    else cout << "! " << found_ls[0].id + 1 << " " << fr + 1 << " " << found_ls[1].id + 1 << " " << sr + 1 << endl;
    return 0;
}
