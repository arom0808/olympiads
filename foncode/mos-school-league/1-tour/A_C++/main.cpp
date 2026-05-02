// #pragma GCC optimize("Ofast,O3")
/* ну же, пострайся, постарайся */
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <deque>
#include <bitset>
#include <iomanip>
#include <queue>
#include <cmath>
#include <ctime>
#include <numeric>
#include <string>
#include <chrono>
#include <random>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using namespace std;

#define pb push_back
#define all(array) array.begin(), array.end()
//const ll MOD = 1000000007;
const ll MOD = 998244353;
const ll inf = 1e9;
const ld eps = 1e-8;
ld pi = asin(0.5) * (ld)6;

//std::mt19937 rnd(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
std::mt19937 rnd(78946);

template <typename T1>
istream &operator>>(istream &in, vector<T1> &a) {
    for (T1 &i : a) in >> i;
    return in;
}
template <typename T1>
ostream &operator<<(ostream &out, vector<T1> &a) {
    for (T1 &i : a) out << i << " ";
    return out;
}

const int maxn = 3e5;
// namespace St{
//     struct Node{
//         int sum = 0;
//         Node* left=nullptr, *right=nullptr;
//     }
//     constexpr int max_nodes_cnt = 5e7;
//     Node tree[max_nodes_cnt];
//     int used_nodes, size;

//     Node* get_new_node(){
//         return &tree[used_nodes++];
//     }

//     Node* init(int _size){
//         size = _size;
//         return get_new_node();
//     }

//     void check_add_childs(Node* v){
//         if(!v->left) v->left = get_new_node();
//         if(!v->right) v->right = get_new_node();
//     }

//     Node* add(Node *v, int l, int r, int pos, int val){
//         if(l>=pos+1||pos>=r) return v;
//         Node *cur_node= get_new_node();
//         if(l==pos && r==pos+1){
//             cur_node->sum = v->sum + val;
//             return cur_node;
//         }
//         check_add_childs(cur_node);

//     }
// }

vector<int> raw_xs, raw_ys;
struct Pereg{
    int x1, y1, x2, y2;
    double get_in_x(int x){
        return static_cast<double>(raw_ys[y2]-raw_ys[y1])*(raw_xs[x]-raw_xs[x1])/(raw_xs[x2]-raw_xs[x1])+raw_ys[y1];
    }
    int bottom(){
        return std::min(y1,y2);
    }
};

Pereg peregs[maxn];


struct Action{
    int type; // 0 - убрать, 1 - добавить, 2 - нижняя граница
    int seg_id;

    int get_pos(){
        if(type ==0) return peregs[seg_id].x2+1;
        if(type==1) return peregs[seg_id].x1;
        if(peregs[seg_id].y1< peregs[seg_id].y2) return peregs[seg_id].x1;
        return peregs[seg_id].x2;
    }

    bool operator<(Action other){
        if(get_pos()!=other.get_pos()) return get_pos()<other.get_pos();
        return type< other.type;
    }
};

struct NextSeg{
    bool tt; // 0 - no seg, 1 - seg
    int v; // x or next_seg_id
};
NextSeg next_seg[maxn];

int n,m;

int get_zip_val(const vector<int>& rzvs, int val){
    return distance(rzvs.begin(), lower_bound(rzvs.begin(), rzvs.end(), val));
}

int dp[maxn];
int get_dp_val(int seg_id){
    if(dp[seg_id]!=inf) return dp[seg_id];
    if(!next_seg[seg_id].tt) return dp[seg_id] = next_seg[seg_id].v;
    return dp[seg_id] = get_dp_val(next_seg[seg_id].v);
}


void solve() {
    cin>>n;
    for(int i = 0; i < n; ++i) cin>>peregs[i].x1>>peregs[i].y1>>peregs[i].x2>>peregs[i].y2;
    cin>>m;
    vector<int> queries(m);
    for(auto&el:queries) cin>>el;
    raw_xs.resize(n*2), raw_ys.resize(n*2);
    for(int i = 0; i < n;++i) raw_xs[i*2] = peregs[i].x1, raw_xs[i*2+1] = peregs[i].x2;
    for(int i = 0; i < n;++i) raw_ys[i*2] = peregs[i].y1, raw_ys[i*2+1] = peregs[i].y2;
    raw_xs.insert(raw_xs.end(), queries.begin(), queries.end());
    sort(raw_xs.begin(), raw_xs.end());
    sort(raw_ys.begin(), raw_ys.end());
    raw_xs.erase(unique(raw_xs.begin(), raw_xs.end()), raw_xs.end());
    raw_ys.erase(unique(raw_ys.begin(), raw_ys.end()), raw_ys.end());
    for(int i =0; i < n;++i){
        peregs[i].x1 = get_zip_val(raw_xs, peregs[i].x1);
        peregs[i].x2 = get_zip_val(raw_xs, peregs[i].x2);
        peregs[i].y1 = get_zip_val(raw_ys, peregs[i].y1);
        peregs[i].y2 = get_zip_val(raw_ys, peregs[i].y2);
    }
    for(auto&el:queries) el = get_zip_val(raw_xs, el);
    vector<Action> actions(n*3);
    for(int i = 0; i < n;++i){
        const auto& cper = peregs[i];
        actions[i*3] = Action{1, i};
        actions[i*3+1] = Action{0, i};
        actions[i*3+2] = Action{2, i};
    }
    sort(actions.begin(), actions.end());
    map<int, int> top_seg_for_x;
    int for_cmp_x = 0;
    auto cmp = [&](int a, int b) {
        return peregs[a].get_in_x(for_cmp_x) < peregs[b].get_in_x(for_cmp_x);
    };
    set<int, decltype(cmp)> sorted_segs(cmp);
    for(auto & act:actions){
        if(act.type==0){
            auto ttt = top_seg_for_x.find(act.get_pos()-1);
            if(ttt == top_seg_for_x.end()) top_seg_for_x.emplace(act.get_pos()-1, sorted_segs.empty()?(-1):*sorted_segs.rbegin());
            else ttt->second = std::max(ttt->second, sorted_segs.empty()?(-1):*sorted_segs.rbegin());
            sorted_segs.erase(act.seg_id);
            continue;
        }
        if(act.type==1){
            for_cmp_x = act.get_pos();
            sorted_segs.insert(act.seg_id);
        }
        auto ttt = top_seg_for_x.find(act.get_pos());
        if(ttt == top_seg_for_x.end()) top_seg_for_x.emplace(act.get_pos(), sorted_segs.empty()?(-1):*sorted_segs.rbegin());
        else ttt->second = std::max(ttt->second, sorted_segs.empty()?(-1):*sorted_segs.rbegin());
        for_cmp_x = act.get_pos();
        if(act.type==1) continue;
        auto it = sorted_segs.lower_bound(act.seg_id);
        if(it==sorted_segs.begin()){
            next_seg[act.seg_id] = NextSeg{false, for_cmp_x};
        }else{
            next_seg[act.seg_id] = NextSeg{true, *prev(it)};
        }
    }
    for(int i = 0; i < n;++i) dp[i] = inf;
    for(auto &que: queries){
        auto it = top_seg_for_x.lower_bound(que);
        if(it == top_seg_for_x.end() || it->second==-1) {
            cout<<raw_xs[que]<<"\n";
        }else if (peregs[it->second].x1 <= que){
            cout<<raw_xs[get_dp_val(it->second)]<<"\n";
        }else {
            cout<<raw_xs[que]<<"\n";
        }
    }
}

int main() {
    #ifdef LOCAL
    freopen("_INPUT.TXT", "r", stdin);
    freopen("_OUTPUT.TXT", "w", stdout);
    cout << fixed << setprecision(10);
    clock_t timer = clock();
#else
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
#endif
    solve();
#ifdef LOCAL
    cout << endl
         << "Execution time: " << (long double) (clock() - timer) / CLOCKS_PER_SEC;
#endif
    return 0;
}