#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long gcd(long long a,long long b) {
    a=abs(a);
    b=abs(b);
    while (b>0) {
        a%=b;
        swap(a,b);
    }
    return a;
}

struct Frac {
    long long a,b;
    void init(int _a,int _b) {
        a=_a;
        b=_b;
    }
    void upd() {
        if (b<0) {
            a=-a;
            b=-b;
        }
        long long c=gcd(a,b);
        if (c!=0) {
            a /= c;
            b /= c;
        }
    }
};
Frac Kmul(Frac i,Frac j) {
    Frac c;
    c.init(i.a*j.a,i.b*j.b);
    c.upd();
    return c;
}
Frac Ksum(Frac i,Frac j) {
    Frac c;
    c.init(i.a*j.b+j.a*i.b,i.b*j.b);
    c.upd();
    return c;
}
Frac Ksub(Frac i,Frac j) {
    Frac c;
    c.init(i.a*j.b-j.a*i.b,i.b*j.b);
    c.upd();
    return c;
}
Frac Kdiv(Frac i,Frac j) {
    Frac c;
    c.init(i.a*j.b,i.b*j.a);
    c.upd();
    return c;
}
bool islower(Frac i,Frac j) {
    return i.a*j.b<j.a*i.b;
}
bool isnotupper(Frac i,Frac j) {
    return islower(i,j) || (!islower(i,j) && !islower(j,i));
}

int n,q;
int lineinters(int x1,int y1,int x2,int y2,int I) {
    if (x1==x2) {
        if (x1==-I || x1==I) return 1;
        else if (-I<x1 && x1<I) return 2;
        else return 0;
    } else {
        Frac X1,Y1,X2,Y2;
        X1.init(x1,1);
        Y1.init(y1,1);
        X2.init(x2,1);
        Y2.init(y2,1);
        Frac k=Kdiv(Ksub(Y1,Y2),Ksub(X1,X2));
        Frac b=Ksub(Y1,Kmul(k,X1));
        long long _k[4]={1,-1,1,-1},_b[4]={-I,I,I,-I},_x1[4]={-I,0,0,-I},_x2[4]={0,I,I,0},_y1[4]={0,0,-I,-I},_y2[4]={I,I,0,0};
        vector <pair<pair<int,int>,pair<int,int>>> ans;
        for (int i=0;i<4;i++) {
            Frac k1,b1;
            k1.init(_k[i],1);
            b1.init(_b[i],1);
            if (islower(k1,k) || islower(k,k1)) {
                Frac X=Kdiv(Ksub(b,b1),Ksub(k1,k));
                Frac Y=Ksum(Kmul(k,X),b);
                Frac gx1,gx2,gy1,gy2;
                gy1.init(_x1[i],1);
                gy2.init(_x2[i],1);
                gx1.init(_y1[i],1);
                gx2.init(_y2[i],1);
                if (isnotupper(gx1,X) && isnotupper(X,gx2) && isnotupper(gy1,Y) && isnotupper(Y,gy2)) {
                    ans.push_back({{X.a,X.b},{Y.a,Y.b}});
                }
            }
        }
        sort(ans.begin(),ans.end());
        ans.resize(unique(ans.begin(),ans.end())-ans.begin());
        return ans.size();
    }
}

int main() {
    cin >> n >> q;
    for (int i=0;i<q;i++) {
        long long x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long anss=0;
        for (int j=1;j<=n;j++) {
            anss+= lineinters(x1,y1,x2,y2,j);
        }
        /*
        long long l=0;
        long long r=n;
        while (r-l>1) {
            long long M=l+(r-l)/2;
            if (lineinters(x1,y1,x2,y2,M)==0) l=M;
            else r=M;
        }
        anss+=lineinters(x1,y1,x2,y2,r);
        if (r<n) {
            anss+=2*(n-r);
        }*/
        cout << anss << "\n";
    }
}