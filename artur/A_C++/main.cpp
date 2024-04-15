#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

struct Way {
    int32_t start_time, way_time, to;
};

int main() {
    string temp, sa, sb, sc, sd, fta, ftb, sta, stb;
    getline(cin, temp);
    int32_t n = stoi(temp);
    map<string, int32_t> towns_by_names;
    vector<string> names_by_id;
    names_by_id.reserve(n);
    vector<vector<Way>> graph;
    int32_t from_town = 1e9, target_town = 1e9;
    graph.reserve(n);
    for (int32_t _ = 0; _ < n; ++_) {
        getline(cin, temp);
        int32_t a = temp.find('|'), b = temp.find('|', a + 1), c = temp.find('|', b + 1);
        sa = temp.substr(0, a);
        sb = temp.substr(a + 1, b - a - 1);
        sc = temp.substr(b + 1, c - b - 1);
        sd = temp.substr(c + 1);
        int32_t fid, sid;
        auto fit = towns_by_names.find(sa);
        if (fit != towns_by_names.end()) fid = fit->second;
        else {
            fid = towns_by_names.emplace(sa, towns_by_names.size()).first->second;
            graph.emplace_back();
            if (sa == "Moscow") from_town = fid;
            if (sa == "Malokribirsk") target_town = fid;
            names_by_id.emplace_back(sa);
        }
        auto sit = towns_by_names.find(sb);
        if (sit != towns_by_names.end()) sid = sit->second;
        else {
            sid = towns_by_names.emplace(sb, towns_by_names.size()).first->second;
            graph.emplace_back();
            if (sb == "Malokribirsk") target_town = sid;
            if (sb == "Moscow") from_town = sid;
            names_by_id.emplace_back(sb);
        }
        int32_t ftid = sc.find(':'), stid = sd.find(':');
        int32_t ft = stoi(sc.substr(0, ftid)) * 60 + stoi(sc.substr(ftid + 1)),
                st = stoi(sd.substr(0, stid)) * 60 + stoi(sd.substr(stid + 1));
        graph[fid].emplace_back(ft, st, sid);
    }
    if (from_town == 1e9 || target_town == 1e9) {
        cout << 0;
        return 0;
    }
    multimap<int32_t, pair<int32_t, int32_t>> queue;
    queue.emplace(0, pair<int32_t, int32_t>(from_town, 1e9));
    vector<int32_t> min_times(graph.size(), 1e9);
    vector<int32_t> pre_town(graph.size(), 1e9);
    while (!queue.empty()) {
        auto [tt, ss] = *queue.begin();
        auto [town, cur_pre_t] = ss;
        queue.erase(queue.begin());
        if (tt >= min_times[town] || tt > 5520) continue;
        min_times[town] = tt;
        pre_town[town] = cur_pre_t;
        for (auto [start_time, way_time, to]: graph[town]) {
            if (tt % 1440 >= start_time || (tt + 30) % 1440 < 30 || (tt + 30) % 1440 > start_time)
                queue.emplace((tt / 1440 + 1) * 1440 + start_time + way_time, pair<int32_t, int32_t>(to, town));
            else queue.emplace(tt / 1440 * 1440 + start_time + way_time, pair<int32_t, int32_t>(to, town));
        }
    }
    if (min_times[target_town] == 1e9) cout << 0;
    else {
        list<int32_t> sway;
        int32_t tt = target_town;
        while (tt != 1e9) {
            sway.push_back(tt);
            tt = pre_town[tt];
        }
        vector<int32_t> vway(sway.rbegin(), sway.rend());
        for (int32_t i = 0; i < vway.size(); ++i) {
            cout << names_by_id[vway[i]];
            if (i + 1 < vway.size()) cout << '|';
        }
        cout << "\n" << min_times[target_town] / 60 << ":" << (min_times[target_town] % 60 < 10 ? "0" : "") <<
             min_times[target_town] % 60;
    }
    return 0;
}
