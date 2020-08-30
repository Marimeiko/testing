#include "catch.hpp"

#include "fileHandler.hpp"

#include <filesystem>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Catch::Matchers::Equals;

using Access = FileHandler::FileAccess;

std::string vectorToString(const std::vector<std::string>& toPrint)
{
    std::stringstream ss;
    for (size_t i = 0; i < toPrint.size(); ++i) {
        if (toPrint[i] == "") {
            ss << "<empty line>\n";
        }
        else {
            ss << toPrint[i] << '\n';
        }
    }
    return ss.str();
}

SCENARIO("FileHandler object can be created for input", "FileHandler")
{
    auto [testFileName, expectedIsFileOpened] =
        GENERATE(std::make_pair("testDirectory/testFile1.txt", true),
                 std::make_pair("testDirectory/emptyFile.txt", true),
                 std::make_pair("noExistingFile.txt", false),
                 std::make_pair("", false));

    GIVEN("File name: " << testFileName)
    {
        WHEN("FileHandler object is created, with INPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::INPUT);
            THEN("File is opened for read")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);
            }
        }
    }
}

SCENARIO("FileHandler object can be created for output", "FileHandler")
{
    auto [testFileName, expectedIsFileOpened] =
        GENERATE(std::make_pair("testDirectory/testOutputFile.txt", true),
                 std::make_pair("", false));

    GIVEN("File name: " << testFileName)
    {
        WHEN("FileHandler object is created, with OUTPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::OUTPUT);
            THEN("File is opened for write")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);
            }
        }
        //cleanup after test
        std::filesystem::remove(testFileName);
    }
}

SCENARIO("FileHandler object created for output, so lines should not be read from file", "FileHandler")
{
    std::string testFileName{"testDirectory/testFileWrongOutput.txt"};
    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};
    std::vector<std::string> expectedLinesInFile{};
    expectedLinesInFile.push_back("line1");
    expectedLinesInFile.push_back("line2");
    expectedLinesInFile.push_back("line3");
    expectedLinesInFile.push_back("");

    GIVEN("File: " << testFileName << " with lines inside: \n"
                   << vectorToString(expectedLinesInFile))
    {
        WHEN("FileHandler object is created, with OUTPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::OUTPUT);
            THEN("File is opened for write, so empty lines should be read from file")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
            }
        }
    }
}

SCENARIO("FileHandler object can be created for empty input and empty strings are returned when file is read", "FileHandler")
{
    std::string testFileName{"testDirectory/emptyFile.txt"};
    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};

    GIVEN("File: " << testFileName << " which is empty")
    {
        WHEN("FileHandler object is created, with INPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::INPUT);
            THEN("File is opened for read and empty string are read from file")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
            }
        }
    }
}

SCENARIO("FileHandler object can be created for input and lines from file can be read", "FileHandler")
{
    std::string testFileName{"testDirectory/testFile1.txt"};
    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};
    std::vector<std::string> expectedLinesInFile{};
    expectedLinesInFile.push_back("line1");
    expectedLinesInFile.push_back("line2");
    expectedLinesInFile.push_back("line3");
    expectedLinesInFile.push_back("");

    GIVEN("File: " << testFileName << " with lines inside: \n"
                   << vectorToString(expectedLinesInFile))
    {
        WHEN("FileHandler object is created, with INPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::INPUT);
            THEN("File is opened for read and lines can be read from file")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[0]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[1]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[2]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
            }
        }
    }
}

SCENARIO("FileHandler object can be created for input and lines from file can be read skipping empty lines", "FileHandler")
{
    auto testFileName = GENERATE("testDirectory/testFileWithEmptyLines.txt",
                                 "testDirectory/testFileWithSeveralEmptyLinesInRow.txt");

    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};
    std::vector<std::string> expectedLinesInFile{};
    expectedLinesInFile.push_back("line1");
    expectedLinesInFile.push_back("");
    expectedLinesInFile.push_back("line2");
    expectedLinesInFile.push_back("");
    expectedLinesInFile.push_back("line3");

    GIVEN("File: " << testFileName << " with lines inside: \n"
                   << vectorToString(expectedLinesInFile))
    {
        WHEN("FileHandler object is created, with INPUT flag")
        {
            FileHandler testFileHandler(testFileName, Access::INPUT);
            THEN("File is opened for read and lines can be read from file")
            {
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[0]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[2]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[4]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
            }
        }
    }
}

SCENARIO("FileHandler object can be created for output and lines can be write to file", "FileHandler")
{
    std::string testFileName{"testDirectory/testOutput1.txt"};

    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};
    std::vector<std::string> expectedLinesToWrite{};
    expectedLinesToWrite.push_back("line1");
    expectedLinesToWrite.push_back("line2");
    expectedLinesToWrite.push_back("line3");

    GIVEN("File: " << testFileName)
    {
        WHEN("FileHandler object is created, with OUTPUT flag")
        {
            THEN("File is opened for write and lines can be write to file. Then file can be opened for read and lines can be read.")
            {
                {
                    FileHandler testFileHandlerOut(testFileName, Access::OUTPUT);
                    REQUIRE(testFileHandlerOut.isFileOpened() == expectedIsFileOpened);

                    for (auto el : expectedLinesToWrite) {
                        REQUIRE(testFileHandlerOut.write(el + '\n'));
                    }
                }
                {
                    FileHandler testFileHandlerIn(testFileName, Access::INPUT);
                    REQUIRE(testFileHandlerIn.isFileOpened() == expectedIsFileOpened);

                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedLinesToWrite[0]));
                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedLinesToWrite[1]));
                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedLinesToWrite[2]));
                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedEmpty));
                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedEmpty));
                    REQUIRE_THAT(testFileHandlerIn.readLine(), Equals(expectedEmpty));
                }
            }
            //cleanup after test
            std::filesystem::remove(testFileName);
        }
    }
}

SCENARIO("FileHandler object created for input, so lines should not be write to file and file content should not be changed", "FileHandler")
{
    std::string testFileName{"testDirectory/testFile1.txt"};
    bool expectedIsFileOpened = true;
    std::string expectedEmpty{};
    std::vector<std::string> expectedLinesInFile{};
    expectedLinesInFile.push_back("line1");
    expectedLinesInFile.push_back("line2");
    expectedLinesInFile.push_back("line3");

    GIVEN("File: " << testFileName << " with lines inside: \n"
                   << vectorToString(expectedLinesInFile))
    {
        WHEN("FileHandler object is created, with INPUT flag")
        {
            THEN("File is opened for read and lines shoule not be written to file")
            {
                FileHandler testFileHandler(testFileName, Access::INPUT);
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                for (auto el : expectedLinesInFile) {
                    REQUIRE_FALSE(testFileHandler.write("write: " + el + '\n'));
                }
            }
            AND_THEN("File should not be modified")
            {
                FileHandler testFileHandler(testFileName, Access::INPUT);
                REQUIRE(testFileHandler.isFileOpened() == expectedIsFileOpened);

                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[0]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[1]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedLinesInFile[2]));
                REQUIRE_THAT(testFileHandler.readLine(), Equals(expectedEmpty));
            }
        }
    }
}
