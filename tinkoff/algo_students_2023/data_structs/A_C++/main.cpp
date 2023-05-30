#include <iostream>
#include <stack>

int main() {
    std::stack<std::int32_t> stack;
    std::string line;
    std::getline(std::cin, line);
    for (std::uint32_t i = 0; i < line.size(); i += 2) {
        if (line[i] >= '0' && line[i] <= '9') stack.push(line[i] - '0');
        else {
            auto b = stack.top();
            stack.pop();
            auto a = stack.top();
            stack.pop();
            if (line[i] == '+') stack.push(a + b);
            else if (line[i] == '-') stack.push(a - b);
            else if (line[i] == '*') stack.push(a * b);
        }
    }
    std::cout << stack.top();
    return 0;
}
