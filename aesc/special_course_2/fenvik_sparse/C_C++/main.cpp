#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class FenwickTree {
private:
//    static inline int64_t f(int64_t x) { return x - (x & (-x)) + 1; }

    vector<vector<vector<T>>> tree;

public:
    T sum(int64_t _x, int64_t _y, int64_t _z) {
        T res = 0;
        for (auto x = _x; x > 0; x -= x & -x)
            for (auto y = _y; y > 0; y -= y & -y)
                for (auto z = _z; z > 0; z -= z & -z)
                    res += tree[x][y][z];
        return res;
    }

    T sum(int64_t x1, int64_t y1, int64_t z1, int64_t x2, int64_t y2, int64_t z2) { // [l, r) in 0-indexation
        return sum(x2, y2, z2) - sum(x1, y2, z2) - sum(x2, y1, z2) - sum(x2, y2, z1) + sum(x2, y1, z1) +
               sum(x1, y2, z1) + sum(x1, y1, z2) - sum(x1, y1, z1);
    }

    void add(int64_t _x, int64_t _y, int64_t _z, T val) {
        for (uint64_t x = _x + 1; x < tree.size(); x += x & -x)
            for (uint64_t y = _y + 1; y < tree.size(); y += y & -y)
                for (uint64_t z = _z + 1; z < tree.size(); z += z & -z)
                    tree[x][y][z] += val;
    }

    explicit FenwickTree(int64_t n) : tree(n + 1, vector<vector<T>>(n + 1, vector<T>(n + 1, 0))) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int64_t n;
    cin >> n;
    FenwickTree<int64_t> ft(n);
    int64_t m, x, y, z, k, x1, y1, z1, x2, y2, z2;
    do {
        cin >> m;
        if (m == 1) {
            cin >> x >> y >> z >> k;
            ft.add(x, y, z, k);
        } else if (m == 2) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << ft.sum(x1, y1, z1, x2 + 1, y2 + 1, z2 + 1) << "\n";
        }
    } while (m != 3);
    return 0;
}



//template<typename T>
//class StupidFT {
//    vector<vector<vector<T>>> values;
//
//public:
//    T sum(int64_t x1, int64_t y1, int64_t z1, int64_t x2, int64_t y2, int64_t z2) {
//        int64_t res = 0;
//        for (auto x = x1; x < x2; ++x)
//            for (auto y = y1; y < y2; ++y)
//                for (auto z = z1; z < z2; ++z)
//                    res += values[x][y][z];
//        return res;
//    }
//
//    void add(int64_t x, int64_t y, int64_t z, uint64_t val) {
//        values[x][y][z] += val;
//    }
//
//    explicit StupidFT(int64_t n) : values(n + 1, vector<vector<T>>(n + 1, vector<T>(n + 1, 0))) {}
//};
//
//namespace Test {
//    random_device dev;
//    mt19937 rng(dev());
//
//    int64_t randint(int64_t a, int64_t b) { return uniform_int_distribution<int64_t>(a, b)(rng); }
//
//    void Test() {
//        int64_t n = 3;
//        FenwickTree<int64_t> ft(n);
//        StupidFT<int64_t> stup_ft(n);
//        while (true) {
//            auto t = randint(1, 2);
//            if (t == 1) {
//                auto x = randint(0, n - 1), y = randint(0, n - 1), z = randint(0, n - 1), k = randint(-2, 2);
//                ft.add(x, y, z, k);
//                stup_ft.add(x, y, z, k);
//                cout << 1 << " " << x << " " << y << " " << z << " " << k << "\n";
//            } else if (t == 2) {
//                auto x1 = randint(0, n - 1), y1 = randint(0, n - 1), z1 = randint(0, n - 1),
//                        x2 = randint(x1, n - 1), y2 = randint(y1, n - 1), z2 = randint(z1, n - 1);
//                auto my_res = ft.sum(x1, y1, z1, x2 + 1, y2 + 1, z2 + 1),
//                        st_res = stup_ft.sum(x1, y1, z1, x2 + 1, y2 + 1, z2 + 1);
//                cout << 2 << " " << x1 << " " << y1 << " " << z1 << " " << x2 << " " << y2 << " " << z2 << "\n";
//                if (my_res != st_res) {
//                    cout << "my res: " << my_res << "\nstupid res: " << st_res;
//                    break;
//                }
//            }
//        }
//    }
//}