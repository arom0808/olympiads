/* ну же, пострайся, постарайся */
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <set>
#include <map>
#include <unordered_map>
#include <deque>
#include <bitset>
#include <iomanip>
#include <limits>
#include <queue>
#include <cmath>
#include <ctime>
#include <numeric>
#include <string>
#include <chrono>
#include <tuple>
#include <random>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using namespace std;

#define pb push_back
#define all(array) array.begin(), array.end()
//const ll MOD = 1000000007;
const ll MOD = 998244353;
const ll inf = 1e18;
const ld eps = 1e-8;
ld pi = asin(0.5) * (ld)6;

//std::mt19937 rnd(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
std::mt19937_64 rnd(78946);

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

const int maxn = 1000;
int full_table[maxn][maxn];
int n,m;
int near_top_wall[maxn][maxn],
    near_right_wall[maxn][maxn],
    near_bottom_wall[maxn][maxn],
    near_left_wall[maxn][maxn];
bool used[maxn][maxn];
bool used_c[maxn*maxn];
int comp[maxn][maxn];
bool is_comp_can_port[maxn*maxn];
vector<int> comp_telep_pos[maxn*maxn];
int comp_cnt=0;
struct Els{
    int fff[5];
    int& operator[](int i){return fff[i];}
    Els(int a, int b, int c, int d, int e){
        fff[0] = a;
        fff[1] = b;
        fff[2] = c;
        fff[3] = d;
        fff[4] = e;
    }
};
vector<pair<int, Els>> g[maxn*maxn];
pair<int,int> what_from[maxn*maxn];
vector<pair<int, int>> way;

struct CompWay{
    int si, sj, gi,gj,dg,ti,tj,dt;
};

bool dfs1(int i, int j, int c_id){
    if(full_table[i][j]==2) {
        is_comp_can_port[c_id] = true;
        return true;
    }
    if(used[i][j] || full_table[i][j]) return false;
    used[i][j] = true;
    comp[i][j] = c_id;
    if (i+1<n && dfs1(i+1,j,c_id)) comp_telep_pos[c_id] = {i,j,2};
    if (i-1>=0 && dfs1(i-1,j,c_id)) comp_telep_pos[c_id] = {i,j,0};
    if(j+1<m && dfs1(i,j+1,c_id)) comp_telep_pos[c_id] = {i,j,1};
    if(j-1>=0 && dfs1(i,j-1,c_id)) comp_telep_pos[c_id] = {i,j,3};
    return false;
}

bool dfs2(int i, int j, int fi, int fj){
    if(used[i][j] || full_table[i][j]) return false;
    used[i][j]  =true;
    if(i==fi&&j==fj) return true;
    if(i+1 < n){
        way.emplace_back(0, 2);
        if(dfs2(i+1,j,fi,fj)) return true;
        way.pop_back();
    }
    if(i-1 >=0){
        way.emplace_back(0, 0);
        if(dfs2(i-1,j,fi,fj)) return true;
        way.pop_back();
    }
    if(j+1<m){
        way.emplace_back(0, 1);
        if(dfs2(i,j+1,fi,fj)) return true;
        way.pop_back();
    }
    if(j-1>=0){
        way.emplace_back(0, 3);
        if(dfs2(i,j-1,fi,fj)) return true;
        way.pop_back();
    }
}

void solve() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin>>n>>m;
    // for(auto&el:comp_telep_pos)
    char c;
    for(int i = 0; i < n;++i){
        for(int j = 0; j < m; ++j){
            cin>>c;
            if(c=='G') full_table[i][j] = 1;
            if(c=='W') full_table[i][j] = 2; 
        }
    }
    for(int i = 0; i < n; ++i){
        for(int lw =0, j = 0; j < m;++j){
            if(full_table[i][j]==2) lw = j;
            near_left_wall[i][j] = lw;
        }
        for(int lw=m-1, j = m-1; j >=0; --j){
            if(full_table[i][j]==2) lw = j;
            near_right_wall[i][j] = lw;
        }
    }
    for(int j = 0; j < m; ++j){
        for(int lw =0, i = 0; i < n;++i){
            if(full_table[i][j]==2) lw = i;
            near_top_wall[i][j] = lw;
        }
        for(int lw=n-1, i = n-1; i >=0; --i){
            if(full_table[i][j]==2) lw = i;
            near_bottom_wall[i][j] = lw;
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(full_table[i][j]==0 && used[i][j]==false) 
                dfs1(i,j,comp_cnt++);
    for(int i = 0; i < n;++i){
        for(int j =0; j < m; ++j){
            if(full_table[i][j] || !is_comp_can_port[comp[i][j]]) continue;
            if(!full_table[near_top_wall[i][j] + 1][j]
                && comp[near_top_wall[i][j] + 1][j] != comp[i][j]) 
                g[comp[i][j]].emplace_back(comp[near_top_wall[i][j] + 1][j],
                        Els(i,j,0,near_top_wall[i][j] + 1,j));
            if(!full_table[near_bottom_wall[i][j] - 1][j]
                && comp[near_bottom_wall[i][j] - 1][j] != comp[i][j]) 
                g[comp[i][j]].emplace_back(comp[near_bottom_wall[i][j] - 1][j],
                        Els(i,j,2,near_bottom_wall[i][j] - 1,j));
            if(!full_table[i][near_left_wall[i][j]+1]
                && comp[i][near_left_wall[i][j]+1] != comp[i][j]) 
                g[comp[i][j]].emplace_back(comp[i][near_left_wall[i][j]+1],
                        Els(i,j,3,i,near_left_wall[i][j]+1));
            if(!full_table[i][near_right_wall[i][j]-1]
                && comp[i][near_left_wall[i][j]-1] != comp[i][j]) 
                g[comp[i][j]].emplace_back(comp[i][near_left_wall[i][j]-1],
                        Els(i,j,3,i,near_left_wall[i][j]-1));
        }
    }
    int si, sj, fi, fj;
    cin>>si>>sj>>fi>>fj, --si,--sj,--fi,--fj;
    int sp = comp[si][sj], fp=comp[fi][fj];
    for(int i = 0; i < maxn*maxn;++i) what_from[i].first=-1;
    for(auto &el:used_c) el = false;
    deque<int> que;
    que.push_back(sp);
    used_c[sp] = true;
    while(!que.empty() && !used_c[fp]){
        auto c_id = que.front();
        que.pop_front();
        for (int e_id = 0;  e_id < g[c_id].size(); ++e_id){
            if(used_c[g[c_id][e_id].first]) continue;
            used_c[g[c_id][e_id].first] = true;
            what_from[g[c_id][e_id].first] = {c_id,e_id};
            que.push_back(g[c_id][e_id].first);
        }
    }
    if(!used_c[fp]){
        cout<<"-1\n";
        return;
    }
    vector<CompWay> comp_way;
    comp_way.emplace_back(-1,-1,-1,-1,-1,fi,fj,-1);
    int now_comp= fp;
    while(now_comp!=sp){
        auto wff = what_from[now_comp].first, wfs = what_from[now_comp].second;
        comp_way.back().si=g[wff][wfs].second[3];
        comp_way.back().sj=g[wff][wfs].second[4];
        if(now_comp!=fp){
            // comp_way.back().ti = comp_telep_pos[now_comp][0];
            // comp_way.back().tj = comp_telep_pos[now_comp][1];
            // comp_way.back().dt = comp_telep_pos[now_comp][2];
            comp_way.back().ti = comp_way.back().si;
            comp_way.back().tj = comp_way.back().sj;
            comp_way.back().dt = g[wff][wfs].second[2];
        }
        comp_way.emplace_back(-1,-1,g[wff][wfs].second[0],
                                    g[wff][wfs].second[1],
                                    g[wff][wfs].second[2],-1,-1,-1);
    }
    if(comp_way.size()>1){
        comp_way.back().si = si;
        comp_way.back().sj = sj;
        comp_way.back().ti = comp_telep_pos[sp][0];
        comp_way.back().tj = comp_telep_pos[sp][1];
        comp_way.back().dt = comp_telep_pos[sp][2];
    }
    reverse(comp_way.begin(),comp_way.end());
    for(auto &row:used) for(auto&el:row) el= false;
    bool nfpc = false;
    for(int i =0; i +1 < comp_way.size(); ++i){
        dfs2(comp_way[i].si,comp_way[i].sj,comp_way[i].gi, comp_way[i].gj);
        way.emplace_back(1+nfpc, comp_way[i].dg);
        dfs2(comp_way[i].gi, comp_way[i].gj, comp_way[i].ti, comp_way[i].tj);
        if(i==0) way.emplace_back(1+(!nfpc), comp_way[i].dt);
        way.emplace_back(0,comp_way[i].dt);
        nfpc = !nfpc;
    }
    for(auto el:way){
        auto s_type=el.first;
        auto s_fir = el.second;
        if(s_type==0) cout<<"M";
        else if(s_type==1) cout<<" ";
        else cout<<"B";
        if(s_fir == 0) cout<<"U\n";
        if(s_fir == 1) cout<<"R\n";  
        if(s_fir == 2) cout<<"D\n";  
        if(s_fir == 3) cout<<"L\n";  
    }
}


int main() {
    #ifdef LOCAL
    freopen("_INPUT.TXT", "r", stdin);
    freopen("_OUTPUT.TXT", "w", stdout);
    cout << fixed << setprecision(8);
    clock_t timer = clock();
#else
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(8);
#endif
    solve();
#ifdef LOCAL
    cout << endl
         << "Execution time: " << (long double) (clock() - timer) / CLOCKS_PER_SEC;
#endif
    return 0;
}