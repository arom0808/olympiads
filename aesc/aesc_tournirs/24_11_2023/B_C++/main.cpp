#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    vector<pair<uint32_t, uint32_t>> triangles(n);
    for (auto &p: triangles) cin >> p.first >> p.second;
    sort(triangles.begin(), triangles.end(), [](const pair<uint32_t, uint32_t> &a, const pair<uint32_t, uint32_t> &b) {
        return a.second < b.second;
    });
    int32_t res = -1;
    for (uint32_t i = 0; i + 2 < 150 && i + 2 < n; ++i)
        for (uint32_t j = i + 1; j + 1 < 150 && j + 1 < n; ++j)
            for (uint32_t k = j + 1; k < 150 && k < n; ++k)
                if (triangles[i].first + triangles[j].first > triangles[k].first &&
                    triangles[i].first + triangles[k].first > triangles[j].first &&
                    triangles[k].first + triangles[j].first > triangles[i].first &&
                    (res == -1 || triangles[i].second + triangles[j].second + triangles[k].second < res))
                    res = triangles[i].second + triangles[j].second + triangles[k].second;
    cout << res;
    return 0;
}