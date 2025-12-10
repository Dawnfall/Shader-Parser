#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "ParserConstants.h"

namespace Twisted
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
		TokenType Type;
		std::string Str;
	};

	enum class COMMENT_REMOVE_MODE
	{
		NORMAL,
		LINE_COMMENT,
		MULTI_LINE_COMMENT
	};
	class ShaderParser
	{
	public:

		std::string RemoveComments(const std::string& str)const;

		std::vector<Token> Tokenize(const std::string& str);
		//std::string ReplaceUseLine(const std::string& input)
		//{
		//	size_t startPos = detectWord(Constants::SHADER_USE_KEYWORD, input, 0);
		//	if (startPos == std::string::npos)
		//		return input;



		//	while (std::getline(ss, line))
		//	{
		//		if (line.rfind("#USE", 0) == 0)
		//		{
		//			out += replacement + "\n";
		//		}
		//		else
		//		{
		//			out += line + "\n";
		//		}
		//	}
		//	return out;
		//}
	private:
		size_t detectWord(const std::string& str, const std::string& word, size_t beginSearchPos)
		{
			if (beginSearchPos > str.size()) return std::string::npos;
			return str.find(word, beginSearchPos);
		}

		size_t detectSpaces(const std::string& str, size_t startPos)
		{
			if (startPos >= str.size()) return std::string::npos;

			size_t i = startPos;
			if (!std::isspace(static_cast<unsigned char>(str[i])))
				return std::string::npos;  // must start with whitespace

			while (i < str.size() &&
				std::isspace(static_cast<unsigned char>(str[i])))
			{
				++i;
			}

			return i; // return first non-whitespace char index
		}


	};


}