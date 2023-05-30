#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <random>
#include <fstream>
#include <memory>

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

//
//namespace Random {
//    std::random_device dev;
//    std::uint32_t seed = dev();
//    std::mt19937 rng(seed);
//}

class Deck {
private:
    std::map<char, std::uint32_t> data;
    std::uint32_t sum, cards_count;
public:

    void swap(Deck &&other) {
        data.swap(other.data);
        std::swap(sum, other.sum);
        std::swap(cards_count, other.cards_count);
    }

    [[nodiscard]] const std::map<char, std::uint32_t> &GetRawData() const { return data; }

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

    void DeleteCards(const Deck &cards) {
        for (const auto &card: cards.data) {
            auto it = data.find(card.first);
            if (it == data.end() || it->second == 0) continue;
            std::uint32_t del_cnt = std::min(it->second, card.second);
            it->second -= del_cnt;
            sum -= cards_prices[card.first] * del_cnt;
            cards_count -= del_cnt;
        }
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

template<typename T>
class Regression {
private:
    [[nodiscard]] virtual T GetY(const T &x) const = 0;

public:
    std::unique_ptr<Regression<T>> pre_regression;

    explicit Regression(Regression<T> *pre_regression) : pre_regression(pre_regression) {}

    T operator()(const T &x) const {
        if (pre_regression) return GetY(pre_regression->operator()(x));
        else return GetY(x);
    }
};

template<typename T>
class LinealRegression : public Regression<T> {
private:
    [[nodiscard]] T GetY(const T &x) const override { return k * x + b; }

public:
    T k, b;

    LinealRegression(Regression<T> *pre_regression, T k, T b)
            : Regression<T>(pre_regression), k(k), b(b) {}

    LinealRegression(Regression<T> *pre_regression, T x1, T y1, T x2, T y2)
            : Regression<T>(pre_regression) {
        k = (y1 - y2) / (x1 - x2);
        b = y1 - k * x1;
    }
};

template<typename T>
class SquareRegression : public Regression<T> {
private:
    T GetY(const T &x) const override { return a * x * x + b * x + c; }

public:
    T a, b, c;

    SquareRegression(Regression<T> *pre_regression, T a, T b, T c)
            : Regression<T>(pre_regression), a(a), b(b), c(c) {}
};

template<typename T>
class CubeRegression : public Regression<T> {
private:
    T GetY(const T &x) const override { return a * x * x * x + b * x * x + c * x + d; }

public:
    T a, b, c, d;

    CubeRegression(Regression<T> *pre_regression, T a, T b, T c, T d)
            : Regression<T>(pre_regression), a(a), b(b), c(c), d(d) {}
};

template<typename T>
class MinMaxLimit : public Regression<T> {
private:
    [[nodiscard]] T GetY(const T &x) const override { return std::max(min, std::min(x, max)); }

public:
    T min, max;

    MinMaxLimit(Regression<T> *pre_regression, T min, T max)
            : Regression<T>(pre_regression), min(min), max(max) {}
};

class BJIObject {
public:
    virtual bool StartReadIsShuffle() = 0;

    virtual void Exit() = 0;

    virtual std::pair<Deck *, Deck *> StartBet(std::uint32_t bet) = 0;

    virtual char Hit() = 0;

    virtual char Double() = 0;

    virtual Deck Break() = 0;
};

//class MyFirstSolutionSolution {
//public:
//    std::uint32_t balance = 500000, bet = 0;
//    Deck now_deck, my_hand, dealer_hand;
//    long double max_bet_percent;
//    long double max_n_for_double, min_next_n_probability_for_double;
//    long double max_n_for_hit;
//    std::uint32_t min_next_n_for_double;
//
//    BJIObject &in_out;
//
//    const MinMaxLimit<long double> k0, k1, k2;
//    enum class Action {
//        Hit,
//        Double,
//        Break
//    };
//
//    explicit MyFirstSolutionSolution(BJIObject &in_out, long double k0_k, long double k0_b, long double k0_min,
//                                     long double k0_max,
//                                     long double k1_k, long double k1_b, long double k1_min, long double k1_max,
//                                     long double k2_k,
//                                     long double k2_b, long double k2_min, long double k2_max,
//                                     long double max_bet_percent,
//                                     long double max_n_for_double, long double min_next_n_probability_for_double,
//                                     long double max_n_for_hit, std::uint32_t min_next_n_for_double) :
//            in_out(in_out),
//            k0(new LinealRegression<long double>(nullptr, k0_k, k0_b), k0_min, k0_max),
//            k1(new LinealRegression<long double>(nullptr, k1_k, k1_b), k1_min, k1_max),
//            k2(new LinealRegression<long double>(nullptr, k2_k, k2_b), k2_min, k2_max),
//            now_deck(true), my_hand(false), dealer_hand(false),
//            max_bet_percent(max_bet_percent), max_n_for_double(max_n_for_double),
//            min_next_n_probability_for_double(min_next_n_probability_for_double), max_n_for_hit(max_n_for_hit),
//            min_next_n_for_double(min_next_n_for_double) {}
//
//    long double ProbabilityNextCardSumBtn(std::uint32_t n) {
//        return now_deck.ProbabilityThatCardBTN((n >= my_hand.GetSum(true) ? n - my_hand.GetSum(true) : 0),
//                                               my_hand.GetSum(true) > 10);
//    }
//
//    Action GetAction() {
//        if (my_hand.GetSum(true) >= 20) return Action::Break;
//        auto n = ProbabilityNextCardSumBtn(21);
//        if (n <= max_n_for_double &&
//            ProbabilityNextCardSumBtn(min_next_n_for_double) >= min_next_n_probability_for_double)
//            if (bet * 2 <= balance * max_bet_percent)
//                return Action::Double;
//        if (n <= max_n_for_hit) return Action::Hit;
//        return Action::Break;
//    }
//
//    void ProcessNewPlayerCard(char card) {
//        my_hand.AddCard(card);
//        now_deck.DeleteCard(card);
//    }
//
//    void Solute() {
//        for (std::uint32_t round = 0; round < 10001; ++round) {
//            if (balance >= 4200000) break;
//            if (in_out.StartReadIsShuffle()) now_deck.ResetToStartDeck();
//            bet = std::min<std::uint32_t>(
//                    std::min<std::uint32_t>(balance * k0(balance) * k1(now_deck.GetCardsCount()) * k2(balance),
//                                            balance * max_bet_percent), balance);
//            auto my_and_dealer_hands = in_out.StartBet(bet);
//            dealer_hand.swap(std::move(*my_and_dealer_hands.first));
//            my_hand.swap(std::move(*my_and_dealer_hands.second));
//            delete my_and_dealer_hands.first;
//            delete my_and_dealer_hands.second;
//            now_deck.DeleteCards(dealer_hand);
//            now_deck.DeleteCards(my_hand);
//            for (auto action = GetAction(); action != Action::Break; action = GetAction()) {
//                if (action == Action::Hit) {
//                    ProcessNewPlayerCard(in_out.Hit());
//                } else {
//                    ProcessNewPlayerCard(in_out.Double());
//                    bet *= 2;
//                }
//            }
//            dealer_hand = in_out.Break();
//            auto my_res = (21 >= my_hand.GetSum(true) ? 21 - my_hand.GetSum(true) : 21);
//            auto dealer_res = (21 >= dealer_hand.GetSum(true) ? 21 - dealer_hand.GetSum(true) : 21);
//            if (my_res > dealer_res)balance -= bet;
//            else if (my_res < dealer_res)balance += bet;
//        }
//        in_out.StartReadIsShuffle();
//        in_out.Exit();
//    }
//
//};

class UAPCSolution {
public:
    Deck now_deck, dealer_hand, my_hand;
    std::uint32_t balance = 500000, bet;
    std::int32_t now_counting_value = 0;
    BJIObject &in_out;
    const std::map<char, std::int32_t> counting_cards_values{{'2', 1},
                                                             {'3', 2},
                                                             {'4', 2},
                                                             {'5', 3},
                                                             {'6', 2},
                                                             {'7', 2},
                                                             {'8', 1},
                                                             {'9', -1},
                                                             {'0', -3},
                                                             {'J', -3},
                                                             {'Q', -3},
                                                             {'K', -3},
                                                             {'A', 0}};
    enum class Action {
        Hit,
        Double,
        Break
    };

    LinealRegression<long double> ase_koef;
    MinMaxLimit<long double> value_to_percent, value_to_is_double;

//    [[nodiscard]] long double ProbabilityNextCardSumBtn(std::uint32_t n) const {
//        return now_deck.ProbabilityThatCardBTN((n >= my_hand.GetSum(true) ? n - my_hand.GetSum(true) : 0),
//                                               my_hand.GetSum(true) > 10);
//    }

    Action GetAction() {
        if (my_hand.GetSum(true) >= 20) return Action::Break;
        long double start_value = std::round(ase_koef(now_deck.GetCardCount('A'))) + now_counting_value;

//        auto n = ProbabilityNextCardSumBtn(21);
//        if (n <= max_n_for_double &&
//            ProbabilityNextCardSumBtn(min_next_n_for_double) >= min_next_n_probability_for_double)
        if (bet * 2 <= balance)
            if (value_to_is_double(start_value / (static_cast<long double>(now_deck.GetCardsCount()) / 52 + 1)) > 0.5)
                return Action::Double;
//        if (n <= max_n_for_hit) return Action::Hit;
        return Action::Hit;
    }

    void ProcessNewPlayerCard(char card) {
        my_hand.AddCard(card);
        now_deck.DeleteCard(card);
        now_counting_value += counting_cards_values.find(card)->second;
    }

    void Solute() {
        for (std::uint32_t round = 0; round < 10001; ++round) {
            if (balance >= 4200000) break;
            if (in_out.StartReadIsShuffle()) {
                now_deck.ResetToStartDeck();
                now_counting_value = 0;
            }
            long double start_value = std::round(ase_koef(now_deck.GetCardCount('A'))) + now_counting_value;
            bet = static_cast<std::uint32_t>(
                    value_to_percent(start_value / (static_cast<long double>(now_deck.GetCardsCount()) / 52 + 1)) *
                    balance);
            auto my_and_dealer_hands = in_out.StartBet(bet);
            dealer_hand.swap(std::move(*my_and_dealer_hands.first));
            my_hand.swap(std::move(*my_and_dealer_hands.second));
            delete my_and_dealer_hands.first;
            delete my_and_dealer_hands.second;
            for (const auto &c: dealer_hand.GetRawData())
                now_counting_value += counting_cards_values.find(c.first)->second * static_cast<std::int32_t>(c.second);
            for (const auto &c: my_hand.GetRawData())
                now_counting_value += counting_cards_values.find(c.first)->second * static_cast<std::int32_t>(c.second);
            now_deck.DeleteCards(dealer_hand);
            now_deck.DeleteCards(my_hand);
            for (auto action = GetAction(); action != Action::Break; action = GetAction()) {
                if (action == Action::Hit) {
                    ProcessNewPlayerCard(in_out.Hit());
                } else {
                    ProcessNewPlayerCard(in_out.Double());
                    bet *= 2;
                }
            }
            char start_dealer_card = dealer_hand.GetRawData().begin()->first;
            dealer_hand = in_out.Break();
            for (const auto &card: dealer_hand.GetRawData()) {
                now_counting_value
                        += counting_cards_values.find(card.first)->second *
                           static_cast<std::int32_t>(card.first == start_dealer_card ? card.second - 1 : card.second);
            }
            auto my_res = (21 >= my_hand.GetSum(true) ? 21 - my_hand.GetSum(true) : 21);
            auto dealer_res = (21 >= dealer_hand.GetSum(true) ? 21 - dealer_hand.GetSum(true) : 21);
            if (my_res > dealer_res)balance -= bet;
            else if (my_res < dealer_res)balance += bet;
        }
        in_out.StartReadIsShuffle();
        in_out.Exit();
    }

    explicit UAPCSolution(BJIObject &in_out)
            : in_out(in_out), now_deck(true), ase_koef(nullptr, 0, -3, 24, 3),
              value_to_percent(
                      new SquareRegression<long double>(nullptr, 0.00000107282706643729,
                                                        0.00046292717293356267, 0.04999999999999998890), 0, 1),
              value_to_is_double(
                      new SquareRegression<long double>(nullptr, 0.00000127385926108,
                                                        0.00119872614073892, 0.25000000000000000), 0, 1)/*,
              max_bet_percent(0.5), max_n_for_double(0.0902445), min_next_n_probability_for_double(0.648217),
              max_n_for_hit(0.645046), min_next_n_for_double(15)*/ {}
};

class ConsoleBJIObject : public BJIObject {
private:
    std::string temp;
public:
    bool StartReadIsShuffle() override {
        std::cin >> temp;
        if (temp == "shuffle") {
            std::cin >> temp;
            return true;
        }
        return false;
    }

    void Exit() override {
        std::cout << "-1\n";
        std::cout.flush();
    }

    std::pair<Deck *, Deck *> StartBet(std::uint32_t bet) override {
        std::cout << bet << "\n";
        std::cout.flush();
        std::cin >> temp;
        Deck *dealer_hand = new Deck(), *my_hand = new Deck();
        dealer_hand->AddCard(temp[0]);
        my_hand->AddCard(temp[2]);
        my_hand->AddCard(temp[3]);
        return {dealer_hand, my_hand};
    }

    char Hit() override {
        std::cout << "hit\n";
        std::cout.flush();
        std::cin >> temp;
        return temp.back();
    }

    char Double() override {
        std::cout << "double\n";
        std::cout.flush();
        std::cin >> temp;
        return temp.back();
    }

    Deck Break() override {
        std::cout << "break\n";
        std::cout.flush();
        std::cin >> temp;
        Deck dealer_hand;
        for (std::uint32_t i = 0; i < temp.size() && temp[i] != '#'; ++i) dealer_hand.AddCard(temp[i]);
        return dealer_hand;
    }
};

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
            for (const auto &d: deck.GetRawData()) {
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

    class TestBJIObject : public BJIObject {
    public:
        std::uint32_t player_balance = 500000, player_bet = 0, motion_id = 0;
        Deck now_deck, player_hand, dealer_hand;

        bool StartReadIsShuffle() override {
            ++motion_id;
            player_hand.Clear();
            dealer_hand.Clear();
            if (now_deck.GetCardsCount() < 20) {
                now_deck.ResetToStartDeck();
                return true;
            }
            return false;
        }

        void Exit() override {
        }

        std::pair<Deck *, Deck *> StartBet(std::uint32_t bet) override {
            player_bet = bet;
            auto dealer_card = Random::GetRandomCardFromDeck(now_deck);
            now_deck.DeleteCard(dealer_card);
            dealer_hand.AddCard(dealer_card);
            auto first_player_card = Random::GetRandomCardFromDeck(now_deck);
            now_deck.DeleteCard(first_player_card);
            player_hand.AddCard(first_player_card);
            auto second_player_card = Random::GetRandomCardFromDeck(now_deck);
            now_deck.DeleteCard(second_player_card);
            player_hand.AddCard(second_player_card);
            return std::pair<Deck *, Deck *>{new Deck(dealer_hand), new Deck(player_hand)};
        }

        char Hit() override {
            auto new_player_card = Random::GetRandomCardFromDeck(now_deck);
            now_deck.DeleteCard(new_player_card);
            player_hand.AddCard(new_player_card);
            return new_player_card;
        }

        char Double() override {
            player_bet *= 2;
            auto new_player_card = Random::GetRandomCardFromDeck(now_deck);
            now_deck.DeleteCard(new_player_card);
            player_hand.AddCard(new_player_card);
            return new_player_card;
        }

        Deck Break() override {
            if (player_balance > 100)std::cout << player_balance << "\n";
            while (dealer_hand.GetSum(true) < 17 && now_deck.GetCardsCount() > 0) {
                auto new_dealer_card = Random::GetRandomCardFromDeck(now_deck);
                now_deck.DeleteCard(new_dealer_card);
                dealer_hand.AddCard(new_dealer_card);
            }
            std::uint32_t player_res = (21 >= player_hand.GetSum(true) ? 21 - player_hand.GetSum(true) : 21);
            std::uint32_t dealer_res = (21 >= dealer_hand.GetSum(true) ? 21 - dealer_hand.GetSum(true) : 21);
            if (player_res > dealer_res) player_balance -= player_bet;
            else if (player_res < dealer_res) player_balance += player_bet;
            return dealer_hand;
        }
    };

//    void Test() {
//        std::ofstream out_file("out.txt");
//        out_file << "seed: " << Random::seed << "\n\n";
//        out_file.flush();
//        while (true) {
//            std::uint32_t winned = 0;
//            long double k0_x1 = Random::GetRandomLongDouble(1e6, 1e7),
//                    k0_y1 = Random::GetRandomLongDouble(0.03, 0.2),
//                    k0_x2 = Random::GetRandomLongDouble(5e4, 4e5),
//                    k0_y2 = Random::GetRandomLongDouble(0.2, 0.8),
//                    k0_min = Random::GetRandomLongDouble(0.005, 0.05),
//                    k0_max = Random::GetRandomLongDouble(0.25, 0.75),
//                    k1_x1 = 312,
//                    k1_y1 = Random::GetRandomLongDouble(0.8, 1.02),
//                    k1_x2 = Random::GetRandomLongDouble(5, 20),
//                    k1_y2 = Random::GetRandomLongDouble(1.25, 1.75),
//                    k1_min = 1,
//                    k1_max = Random::GetRandomLongDouble(1.25, 1.75),
//                    k2_x1 = Random::GetRandomLongDouble(1e6, 1e7),
//                    k2_y1 = 1,
//                    k2_x2 = Random::GetRandomLongDouble(5e4, 2e5),
//                    k2_y2 = Random::GetRandomLongDouble(0.25, 0.75),
//                    k2_min = Random::GetRandomLongDouble(0.3, 0.9),
//                    k2_max = 1,
//                    max_bet_percent = Random::GetRandomLongDouble(0.3, 0.7),
//                    max_n_for_double = Random::GetRandomLongDouble(0.05, 0.2),
//                    min_next_n_probability_for_double = Random::GetRandomLongDouble(0.5, 0.95),
//                    max_n_for_hit = Random::GetRandomLongDouble(0.25, 0.75);
//            std::uint32_t min_next_n_for_double = Random::GetRandomInt(5, 20);
//            MinMaxLimit<long double> k0(new LinealRegression<long double>(nullptr, k0_x1, k0_y1, k0_x2, k0_y2), k0_min,
//                                        k0_max), k1(
//                    new LinealRegression<long double>(nullptr, k1_x1, k1_y1, k1_x2, k1_y2), k1_min, k1_max), k2(
//                    new LinealRegression<long double>(nullptr, k2_x1, k2_y1, k2_x2, k2_y2), k2_min, k2_max);
//            out_file << "{";
//            out_file << "{k0_k, " << dynamic_cast<LinealRegression<long double> *>(k0.pre_regression.get())->k << "},";
//            out_file << "{k0_b, " << dynamic_cast<LinealRegression<long double> *>(k0.pre_regression.get())->b << "},";
//            out_file << "{k0_min, " << k0_min << "},";
//            out_file << "{k0_max, " << k0_max << "},";
//            out_file << "{k1_k, " << dynamic_cast<LinealRegression<long double> *>(k1.pre_regression.get())->k << "},";
//            out_file << "{k1_b, " << dynamic_cast<LinealRegression<long double> *>(k1.pre_regression.get())->b << "},";
//            out_file << "{k1_min, " << k1_min << "},";
//            out_file << "{k1_max, " << k1_max << "},";
//            out_file << "{k2_k, " << dynamic_cast<LinealRegression<long double> *>(k2.pre_regression.get())->k << "},";
//            out_file << "{k2_b, " << dynamic_cast<LinealRegression<long double> *>(k2.pre_regression.get())->b << "},";
//            out_file << "{k2_min, " << k2_min << "},";
//            out_file << "{k2_max, " << k2_max << "},";
//            out_file << "{max_bet_percent, " << max_bet_percent << "},";
//            out_file << "{max_n_for_double, " << max_n_for_double << "},";
//            out_file << "{min_next_n_probability_for_double, " << min_next_n_probability_for_double << "},";
//            out_file << "{max_n_for_hit, " << max_n_for_hit << "}";
//            out_file << "{min_next_n_for_double, " << min_next_n_for_double << "}";
//            out_file << "}\n";
//            out_file.flush();
//            for (std::uint32_t i = 0; i < 100; ++i) {
//                TestBJIObject test_in_out;
////                MyFirstSolutionSolution sol(test_in_out,
////                                            dynamic_cast<LinealRegression<long double> *>(k0.pre_regression.get())->k,
////                                            dynamic_cast<LinealRegression<long double> *>(k0.pre_regression.get())->b,
////                                            k0_min, k0_max,
////                                            dynamic_cast<LinealRegression<long double> *>(k1.pre_regression.get())->k,
////                                            dynamic_cast<LinealRegression<long double> *>(k1.pre_regression.get())->b,
////                                            k1_min,
////                                            k1_max,
////                                            dynamic_cast<LinealRegression<long double> *>(k2.pre_regression.get())->k,
////                                            dynamic_cast<LinealRegression<long double> *>(k2.pre_regression.get())->b,
////                                            k2_min, k2_max, max_bet_percent, max_n_for_double,
////                                            min_next_n_probability_for_double, max_n_for_hit, min_next_n_for_double);
//                sol.Solute();
//                if (test_in_out.player_balance != sol.balance) {
//                    out_file << "ERROR\n";
//                }
//                if (test_in_out.player_balance >= 4200000) {
//                    ++winned;
//                }
//            }
//            out_file << "Probability " << (static_cast<long double>(winned) / static_cast<long double>(100)) << "\n";
//            out_file.flush();
//        }
//    }
}


int main() {
//    Testing::Test();
//    Testing::TestBJIObject test_in_out;
//    ConsoleBJIObject console_in_out;
//    long double k0_k = -3.75859e-08, k0_b = 0.226961, k0_min = 0.00790036, k0_max = 0.461925, k1_k = -0.00112462, k1_b = 1.29651, k1_min = 1.0, k1_max = 1.58623, k2_k = 1.26713e-07, k2_b = 0.304463, k2_min = 0.464197, k2_max = 1.0, max_bet_percent = 0.465443, max_n_for_double = 0.0902445, min_next_n_probability_for_double = 0.648217, max_n_for_hit = 0.645046;
//    std::uint32_t min_next_n_for_double = 15;
//    MyFirstSolutionSolution sol(
//            console_in_out, k0_k, k0_b, k0_min, k0_max, k1_k, k1_b, k1_min, k1_max, k2_k, k2_b, k2_min,
//            k2_max, max_bet_percent, max_n_for_double, min_next_n_probability_for_double,
//            max_n_for_hit, min_next_n_for_double);
//    Testing::TestBJIObject test_in_out;
    ConsoleBJIObject console_in_out;
    UAPCSolution uapc_sol(console_in_out);
    uapc_sol.Solute();
//    std::cout << test_in_out.player_balance;
}