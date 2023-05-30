#include <iostream>
#include <vector>
#include <map>
#include <charconv>
#include <algorithm>


using ElemCounts = std::map<std::string_view, std::uint32_t>;

void PlusElemCounts(ElemCounts &a, const ElemCounts &b) {
    for (const auto &i: b) {
        auto it = a.find(i.first);
        if (it == a.end()) a.insert(i);
        else it->second += i.second;
    }
}

void MultiplyElemCounts(ElemCounts &a, std::uint32_t b) {
    for (auto &&i: a) i.second *= b;
}

bool IsDigit(char c) { return c >= '0' && c <= '9'; }

bool IsBigAlpha(char c) { return c >= 'A' && c <= 'Z'; }

bool IsBigAlphaOrOpenBracket(char c) { return IsBigAlpha(c) || c == '('; }

std::uint32_t GetCloseBracketPos(const std::string_view &str, std::uint32_t open_pos) {
    std::uint32_t opened_cnt = 1;
    for (std::uint32_t i = open_pos + 1; i < str.size(); ++i) {
        if (str[i] == '(') ++opened_cnt;
        else if (str[i] == ')') --opened_cnt;
        if (opened_cnt == 0) return i;
    }
}

class Seq;

class Elem {
public:
    void Init(const std::string_view &str);

    Elem() = default;

    Elem(const Elem &other);

    Elem(Elem &&other);

    bool GetIsSeq() const { return is_seq; };

    const std::string_view &GetChEl() const { return ch_el; }

    const Seq &GetSeq() const { return *seq; }

    ~Elem();

private:
    std::string_view ch_el;
    Seq *seq = nullptr;
    bool is_seq = false;
};

class PieceOfSeq {
public:
    PieceOfSeq(const std::string_view &str) {
        std::uint32_t start_digit_find = (str.front() == '(' ? GetCloseBracketPos(str, 0) + 1 : 0);
        auto first_digit = std::distance(str.begin(),
                                         std::find_if(std::next(str.begin(), start_digit_find), str.end(), IsDigit));
        if (first_digit == str.size()) num = 1;
        else std::from_chars(str.data() + first_digit, str.data() + str.size(), num);
        elem.Init(str.substr(0, first_digit));
    }

    Elem elem;
    std::uint32_t num;
};

class Seq {
public:
    void Init(const std::string_view &str) {
        std::uint32_t start = 0, end;
        do {
            std::uint32_t find_start = (str[start] == '(' ? GetCloseBracketPos(str, start) : start) + 1;
            end = std::distance(str.begin(),
                                std::find_if(std::next(str.begin(), find_start), str.end(), IsBigAlphaOrOpenBracket));
            pieces.emplace_back(str.substr(start, end - start));
            start = end;
        } while (end != str.size());
    }

    Seq() = default;

//    explicit Seq(std::vector<PieceOfSeq> pieces) : pieces(std::move(pieces)) {};

    std::vector <PieceOfSeq> pieces;
};

void Elem::Init(const std::string_view &str) {
    if (str.size() > 2 && str.front() == '(' && str.back() == ')') {
        is_seq = true;
        seq = new Seq();
        seq->Init(str.substr(1, str.size() - 2));
    } else {
        is_seq = false;
        ch_el = std::string_view(str);
    }
}

Elem::~Elem() {
    delete seq;
}

Elem::Elem(const Elem &other) {
    is_seq = other.is_seq;
    if (other.is_seq) this->seq = new Seq(*other.seq);
    else this->ch_el = other.ch_el;
}

Elem::Elem(Elem &&other) : ch_el(other.ch_el) {
    is_seq = other.is_seq;
    if (other.is_seq) {
        this->seq = other.seq;
        other.seq = nullptr;
    }
}

class PieceOfFormula {
public:
    PieceOfFormula(const std::string_view &str) {
        auto first_alpha_or_bracket = std::distance(str.begin(), std::find_if(str.begin(), str.end(),
                                                                              IsBigAlphaOrOpenBracket));
        if (first_alpha_or_bracket == 0) num = 1;
        else std::from_chars(str.data(), str.data() + first_alpha_or_bracket, num);
        seq.Init(str.substr(first_alpha_or_bracket));
    }

    std::uint32_t num;
    Seq seq;
};

class Formula {
public:
    Formula(const std::string_view &str) {
        std::size_t start = 0, end;
        do {
            end = str.find('+', start);
            pieces.emplace_back(str.substr(start, end - start));
            start = end + 1;
        } while (end < str.size());
    }

    std::vector <PieceOfFormula> pieces;
};

ElemCounts GetElemCountsFromSeq(const Seq &seq);

ElemCounts GetElemCountsFromElem(const Elem &elem) {
    if (elem.GetIsSeq()) return GetElemCountsFromSeq(elem.GetSeq());
    else return ElemCounts{{elem.GetChEl(), 1}};
}

ElemCounts GetElemCountsFromPieceOfSeq(const PieceOfSeq &piece_of_seq) {
    ElemCounts res = GetElemCountsFromElem(piece_of_seq.elem);
    MultiplyElemCounts(res, piece_of_seq.num);
    return res;
}

ElemCounts GetElemCountsFromSeq(const Seq &seq) {
    ElemCounts res;
    for (const auto &i: seq.pieces)
        PlusElemCounts(res, GetElemCountsFromPieceOfSeq(i));
    return res;
}

ElemCounts GetElemCountsFromPieceOfFromFormula(const PieceOfFormula &piece_of_formula) {
    ElemCounts res = GetElemCountsFromSeq(piece_of_formula.seq);
    MultiplyElemCounts(res, piece_of_formula.num);
    return res;
}

ElemCounts GetElemCountsFromFormula(const Formula &formula) {
    ElemCounts res;
    for (const auto &i: formula.pieces)
        PlusElemCounts(res, GetElemCountsFromPieceOfFromFormula(i));
    return res;
}

int main() {
    std::string start_str;
    std::cin >> start_str;
    auto start_elem_counts = GetElemCountsFromFormula(Formula(start_str));
    std::uint32_t n;
    std::cin >> n;
    std::vector <std::string> strings(n);
    for (auto &&str: strings) std::cin >> str;
    for (const auto &str: strings) {
        std::cout << start_str;
        if (GetElemCountsFromFormula(Formula(str)) == start_elem_counts) std::cout << "=="; else std::cout << "!=";
        std::cout << str << "\n";
    }
    return 0;
}
