#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <set>

std::random_device rnd_dev;
auto rnd_seed = rnd_dev();
//std::uint32_t rnd_seed = 3519345167;
std::mt19937 rng(rnd_seed);
std::bernoulli_distribution mid_bool_rnd(0.5);

struct MetaElement {
    std::uint32_t zeros_count = 0, ones_count = 0;
    bool is_dif_fok = false;
};

struct FullMetaElements {
    std::vector<MetaElement> rows, columns;

    explicit FullMetaElements(std::uint32_t n) : rows(n), columns(n) {}
};

enum class Ceil {
    zero = false,
    one = true,
    nothing = 'n'
};

using Table = std::vector<std::vector<Ceil>>;

using Inputs = std::vector<std::pair<std::uint32_t, std::uint32_t>>;

using TimePoint = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;

std::uint32_t DistanceBetween(std::uint32_t a, std::uint32_t b) {
    return std::max(a, b) - std::min(a, b);
}

void PrintTable(const Table &table) {
    for (const auto &row: table) {
        for (const auto &ceil: row) {
            if (ceil == Ceil::nothing) std::cout << static_cast<char>(ceil);
            else std::cout << static_cast<bool>(ceil);
        }
        std::cout << "\n";
    }
}

bool IsSolutionCorrect(FullMetaElements &full_meta_elements) {
    auto IsOk = [](const MetaElement &a) { return a.is_dif_fok; };
    if (!std::all_of(full_meta_elements.rows.begin(), full_meta_elements.rows.end(), IsOk))
        return false;
    if (!std::all_of(full_meta_elements.columns.begin(), full_meta_elements.columns.end(), IsOk))
        return false;
    return true;
}

void InverseOneCeil(Table &table, std::uint32_t x, std::uint32_t y, FullMetaElements &full_meta_elements) {
    table[y][x] = static_cast<Ceil>(!static_cast<bool>(table[y][x]));
    if (table[y][x] == Ceil::one) {
        ++full_meta_elements.rows[y].ones_count;
        --full_meta_elements.rows[y].zeros_count;
        ++full_meta_elements.columns[x].ones_count;
        --full_meta_elements.columns[x].zeros_count;
    } else {
        --full_meta_elements.rows[y].ones_count;
        ++full_meta_elements.rows[y].zeros_count;
        --full_meta_elements.columns[x].ones_count;
        ++full_meta_elements.columns[x].zeros_count;
    }
    full_meta_elements.rows[y].is_dif_fok =
            DistanceBetween(full_meta_elements.rows[y].zeros_count, full_meta_elements.rows[y].ones_count) <= 1;
    full_meta_elements.columns[x].is_dif_fok =
            DistanceBetween(full_meta_elements.columns[x].zeros_count, full_meta_elements.columns[x].ones_count) <= 1;
}

void OneStepOfSolution(Table &table, const Inputs &inputs, FullMetaElements &full_meta_elements) {
    std::uniform_int_distribution dist_a(0, static_cast<std::int32_t>(inputs.size() - 1));
    std::uint32_t a = dist_a(rng), y = inputs[a].first, x = inputs[a].second;
    std::uint32_t pre_res = full_meta_elements.rows[y].is_dif_fok + full_meta_elements.columns[x].is_dif_fok;
    InverseOneCeil(table, x, y, full_meta_elements);
    std::uint32_t now_res = full_meta_elements.rows[y].is_dif_fok + full_meta_elements.columns[x].is_dif_fok;
    if (now_res < pre_res) InverseOneCeil(table, x, y, full_meta_elements);
}

bool Solute(const TimePoint &start_time, Table &table, const Inputs &inputs, FullMetaElements &full_meta_elements) {
    if (IsSolutionCorrect(full_meta_elements)) return true;
    TimePoint end_time;
    while (true) {
        OneStepOfSolution(table, inputs, full_meta_elements);
        end_time = std::chrono::steady_clock::now();
        if (IsSolutionCorrect(full_meta_elements)) {
            return true;
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() > 990) {
            return false;
        }
    }
}

int main() {
    TimePoint start_time = std::chrono::steady_clock::now();
//    std::ifstream in_f("in.txt");
    std::uint32_t S, N;
    std::cin >> S >> N;
    Table table(S, std::vector<Ceil>(S, Ceil::nothing));
    Inputs inputs(N);
    FullMetaElements full_meta_elements(S);
    for (auto &&input: inputs) {
        std::cin >> input.first >> input.second;
        table[--input.first][--input.second] = static_cast<Ceil>(mid_bool_rnd(rng));
        if (table[input.first][input.second] == Ceil::zero) {
            ++full_meta_elements.rows[input.first].zeros_count;
            ++full_meta_elements.columns[input.second].zeros_count;
        } else {
            ++full_meta_elements.rows[input.first].ones_count;
            ++full_meta_elements.columns[input.second].ones_count;
        }
    }
    for (std::uint32_t i = 0; i < full_meta_elements.rows.size(); ++i) {
        if (DistanceBetween(full_meta_elements.rows[i].zeros_count, full_meta_elements.rows[i].ones_count) <= 1)
            full_meta_elements.rows[i].is_dif_fok = true;
        if (DistanceBetween(full_meta_elements.columns[i].zeros_count, full_meta_elements.columns[i].ones_count) <= 1)
            full_meta_elements.columns[i].is_dif_fok = true;
    }
    if (Solute(start_time, table, inputs, full_meta_elements)) {
        for (const auto coords: inputs)
            std::cout << static_cast<bool>(table[coords.first][coords.second]);
    } else {
        std::cout << "Impossible";
    }
//    std::cout << "\n\n";
//    PrintTable(table);
    return 0;
}
