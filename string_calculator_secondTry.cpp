#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>

// A helper function to split a string by multiple delimiters.
// It returns a vector of strings (tokens).
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

// A helper function to process the numbers, check for negatives, and compute the sum.
int processNumbers(const std::vector<std::string>& tokens) {
    int sum = 0;
    std::vector<int> negatives;
    
    // Iterate through each token to parse, validate, and sum.
    for (const auto& token : tokens) {
        if (token.empty()) {
            continue; // Skip empty tokens that can result from multiple delimiters.
        }
        try {
            int number = std::stoi(token);
            if (number < 0) {
                negatives.push_back(number);
            }
            sum += number;
        } catch (const std::invalid_argument& e) {
            // Handle non-numeric strings gracefully if they occur.
            // For this problem, we assume all tokens are valid numbers.
        }
    }
    
    // If any negative numbers were found, throw an exception.
    if (!negatives.empty()) {
        std::string error_msg = "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            error_msg += std::to_string(negatives[i]);
            if (i < negatives.size() - 1) {
                error_msg += ", ";
            }
        }
        throw std::runtime_error(error_msg);
    }
    
    return sum;
}

// The main String Calculator function.
int Add(const std::string& numbers) {
    // 1. Handle empty string case.
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiters = ",";
    std::string numbers_str = numbers;

    // 2. Check for custom delimiters.
    if (numbers.substr(0, 2) == "//") {
        size_t newline_pos = numbers.find('\n');
        if (newline_pos != std::string::npos) {
            delimiters = numbers.substr(2, newline_pos - 2);
            numbers_str = numbers.substr(newline_pos + 1);
        }
    }

    // Add newline as a default delimiter if not already present.
    if (delimiters.find('\n') == std::string::npos) {
        delimiters += '\n';
    }

    // 3. Split the string into number tokens.
    std::vector<std::string> tokens = split(numbers_str, delimiters);

    // 4. Process the numbers to validate and sum.
    return processNumbers(tokens);
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
