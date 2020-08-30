#include "catch.hpp"

#include "singleGame.hpp"

#include <utility>
#include <vector>

SCENARIO("Reading names from game input in SingleGame class")
{
    GIVEN("Constructor takes a game input as string")
    {
        using somePairs = std::vector<std::pair<SingleGame, std::string>>;

        somePairs whosPlay{
            {SingleGame("Romek: X|13|14|14|12|"), {"Romek"}},
            {SingleGame("Zenon: X|13|14|14|12|"), {"Zenon"}},
            {SingleGame("Gienia: 1/|13|14|14|12|"), {"Gienia"}},
            {SingleGame("Matylda: 12|13|14|14|12|"), {"Matylda"}},
            {SingleGame("Eustachy: 33|13|14|14|12|"), {"Eustachy"}},
            {SingleGame("Zuzka:X|13|14|14|12|"), {"Zuzka"}},
            {SingleGame(": -2|13|14|14|12|"), {"Anonymous"}}};

        WHEN("Constructor indirectly call private method readPlayerName() which store player name from game input")
        {
            THEN("You can get player name by using appropriate getter")
            {
                for (size_t i = 0; i < whosPlay.size(); i++) {
                    REQUIRE(whosPlay[i].first.getPlayerName() == whosPlay[i].second);
                }
            }
        }
    }
}

SCENARIO("Reading scores from game input in SingleGame class")
{
    GIVEN("Constructor takes a game input as string")
    {
        using somePairs = std::vector<std::pair<SingleGame, std::vector<size_t>>>;

        somePairs whosPlay{
            {SingleGame("Romek:X|X|X|X|X|X|X|X|X|X||XX"), {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}},
            {SingleGame("Zenon:9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||"), {9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0}},
            {SingleGame("Gienia:5/|5/|5/|5/|5/|5/|5/|5/|5/|5/||5"), {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}},
            {SingleGame("Matylda:X|7/|9-|X|-8|8/|-6|X|X|X||81"), {10, 7, 3, 9, 0, 10, 0, 8, 8, 2, 0, 6, 10, 10, 10, 8, 1}},
            {SingleGame("Eustachy:33|13|14|14|12|"), {3, 3, 1, 3, 1, 4, 1, 4, 1, 2}},
            {SingleGame("Zuzka:X|13|14|14|12|"), {10, 1, 3, 1, 4, 1, 4, 1, 2}},
            {SingleGame(":-2|13|14|14|12|"), {0, 2, 1, 3, 1, 4, 1, 4, 1, 2}}};

        WHEN("Constructor indirectly call private method putScoresToVector() which analize game input, transforms input to nums and store in vector")
        {
            THEN("You can get stored nums by using appropriate getter")
            {
                for (size_t i = 0; i < whosPlay.size(); i++) {
                    CHECK(whosPlay[i].first.getRolls() == whosPlay[i].second);
                }
            }
        }
    }
}

using gs = SingleGame::GameStatus;

SCENARIO("SingleGame should check if game is started, in progress or finished")
{
    auto [testGameInput, expectedGameStatus] =
        GENERATE(
            std::make_pair("", gs::NOT_STARTED),
            std::make_pair("Jan:", gs::NOT_STARTED),
            std::make_pair("Jan:1", gs::IN_PROGRESS),
            std::make_pair("Jan:11", gs::IN_PROGRESS),
            std::make_pair("Jan:1-", gs::IN_PROGRESS),
            std::make_pair("Jan:X", gs::IN_PROGRESS),
            std::make_pair("Jan:1/", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|5", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|5/|", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|5/|--", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|5/|--|", gs::IN_PROGRESS),
            std::make_pair("Jan:1/|5/|--|6", gs::IN_PROGRESS),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|X||8", gs::IN_PROGRESS),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|X||X", gs::IN_PROGRESS),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|8/||", gs::IN_PROGRESS),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|8/||8", gs::FINISHED),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|X||82", gs::FINISHED),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|X||XX", gs::FINISHED),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|44||", gs::FINISHED),
            std::make_pair("Jan:X|7/|9-|X|-8|8/|-6|X|X|9-||", gs::FINISHED),
            std::make_pair("Jan:X|X|X|X|X|X|X|X|X|X||XX", gs::FINISHED),
            std::make_pair("Jan:--|--|--|--|--|--|--|--|--|--||", gs::FINISHED));

    GIVEN("Input of the game: " << testGameInput)
    {
        WHEN("SingleGame class is created and analyzed input in context of game state")
        {
            SingleGame testSingleGame(testGameInput);
            THEN("Game state: " << ((expectedGameStatus == gs::FINISHED)
                                        ? "finished"
                                        : (expectedGameStatus == gs::IN_PROGRESS)
                                              ? "in progress"
                                              : "not started")
                                << " is returned")
            {
                REQUIRE(testSingleGame.getGameStatus() == expectedGameStatus);
            }
        }
    }
}

/*SCENARIO("SingleGame should count game score")
{
    auto [testGameInput2, expectedScore] =
        GENERATE(
            std::make_pair("", 0),
            std::make_pair("Jan:", 0),
            std::make_pair("Jan:11|11|11|11|11|11|11|11|11|11||", 20),
            std::make_pair("Jan:9/|9/|9/|9/|9/|9/|9/|9/|9/|9/||9", 190),
            std::make_pair("Jan:9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||", 90),
            std::make_pair("Jan:X|X|X|X|X|X|X|X|X|X||XX", 300),
            std::make_pair("Jan:--|--|--|--|--|--|--|--|--|--||", 0),
            std::make_pair("Jan:-", 0),
            std::make_pair("Jan:--", 0),
            std::make_pair("Jan:--|", 0),
            std::make_pair("Jan:--|--", 0),
            std::make_pair("Jan:--|--|--|--|--|--|--|--|--", 0),
            std::make_pair("Jan:1", 1),
            std::make_pair("Jan:11", 2),
            std::make_pair("Jan:11|", 2),
            std::make_pair("Jan:11|1", 3),
            std::make_pair("Jan:11|11", 4),
            std::make_pair("Jan:11|11|", 4),
            std::make_pair("Jan:11|11|11|11|11|11|11|11|1", 17),
            std::make_pair("Jan:11|11|11|11|11|11|11|11|11|", 18),
            std::make_pair("Jan:11|11|11|11|11|11|11|11|11|1", 19),
            std::make_pair("Jan:1/", 10),
            std::make_pair("Jan:1/|", 10),
            std::make_pair("Jan:1/|1", 12),
            std::make_pair("Jan:1/|1/", 21),
            std::make_pair("Jan:1/|1/|1", 23),
            std::make_pair("Jan:9/|9/|9/|9/|9/|9/|9/|9/|9/|9/", 181),
            std::make_pair("Jan:9/|9/|9/|9/|9/|9/|9/|9/|9/|9/||", 181),
            std::make_pair("Jan:X", 10),
            std::make_pair("Jan:X|", 10),
            std::make_pair("Jan:X|1", 12),
            std::make_pair("Jan:X|11", 14),
            std::make_pair("Jan:X|11|", 14),
            std::make_pair("Jan:X|X|", 30),
            std::make_pair("Jan:X|X|X|", 60));

    GIVEN("Input of the game: " << testGameInput2)
    {
        WHEN("SingleGame class is created and score is calculated")
        {
            SingleGame testSingleGame2(testGameInput2);
            THEN("Score = " << expectedScore)
            {
                REQUIRE(testSingleGame2.getScore() == (size_t)expectedScore);
            }
        }
    }
}*/

SCENARIO("GameInput checker in SingleGame class")
{
    GIVEN("Input of the game with spaces")
    {
        auto [gameInput, expectedInput] =
            GENERATE(
                std::make_pair("", ""),
                std::make_pair("Ja      n:      ", "Jan:"),
                std::make_pair("    J  a n :    1   ", "Jan:1"),
                std::make_pair(" J   a  n:    11", "Jan:11"),
                std::make_pair("J   a  n:    1- ", "Jan:1-"),
                std::make_pair("J an: X|7/|9 - |X|-8|   8/|-6  | X|X|X ||   8", "Jan:X|7/|9-|X|-8|8/|-6|X|X|X||8"),
                std::make_pair("Jan :X| 7/|9  -|X|  -8|8/|-6|  X| X|  X||X", "Jan:X|7/|9-|X|-8|8/|-6|X|X|X||X"),
                std::make_pair("J a n: X       |X|X|  X|X  |X|X |X     |X|X||XX", "Jan:X|X|X|X|X|X|X|X|X|X||XX"),
                std::make_pair("  J a n:--   |--|  --|--   |--|--|--     |--|--|  --||", "Jan:--|--|--|--|--|--|--|--|--|--||"));

        WHEN("Constructor called isBowlingGameInput() when game input is: " << gameInput)
        {
            SingleGame singleGame(gameInput);

            THEN("All spaces should be erased")

            {
                REQUIRE(singleGame.getGameInput() == expectedInput);
            }
        }
    }

    GIVEN("Input of the game with fobidden signs after player Name")
    {
        auto [gameInput, expectedInput] =
            GENERATE(
                std::make_pair("", ""),
                std::make_pair("Ja      n:   QŹ   ", ""),
                std::make_pair("    J  a n :  a  1   ", ""),
                std::make_pair(" J   a  n:    10011", ""),
                std::make_pair("J   a  n:    []1- ", ""),
                std::make_pair("J an: X|7/|9 - |X|-8|   8/|-6 cv | X|X|X ||   8", ""),
                std::make_pair("Jan :X| 7/|9  -|X|  -8|8/|-6|  X| X| =- X||X", ""),
                std::make_pair("J a n: X       |X|X|  X|X  |X|X |X +++    |X|X||XX", ""),
                std::make_pair("Jan :X| 7/|9  -|X|  -8|8/|-6|  X| X|  X||X", "Jan:X|7/|9-|X|-8|8/|-6|X|X|X||X"),
                std::make_pair("  J a n:--   |--|  --|--   |--|--|-- ;'/?    |--|--|  --||", ""),
                std::make_pair(":", ""));

        WHEN("Constructor called isBowlingGameInput() when game input is: " << gameInput)
        {
            SingleGame singleGame(gameInput);

            THEN("If input has forbidden letters shouldn't be initialized")

            {
                REQUIRE(singleGame.getGameInput() == expectedInput);
            }
        }
    }
}
