#include <iostream>

int main() {
    std::uint32_t number;
    std::cin >> number;
    std::uint32_t first_in_column = 1, column_size = 1;
    while (number >= first_in_column + column_size) {
        first_in_column += column_size;
        column_size += 2;
    }
    std::uint32_t number_index_in_column = number - first_in_column;
    bool is_top_exists = number_index_in_column != 0;
    bool is_bottom_exists = number + 1 != first_in_column + column_size;
    bool is_left_exists = is_top_exists && is_bottom_exists;
    std::uint32_t left_number, top_number, bottom_number, right_number;
    if (is_top_exists) top_number = number - 1;
    if (is_bottom_exists) bottom_number = number + 1;
    if (is_left_exists) left_number = number - column_size + 1;
    right_number = first_in_column + column_size + number_index_in_column + 1;
    if (is_left_exists) std::cout << left_number << " ";
    if (is_top_exists) std::cout << top_number << " ";
    if (is_bottom_exists) std::cout << bottom_number << " ";
    std::cout << right_number;
    return 0;
}
