#include "lane.hpp"

#include <filesystem>

// private

void Lane::parseFile(std::string fileName)
{
    fileName = std::filesystem::path(fileName).stem();

    if(fileName[0] == '.') {

        std::string fileExtension = std::filesystem::path(fileName).extension();
        std::size_t foundExtensionIndex = fileName.find(fileExtension);

        if (foundExtensionIndex != std::string::npos) {
            fileName.erase(foundExtensionIndex);
        }

    }

    this->laneName_ = fileName;
}

void Lane::parseLaneName(std::string laneName) {}

// public

Lane::Lane(std::string fileName)
{
    this->parseFile(fileName);
    this->parseLaneName(fileName);
}

Lane::~Lane() {}

std::string Lane::getLaneName()
{
    return this->laneName_;
}
