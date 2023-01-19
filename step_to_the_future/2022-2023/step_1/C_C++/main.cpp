#include <iostream>
#include <bitset>

std::uint32_t GetBitSize(std::uint32_t number) {
    std::uint32_t result = 0;
    while (number != 0) {
        number /= 2;
        ++result;
    }
    return result;
}

int main() {
    std::uint32_t input_number;
    std::cin >> input_number;
    std::bitset<32> bits(input_number);
    std::bitset<32> result_bits;
    std::uint32_t number_bit_size = GetBitSize(input_number);
    number_bit_size = (number_bit_size / 4 + (number_bit_size % 4 == 0 ? 0 : 1)) * 4;
    for (std::uint32_t i = 0, r_i = 0; i < number_bit_size; i += 4, r_i += 3) {
        bool is_two_del = false;
        if (bits[i + 1]) is_two_del = !is_two_del;
        if (bits[i + 2]) is_two_del = !is_two_del;
        if (bits[i + 3]) is_two_del = !is_two_del;
        if (bits[i] != is_two_del) {
            std::cout << -1;
            return 0;
        }
        result_bits[r_i] = bits[i + 1];
        result_bits[r_i + 1] = bits[i + 2];
        result_bits[r_i + 2] = bits[i + 3];
    }
    std::cout << result_bits.to_ulong();
    return 0;
}
