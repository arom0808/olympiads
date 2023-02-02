#include <iostream>
#include <vector>
#include <random>

std::random_device dev;
// std::uint32_t seed = 123;
auto seed = dev();
std::mt19937 rng(seed);

using Row = std::vector<std::int32_t>;
using Field = std::vector<Row>;

std::uint32_t NumberDigitsCount(std::int32_t num) {
    if (num == 0) return 1;
    std::uint32_t digits_cnt = 0;
    if (num < 0) ++digits_cnt;
    while (num) {
        num /= 10;
        ++digits_cnt;
    }
    return digits_cnt;
}

const std::int32_t glob_min_value = -10000, glob_max_value = 10000;
const std::uint32_t glob_max_value_digits_count = std::max(NumberDigitsCount(glob_min_value),
                                                           NumberDigitsCount(glob_max_value));

struct Coords {
    std::uint32_t x, y;

    explicit Coords(std::uint32_t x = 0, std::uint32_t y = 0) : x(x), y(y) {}
};

struct Request {
    Coords left_top, right_bottom;

    explicit Request(const Coords &left_top = Coords(), const Coords &right_bottom = Coords())
            : left_top(left_top), right_bottom(right_bottom) {}
};

Field &GenerateRandomField(Field &field) {
    std::uniform_int_distribution dist_size(100, 10000), dist_value(glob_min_value, glob_max_value);
    std::uint32_t x_size = dist_size(rng), y_size = dist_size(rng);
    field.clear();
    field.resize(y_size, Row(x_size));
    for (auto &&row: field) for (auto &&value: row) value = dist_value(rng);
    return field;
}

Request &GenerateRandomRequest(const Field &field, Request &request) {
    std::uniform_int_distribution dist_left_x(0, static_cast<std::int32_t>(field[0].size() - 1));
    std::uniform_int_distribution dist_top_y(0, static_cast<std::int32_t>(field.size() - 1));
    request.left_top.x = dist_left_x(rng);
    request.left_top.y = dist_top_y(rng);
    std::uniform_int_distribution dist_right_x(static_cast<std::int32_t>(request.left_top.x + 1),
                                               static_cast<std::int32_t>(field[0].size()));
    std::uniform_int_distribution dist_bottom_y(static_cast<std::int32_t>(request.left_top.y + 1),
                                                static_cast<std::int32_t>(field.size()));
    request.right_bottom.x = dist_right_x(rng);
    request.right_bottom.y = dist_bottom_y(rng);
    return request;
}

inline std::int32_t GetSumFromTop(const Field &sums_field, const Coords &coords) {
    if (coords.y == 0) return 0;
    return sums_field[coords.y - 1][coords.x];
}

inline std::int32_t GetSumFromLeft(const Field &sums_field, const Coords &coords) {
    if (coords.x == 0) return 0;
    return sums_field[coords.y][coords.x - 1];
}

inline std::int32_t GetSumFromTopAndLeft(const Field &sums_field, const Coords &coords) {
    if (coords.x == 0 || coords.y == 0) return 0;
    return sums_field[coords.y - 1][coords.x - 1];
}

inline void UpdateSumInCell(const Field &field, Field &sums_field, const Coords &coords) {
    sums_field[coords.y][coords.x] = GetSumFromTop(sums_field, coords) + GetSumFromLeft(sums_field, coords) -
                                     GetSumFromTopAndLeft(sums_field, coords) + field[coords.y][coords.x];
}

Field &GenerateSumsField(const Field &field, Field &sums_field) {
    sums_field.clear();
    if (field.empty()) return sums_field;
    sums_field.resize(field.size(), Row(field[0].size(), 0));
    sums_field[0][0] = field[0][0];
    for (std::uint32_t i = 0; i < std::min(field.size(), field[0].size()); ++i) {
        UpdateSumInCell(field, sums_field, Coords{i, i});
        if (i + 1 < field[0].size())
            for (std::uint32_t x = i + 1, y = i; x < field[0].size(); ++x)
                UpdateSumInCell(field, sums_field, Coords{x, y});
        if (i + 1 < field.size())
            for (std::uint32_t x = i, y = i + 1; y < field.size(); ++y)
                UpdateSumInCell(field, sums_field, Coords{x, y});
    }
    return sums_field;
}

std::int32_t SoluteRequest(const Field &sums_field, const Request &request) {
    return sums_field[request.right_bottom.y - 1][request.right_bottom.x - 1] -
           GetSumFromLeft(sums_field, Coords(request.left_top.x, request.right_bottom.y - 1)) -
           GetSumFromTop(sums_field, Coords(request.right_bottom.x - 1, request.left_top.y)) +
           GetSumFromTopAndLeft(sums_field, request.left_top);
}

std::int32_t RightSoluteRequest(const Field &field, const Request &request) {
    std::int32_t result = 0;
    for (std::uint32_t y = request.left_top.y; y < request.right_bottom.y; ++y)
        for (std::uint32_t x = request.left_top.x; x < request.right_bottom.x; ++x)
            result += field[y][x];
    return result;
}

void PrintFieldPart(const Field &field, const Request &request) {
    for (std::uint32_t y = request.left_top.y; y < request.right_bottom.y; ++y) {
        for (std::uint32_t x = request.left_top.x; x < request.right_bottom.x; ++x) {
            if (field[y][x] >= 0) std::cout << " ";
            std::uint32_t value_size = NumberDigitsCount(field[y][x]);
            std::cout << field[y][x];
            if (field[y][x] < 0) std::cout << " ";
            for (std::uint32_t i = value_size; i < glob_max_value_digits_count; ++i) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void PrintFullField(const Field &field) {
    if (field.empty()) return;
    PrintFieldPart(field, Request(Coords(0, 0), Coords(field[0].size(), field.size())));
}

int main() {
    std::cout << "seed: " << seed << std::endl << std::endl;
    Field field, sums_field;
    GenerateRandomField(field);
    GenerateSumsField(field, sums_field);
//    PrintFullField(field);
    Request temp_req;
    std::cout << std::endl;
    for (std::uint32_t i = 0; i < 100000; ++i) {
        temp_req = GenerateRandomRequest(field, temp_req);
        std::cout << "Request:" << std::endl;
//        PrintFieldPart(field, temp_req);
        std::int32_t my_res = SoluteRequest(sums_field, temp_req);
        std::int32_t right_res = RightSoluteRequest(field, temp_req);
        std::cout << "My result: " << my_res << std::endl;
        std::cout << "Right result: " << right_res << std::endl;
        std::cout << std::endl;
        if (my_res != right_res) {
            std::cout << "Error!" << std::endl;
            return 0;
        }
    }
    return 0;
}
