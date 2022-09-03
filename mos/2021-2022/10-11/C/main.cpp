#include <fstream>
#include <vector>
#include <bitset>
#include <map>
#include <iostream>
//#include <unordered_map>

using Screen = std::bitset<100>;
using Commands = std::vector<std::pair<std::uint32_t, std::uint32_t>>;

struct ScreenLess {
    bool operator()(const Screen &x, const Screen &y) const {
        for (int i = 99; i >= 0; --i)
            if (x[i] ^ y[i]) return y[i];
        return false;
    }

    typedef Screen first_argument_type;
    typedef Screen second_argument_type;
    typedef bool result_type;
};

using ScreensWithCommands = std::map<Screen, Commands, ScreenLess>;


void ExecuteCommand(Screen &to_screen, std::uint32_t k, std::uint32_t row, std::uint32_t col) {
    for (std::uint32_t i = row * k; i < (row + 1) * k; ++i)
        to_screen.flip(i);
    for (std::uint32_t i = col; i < k * k; i += k)
        to_screen.flip(i);
    to_screen.flip(row * k + col);
}


ScreensWithCommands::iterator
ExecuteAllCommands(const Screen &find_screen, const std::pair<Screen, Commands> &f_sc,
                   ScreensWithCommands &r_scs, std::uint32_t k) {
    for (std::uint32_t i = 0; i < k; ++i) {
        for (std::uint32_t j = 0; j < k; ++j) {
            auto cmds = f_sc.second;
            cmds.emplace_back(i, j);
            auto screen = f_sc.first;
            ExecuteCommand(screen, k, i, j);
            auto ins_res = r_scs.insert({screen, cmds});
            if (screen == find_screen)
                return ins_res.first;
        }
    }
    return r_scs.end();
}


int main() {
    std::uint32_t t, k;
    bool bool_cache;
    std::ifstream inp("c_inp.txt");
    inp >> t;
    std::vector<Commands> results(t);
    std::uint32_t ex_number = 0;
    std::ofstream out("c_out.txt");
    out.close();
    for (auto &res: results) {
        inp >> k;
        Screen input_screen;
        for (std::uint32_t i = 0; i < k * k; ++i) {
            inp >> bool_cache;
            input_screen.set(i, bool_cache);
        }
        ScreensWithCommands result_screens{{Screen(), {}}};
        std::uint32_t level = 0;
        std::cout << "Ex " << ex_number << " started" << std::endl;
        while (true) {
            std::cout << "    Started level " << level << std::endl;
            ScreensWithCommands temp_result_screens;
            ScreensWithCommands::iterator r;
            for (const auto &rs_sc: result_screens) {
                r = ExecuteAllCommands(input_screen, rs_sc, temp_result_screens, k);
                if (r != temp_result_screens.end())
                    break;
            }
            if (r != temp_result_screens.end()) {
                res = r->second;
                out.open("c_out.txt", std::ios_base::app);
                out << res.size() << std::endl;
                for (const auto &cmd: res)
                    out << cmd.first << " " << cmd.second << std::endl;
                out.close();
                break;
            }
            std::swap(result_screens, temp_result_screens);
            result_screens.insert(temp_result_screens.begin(), temp_result_screens.end());
            ++level;
        }
        std::cout << "Ex " << ex_number << " finished" << std::endl;
        ++ex_number;
    }
    inp.close();
    return 0;
}
