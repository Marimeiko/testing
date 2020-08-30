#include "singleGame.hpp"

#include <algorithm>

SingleGame::SingleGame(std::string gameInput)
{
    this->gameInput_ = gameInput;
    parseGameInput();
}

SingleGame::~SingleGame() {}

void SingleGame::parseGameInput()
{
    readPlayerName();
    putScoresToVector();
    checkGameStatus();
    countScore();
}

void SingleGame::readPlayerName()
{
    auto foundIndexAfterName = getGameInput().find(':');
    if (foundIndexAfterName != std::string::npos) {
        if (foundIndexAfterName) {
            setPlayerName(getGameInput().substr(0, foundIndexAfterName));
        }
        else {
            std::string anonymousPlayer("Anonymous");
            setPlayerName(anonymousPlayer);
        }
    }
}

void SingleGame::putScoresToVector()
{
    auto foundIndexAfterName = getGameInput().find(":");
    if (foundIndexAfterName != std::string::npos) {
        setBowlingSigns(getGameInput().substr(++foundIndexAfterName));
    }

    makePointsFromSigns();
}

bool SingleGame::isGameFinished()
{
    const auto foundIndexOfBonus = getBowlingSings().find("||");
    if (foundIndexOfBonus == std::string::npos) {
        return false;
    }
    else {
        const auto rollsBeforeBonus = getBowlingSings().substr(0, foundIndexOfBonus);
        const auto foundIndexOfLastFrameStart = rollsBeforeBonus.rfind('|');
        const auto lengthOfLastFrame = foundIndexOfBonus - foundIndexOfLastFrameStart - 1;
        const auto rollsInLastFrame = getBowlingSings().substr(foundIndexOfLastFrameStart + 1, lengthOfLastFrame);
        const auto numberOfBonusPoints = getBowlingSings().length() - (foundIndexOfBonus + 2);

        if (rollsInLastFrame[0] == 'X' &&
            numberOfBonusPoints == 2) {
            return true;
        }
        else if (rollsInLastFrame[1] == '/' &&
                 numberOfBonusPoints == 1) {
            return true;
        }
        else if (rollsInLastFrame[0] != 'X' &&
                 rollsInLastFrame[1] != '/' &&
                 numberOfBonusPoints == 0) {
            return true;
        }
    }
    return false;
}

bool SingleGame::isGameNotStarted()
{
    return getBowlingSings().empty();
}

void SingleGame::checkGameStatus()
{
    if (isGameNotStarted()) {
        gameStatus_ = SingleGame::GameStatus::NOT_STARTED;
    }
    else if (isGameFinished()) {
        gameStatus_ = SingleGame::GameStatus::FINISHED;
    }
    else {
        gameStatus_ = SingleGame::GameStatus::IN_PROGRESS;
    }
}

bool SingleGame::isStrike(size_t firstInFrame)
{
    return (rolls_[firstInFrame] == 10);
}

bool SingleGame::isSpare(size_t firstInFrame)
{
    if (((firstInFrame + 1) < rolls_.size())) {
        return ((rolls_[firstInFrame] + rolls_[firstInFrame + 1]) == 10);
    }
    else {
        return false;
    }
}

void SingleGame::countScore()
{
    size_t score{};
    size_t firstInFrame{};
    const auto numberOfRollsInGame = rolls_.size();

    for (size_t i = 0; i < 10 && firstInFrame < numberOfRollsInGame; ++i) {
        if (isStrike(firstInFrame)) {
            score += 10;
            if ((firstInFrame + 1) < numberOfRollsInGame) {
                score += rolls_[firstInFrame + 1];
            }
            if ((firstInFrame + 2) < numberOfRollsInGame) {
                score += rolls_[firstInFrame + 2];
            }
            firstInFrame++;
        }
        else if (isSpare(firstInFrame)) {
            score += 10;
            if ((firstInFrame + 2) < numberOfRollsInGame) {
                score += rolls_[firstInFrame + 2];
            }
            firstInFrame += 2;
        }
        else {
            score += rolls_[firstInFrame];
            if ((firstInFrame + 1) < numberOfRollsInGame) {
                score += rolls_[firstInFrame + 1];
            }
            firstInFrame += 2;
        }
    }
    score_ = score;
}

void SingleGame::setRolls(std::size_t point)
{
    this->rolls_.push_back(point);
}

void SingleGame::setPlayerName(std::string playerName)
{
    this->playerName_ = playerName;
}

std::string SingleGame::getPlayerName() const
{
    return this->playerName_;
}

void SingleGame::setBowlingSigns(std::string bowlingSigns)
{
    this->bowlingSigns_ = bowlingSigns;
}

void SingleGame::makePointsFromSigns()
{
    const size_t MAXPOINT = 10;
    const size_t NOPOINT = 0;

    for (auto sign : getBowlingSings()) {
        if (sign == '|') {
            continue;
        }
        if (sign == 'X') {
            setRolls(MAXPOINT);
        }
        if (sign == '/') {
            setRolls(MAXPOINT - (getRolls().back()));
        }
        if (sign == '-') {
            setRolls(NOPOINT);
        }
        if (std::isdigit(sign)) {
            setRolls(sign - '0');
        }
    }
}

std::string SingleGame::getBowlingSings() const
{
    return this->bowlingSigns_;
}

std::vector<std::size_t> SingleGame::getRolls() const
{
    return this->rolls_;
}

std::string SingleGame::getGameInput() const
{
    return gameInput_;
}
