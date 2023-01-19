#include <iostream>

int main() {
    std::uint32_t n, k ;
    std::cin>>n>>k;
    std::uint32_t result = k, buf;
    for(std::uint32_t i =  0; i < n; ++i){
        std::cin>>buf;
        if(buf>result) result=0;
        else result-=buf;
    }
    std::cout<<result;
    return 0;
}
