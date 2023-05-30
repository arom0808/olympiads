#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <fstream>

std::map<char, std::uint32_t> start_deck{{'2', 24},
                                         {'3', 24},
                                         {'4', 24},
                                         {'5', 24},
                                         {'6', 24},
                                         {'7', 24},
                                         {'8', 24},
                                         {'9', 24},
                                         {'0', 24},
                                         {'J', 24},
                                         {'Q', 24},
                                         {'K', 24},
                                         {'A', 24}};

std::map<char, std::uint32_t> cards_prices{{'2', 2},
                                           {'3', 3},
                                           {'4', 4},
                                           {'5', 5},
                                           {'6', 6},
                                           {'7', 7},
                                           {'8', 8},
                                           {'9', 9},
                                           {'0', 10},
                                           {'J', 10},
                                           {'Q', 10},
                                           {'K', 10},
                                           {'A', 11}};


class Deck {
public:
    std::map<char, std::uint32_t> data;
    std::uint32_t sum, cards_count;

    [[nodiscard]] std::uint32_t GetSum(bool is_player_sum) const {
        if (!is_player_sum) return sum;
        else {
            std::uint32_t res = sum, ase_full_used = GetCardCount('A');
            while (ase_full_used > 0 && res > 21) {
                res -= 10;
                --ase_full_used;
            }
            return res;
        }
    }

    [[nodiscard]] std::uint32_t GetCardsCount() const { return cards_count; }

    void ResetToStartDeck() {
        data = start_deck;
        cards_count = sum = 0;
        for (const auto &card: data) {
            sum += cards_prices[card.first] * card.second;
            cards_count += card.second;
        }
    }

    void Clear() {
        data.clear();
        sum = cards_count = 0;
    }

    void AddCard(char card) {
        auto it = data.find(card);
        if (it != data.end()) ++it->second;
        else data.emplace(card, 1);
        sum += cards_prices[card];
        ++cards_count;
    }

    void DeleteCard(char card) {
        auto it = data.find(card);
        if (it == data.end()) return;
        if (it->second == 0) return;
        --it->second;
        sum -= cards_prices[card];
        --cards_count;
    }

    [[nodiscard]] std::uint32_t GetCardCount(char card) const {
        auto it = data.find(card);
        if (it != data.end()) return it->second;
        else return 0;
    }

    [[nodiscard]] long double ProbabilityThatCardBTN(std::uint32_t N, bool is_ase_is_1) const {
        long double res = 0;
        std::uint32_t ase_price = is_ase_is_1 ? 1 : cards_prices['A'];
        for (const auto &card: data)
            res += ((card.first == 'A' ? ase_price : cards_prices[card.first]) > N) * card.second;
        return res / static_cast<long double>(GetCardsCount());
    }

    explicit Deck(bool need_to_set_full = false) {
        if (need_to_set_full) ResetToStartDeck();
        else Clear();
    }
};

enum class Action {
    ht,
    dbl,
    brk
};

template<typename T>
class LinealRegressionWithMinMax {
public:
    T k, b, min, max;

    LinealRegressionWithMinMax(T x1, T y1, T x2, T y2, T min, T max) : min(min), max(max) {
        k = (y1 - y2) / (x1 - x2);
        b = y1 - k * x1;
    }

    LinealRegressionWithMinMax(T k, T b, T min, T max) : k(k), b(b), min(min), max(max) {}

    T operator()(T x) const {
        return std::max(min, std::min(k * x + b, max));
    }
};

class IOobject {
public:
    IOobject &operator<<(const std::uint32_t &int_str) { return this->operator<<(std::to_string(int_str)); }

    virtual IOobject &operator<<(const std::string &str) = 0;

    virtual IOobject &operator>>(std::string &str) = 0;
};

class Solution {
public:
    std::uint32_t balance = 500000, bet = 0;
    Deck now_deck, my_hand, dealer_hand;
    long double max_bet_percent;
    long double max_n_for_double, min_next_n_probability_for_double;
    long double max_n_for_hit;
    std::uint32_t min_next_n_for_double;

    IOobject &io_stream;

    const LinealRegressionWithMinMax<long double> k0, k1, k2;

    explicit Solution(IOobject &io_stream, long double k0_k, long double k0_b, long double k0_min, long double k0_max,
                      long double k1_k, long double k1_b, long double k1_min, long double k1_max, long double k2_k,
                      long double k2_b, long double k2_min, long double k2_max, long double max_bet_percent,
                      long double max_n_for_double, long double min_next_n_probability_for_double,
                      long double max_n_for_hit, std::uint32_t min_next_n_for_double)
            : io_stream(io_stream),
              k0(k0_k, k0_b, k0_min, k0_max),
              k1(k1_k, k1_b, k1_min, k1_max),
              k2(k2_k, k2_b, k2_min, k2_max),
              now_deck(true), my_hand(false), dealer_hand(false),
              max_bet_percent(max_bet_percent), max_n_for_double(max_n_for_double),
              min_next_n_probability_for_double(min_next_n_probability_for_double), max_n_for_hit(max_n_for_hit),
              min_next_n_for_double(min_next_n_for_double) {
        //        max_bet_percent = 0.1;
    }

    void SetStartBet() {
        //        if (now_deck.GetSum(true) <= 21 && now_deck.GetCardCount('A') == 0) bet = balance;
        //        else
        bet = std::min(std::min(
                static_cast<std::uint32_t>(balance * k0(balance) * k1(now_deck.GetCardsCount()) * k2(balance)),
                static_cast<std::uint32_t>(static_cast<long double>(balance) * max_bet_percent)), balance);
    }

    void ReadStartTable(const std::string &str) {
        dealer_hand.AddCard(str[0]);
        my_hand.AddCard(str[2]);
        my_hand.AddCard(str[3]);
        for (std::uint8_t i = 0; i < 4; ++i) if (i != 1) now_deck.DeleteCard(str[i]);
    }

    void ReadNewCardOnTable(const std::string &str) {
        my_hand.AddCard(str.back());
        now_deck.DeleteCard(str.back());
    }

    void AddDealersCards(const std::string &str) {
        for (std::uint32_t i = 1; str[i] != '#' && i < str.size(); ++i) {
            dealer_hand.AddCard(str[i]);
            now_deck.DeleteCard(str[i]);
        }
    }

    void ApplyResults() {
        std::uint32_t my_res = (21 >= my_hand.GetSum(true) ? 21 - my_hand.GetSum(true) : 21);
        std::uint32_t dealer_res = (21 >= dealer_hand.GetSum(true) ? 21 - dealer_hand.GetSum(true) : 21);
        if (my_res > dealer_res) balance -= bet;
        else if (my_res < dealer_res) balance += bet;
    }

    [[nodiscard]] long double ProbabilityNextCardSumBTN(std::uint32_t N) const {
        return now_deck.ProbabilityThatCardBTN((N >= my_hand.GetSum(true) ? N - my_hand.GetSum(true) : 0),
                                               my_hand.GetSum(true) > 10);
    }

    [[nodiscard]] Action GetAction() const {
        if (my_hand.GetSum(true) >= 20) return Action::brk;
        auto n = ProbabilityNextCardSumBTN(21);
        if (n <= max_n_for_double &&
            ProbabilityNextCardSumBTN(min_next_n_for_double) >= min_next_n_probability_for_double)
            if (bet * 2 <= static_cast<long double>(balance) * max_bet_percent)
                return Action::dbl;
        if (n <= max_n_for_hit) return Action::ht;
        return Action::brk;
    }

    void GetSolution() {
        std::string temp_str;
        for (std::uint32_t round = 0; balance < 4200000 && round < 10002; ++round) {
            io_stream >> temp_str;
            if (temp_str == "shuffle") {
                now_deck.ResetToStartDeck();
                io_stream >> temp_str;
            }
            SetStartBet();
            io_stream << bet << "\n";
            my_hand.Clear();
            dealer_hand.Clear();
            io_stream >> temp_str;
            ReadStartTable(temp_str);
            for (auto action = GetAction(); action != Action::brk; action = GetAction()) {
                if (action == Action::ht) {
                    io_stream << "hit" << "\n";
                } else if (action == Action::dbl) {
                    io_stream << "double" << "\n";
                    bet *= 2;
                }
                io_stream >> temp_str;
                ReadNewCardOnTable(temp_str);
            }
            io_stream << "break\n";
            io_stream >> temp_str;
            AddDealersCards(temp_str);
            ApplyResults();
            //            std::cout << "Balance: " << balance << '\n';
        }
        io_stream >> temp_str;
        io_stream << "-1\n";
    }
};

class ConsoleIO : public IOobject {
public:
    ConsoleIO &operator<<(const std::string &str) override {
        std::cout << str;
        std::cout.flush();
        return *this;
    }

    ConsoleIO &operator>>(std::string &str) override {
        std::cin >> str;
        return *this;
    }
};

//212
namespace Testing {
    namespace Random {
        std::random_device dev;
        std::uint32_t seed = dev();
        //        std::uint32_t seed = 2915159076;
        std::mt19937 rng(seed);

        std::uint32_t GetRandomInt(std::uint32_t min, std::uint32_t max) {
            return std::uniform_int_distribution<std::uint32_t>(min, max)(rng);
        }

        long double GetRandomLongDouble(long double min, long double max) {
            return std::uniform_real_distribution<long double>(min, max)(rng);
        }

        char GetRandomCardFromDeck(const Deck &deck) {
            std::uint32_t id = GetRandomInt(0, deck.GetCardsCount() - 1);
            std::uint32_t i = 0;
            char card;
            for (const auto &d: deck.data) {
                if (d.second > 0) {
                    if (i + d.second >= id) {
                        card = d.first;
                        break;
                    } else i += d.second;
                }
            }
            return card;
        }
    };

    class TestIO : public IOobject {
    public:
        enum class State {
            s0 = 0,
            s1 = 1,
            s2 = 2,
            s3 = 3,
            s4 = 4,
            s5 = 5,
            s6 = 6
        };
        std::uint32_t player_balance = 500000, player_bet = 0, motion_id = 0;
        Deck now_deck, player_hand, dealer_hand;
        std::string temp_string;
        std::string now_table;
        State state = State::s0;

        TestIO() : now_deck(true) {}

        TestIO &operator<<(const std::string &str) override {
            if (state == State::s2) {
                if (temp_string.empty() || temp_string.back() != '\n') {
                    temp_string += str;
                    //                    std::cout << str;
                }
                if (temp_string.back() == '\n') {
                    if (temp_string[0] == '-') {
                        return *this;
                    } else {
                        player_bet = std::stoi(temp_string.substr(0, temp_string.size() - 1));
                    }
                    temp_string.clear();
                    state = State::s3;
                }
            } else if (state == State::s4) {
                if (temp_string.empty() || temp_string.back() != '\n') {
                    temp_string += str;
                    //                    std::cout << str;
                }
                if (temp_string.back() == '\n') {
                    std::string act = temp_string.substr(0, temp_string.size() - 1);
                    temp_string.clear();
                    if (act == "hit") {
                        state = State::s5;
                    } else if (act == "double") {
                        player_bet *= 2;
                        state = State::s5;
                    } else {
                        state = State::s6;
                    }
                }
            }
            return *this;
        }

        TestIO &operator>>(std::string &str) override {
            if (state == State::s0) {
                //                std::cout << player_balance << "\n";
                //                std::cout << player_balance << '\n';
                ++motion_id;
                player_hand.Clear();
                dealer_hand.Clear();
                if (now_deck.GetCardsCount() < 20) {
                    state = State::s1;
                    now_deck.ResetToStartDeck();
                    str = "shuffle";
                    //                    std::cout << "shuffle\n";
                } else {
                    state = State::s2;
                    str = "bet";
                    //                    std::cout << "bet\n";
                    temp_string.clear();
                }
            } else if (state == State::s1) {
                str = "bet";
                //                std::cout << "bet\n";
                state = State::s2;
                temp_string.clear();
            } else if (state == State::s3) {
                auto dealer_card = Random::GetRandomCardFromDeck(now_deck);
                now_deck.DeleteCard(dealer_card);
                dealer_hand.AddCard(dealer_card);
                auto first_player_card = Random::GetRandomCardFromDeck(now_deck);
                now_deck.DeleteCard(first_player_card);
                player_hand.AddCard(first_player_card);
                auto second_player_card = Random::GetRandomCardFromDeck(now_deck);
                now_deck.DeleteCard(second_player_card);
                player_hand.AddCard(second_player_card);
                now_table = std::string(1, dealer_card) + "#" + first_player_card + second_player_card;
                str = now_table;
                //                std::cout << now_table << "\n";
                temp_string.clear();
                state = State::s4;
            } else if (state == State::s5) {
                auto new_player_card = Random::GetRandomCardFromDeck(now_deck);
                now_deck.DeleteCard(new_player_card);
                player_hand.AddCard(new_player_card);
                now_table += new_player_card;
                str = now_table;
                temp_string.clear();
                state = State::s4;
            } else if (state == State::s6) {
                while (dealer_hand.GetSum(true) < 17 && now_deck.GetCardsCount() > 0) {
                    auto new_dealer_card = Random::GetRandomCardFromDeck(now_deck);
                    now_deck.DeleteCard(new_dealer_card);
                    dealer_hand.AddCard(new_dealer_card);
                    now_table.insert(std::next(now_table.begin(), now_table.find('#')), new_dealer_card);
                }
                str = now_table;
                std::uint32_t player_res = (21 >= player_hand.GetSum(true) ? 21 - player_hand.GetSum(true) : 21);
                std::uint32_t dealer_res = (21 >= dealer_hand.GetSum(true) ? 21 - dealer_hand.GetSum(true) : 21);
                if (player_res > dealer_res) player_balance -= player_bet;
                else if (player_res < dealer_res) player_balance += player_bet;
                state = State::s0;
            }
            return *this;
        }
    };

    void Test() {
        std::ofstream out_file("out.txt");
        out_file << "seed: " << Random::seed << "\n\n";
        out_file.flush();
        while (true) {
            std::uint32_t winned = 0;
            long double k0_x1 = Random::GetRandomLongDouble(1e6, 1e7),
                    k0_y1 = Random::GetRandomLongDouble(0.03, 0.2),
                    k0_x2 = Random::GetRandomLongDouble(5e4, 4e5),
                    k0_y2 = Random::GetRandomLongDouble(0.2, 0.8),
                    k0_min = Random::GetRandomLongDouble(0.005, 0.05),
                    k0_max = Random::GetRandomLongDouble(0.25, 0.75),
                    k1_x1 = 312,
                    k1_y1 = Random::GetRandomLongDouble(0.8, 1.02),
                    k1_x2 = Random::GetRandomLongDouble(5, 20),
                    k1_y2 = Random::GetRandomLongDouble(1.25, 1.75),
                    k1_min = 1,
                    k1_max = Random::GetRandomLongDouble(1.25, 1.75),
                    k2_x1 = Random::GetRandomLongDouble(1e6, 1e7),
                    k2_y1 = 1,
                    k2_x2 = Random::GetRandomLongDouble(5e4, 2e5),
                    k2_y2 = Random::GetRandomLongDouble(0.25, 0.75),
                    k2_min = Random::GetRandomLongDouble(0.3, 0.9),
                    k2_max = 1,
                    max_bet_percent = Random::GetRandomLongDouble(0.3, 0.7),
                    max_n_for_double = Random::GetRandomLongDouble(0.05, 0.2),
                    min_next_n_probability_for_double = Random::GetRandomLongDouble(0.5, 0.95),
                    max_n_for_hit = Random::GetRandomLongDouble(0.25, 0.75);
            std::uint32_t min_next_n_for_double = Random::GetRandomInt(5, 20);
            LinealRegressionWithMinMax<long double> k0(k0_x1, k0_y1, k0_x2, k0_y2, k0_min, k0_max),
                    k1(k1_x1, k1_y1, k1_x2, k1_y2, k1_min, k1_max),
                    k2(k2_x1, k2_y1, k2_x2, k2_y2, k2_min, k2_max);
            out_file << "{";
            out_file << "{k0_k, " << k0.k << "},";
            out_file << "{k0_b, " << k0.b << "},";
            out_file << "{k0_min, " << k0_min << "},";
            out_file << "{k0_max, " << k0_max << "},";
            out_file << "{k1_k, " << k1.k << "},";
            out_file << "{k1_b, " << k1.b << "},";
            out_file << "{k1_min, " << k1_min << "},";
            out_file << "{k1_max, " << k1_max << "},";
            out_file << "{k2_k, " << k2.k << "},";
            out_file << "{k2_b, " << k2.b << "},";
            out_file << "{k2_min, " << k2_min << "},";
            out_file << "{k2_max, " << k2_max << "},";
            out_file << "{max_bet_percent, " << max_bet_percent << "},";
            out_file << "{max_n_for_double, " << max_n_for_double << "},";
            out_file << "{min_next_n_probability_for_double, " << min_next_n_probability_for_double << "},";
            out_file << "{max_n_for_hit, " << max_n_for_hit << "}";
            out_file << "{min_next_n_for_double, " << min_next_n_for_double << "}";
            out_file << "}\n";
            out_file.flush();
            for (std::uint32_t i = 0; i < 100; ++i) {
                TestIO test_io;
                Solution sol(test_io, k0.k, k0.b, k0_min, k0_max, k1.k, k1.b, k1_min,
                             k1_max, k2.k, k2.b, k2_min, k2_max, max_bet_percent, max_n_for_double,
                             min_next_n_probability_for_double, max_n_for_hit, min_next_n_for_double);
                sol.GetSolution();
                if (test_io.player_balance != sol.balance) {
                    out_file << "ERROR\n";
                }
                if (test_io.player_balance >= 4200000) {
                    ++winned;
                }
            }
            out_file << "Probability " << (static_cast<long double>(winned) / static_cast<long double>(100)) << "\n";
            out_file.flush();
        }
    }
}


int main() {
//        Testing::Test();
    long double k0_k = -3.75859e-08, k0_b = 0.226961, k0_min = 0.00790036, k0_max = 0.461925, k1_k = -0.00112462, k1_b = 1.29651, k1_min = 1.0, k1_max = 1.58623, k2_k = 1.26713e-07, k2_b = 0.304463, k2_min = 0.464197, k2_max = 1.0, max_bet_percent = 0.465443, max_n_for_double = 0.0902445, min_next_n_probability_for_double = 0.648217, max_n_for_hit = 0.645046;
    std::uint32_t min_next_n_for_double = 15;
    ConsoleIO consoleIo;
    //    Testing::TestIO test_io;
    Solution sol(consoleIo, k0_k, k0_b, k0_min, k0_max, k1_b, k1_b, k1_min,
                 k1_max, k2_k, k2_b, k2_min, k2_max, max_bet_percent, max_n_for_double,
                 min_next_n_probability_for_double, max_n_for_hit, min_next_n_for_double);
    sol.GetSolution();
    //    std::cout << test_io.player_balance;
    return 0;
}