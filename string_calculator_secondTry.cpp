#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>

// A helper function to split a string by multiple delimiters.
// CCN = 4.
std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;
    
    while ((end = str.find_first_of(delimiters, start)) != std::string::npos) {
        if (end != start) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }
    
    if (start < str.length()) {
        tokens.push_back(str.substr(start));
    }
    
    return tokens;
}

// A helper function to build the negative numbers exception message.
// CCN = 3.
std::string buildNegativeMessage(const std::vector<int>& negatives) {
    std::string error_msg = "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        error_msg += std::to_string(negatives[i]);
        if (i < negatives.size() - 1) {
            error_msg += ",";
        }
    }
    return error_msg;
}

// A helper function to process the numbers, check for negatives, and compute the sum.
// It is designed to have a CCN of 4.
int sumAndValidateTokens(const std::vector<std::string>& tokens) {
    int sum = 0;
    std::vector<int> negatives;
    
    // First pass: parse and find negatives
    for (const auto& token : tokens) {
        if (token.empty()) {
            continue;
        }
        int number = std::stoi(token);
        if (number < 0) {
            negatives.push_back(number);
        }
        sum += number;
    }
    
    // Second pass: check for negatives and throw exception
    if (!negatives.empty()) {
        throw std::runtime_error(buildNegativeMessage(negatives));
    }
    
    return sum;
}

// The main String Calculator function.
// It is designed to have a CCN of 4.
int Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiters = ",\n";
    std::string numbers_str = numbers;

    // Check for custom delimiters.
    if (numbers.substr(0, 2) == "//") {
        size_t newline_pos = numbers.find('\n');
        if (newline_pos != std::string::npos) {
            delimiters = numbers.substr(2, newline_pos - 2);
            numbers_str = numbers.substr(newline_pos + 1);
        }
    }
    
    std::vector<std::string> tokens = split(numbers_str, delimiters);
    
    return sumAndValidateTokens(tokens);
}

// Main function to demonstrate the String Calculator.
int main() {
    // Test cases
    std::cout << "Add(\"\") = " << Add("") << std::endl;
    std::cout << "Add(\"1\") = " << Add("1") << std::endl;
    std::cout << "Add(\"1,2\") = " << Add("1,2") << std::endl;
    std::cout << "Add(\"1,2,3,4,5\") = " << Add("1,2,3,4,5") << std::endl;
    std::cout << "Add(\"1\\n2,3\") = " << Add("1\n2,3") << std::endl;
    std::cout << "Add(\"//;\\n1;2;3\") = " << Add("//;\n1;2;3") << std::endl;
    
    try {
        Add("1,-2");
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        Add("-1,2,-3");
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
