#include <gtest/gtest.h>
#include "ShaderParser.h"
#include "Token.h"

#include <string>
#include <vector>

inline const std::string testStr=R"(
#include someFile.h;
#use somePredefinedCode;

void vert()
{
}
)";

inline const std::vector<spars::Token> expectedResult = {
spars::Token{spars::TokenType::EMPTY,"\n"},
spars::Token{spars::TokenType::HASHTAG,"#"},
spars::Token{spars::TokenType::IDENTIFIER,"include"},
spars::Token{spars::TokenType::EMPTY," "},
spars::Token{spars::TokenType::IDENTIFIER,"someFile"},
spars::Token{spars::TokenType::DOT,"."},
spars::Token{spars::TokenType::IDENTIFIER,"h"},
spars::Token{spars::TokenType::SEMICOLON,";"},
spars::Token{spars::TokenType::EMPTY,"\n"},

spars::Token{spars::TokenType::HASHTAG,"#"},
spars::Token{spars::TokenType::IDENTIFIER,"use"},
spars::Token{spars::TokenType::EMPTY," "},
spars::Token{spars::TokenType::IDENTIFIER,"somePredefinedCode"},
spars::Token{spars::TokenType::SEMICOLON,";"},
spars::Token{spars::TokenType::EMPTY,"\n\n"},

spars::Token{spars::TokenType::IDENTIFIER,"void"},
spars::Token{spars::TokenType::EMPTY," "},
spars::Token{spars::TokenType::IDENTIFIER,"vert"},
spars::Token{spars::TokenType::FUNCTION_BRACKET_OPEN,"("},
spars::Token{spars::TokenType::FUNCTION_BRACKET_CLOSED,")"},
spars::Token{spars::TokenType::EMPTY,"\n"},

spars::Token{spars::TokenType::SCOPE_BRACKET_OPEN,"{"},
spars::Token{spars::TokenType::EMPTY,"\n"},
spars::Token{spars::TokenType::SCOPE_BRACKET_CLOSED,"}"},
spars::Token{spars::TokenType::EMPTY,"\n"}
};

TEST(ShaderPareserTests, TokenTest)
{
	auto res = spars::internal::Tokenize(testStr);
	EXPECT_EQ(expectedResult, res);
}