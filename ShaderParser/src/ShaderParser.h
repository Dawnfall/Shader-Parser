#pragma once

#include "Token.h"

#include <string>
#include <vector>
//#include <sstream>
#include "Core.h"
#include <cctype>
//#include "ParserConstants.h"
#include "Group.h"
#include <expected>

namespace spars
{
	using GroupResult = std::expected<Group, bool>;

	enum class COMMENT_REMOVE_MODE
	{
		NORMAL,
		LINE_COMMENT,
		MULTI_LINE_COMMENT
	};

	class SPARS_API ShaderParser
	{
	public:

		std::string RemoveComments(const std::string& str)const;

		std::vector<Token> Tokenize(const std::string& str)const;

		//std::expected<bool,std::vector<Group>> DetectGroups(const std::vector<Token>& tokens)const;

	private:
		std::vector<Token> RemoveEmpty(const std::vector<Token>& tokens)
		{
			std::vector<Token> filteredResult;
			for (const auto& token : tokens)
				if (token.Type != TokenType::EMPTY)
					filteredResult.emplace_back(token);
			return filteredResult;
		}

		GroupResult HandleHashTag(const std::vector<Token>& tokens, size_t i)const;

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