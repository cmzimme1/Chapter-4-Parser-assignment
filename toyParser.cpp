#include "toyTokenizer.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)) {}

    bool parse() {
        if (!parseA()) return false;
        if (peek().type == TokenType::C) {
            ++position_; 
            if (!parseB()) return false;
        }
        if (peek().type != TokenType::ENDFILE) {
            fail("end of input");
            return false;
        }
        return true;
    }

    const std::string& error() const { return error_; }

private:
    const Token& peek() const { return tokens_[position_]; }

    bool parseA() {
        if (peek().type != TokenType::A) {
            fail("a");
            return false;
        }
        do { ++position_; } while (peek().type == TokenType::A);
        return true;
    }

    bool parseB() {
        if (peek().type != TokenType::B) {
            fail("b");
            return false;
        }
        do { ++position_; } while (peek().type == TokenType::B);
        return true;
    }

    void fail(const std::string& expected) {
        const Token& token = peek();
        error_ = "line " + std::to_string(token.line) + ", column " +
                 std::to_string(token.column) + ": expected " + expected +
                 ", found " + tokenTypeName(token.type);
        if (token.type != TokenType::ENDFILE) {
            error_ += " ('" + token.lexeme + "')";
        }
    }

    std::vector<Token> tokens_;
    std::size_t position_ = 0;
    std::string error_;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 2;
    }

    std::string line;
    std::size_t lineNumber = 0;
    std::size_t programs = 0;
    std::size_t accepted = 0;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.find_first_not_of(" \t") == std::string::npos) continue;
        ++programs;
        Parser parser(tokenize(line, lineNumber));
        if (parser.parse()) {
            ++accepted;
            std::cout << "Line " << lineNumber << " (" << line << "): ACCEPTED\n";
        } else {
            std::cout << "Line " << lineNumber << " (" << line << "): REJECTED - "
                      << parser.error() << '\n';
        }
    }
    if (input.bad()) {
        std::cerr << "Error while reading file: " << argv[1] << '\n';
        return 2;
    }
    std::cout << "Result: " << accepted << "/" << programs << " accepted\n";
    return accepted == programs ? 0 : 1;
}
