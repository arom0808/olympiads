#include <iostream>
#include <vector>
//#include <random>

using Field = std::vector<std::vector<bool>>;

inline bool IsLeftTop(const Field &field, std::uint32_t y, std::uint32_t x) {
    return (y == 0 ? true : (!field[y - 1][x])) && (x == 0 ? true : (!field[y][x - 1]));
}

inline bool IsRightTop(const Field &field, std::uint32_t y, std::uint32_t x) {
    return (y == 0 ? true : (!field[y - 1][x])) && (x == field.size() - 1 ? true : (!field[y][x + 1]));
}

inline bool IsRightBottom(const Field &field, std::uint32_t y, std::uint32_t x) {
    return (y == field.size() - 1 ? true : (!field[y + 1][x])) && (x == field.size() - 1 ? true : (!field[y][x + 1]));
}

inline bool IsLeftBottom(const Field &field, std::uint32_t y, std::uint32_t x) {
    return (y == field.size() - 1 ? true : (!field[y + 1][x])) && (x == 0 ? true : (!field[y][x - 1]));
}

struct Coords {
    std::uint32_t y, x;

    bool operator==(const Coords &other) const {
        return y == other.y && x == other.x;
    }

    explicit Coords(std::uint32_t y = 0, std::uint32_t x = 0) : y(y), x(x) {}
};

std::uint32_t ToBottomLineSize(const Field &field, std::uint32_t y, std::uint32_t x) {
    std::uint32_t size = 0;
    for (std::uint32_t cur_y = y; field[cur_y][x] && cur_y < field.size() - 1; ++cur_y, ++size)
        if (cur_y == field.size() - 2) if (field[field.size() - 1][x]) ++size;
    if (y == field.size() - 1) ++size;
    return size;
}

std::uint32_t ToRightLineSize(const Field &field, std::uint32_t y, std::uint32_t x) {
    std::uint32_t size = 0;
    for (std::uint32_t cur_x = x; field[y][cur_x] && cur_x < field.size() - 1; ++cur_x, ++size)
        if (cur_x == field.size() - 2) if (field[y][field.size() - 1]) ++size;
    if (x == field.size() - 1) ++size;
    return size;
}

struct Solution {
    std::uint32_t square_size;
    Coords first_left_top, second_left_top;

    bool operator==(const Solution &other) const {
        if (square_size != other.square_size) return false;
        if ((first_left_top == other.first_left_top && second_left_top == other.second_left_top) ||
            (first_left_top == other.second_left_top && second_left_top == other.first_left_top))
            return true;
        return false;
    }

    explicit Solution(std::uint32_t square_size = 0, Coords first_left_top = Coords(),
                      Coords second_left_top = Coords())
            : square_size(square_size), first_left_top(first_left_top), second_left_top(second_left_top) {}
};

Solution GetSolution(const Field &field) {
    std::vector<Coords> left_tops, right_tops, right_bottoms, left_bottoms;
    for (std::uint32_t y = 0; y < field.size(); ++y) {
        for (std::uint32_t x = 0; x < field.size(); ++x) {
            if (!field[y][x]) continue;
            if (IsLeftTop(field, y, x)) left_tops.emplace_back(y, x);
            if (IsRightTop(field, y, x)) right_tops.emplace_back(y, x);
            if (IsRightBottom(field, y, x)) right_bottoms.emplace_back(y, x);
            if (IsLeftBottom(field, y, x)) left_bottoms.emplace_back(y, x);
        }
    }
    if (left_tops.size() == 2) {
        return Solution(std::min(ToBottomLineSize(field, left_tops[0].y, left_tops[0].x),
                                 ToBottomLineSize(field, left_tops[1].y, left_tops[1].x)),
                        Coords(left_tops[0].y, left_tops[0].x),
                        Coords(left_tops[1].y, left_tops[1].x));
    }
    if (left_tops.size() == 1 && right_tops.size() == 1 && right_bottoms.size() == 1 && left_bottoms.size() == 1) {
        std::uint32_t to_bottom_line_size = ToBottomLineSize(field, left_tops[0].y, left_tops[0].x);
        std::uint32_t to_right_line_size = ToRightLineSize(field, left_tops[0].y, left_tops[0].x);
        if (to_bottom_line_size == to_right_line_size) {
            return Solution(to_bottom_line_size, Coords(left_tops[0].y, left_tops[0].x),
                            Coords(left_tops[0].y, left_tops[0].x));
        }
        if (to_bottom_line_size > to_right_line_size) {
            return Solution(to_right_line_size, Coords(left_tops[0].y, left_tops[0].x),
                            Coords(left_tops[0].y + to_bottom_line_size - to_right_line_size, left_tops[0].x));
        }
        if (to_right_line_size > to_bottom_line_size) {
            return Solution(to_bottom_line_size, Coords(left_tops[0].y, left_tops[0].x),
                            Coords(left_tops[0].y, left_tops[0].x + to_right_line_size - to_bottom_line_size));
        }
    }
    if (left_tops.size() == 1 && right_tops.size() == 2 && right_bottoms.size() == 1 && left_bottoms.size() == 2) {
        std::uint32_t square_size = ToRightLineSize(field, left_tops[0].y, left_tops[0].x);
        auto &cur_right_top = right_tops[0];
        if (cur_right_top.y == left_tops[0].y) cur_right_top = right_tops[1];
        return Solution(square_size, Coords(left_tops[0].y, left_tops[0].x),
                        Coords(cur_right_top.y, cur_right_top.x - square_size + 1));
    }
}

//void PrintField(const Field &field) {
//    for (auto &&a: field) {
//        for (auto &&b: a) std::cout << (b ? '#' : '.');
//        std::cout << std::endl;
//    }
//}

//Field &GenerateFieldFromSolutionAndN(Field &field, const Solution &solution, std::uint32_t N) {
//    field.clear();
//    field.resize(N, std::vector<bool>(N, false));
//    for (std::uint32_t y = solution.first_left_top.y; y < solution.first_left_top.y + solution.square_size; ++y)
//        for (std::uint32_t x = solution.first_left_top.x; x < solution.first_left_top.x + solution.square_size; ++x)
//            field[y][x] = true;
//    for (std::uint32_t y = solution.second_left_top.y; y < solution.second_left_top.y + solution.square_size; ++y)
//        for (std::uint32_t x = solution.second_left_top.x; x < solution.second_left_top.x + solution.square_size; ++x)
//            field[y][x] = true;
//    return field;
//}

//std::pair<Field &, Solution &> GenerateRandomFieldAndSolution(Field &field, Solution &solution) {
//    std::random_device dev;
//    std::mt19937 rng(dev());
//    std::uniform_int_distribution<std::mt19937::result_type> rand_N_dist(1, 20);
//    std::uint32_t N = rand_N_dist(rng);
//    std::uniform_int_distribution<std::mt19937::result_type> rand_first_coord_dist(0, N - 1);
//    Coords first_left_top(rand_first_coord_dist(rng), rand_first_coord_dist(rng));
//    std::uint32_t max_square_size = std::min(N - first_left_top.y, N - first_left_top.x);
//    std::uniform_int_distribution<std::mt19937::result_type> rand_square_size_dist(1, max_square_size);
//    std::uint32_t square_size = rand_square_size_dist(rng);
//    std::uniform_int_distribution<std::mt19937::result_type> rand_second_coord_dist(0, N - square_size);
//    Coords second_left_top(rand_second_coord_dist(rng), rand_second_coord_dist(rng));
//    solution.square_size = square_size;
//    solution.first_left_top = first_left_top;
//    solution.second_left_top = second_left_top;
//    GenerateFieldFromSolutionAndN(field, solution, N);
//    return {field, solution};
//}

Field &InputField(Field &field) {
    field.clear();
    std::uint32_t N;
    std::cin >> N;
    field.resize(N, std::vector<bool>(N, false));
    char temp_ch;
    for (auto &&a: field) {
        for (auto &&b: a) {
            std::cin >> temp_ch;
            b = (temp_ch == '#');
        }
    }
    return field;
}

void PrintSolution(const Solution &solution) {
    std::cout << solution.square_size << std::endl;
    std::cout << solution.first_left_top.y + 1 << " " << solution.first_left_top.x + 1 << std::endl;
    std::cout << solution.second_left_top.y + 1 << " " << solution.second_left_top.x + 1;
}

int main() {
    Field field{};

//    std::uint32_t N = 19;
//    Solution right_solution(5, Coords(5, 3), Coords(6, 8));
//    GenerateFieldFromSolutionAndN(field, right_solution, N);
//    PrintField(field);
//    Solution my_solution = GetSolution(field);
//    PrintSolution(my_solution);
//    std::cout << std::endl;
//    PrintSolution(right_solution);

//    Solution right_solution, my_solution;
//    while (true) {
//        GenerateRandomFieldAndSolution(field, right_solution);
//        my_solution = GetSolution(field);
//        if (my_solution != right_solution) {
//            PrintField(field);
//            std::cout << "Right solution:" << std::endl;
//            PrintSolution(right_solution);
//            std::cout << std::endl << "My solution:" << std::endl;
//            PrintSolution(my_solution);
//            return 0;
//        }
//    }

    PrintSolution(GetSolution(InputField(field)));
    return 0;
}
