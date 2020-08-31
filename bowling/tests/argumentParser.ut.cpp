#include "catch.hpp"

#include <string>

#include "argumentParser.hpp"

using Catch::Matchers::Equals;

using ArgNumber = ArgumentParser::ArgumentNumber;

SCENARIO("program arguments and their number should be returned after parsing", "argumentParser")
{
    std::string expectedEmpty{};

    SECTION("Test with null arguments list")
    {
        int testArgc = 0;
        const char** testArgv = NULL;
        size_t expectedArgumentsNumber = 0;

        GIVEN("argc = " << testArgc
                        << " and argv = NULL")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \"empty string\" and getArgument(SECOND_ARGUMENT) returns \"empty string\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }

    SECTION("Test with null arguments list and wrong argc")
    {
        int testArgc = 2;
        const char** testArgv = NULL;
        size_t expectedArgumentsNumber = 0;

        GIVEN("argc = " << testArgc
                        << " and argv = NULL")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \"empty string\" and getArgument(SECOND_ARGUMENT) returns \"empty string\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }

    SECTION("Test with no arguments")
    {
        int testArgc = 1;
        const char* testArgv[] = {"programName", NULL};
        size_t expectedArgumentsNumber = 0;

        GIVEN("argc = " << testArgc
                        << " and argv = {\""
                        << (testArgv[0] ? testArgv[0] : "") << "\", \""
                        << (testArgv[1] ? testArgv[1] : "") << "\"}")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \""
                     << (testArgv[1] ? testArgv[1] : "empty string")
                     << "\" and getArgument(SECOND_ARGUMENT) returns \"empty string\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }

    SECTION("Test with one argument")
    {
        int testArgc = 2;
        const char* testArgv[] = {"programName", "argument_1", NULL};
        size_t expectedArgumentsNumber = 1;

        GIVEN("argc = " << testArgc
                        << " and argv = {\""
                        << (testArgv[0] ? testArgv[0] : "") << "\", \""
                        << (testArgv[1] ? testArgv[1] : "") << "\", \""
                        << (testArgv[2] ? testArgv[2] : "") << "\"}")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \""
                     << (testArgv[1] ? testArgv[1] : "empty string")
                     << "\" and getArgument(SECOND_ARGUMENT) returns \""
                     << (testArgv[2] ? testArgv[2] : "empty string") << "\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(testArgv[1]));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }

    SECTION("Test with two argument")
    {
        int testArgc = 3;
        const char* testArgv[] = {"programName", "argument_1", "argument_2", NULL};
        size_t expectedArgumentsNumber = 2;

        GIVEN("argc = " << testArgc
                        << " and argv = {\""
                        << (testArgv[0] ? testArgv[0] : "") << "\", \""
                        << (testArgv[1] ? testArgv[1] : "") << "\", \""
                        << (testArgv[2] ? testArgv[2] : "") << "\"}")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \""
                     << (testArgv[1] ? testArgv[1] : "empty string")
                     << "\" and getArgument(SECOND_ARGUMENT) returns \""
                     << (testArgv[2] ? testArgv[2] : "empty string") << "\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(testArgv[1]));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(testArgv[2]));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }

    SECTION("Test with argument list with NULL in the middle")
    {
        int testArgc = 3;
        const char* testArgv[] = {"programName", NULL, "argument_1", NULL};
        size_t expectedArgumentsNumber = 0;

        GIVEN("argc = " << testArgc
                        << " and argv = {\""
                        << (testArgv[0] ? testArgv[0] : "") << "\", \""
                        << (testArgv[1] ? testArgv[1] : "") << "\", \""
                        << (testArgv[2] ? testArgv[2] : "") << "\"}")
        {
            WHEN("argumentParser object is created")
            {
                ArgumentParser testArgParser(testArgc, testArgv);
                THEN("getArgument(FIRST_ARGUMENT) returns \""
                     << (testArgv[1] ? testArgv[1] : "empty string")
                     << "\" and getArgument(SECOND_ARGUMENT) returns \""
                     << (testArgv[2] ? testArgv[2] : "empty string") << "\"")
                {
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::FIRST_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE_THAT(testArgParser.getArgument(ArgNumber::SECOND_ARGUMENT),
                                 Equals(expectedEmpty));
                    REQUIRE(testArgParser.getArgumentsNumber() == expectedArgumentsNumber);
                }
            }
        }
    }
}

SCENARIO("program arguments are parsed and it is possible to check if argument was given", "argumentParser")
{
    int testArgc = 3;
    const char* testArgv[] = {"programName", "argument_1", "argument_2", NULL};

    GIVEN("argc = " << testArgc
                    << " and argv = {\""
                    << (testArgv[0] ? testArgv[0] : "") << "\", \""
                    << (testArgv[1] ? testArgv[1] : "") << "\", \""
                    << (testArgv[2] ? testArgv[2] : "") << "\"}")
    {
        WHEN("argumentParser object is created")
        {
            ArgumentParser testArgParser(testArgc, testArgv);
            THEN("checkIfArgumentExists() returns true for existing arguments and false for not existing arguments")
            {
                REQUIRE(testArgParser.checkIfArgumentExists(testArgv[1]));
                REQUIRE(testArgParser.checkIfArgumentExists(testArgv[2]));

                REQUIRE(testArgParser.checkIfArgumentExists("argument_1"));
                REQUIRE(testArgParser.checkIfArgumentExists("argument_2"));

                REQUIRE_FALSE(testArgParser.checkIfArgumentExists(testArgv[0]));
                REQUIRE_FALSE(testArgParser.checkIfArgumentExists("dummy"));
                REQUIRE_FALSE(testArgParser.checkIfArgumentExists(""));
            }
        }
    }
}
