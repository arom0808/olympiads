import math

def gcd(a,b):
    a=abs(a)
    b=abs(b)
    while (b>0):
        a%=b
        a,b = b,a
    return a

class Frac:
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def init(self, _a, _b):
        self.a = _a
        self.b = _b
    def upd(self):
        if (self.b<0):
            self.a=-self.a
            self.b=-self.b
        c=gcd(self.a,self.b)
        if (c!=0):
            self.a //= c
            self.b //= c

def Kmul(i,j):
    c = Frac(0,1)
    c.init(i.a*j.a,i.b*j.b)
    c.upd()
    return c

def Ksum(i,j):
    c = Frac(0,1)
    c.init(i.a*j.b+j.a*i.b,i.b*j.b)
    c.upd()
    return c

def Ksub(i,j):
    c = Frac(0,1)
    c.init(i.a*j.b-j.a*i.b,i.b*j.b)
    c.upd()
    return c

def Kdiv(i,j):
    c = Frac(0,1)
    c.init(i.a*j.b,i.b*j.a)
    c.upd()
    return c

def islower(i,j):
    return i.a*j.b<j.a*i.b

def isnotupper(i,j):
    return islower(i,j) or (not islower(i,j) and not islower(j,i))

n,q = map(int, input().split())
def lineinters(x1,y1,x2,y2,I):
    if (x1==x2):
        if (x1==-I or x1==I): return 1
        elif (-I<x1 and x1<I): return 2
        else: return 0
    else:
        X1,Y1,X2,Y2 = Frac(0,1), Frac(0,1), Frac(0,1), Frac(0,1)
        X1.init(x1,1)
        Y1.init(y1,1)
        X2.init(x2,1)
        Y2.init(y2,1)
        k = Kdiv(Ksub(Y1,Y2),Ksub(X1,X2))
        b = Ksub(Y1,Kmul(k,X1))


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

            x = Kdiv(Ksub(Frac(-I,1),b),k)
            y = Kdiv(Ksub(Frac(I,1),b),k)
            if (isnotupper(x,X1) or isnotupper(X2,x) or isnotupper(y,X1) or isnotupper(X2,y)): return 0
            else: return 2

for i in range(q):
    x1,y1,x2,y2 = map(int, input().split())
    ans=0
    for j in range(1,n+1):
        ans+=lineinters(x1,y1,x2,y2,j)
    print(ans)
