#include <iostream>
#include <string>
#include <cassert>

int Add(const std::string& numbers) {
    // Handle empty input
    if (numbers.empty()) return 0;

    // Find comma separator (supports up to two numbers)
    size_t commaPos = numbers.find(',');

    // No comma: single number
    if (commaPos == std::string::npos) {
        return std::stoi(numbers);
    }

    // Exactly two numbers: split and convert
    std::string left = numbers.substr(0, commaPos);
    std::string right = numbers.substr(commaPos + 1);

    // Convert both sides (std::stoi will throw if invalid; for this kata we assume valid numeric input)
    int a = left.empty() ? 0 : std::stoi(left);
    int b = right.empty() ? 0 : std::stoi(right);
    return a + b;
}

// Simple tests
int main() {
    // Empty string -> 0
    assert(Add("") == 0);

    // Single numbers
    assert(Add("0") == 0);
    assert(Add("5") == 5);
    assert(Add("42") == 42);

    // Two numbers
    assert(Add("1,2") == 3);
    assert(Add("10,0") == 10);
    assert(Add("7,35") == 42);

    // Edge cases (optional for this step of the kata)
    // Treat missing side as 0
    assert(Add(",3") == 3);
    assert(Add("4,") == 4);

    std::cout << "All tests passed!\n";
    return 0;
}
