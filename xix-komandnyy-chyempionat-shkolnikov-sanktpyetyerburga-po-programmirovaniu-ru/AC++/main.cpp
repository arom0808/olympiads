#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

bool isCorrect(std::vector<int> date) {
    if (date[0] == 0 || date[1] == 0)
        return false;
    if (date[2] == 0)
        date[2] += 100;
    date[2] += 2000;
    if (date[1] > 12) {
        return false;
    }
    if (date[1] == 2) {
        if (date[2] % 4 == 0) {
            if (date[2] % 100 == 0) {
                if (date[2] % 400 == 0) {
                    if (date[0] > 29) {
                        return false;
                    }
                } else {
                    if (date[0] > 28) {
                        return false;
                    }
                }
            } else {
                if (date[0] > 29) {
                    return false;
                }
            }
        } else {
            if (date[0] > 28) {
                return false;
            }
        }
    } else if (date[1] == 1 || date[1] == 3 || date[1] == 5 || date[1] == 7 || date[1] == 8 || date[1] == 10 ||
               date[1] == 12) {
        if (date[0] > 31) {
            return false;
        }
    } else {
        if (date[0] > 30) {
            return false;
        }
    }
    return true;
}

std::string addZero(int integer) {
    if (integer < 10)
        return "0" + std::to_string(integer);
    return std::to_string(integer);
}

//void mmain() {
//    std::string istr;
//    std::ifstream ifile("chronicleCopy.in");
//    std::ofstream ofile("chronicleCopy.out");
//    for (; std::getline(ifile, istr);) {
//        std::vector<int> idates(3);
//        for (int i = 0; i < 3; ++i)
//            idates[i] = std::stoi(istr.substr(i * 3, 2));
//        std::vector<std::vector<int>> correct_dates;
//        std::vector<std::vector<int>> dates = {
//                {idates[0], idates[1], idates[2]},
//                {idates[0], idates[2], idates[1]},
//                {idates[1], idates[0], idates[2]},
//                {idates[1], idates[2], idates[0]},
//                {idates[2], idates[0], idates[1]},
//                {idates[2], idates[1], idates[0]}
//        };
//        for (const auto &date: dates) {
//            if (std::find(correct_dates.begin(), correct_dates.end(), date) != correct_dates.end())
//                continue;
//            if (isCorrect(date))
//                correct_dates.push_back(date);
//        }
//        if (correct_dates.empty())
//            ofile << "No such date\n";
//        else {
//            for (const auto &date: correct_dates) {
//                ofile << addZero(date[0]) + '/' + addZero(date[1]) + '/' +
//                         addZero(date[2]) << '\n';
//            }
//        }
//        ofile << '\n';
//    }
//    ifile.close();
//    ofile.close();
//}

int main() {
//    mmain();
    std::string istr;
    std::ifstream ifile("chronicle.in");
    std::getline(ifile, istr);
    ifile.close();
    std::vector<int> idates(3);
    for (int i = 0; i < 3; ++i)
        idates[i] = std::stoi(istr.substr(i * 3, 2));
    std::vector<std::vector<int>> correct_dates;
    std::sort(idates.begin(), idates.end());
    do {
        if (std::find(correct_dates.begin(), correct_dates.end(), idates) != correct_dates.end())
            continue;
        if (isCorrect(idates))
            correct_dates.push_back(idates);
    } while (std::next_permutation(idates.begin(), idates.end()));
    std::ofstream ofile("chronicle.out");
    if (correct_dates.empty())
        ofile << "No such date";
    else {
        ofile << addZero(correct_dates[0][0]) + '/' + addZero(correct_dates[0][1]) + '/' + addZero(correct_dates[0][2]);
        for (auto date = ++correct_dates.begin(); date != correct_dates.end(); ++date) {
            ofile << '\n' + addZero((*date)[0]) + '/' + addZero((*date)[1]) + '/' + addZero((*date)[2]);
        }
    }
    ofile.close();
    return 0;
}
