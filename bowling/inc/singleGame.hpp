#pragma once

#include <iostream>
#include <string>
#include <vector>

class SingleGame {
public:
    enum class GameStatus {
        FINISHED,
        IN_PROGRESS,
        NOT_STARTED
    };

private:
    std::string gameInput_{};
    std::string playerName_{};
    std::string bowlingSigns_{};
    std::vector<size_t> rolls_{};
    size_t score_{};

    GameStatus gameStatus_{};

    void parseGameInput();
    void putScoresToVector();
    void checkGameStatus();
    void countScore();
    bool isNotPlayerName();
    bool isNotBowlingSigns();
    bool isNotBowlingGameInput();
    void eraseSpaces();
    bool isNotAllowedChar();
    bool isNotBowlingOrder();

    bool isGameFinished();
    bool isGameNotStarted();

    bool isStrike(size_t firstInFrame);
    bool isSpare(size_t firstInFrame);
    size_t getBonusPointsForStrike(size_t firstInFrame);
    size_t getBonusPointsForSpare(size_t firstInFrame);
    size_t getPointsForRegularGame(size_t firstInFrame);

public:
    SingleGame(std::string gameInput);
    ~SingleGame();

    void setRolls(std::size_t point);
    void setPlayerName(std::string playerName);
    void setGameInput(std::string gameInput);
    void setBowlingSigns(std::string bowlingSigns);
    void makePointsFromSigns();

    std::string getPlayerName() const;
    std::string getBowlingSigns() const;
    std::vector<std::size_t> getRolls() const;
    std::size_t getScore() const { return score_; };
    std::string getGameInput() const;
    GameStatus getGameStatus() const { return gameStatus_; };
    friend std::ostream& operator<<(std::ostream& os, const SingleGame& singleGame);
};
