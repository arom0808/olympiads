#include <iostream>
#include <vector>
#include <deque>
#include <iomanip>

using namespace std;

const int32_t maxn = 101, k = 26;
const uint64_t mod = 1000000007;

vector<string> bad_strings;
int32_t n, m;

int32_t go[maxn][k];
int32_t link[maxn], p[maxn], in_c[maxn], pos_term[maxn];
bool term[maxn];
int32_t bor_size = 1;

using Matrix = vector<vector<uint64_t>>;

Matrix identityMatrix(int32_t size) {
    Matrix res(size, vector<uint64_t>(size));
    for (int32_t i = 0; i < size; ++i) res[i][i] = 1;
    return res;
}

Matrix transpose(const Matrix &a) {
    Matrix res(a[0].size(), vector<uint64_t>(a.size()));
    for (int32_t i = 0; i < a.size(); ++i)
        for (int32_t j = 0; j < a[0].size(); ++j)
            res[j][i] = a[i][j];
    return res;
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    auto tb = transpose(b);
    Matrix res(a.size(), vector<uint64_t>(tb.size()));
    for (int32_t y = 0; y < res.size(); ++y)
        for (int32_t x = 0; x < res[0].size(); ++x)
            for (int32_t i = 0; i < a[0].size(); ++i)
                res[y][x] = (res[y][x] + a[y][i] * tb[x][i] % mod) % mod;
    return res;
}

Matrix pow(const Matrix &a, uint64_t p) {
    if (!p) return identityMatrix(a.size());
    if (p % 2) return pow(a, p - 1) * a;
    Matrix r = pow(a, p / 2);
    return r * r;
}

void add_string(const string &str) {
    int32_t v = 0;
    for (auto _c: str) {
        int c = _c - 'a';
        if (go[v][c] == -1) in_c[bor_size] = c, p[bor_size] = v, go[v][c] = bor_size++;
        v = go[v][c];
    }
    term[v] = true;
}

void bfs1() {
    deque<int32_t> deq;
    for (int32_t c = 0; c < k; ++c) {
        if (go[0][c] != -1) deq.push_back(go[0][c]);
        else go[0][c] = 0;
    }
    while (!deq.empty()) {
        auto v = deq.front();
        deq.pop_front();
        if (p[v] == 0) link[v] = 0;
        else link[v] = go[link[p[v]]][in_c[v]];
        if (term[v]) pos_term[v] = v;
        else pos_term[v] = pos_term[link[v]];
        for (int32_t c = 0; c < k; ++c) {
            if (go[v][c] == -1) go[v][c] = go[link[v]][c];
            else deq.push_back(go[v][c]);
        }
    }
}

uint64_t sol() {
    for (const auto &s: bad_strings) add_string(s);
    bfs1();
    Matrix matrix(bor_size, vector<uint64_t>(bor_size));
    for (int32_t v = 0; v < bor_size; ++v) {
        if (pos_term[v] != -1) continue;
        for (int32_t c = 0; c < k; ++c) if (pos_term[go[v][c]] == -1) ++matrix[v][go[v][c]];
    }
//    for (int32_t v = 0; v < bor_size; ++v) {
//        for (int32_t u = 0; u < bor_size; ++u) cout << std::left << std::setw(10) << matrix[v][u];
//        cout << "\n";
//    }
//    cout << "\n\n\n";
    Matrix result = pow(matrix, m);
//    for (int32_t i = 1; i < m; ++i) result = result * matrix;
//    result = matrix * matrix;
//    for (int32_t v = 0; v < bor_size; ++v) {
//        for (int32_t u = 0; u < bor_size; ++u) cout << std::left << std::setw(10) << result[v][u];
//        cout << "\n";
//    }
    uint64_t res = 0;
    for (int32_t i = 0; i < bor_size; ++i) res = (res + result[0][i]) % mod;
    return res;
}


namespace Stupid {
    string str;
    uint64_t result = 0;

    void rec_fg(uint32_t level) {
        if (level >= m) {
            bool ok = true;
            for (const auto &bs: bad_strings) {
                if (str.find(bs) != string::npos) {
                    ok = false;
                    break;
                }
            }
            if (ok) result = (result + 1) % mod;
        } else {
            for (char c = 'a'; c <= 'z'; ++c) {
                str[level] = c;
                rec_fg(level + 1);
            }
        }
    }

    void stupid_sol() {
        str.resize(m, 'a');
        rec_fg(0);
    }
}

int main() {
    for (int32_t i = 0; i < maxn; ++i) {
        link[i] = p[i] = in_c[i] = pos_term[i] = -1;
        for (int32_t j = 0; j < k; ++j) go[i][j] = -1;
    }
    cin >> n >> m;
    bad_strings.resize(n);
    for (int32_t i = 0; i < n; ++i) cin >> bad_strings[i];
//    Stupid::stupid_sol();
//    cout << Stupid::result;
    cout << sol() << "\n";

//    if (n <= 10 && m <= 4) {
//        FirstGroup::first_group();
//        cout << (FirstGroup::result % mod) << "\n";
//        return 0;
//    } else if (m <= 25) {
//
//    }
    return 0;
}
