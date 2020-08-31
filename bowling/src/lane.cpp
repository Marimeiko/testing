#include "lane.hpp"

#include <filesystem>
#include <string>

// private

void Lane::parseFile(std::string fileName) {
    FileHandler file(fileName,Access::INPUT);
    std::string line;
    while (std::getline(file.readLine(), line)) {
        gamesInLine_.emplace_back(SingleGame(line));
    }
}

void Lane::parseLaneName(std::string fileName) {
    std::string fileExtension = std::filesystem::path(fileName).extension();
    std::size_t foundExtensionIndex = fileName.find(fileExtension);

    if (foundExtensionIndex != std::string::npos) {
        fileName.erase(foundExtensionIndex);
    }

    laneName_ = fileName;
}

// public

Lane::Lane(std::string fileName)
{
    parseFile(fileName);
    parseLaneName(fileName);
}

Lane::~Lane() {}

std::string Lane::getLaneName()
{
    return laneName_;
}
