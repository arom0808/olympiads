#include <iostream>
#include <vector>

int main() {
    std::uint32_t N,M;
    std::cin>>N>>M;
    std::vector<std::uint32_t> counts(N,0);
    std::uint32_t temp_int;
    for(std::uint32_t i = 0; i < 2*M;++i){
        std::cin>>temp_int;
        ++counts[temp_int-1];
    }
    for(const auto&num:counts) std::cout<<num<<" ";
    return 0;
}
