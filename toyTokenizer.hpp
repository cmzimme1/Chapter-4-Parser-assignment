#ifndef TOY_TOKENIZER_HPP
#define TOY_TOKENIZER_HPP

#include <cstddef>
#include <string>
#include <vector>

enum class TokenType { A, B, C, ENDFILE, UNKNOWN };

struct Token {
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

const char* tokenTypeName(TokenType type);
TokenType lookupKeyword(char symbol);
std::vector<Token> tokenize(const std::string& line, std::size_t lineNumber);

#endif
