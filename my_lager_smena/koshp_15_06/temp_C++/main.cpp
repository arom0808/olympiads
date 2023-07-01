#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN=15;

int dp[1<<MAXN];
int n,m,t;
vector <int> a,b,c;
int isT=0;
void genval(int i,int cnt) {
    if (i==n) {
        for (int j=0;j<n;j++) {
            if (isT&(1<<j)) {
                if (dp[isT^(1<<j)]>=a[j]) dp[isT]=max(dp[isT],dp[isT^(1<<j)]-a[j]+b[j]);
            }
        }
    } else if (i==n-cnt) {
        isT*=2;
        isT+=1;
        genval(i+1,cnt-1);
        isT/=2;
    } else {
        isT*=2;
        genval(i+1,cnt);
        isT++;
        genval(i+1,cnt-1);
        isT/=2;
    }
}
int main() {
    cin >> n >> m >> t;
    a.resize(n);
    b.resize(n);
    c.resize(m);
    for (int i=0;i<n;i++) {
        cin >> a[i];
    }
    for (int i=0;i<n;i++) {
        cin >> b[i];
    }
    for (int i=0;i<m;i++) {
        cin >> c[i];
    }
    for (int i=1;i<(1<<n);i++) dp[i]=0;
    dp[0]=t;
    for (int i=1;i<=n;i++) {
        genval(0,i);
    }
    int maxd=0;
    for (int i=0;i<(1<<n);i++) {
        maxd=max(maxd,dp[i]);
    }
    int csum=0;
    for (int i=0;i<m;i++) csum+=c[i];
    if (csum<=dp[(1<<n)-1]) cout << "SUPER\n";
    else if (csum<=maxd) cout << "SCHOOL\n";
    else cout << "EPIC FAIL\n";
}