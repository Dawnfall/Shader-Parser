#pragma once

#include <string>

namespace spars
{
	enum class TokenType
	{
		NUMBER, // 0 - 9
		IDENTIFIER, // a-z, A-Z , _
		OPERATOR, // + - * / % = += -= *= /= %= == != < > <= >= && || ! & | ^ ~ << >> ++ -- ?
		HASHTAG,
		FUNCTION_BRACKET_OPEN,
		FUNCTION_BRACKET_CLOSED,
		SCOPE_BRACKET_OPEN,
		SCOPE_BRACKET_CLOSED,
		ACCESS_BRACKET_OPEN,
		ACCESS_BRACKET_CLOSED,
		SEMICOLON, // ;
		COMMA, // ,
		DOT, // .
		COLON, // :
		EMPTY
	};

	struct Token
	{
		TokenType Type = TokenType::EMPTY;
		std::string Str{};

		auto operator<=>(const Token&) const = default;
	};
}

