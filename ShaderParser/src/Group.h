#pragma once

#include "Token.h"
#include <vector>

namespace spars
{
	struct Group
	{
		std::vector<Token> tokens;

		auto operator<=>(const Group&) const = default;

	};
}