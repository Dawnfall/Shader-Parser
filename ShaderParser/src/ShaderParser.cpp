#include "ShaderParser.h"
#include <cctype>
#include <string>

namespace Twisted
{
	inline bool IsDigit(char c) {
		return std::isdigit(static_cast<unsigned char>(c));
	}

	inline bool IsLetter(char c) {
		return (c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z');
	}


	std::string ShaderParser::RemoveComments(const std::string& str)const
	{
		std::string outStr;

		COMMENT_REMOVE_MODE mode = COMMENT_REMOVE_MODE::NORMAL;

		for (size_t i = 0; i < str.size(); i++)
		{
			if (mode == COMMENT_REMOVE_MODE::NORMAL)
			{
				if (i < str.size() - 1 && str[i] == '/' && str[i + 1] == '/')
				{
					i += 1;
					mode = COMMENT_REMOVE_MODE::LINE_COMMENT;
				}
				else if (i < str.size() - 1 && str[i] == '/' && str[i + 1] == '*')
				{
					i += 1;
					mode = COMMENT_REMOVE_MODE::MULTI_LINE_COMMENT;
				}
				else
					outStr += str[i];
			}
			else if (mode == COMMENT_REMOVE_MODE::LINE_COMMENT)
			{
				if (str[i] == '\n')
				{
					outStr += '\n';
					mode = COMMENT_REMOVE_MODE::NORMAL;
				}
			}
			else if (mode == COMMENT_REMOVE_MODE::MULTI_LINE_COMMENT)
			{
				if (i < str.size() - 1 && str[i] == '*' && str[i + 1] == '/')
				{
					i += 1;
					mode = COMMENT_REMOVE_MODE::NORMAL;
				}
			}
		}
		return outStr;
	}

	std::vector<Token> ShaderParser::Tokenize(const std::string& str)
	{
		std::vector<Token> tokens;

		auto emit = [&tokens](char c, TokenType type) {
			if (!tokens.empty() && tokens.back().Type == type)
			{
				if (type == TokenType::NUMBER || type == TokenType::IDENTIFIER || type == TokenType::EMPTY)
				{
					tokens.back().Str += c;
					return;
				}
			}

			Token newToken;
			newToken.Str = c;
			newToken.Type = type;
			tokens.emplace_back(newToken);
			};

		for (size_t i = 0; i < str.size(); i++)
		{
			char c = str[i];
			if (c == '{')
				emit(c, TokenType::SCOPE_BRACKET_OPEN);
			else if (c == '}')
				emit(c, TokenType::SCOPE_BRACKET_CLOSED);
			if (c == '[')
				emit(c, TokenType::ACCESS_BRACKET_OPEN);
			else if (c == ']')
				emit(c, TokenType::ACCESS_BRACKET_CLOSED);
			if (c == '(')
				emit(c, TokenType::FUNCTION_BRACKET_OPEN);
			else if (c == ')')
				emit(c, TokenType::FUNCTION_BRACKET_CLOSED);
			else if (c == '#')
				emit(c, TokenType::HASHTAG);
			else if (c == ';')
				emit(c, TokenType::SEMICOLON);
			else if (c == ' ' || c == '\n' || c == '\t')
				emit(c, TokenType::EMPTY);
			else if (IsDigit(c) || c == '.')
				emit(c, TokenType::NUMBER);
			else if (IsLetter(c) || c == '_')
				emit(c, TokenType::IDENTIFIER);
		}

		return tokens;
	}
}