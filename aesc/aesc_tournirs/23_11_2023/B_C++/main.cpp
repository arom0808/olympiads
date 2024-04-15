#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

struct Request {
    uint32_t id;
    uint64_t year;
    uint32_t ans;
};

int main() {
    uint32_t n, m, q;
    cin >> n >> m >> q;
    vector<uint32_t> raw_counts(m, 0);
    for (uint32_t i = 0, a; i < n; ++i) {
        cin >> a;
        ++raw_counts[a - 1];
    }
    vector<Request> reqs(q);
    for (uint32_t i = 0; i < q; ++i) {
        reqs[i].id = i;
        cin >> reqs[i].year;
    }
    sort(reqs.begin(), reqs.end(), [](const Request &a, const Request &b) { return a.year < b.year; });
    map<uint64_t, set<uint32_t>> start_counts;
    for (uint32_t i = 0; i < m; ++i) {
        auto it = start_counts.find(raw_counts[i]);
        if (it != start_counts.end()) it->second.insert(i);
        else start_counts.emplace(raw_counts[i], set<uint32_t>{i});
    }
    uint64_t now_year = n, now_h = start_counts.begin()->first;
    set<uint32_t> now_min = start_counts.begin()->second;
    auto next_h = next(start_counts.begin());
    auto req = reqs.begin();
    while (next_h != start_counts.end()) {
        uint64_t dy = (next_h->first - now_h) * now_min.size();
        while (req != reqs.end() && now_year + dy >= req->year) {
            req->ans = *next(now_min.begin(), static_cast<int64_t>((req->year - now_year - 1) % now_min.size()));
            ++req;
        }
        if (req == reqs.end()) break;
        now_year += dy;
        now_min.insert(next_h->second.begin(), next_h->second.end());
        now_h = next_h->first;
        ++next_h;
    }
    while (req != reqs.end()) {
        req->ans = *next(now_min.begin(), static_cast<int64_t>((req->year - now_year - 1) % now_min.size()));
        ++req;
    }
    sort(reqs.begin(), reqs.end(), [](const Request &a, const Request &b) { return a.id < b.id; });
    for (const auto &out_req: reqs) cout << out_req.ans + 1 << "\n";
    return 0;
}
