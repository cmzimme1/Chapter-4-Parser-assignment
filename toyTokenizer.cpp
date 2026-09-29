#include "toyTokenizer.hpp"

const char* tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::A: return "a";
        case TokenType::B: return "b";
        case TokenType::C: return "c";
        case TokenType::ENDFILE: return "ENDFILE";
        case TokenType::UNKNOWN: return "UNKNOWN";
    }
    return "UNKNOWN";
}

TokenType lookupKeyword(char symbol) {
    switch (symbol) {
        case 'a': return TokenType::A;
        case 'b': return TokenType::B;
        case 'c': return TokenType::C;
        default: return TokenType::UNKNOWN;
    }
}

std::vector<Token> tokenize(const std::string& line, std::size_t lineNumber) {
    std::vector<Token> tokens;
    for (std::size_t i = 0; i < line.size(); ++i) {
        tokens.push_back({lookupKeyword(line[i]), line.substr(i, 1), lineNumber, i + 1});
    }
    tokens.push_back({TokenType::ENDFILE, "", lineNumber, line.size() + 1});
    return tokens;
}
