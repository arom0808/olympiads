#include <bits/stdc++.h>
#include <random>
#define all(a) a.begin(), a.end()

using namespace std;

int a =  563, b = 297, c = 192, d = 247929;

int main(int argc, char* argv[]) {
    ofstream field("field.txt");
    int n = stoi(argv[1]), m = stoi(argv[2]), r = stoi(argv[3]);
    vector<pair<int, int>> w;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            w.emplace_back(i, j);
        }
    }
    int seed = a * n + b * m + c * r + d;
    mt19937 rnd(seed);
    shuffle(all(w), rnd);
    if (n < 5 || m < 5) {
        cout << "Field width and height must be bigger than 4!\n";
        return 0;
    }
    if (r > n * m - 2) {
        cout << "You entered too mush rocks!\n";
        return 0;
    }
    vector<vector<int>> res(n, vector<int>(m));
    res[w[0].first][w[0].second] = 1;
    res[w[1].first][w[1].second] = 2;
    for (int i = 2; r-- && i < n * m; ++i) {
        res[w[i].first][w[i].second] = -100;
    }
    field << n << ' ' << m << ' ' << 2 << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            field << res[i][j] << ' ';
        }
        field << '\n';
    }
}