#pragma once

#include "argumentParser.hpp"
#include "lane.hpp"

#include <string>
#include <vector>

class BowlingGame {
public:
    BowlingGame(int argc, const char** argv);
    BowlingGame() = delete;

    bool isHelpToBePrinted();
    std::string& printHelp() const;

    void calculateScores();
    void outputScores();

private:
    ArgumentParser parser_;
    std::vector<Lane> lanes_;

    std::string getOutputFileName();
    bool isOutputFileGiven();
    bool isInputDirectoryGiven();

    void showScores();
    void saveScores();
};
