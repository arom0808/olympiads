#include <iostream>
#include <vector>

using namespace std;

int main(){
  int32_t n;
  uint32_t a0;
  cin >> n >> a0;
  vector<uint32_t> a(n);
  a[0] = a0;
  for (int32_t i = 1; i < n; ++i) a[i] = a[i - 1] * 214013u + 2531011u;
  int64_t res = 0;
  for(int32_t i =0; i < n;++i){
    int32_t left_pos=i, right_pos=i;
    while(left_pos>=0 && left_pos
  }
}