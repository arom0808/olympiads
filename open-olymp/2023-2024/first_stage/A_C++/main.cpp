#include <iostream>
#include <map>
#include <list>

using namespace std;

class TimeSec {
public:
    struct Act {
        int32_t time;
        bool type;

        bool operator<(const Act &other) const {
            if (time != other.time) return time < other.time;
            return type && !other.type;
        }
    };

    list<Act> acts;

    TimeSec(int32_t start, int32_t end) {
        if (start > end) swap(start, end);
        acts.emplace_back(start, true);
        acts.emplace_back(end, false);
    }

    TimeSec() = default;

    TimeSec(TimeSec &&other) noexcept: acts(std::move(other.acts)) {}

    TimeSec(const TimeSec &other) = default;

    TimeSec &operator&=(const TimeSec &other) {
        int32_t counter = 0;
        for (auto it1 = acts.cbegin(), it2 = other.acts.cbegin(); it1 != acts.end() || it2 != other.acts.end();) {
            if (it1 != acts.end() && (it2 == other.acts.end() || it1->time < it2->time ||
                                      (it1->time == it2->time && (it1->type || !it2->type)))) {
                if ((it1->type && ++counter < 2) || ((!it1->type) && counter-- < 2)) it1 = acts.erase(it1);
                else ++it1;
            } else {
                if ((it2->type && ++counter == 2) || (!it2->type && counter-- == 2)) acts.insert(it1, *it2);
                ++it2;
            }
        }
        return *this;
    }

    TimeSec &operator|=(const TimeSec &other) {
        int32_t counter = 0;
        for (auto it1 = acts.cbegin(), it2 = other.acts.cbegin(); it1 != acts.end() || it2 != other.acts.end();) {
            if (it1 != acts.end() && (it2 == other.acts.end() || it1->time < it2->time ||
                                      (it1->time == it2->time && (it1->type || !it2->type)))) {
                if ((it1->type && counter++ > 0) || (!it1->type && --counter > 0)) it1 = acts.erase(it1);
                else ++it1;
            } else {
                if ((it2->type && counter++ == 0) || (!it2->type && --counter == 0)) acts.insert(it1, *it2);
                ++it2;
            }
        }
        for (auto it = acts.cbegin(); it != acts.end() && next(it) != acts.end(); ++it)
            if (!it->type && next(it)->type && it->time == next(it)->time)
                it = acts.erase(acts.erase(it));
        return *this;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n, m;
    cin >> n >> m;
    map<int32_t, TimeSec> pre_time_secs, now_time_secs;
    for (int32_t i = 0, ct; i < n; ++i) {
        cin >> ct;
        int32_t min_day = (ct + 2) / m + ((ct + 2) % m != 0) - 2, max_day = ct / m;
        if (!i) {
            for (auto day = min_day; day <= max_day; ++day) {
                int32_t min_k = max<int32_t>(ct - day * m - m + 1, 0), max_k = min<int32_t>(ct - day * m, m - 1);
                pre_time_secs.emplace(day, TimeSec(min_k, max_k));
            }
            continue;
        }
        now_time_secs.clear();
        for (auto day = min_day; day <= max_day; ++day) {
            int32_t min_k = max<int32_t>(ct - day * m - m + 1, 0), max_k = min<int32_t>(ct - day * m, m - 1);
            auto it1 = pre_time_secs.find(day), it2 = pre_time_secs.find(day - 1);
            if (it1 == pre_time_secs.end()) swap(it1, it2);
            if (it1 != pre_time_secs.end() && it2 != pre_time_secs.end()) {
                TimeSec ts(std::move(it2->second));
                ts |= it1->second;
                ts &= TimeSec(min_k, max_k);
                if (!ts.acts.empty()) now_time_secs.emplace(day, std::move(ts));
            } else if (it1 != pre_time_secs.end()) {
                if (it1->first == day - 1) {
                    TimeSec ts(std::move(it1->second));
                    ts &= TimeSec(min_k, max_k);
                    if (!ts.acts.empty()) now_time_secs.emplace(day, std::move(ts));
                } else {
                    TimeSec ts(it1->second);
                    ts &= TimeSec(min_k, max_k);
                    if (!ts.acts.empty()) now_time_secs.emplace(day, std::move(ts));
                }
            }
        }
        pre_time_secs.swap(now_time_secs);
        if (pre_time_secs.empty()) break;
    }
    if (pre_time_secs.empty()) {
        cout << "-1";
        return 0;
    }
    int32_t min_k = m;
    for (const auto &tss: pre_time_secs)
        if (tss.second.acts.begin()->time < min_k)
            min_k = tss.second.acts.begin()->time;
    cout << min_k;
    return 0;
}
