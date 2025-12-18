#pragma once

#include <string>

namespace spars
{
	enum class COMMENT_REMOVE_MODE
	{
		NORMAL,
		LINE_COMMENT,
		MULTI_LINE_COMMENT
	};

	struct ParsedShader
	{
		std::string VertexShader{};
		std::string FragmentShader{};
		std::string GeometryShader{};
	};

	inline bool IsDigit(char c)
	{
		return std::isdigit(static_cast<unsigned char>(c));
	}

	inline bool IsLetter(char c)
	{
		return (c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z');
	}

	inline const Token* getToken(const std::vector<Token>& tokens, size_t index)
	{
		if (index >= tokens.size())
			return &tokens[index];
		return nullptr;
	}

	inline size_t detectWord(const std::string& str, const std::string& word, size_t beginSearchPos)
	{
		if (beginSearchPos > str.size()) return std::string::npos;
		return str.find(word, beginSearchPos);
	}

	inline size_t detectSpaces(const std::string& str, size_t startPos)
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


}