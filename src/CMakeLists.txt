# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

# This allows for faster build times since this is used in
# two executables.
add_library(catch_main_standbox STATIC)
target_sources(catch_main_standbox
    PRIVATE
        catch_main.cpp)
target_link_libraries(catch_main_standbox PUBLIC CONAN_PKG::catch2)

set(TEST_SOURCE_FILES example_tests.cpp listener.cpp )

add_executable(catch2_tests)
target_sources(catch2_tests
    PUBLIC
        ${TEST_SOURCE_FILES})
target_link_libraries(catch2_tests PRIVATE catch_main_standbox CONAN_PKG::catch2)

# automatically discover tests that are defined in catch based test files you
# can modify the unittests. TEST_PREFIX to whatever you want, or use different
# for different binaries
catch_discover_tests(
    catch2_tests
    TEST_PREFIX
    "catch2.unittests."
    EXTRA_ARGS
    -s
    --reporter=xml
    --out=tests.xml)

# Disable the static assert check so that they are runtime, this allows us to have 
# a executable that we can debugg when things go wrong with the constexpr testing.
add_executable(catch2_relaxed_constexpr_tests)
target_sources(catch2_relaxed_constexpr_tests
    PUBLIC
        ${TEST_SOURCE_FILES})
target_link_libraries(catch2_relaxed_constexpr_tests PRIVATE catch_main CONAN_PKG::catch2)
target_compile_definitions(catch2_relaxed_constexpr_tests
    PRIVATE
        CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(
    catch2_relaxed_constexpr_tests
    TEST_PREFIX
    "catch2.relaxed_constexpr."
    EXTRA_ARGS
    -s
    --reporter=xml
    --out=relaxed_constexpr.xml)

