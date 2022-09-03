#include <iostream>

std::uint64_t
TheNumberOfTreesThatOneLumberjackWillCutDown(const std::uint64_t &treesPerDay, const std::uint64_t &restFrequency,
                                             const std::uint64_t &days) {
    return (days / restFrequency * (restFrequency - 1) + (days % restFrequency)) * treesPerDay;
}

std::uint64_t
TheNumberOfTreesThatTwoLumberjacksWillCutDown(const std::uint64_t &treesPerDay1, const std::uint64_t &restFrequency1,
                                              const std::uint64_t &treesPerDay2, const std::uint64_t &restFrequency2,
                                              const std::uint64_t &days) {
    return TheNumberOfTreesThatOneLumberjackWillCutDown(treesPerDay1, restFrequency1, days) +
           TheNumberOfTreesThatOneLumberjackWillCutDown(treesPerDay2, restFrequency2, days);
}

std::uint64_t
TheNumberOfDaysThatOneLumberjackNeedToCutDownTrees(const std::uint64_t &treesPerDay, const std::uint64_t &restFrequency,
                                                   const std::uint64_t &treesCount) {
    auto oneRestTreesCount = (restFrequency - 1) * treesPerDay;
    auto ostatokTres = treesCount % oneRestTreesCount;
    return treesCount / oneRestTreesCount * restFrequency + ostatokTres / treesPerDay +
           (ostatokTres % treesPerDay != 0 ? 1 : 0);
}

int main() {
    std::uint64_t A, K, B, M, X;
    std::cin >> A >> K >> B >> M >> X;
    std::uint64_t min = 0, max = TheNumberOfDaysThatOneLumberjackNeedToCutDownTrees(A, K, X);
    while (min != max) {
        std::uint64_t middleDays = (min + max) / 2;
        std::uint64_t middleTrees = TheNumberOfTreesThatTwoLumberjacksWillCutDown(A, K, B, M, middleDays);
        if (middleTrees < X) {
            min = middleDays + 1;
        } else {
            max = middleDays;
        }
    }
    std::cout << min;
    return 0;
}
