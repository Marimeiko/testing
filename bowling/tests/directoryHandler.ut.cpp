#include "catch.hpp"

#include "directoryHandler.hpp"

#include <algorithm>

using Catch::Matchers::Equals;
using Catch::Matchers::VectorContains;

// This scenario may fail under github CI, because it is not possible to commit empty directory
// in git. Scenario marked with tag: [!mayfail]
SCENARIO("DirectoryHandler object created for empty directory", "FileDirectory [!mayfail]")
{
    std::string testDirectoryName{"testDirectory/dirEmpty"};
    GIVEN("Directory: " << testDirectoryName << " with no files inside")
    {
        WHEN("DirectoryHandler object is created")
        {
            DirectoryHandler testDirectoryHandler(testDirectoryName);
            THEN("Empty vector is returned")
            {
                REQUIRE(testDirectoryHandler.getFilesInDirectory().empty());
            }
        }
    }
}

SCENARIO("DirectoryHandler object created for directory containing one file", "FileDirectory")
{
    std::string testDirectoryName{"testDirectory/dirOneFile"};
    std::vector<std::string> expectedFilesInDirectory{};
    expectedFilesInDirectory.push_back("testDirectory/dirOneFile/file1.txt");

    GIVEN("Directory: " << testDirectoryName << " with one file inside")
    {
        WHEN("DirectoryHandler object is created")
        {
            DirectoryHandler testDirectoryHandler(testDirectoryName);
            THEN("Vector with one element is returned")
            {
                REQUIRE(testDirectoryHandler.getFilesInDirectory().size() == 1);
                REQUIRE_THAT(testDirectoryHandler.getFilesInDirectory()[0], Equals(expectedFilesInDirectory[0]));
            }
        }
    }
}

SCENARIO("DirectoryHandler object created for directory containing three files", "FileDirectory")
{
    std::string testDirectoryName{"testDirectory/dirThreeFiles"};
    std::vector<std::string> expectedFilesInDirectory{};
    expectedFilesInDirectory.push_back("testDirectory/dirThreeFiles/file1.txt");
    expectedFilesInDirectory.push_back("testDirectory/dirThreeFiles/file2.txt");
    expectedFilesInDirectory.push_back("testDirectory/dirThreeFiles/file3.txt");

    GIVEN("Directory: " << testDirectoryName << " with three file inside")
    {
        WHEN("DirectoryHandler object is created")
        {
            DirectoryHandler testDirectoryHandler(testDirectoryName);
            THEN("Vector with one element is returned")
            {
                REQUIRE(testDirectoryHandler.getFilesInDirectory().size() == 3);

                for (auto& el : expectedFilesInDirectory) {
                    REQUIRE_THAT(testDirectoryHandler.getFilesInDirectory(), VectorContains(el));
                }
            }
        }
    }
}
