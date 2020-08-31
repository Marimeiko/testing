#include "singleGame.hpp"

#include <algorithm>

SingleGame::SingleGame(std::string gameInput)
{
    setGameInput(gameInput);
    eraseSpaces();

    if (this->isNotBowlingGameInput()) {
        std::string badInput = "";
        setGameInput(badInput);
    }

    parseGameInput();
    countScore();
}

SingleGame::~SingleGame() {}

void SingleGame::parseGameInput()
{
    this->putScoresToVector();
    this->checkGameStatus();
}

bool SingleGame::isNotBowlingGameInput()
{
    if (getGameInput().empty()) {
        return true;
    }

    if (isNotPlayerName()) {
        return true;
    }

    if (isNotBowlingSigns()) {
        return true;
    }

    if (isNotAllowedChar()) {
        return true;
    }

    if (isNotBowlingOrder()) {
        return true;
    }
    return false;
}

void SingleGame::eraseSpaces()
{
    std::string gameInput = getGameInput();
    gameInput.erase(std::remove(gameInput.begin(), gameInput.end(), ' '),
                    gameInput.end());
    setGameInput(gameInput);
}

bool SingleGame::isNotAllowedChar()
{
    std::string gameInput = getGameInput();

    const std::string ALLOWEDCHARACTERS = "X/-|123456789";

    auto foundIndexAfterName = gameInput.find(':');

    if (getGameInput() == ":") {
        return true;
    }

    if (foundIndexAfterName != std::string::npos) {
        auto foundNotAllowedCharacter = gameInput.find_first_not_of(ALLOWEDCHARACTERS, ++foundIndexAfterName);
        if (foundNotAllowedCharacter != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool SingleGame::isNotBowlingOrder()
{
    std::string bowlingSigns = getBowlingSigns();

    size_t ballThrows = 1;
    size_t movesAfterTwoPipes = 3;
    bool expectedPipe = false;
    bool expectedSecondPipe = false;
    bool afterTwoPipes = false;

    for (auto sign : bowlingSigns) {
        if(afterTwoPipes) {
            movesAfterTwoPipes--;
            if(!movesAfterTwoPipes) {
                return true;
            }
        }

        if (expectedSecondPipe) {
            expectedSecondPipe = false;
            expectedPipe = false;
            afterTwoPipes = true;
            continue;
        }

        if (expectedPipe && (sign == '|')) {
            if (ballThrows == 21) {
                expectedSecondPipe = true;
                expectedPipe = false;
                continue;
            }
            else {
                expectedPipe = false;
                continue;
            }
            return true;
        }

        if (ballThrows % 2) {
            if ((std::isdigit(sign) || sign == 'X' || sign == '-') && (!expectedPipe)) {
                if (sign == 'X') {
                    if (ballThrows != 21) {
                        expectedPipe = true;
                    }
                    ballThrows++;
                }
                ballThrows++;
            }
            else {
                return true;
            }
        }
        else {
            if ((std::isdigit(sign) || sign == '/' || sign == '-') && (!expectedPipe)) {
                ballThrows++;
                expectedPipe = true;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

bool SingleGame::isNotPlayerName()
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
    else {
        return true;
    }
    return false;
}

bool SingleGame::isNotBowlingSigns()
{
    auto foundIndexAfterName = getGameInput().find(':');

    if (foundIndexAfterName != std::string::npos) {
        if (++foundIndexAfterName) {
            setBowlingSigns(getGameInput().substr(foundIndexAfterName));
        }
    }
    else {
        return true;
    }

    return false;
}

void SingleGame::putScoresToVector()
{
    makePointsFromSigns();
}

bool SingleGame::isGameFinished()
{
    const auto foundIndexOfBonus = getBowlingSigns().find("||");
    if (foundIndexOfBonus == std::string::npos) {
        return false;
    }
    else {
        const auto rollsBeforeBonus = getBowlingSigns().substr(0, foundIndexOfBonus);
        const auto foundIndexOfLastFrameStart = rollsBeforeBonus.rfind('|');
        const auto lengthOfLastFrame = foundIndexOfBonus - foundIndexOfLastFrameStart - 1;
        const auto rollsInLastFrame = getBowlingSigns().substr(foundIndexOfLastFrameStart + 1, lengthOfLastFrame);
        const auto numberOfBonusPoints = getBowlingSigns().length() - (foundIndexOfBonus + 2);

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
    return getBowlingSigns().empty();
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

    return false;
}

size_t SingleGame::getBonusPointsForStrike(size_t firstInFrame)
{
    const auto numberOfRollsInGame = rolls_.size();
    size_t bonusPoints{};

    if ((firstInFrame + 1) < numberOfRollsInGame) {
        bonusPoints += rolls_[firstInFrame + 1];
    }
    if ((firstInFrame + 2) < numberOfRollsInGame) {
        bonusPoints += rolls_[firstInFrame + 2];
    }

    return bonusPoints;
}

size_t SingleGame::getBonusPointsForSpare(size_t firstInFrame)
{
    const auto numberOfRollsInGame = rolls_.size();
    size_t bonusPoints{};

    if ((firstInFrame + 2) < numberOfRollsInGame) {
        bonusPoints += rolls_[firstInFrame + 2];
    }
    return bonusPoints;
}

size_t SingleGame::getPointsForRegularGame(size_t firstInFrame)
{
    const auto numberOfRollsInGame = rolls_.size();
    size_t bonusPoints{};

    bonusPoints += rolls_[firstInFrame];
    if ((firstInFrame + 1) < numberOfRollsInGame) {
        bonusPoints += rolls_[firstInFrame + 1];
    }

    return bonusPoints;
}

void SingleGame::countScore()
{
    size_t score{};
    size_t firstInFrame{};
    const auto numberOfRollsInGame = rolls_.size();

    for (size_t i = 0; i < 10 && firstInFrame < numberOfRollsInGame; ++i) {
        if (isStrike(firstInFrame)) {
            score += 10 + getBonusPointsForStrike(firstInFrame);
            firstInFrame++;
        }
        else if (isSpare(firstInFrame)) {
            score += 10 + getBonusPointsForSpare(firstInFrame);
            firstInFrame += 2;
        }
        else {
            score += getPointsForRegularGame(firstInFrame);
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

    for (auto sign : getBowlingSigns()) {
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

std::string SingleGame::getBowlingSigns() const
{
    return this->bowlingSigns_;
}

std::vector<std::size_t> SingleGame::getRolls() const
{
    return this->rolls_;
}

void SingleGame::setGameInput(std::string gameInput)
{
    this->gameInput_ = gameInput;
}

std::string SingleGame::getGameInput() const
{
    return gameInput_;
}
