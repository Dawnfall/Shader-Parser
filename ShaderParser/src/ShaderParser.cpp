#include "ShaderParser.h"
#include <cctype>
#include <string>
#include <vector>
#include "Token.h"

#include <expected>

namespace spars
{
	static inline bool IsDigit(char c)
	{
		return std::isdigit(static_cast<unsigned char>(c));
	}

	static inline bool IsLetter(char c)
	{
		return (c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z');
	}

	static inline const Token* getToken(const std::vector<Token>& tokens, size_t index)
	{
		if (index >= tokens.size())
			return &tokens[index];
		return nullptr;
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

	std::vector<Token> ShaderParser::Tokenize(const std::string& str)const
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
				emit(c, TokenType::DOT);
			else if (IsLetter(c) || c == '_')
				emit(c, TokenType::IDENTIFIER);
		}

		return tokens;
	}

	//auto ShaderParser::DetectGroups(const std::vector<Token>& tokens)const
	//{
		//std::expected<bool, std::vector<Group>> result;

		//for (size_t i = 0; i < tokens.size(); ++i)
		//{
		//	const auto& startToken = tokens[i];
		//	switch (startToken.Type)
		//	{
		//	case TokenType::HASHTAG:
		//	{
		//		GroupResult res = HandleHashTag(tokens, i);
		//		if (!res)
		//			return {};
		//		result.emplace_back(res,);
		//		break;
		//	}
		//	default:
		//		break;
		//		//we look for first and determine 
		//	}
		//}
		//return result;

	//}

	GroupResult ShaderParser::HandleHashTag(const std::vector<Token>& tokens, size_t i)const
	{
		const Token* hashToken = getToken(tokens, i);
		const Token* wordToken = getToken(tokens, i + 1);
		if (!wordToken || wordToken->Type != TokenType::IDENTIFIER)
			return  std::unexpected(false);

		const Token* emptyToken = getToken(tokens, i + 2);
		if (!emptyToken)
			return  std::unexpected(false);

		if (wordToken->Str == "include")
		{
			auto fileNameToken = getToken(tokens, i + 3);
			auto dotToken = getToken(tokens, i + 4);
			auto extToken = getToken(tokens, i + 5);
			auto lastEmptyToken = getToken(tokens, i + 6);

			if (!fileNameToken || !dotToken || !extToken || !lastEmptyToken)
				return  std::unexpected(false);
		}
		else if (wordToken->Str == "use")
		{
			auto keyWordToken = getToken(tokens, i + 3);
			auto lastEmptyToken = getToken(tokens, i + 4);

			if (!keyWordToken || !lastEmptyToken)
				return  std::unexpected(false);
		}
	}
}