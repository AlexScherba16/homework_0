#include "gtest/gtest.h"
#include "lib.h"

TEST(testValidVersion, versionIsBiggerNull)
{
    ASSERT_TRUE(version() > 0);	
}
