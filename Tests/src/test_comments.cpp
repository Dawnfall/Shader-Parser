#include <gtest/gtest.h>
#include "ShaderParser.h"

#include <string>

const std::string testStr = R"(
#include "someFile.h";
#use "somePredefinedCode"; //first comment

void vert()
{
/* multi
line 
comment */
}
)";

const std::string testStrRemovedComments = R"(
#include "someFile.h";
#use "somePredefinedCode";

void vert()
{
}
)";

TEST(ShaderParserTests, CommentsTest)
{
	auto result = spars::internal::RemoveComments(testStr);
	EXPECT_EQ(testStr, testStr);
}