#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <regex>

// Exception for negative numbers
class NegativeNumberException : public std::runtime_error {
public:
    NegativeNumberException(const std::vector<int>& negatives)
        : std::runtime_error("negatives not allowed: " + joinNegatives(negatives)) {}

private:
    static std::string joinNegatives(const std::vector<int>& negatives) {
        std::string msg;
        for (size_t i = 0; i < negatives.size(); ++i) {
            msg += std::to_string(negatives[i]);
            if (i != negatives.size() - 1) msg += ", ";
        }
        return msg;
    }
};

// Helper function: split string by multiple delimiters (comma or newline)
std::vector<std::string> split(const std::string& s, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t pos = 0;
    while ((pos = s.find_first_of(delimiters, start)) != std::string::npos) {
        if (pos > start) {
            tokens.push_back(s.substr(start, pos - start));
        }
        start = pos + 1;
    }
    if (start < s.length()) {
        tokens.push_back(s.substr(start));
    }
    return tokens;
}

// Main Add function
int Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string delimiters = ",\n";
    std::string numString = numbers;

    // Check for custom delimiter pattern: //delimiter\nnumbers
    if (numbers.size() > 2 && numbers[0] == '/' && numbers[1] == '/') {
        size_t newlinePos = numbers.find('\n');
        if (newlinePos == std::string::npos) {
            throw std::invalid_argument("Invalid input: missing newline after delimiter declaration");
        }
        // delimiter is between // and \n
        delimiters = numbers.substr(2, newlinePos - 2);
        if (delimiters.empty()) {
            throw std::invalid_argument("Invalid input: empty custom delimiter");
        }
        numString = numbers.substr(newlinePos + 1);
    }

    // Split numbers by delimiters (multiple delimiters possible)
    std::vector<std::string> tokens = split(numString, delimiters);

    int sum = 0;
    std::vector<int> negatives;

    for (const auto& token : tokens) {
        if (token.empty()) {
            // Invalid cases like "1,\n" will cause empty tokens
            throw std::invalid_argument("Invalid number format: empty number");
        }
        int n;
        try {
            n = std::stoi(token);
        } catch (...) {
            throw std::invalid_argument("Invalid number: " + token);
        }
        if (n < 0) {
            negatives.push_back(n);
        } else {
            sum += n;
        }
    }

    if (!negatives.empty()) {
        throw NegativeNumberException(negatives);
    }

    return sum;
}

// Simple test runner to demo
void runTests() {
    struct Test {
        std::string input;
        int expected;
        bool throws;
        std::string exceptionMsg;
    };

    Test tests[] = {
        {"", 0, false, ""},
        {"1", 1, false, ""},
        {"1,2", 3, false, ""},
        {"1\n2,3", 6, false, ""},
        {"//;\n1;2", 3, false, ""},
        {"//|\n4|5|6", 15, false, ""},
        {"//sep\n7sep8sep9", 24, false, ""},
        {"-1,2,-3", 0, true, "negatives not allowed: -1, -3"},
        {"1,\n", 0, true, "Invalid number format: empty number"},
    };

    for (auto& test : tests) {
        try {
            int result = Add(test.input);
            if (test.throws) {
                std::cerr << "Test failed: expected exception but got result " << result << "\n";
            } else if (result != test.expected) {
                std::cerr << "Test failed for input: '" << test.input << "' Expected: " << test.expected << " Got: " << result << "\n";
            } else {
                std::cout << "Test passed: '" << test.input << "' = " << result << "\n";
            }
        } catch (const std::exception& e) {
            if (!test.throws) {
                std::cerr << "Test failed: unexpected exception '" << e.what() << "' for input '" << test.input << "'\n";
            } else if (test.exceptionMsg != e.what()) {
                std::cerr << "Test failed: exception mismatch. Expected '" << test.exceptionMsg << "', got '" << e.what() << "'\n";
            } else {
                std::cout << "Test passed with expected exception: '" << e.what() << "'\n";
            }
        }
    }
}

int main() {
    runTests();
    return 0;
}
