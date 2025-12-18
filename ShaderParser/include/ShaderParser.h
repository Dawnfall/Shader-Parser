#pragma once

#include "Token.h"
#include "Group.h"
#include "Core.h"
#include "Helper.h"

#include <string>
#include <vector>
#include <cctype>
#include <expected>
//#include <sstream>

namespace spars
{
	using GroupResult = std::expected<Group, bool>;

	ParsedShader SPARS_API ParseShader(const std::string& shaderText);

	namespace internal
	{
		std::string RemoveComments(const std::string& shaderText);
		std::vector<Token> Tokenize(const std::string& str);
		std::vector<Token> RemoveEmpty(const std::vector<Token>& tokens);
		GroupResult HandleHashTag(const std::vector<Token>& tokens, size_t i);
		std::expected<bool, std::vector<Group>> DetectGroups(const std::vector<Token>& tokens);
		//std::string ReplaceUseLine(const std::string& input);
	}
}