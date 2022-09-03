#include <iostream>
#include <vector>
#include<map>

struct ElectricTrain {
    std::uint32_t A, B, C, D;
    std::vector<std::vector<ElectricTrain>::const_iterator> earlier;
    std::uint32_t id;
};

std::uint32_t WhenTrainWillBeOnThisStation(const ElectricTrain &train, std::uint32_t station) {
    if (train.A > station) throw std::invalid_argument("Station is before first train station");
    if (train.B < station) throw std::invalid_argument("Station is farther than last train station");
    return train.C + (station - train.A) * train.D;
}

void ProcessResult(const std::vector<ElectricTrain>::const_iterator train,
                   std::map<std::vector<ElectricTrain>::const_iterator, bool> &isVisited,
                   std::vector<std::uint32_t> &results, std::uint32_t &res_n) {
    if (isVisited[train]) return;
    isVisited[train] = true;
    for (const auto &earlier: train->earlier) ProcessResult(earlier, isVisited, results, res_n);
    results[res_n++] = train->id;
}

int main() {
    std::int32_t N;
    std::cin >> N;
    std::vector<ElectricTrain> trains(N);
    std::uint32_t t_id = 1;
    for (auto &&train: trains) {
        std::cin >> train.A >> train.B >> train.C >> train.D;
        train.id = t_id++;
    }
    for (auto f_tr = trains.begin(); std::next(f_tr) != trains.end(); ++f_tr) {
        for (auto s_tr = std::next(f_tr); s_tr != trains.end(); ++s_tr) {
            if (s_tr->A >= f_tr->A && s_tr->A <= f_tr->B) {
                if (WhenTrainWillBeOnThisStation(*f_tr, s_tr->A) < WhenTrainWillBeOnThisStation(*s_tr, s_tr->A))
                    s_tr->earlier.emplace_back(f_tr);
                else f_tr->earlier.emplace_back(s_tr);
            } else if (s_tr->B >= f_tr->A && s_tr->B <= f_tr->B) {
                if (WhenTrainWillBeOnThisStation(*f_tr, f_tr->A) < WhenTrainWillBeOnThisStation(*s_tr, f_tr->A))
                    s_tr->earlier.emplace_back(f_tr);
                else f_tr->earlier.emplace_back(s_tr);
            }
        }
    }
    std::map<std::vector<ElectricTrain>::const_iterator, bool> isVisited;
    for (auto f_tr = trains.begin(); f_tr != trains.end(); ++f_tr) isVisited.insert({f_tr, false});
    std::vector<std::uint32_t> results(N, 0);
    std::uint32_t t_r_n = 0;
    ProcessResult(trains.begin(), isVisited, results, t_r_n);
    std::cout << std::endl;
    for (const auto &train_id: results) std::cout << train_id << " ";
    std::cout << std::endl;
    return 0;
}