/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}
*/
TEST(SetGuesserTest, set_secret)
{
	Guesser guesser("secret");
	bool actual = guesser.match("secret");
	ASSERT_EQ(true, actual);
}
TEST(SetGuesserTest, truncate_secret)
{
	Guesser guesser("1234567890123456789012345678901234567890"); // 40 characters
	bool actual = guesser.match("12345678901234567890123456789012"); // truncate to 32 characters
	ASSERT_EQ(true, actual);
}
TEST(SetGuesserTest, empty_secret)
{
	Guesser guesser("");
	bool actual = guesser.match("");
	ASSERT_EQ(true, actual);
}
TEST(SetGuesserTest, no_attempts)
{
	Guesser guesser("secret");
	int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(MatchTest, different_case)
{
	Guesser guesser("secret");
	bool actual = guesser.match("Secret");
	ASSERT_EQ(false, actual);
}

TEST(RemainingTest, three_attempts)
{
	Guesser guesser("secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("Secret");
	int actual = guesser.remaining();
	ASSERT_EQ(0, actual);
}
TEST(RemainingTest, four_attempts)
{
	Guesser guesser("secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("Secret");
	int actual = guesser.remaining();
	ASSERT_EQ(0, actual);
}
TEST(RemainingTest, reset)
{
	Guesser guesser("secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("secret");
	int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}
TEST(RemainingTest, no_reset_allowed)
{
	Guesser guesser("secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("secret");
	int actual = guesser.remaining();
	ASSERT_EQ(0, actual);
}

TEST(LockTest, three_bad_attempts)
{
	Guesser guesser("secret");
	guesser.match("Secret");
	guesser.match("Secret");
	guesser.match("Secret");
	bool actual = guesser.match("secret");
	ASSERT_EQ(false, actual);
}
TEST(LockTest, brute_force)
{
	Guesser guesser("secret");
	guesser.match("definitely not secret");
	bool actual = guesser.match("secret");
	ASSERT_EQ(false, actual);
}
TEST(LockTest, one_different_two_extra)
{
	Guesser guesser("secret");
	guesser.match("Secret11"); // should lock due to distance of 3
	bool actual = guesser.match("secret");
	ASSERT_EQ(false, actual);
}