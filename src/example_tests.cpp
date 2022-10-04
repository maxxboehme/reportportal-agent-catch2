#include <catch2/catch.hpp>

constexpr uint32_t factorial(uint32_t number)
{
    return number <= 1 ? number : factorial(number -1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("Factorials are computed at compile time", "[factorial]")
{
    STATIC_REQUIRE(factorial(1) == 1);
    STATIC_REQUIRE(factorial(2) == 2);
    STATIC_REQUIRE(factorial(3) == 6);
    STATIC_REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("Hidden testcase", "[.hidden]")
{
}

// TEST_CASE("Testcase with sections", "[tag-A][tag-B]")
// {
//     int i = 42;
// 
//     REQUIRE(i == 42);
// 
//     SECTION("Section 1") {
//         INFO("Section 1");
//         i = 7;
//         SECTION("Section 1.1") {
//             INFO("Section 1.1");
//             REQUIRE(i == 42);
//         }
//     }
// 
//     SECTION("Section 2") {
//         INFO("Section 2");
//         REQUIRE(i == 42);
//     }
//     WARN("At end of test case");
// }

struct Fixture {
    int fortytwo() const {
        return 42;
    }
};

TEST_CASE_METHOD(Fixture,"Testcase with class-based fixture", "[tag-C][tag-D]")
{
    REQUIRE(fortytwo() == 42);
}
