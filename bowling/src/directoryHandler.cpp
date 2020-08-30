#include "directoryHandler.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

DirectoryHandler::DirectoryHandler(std::string directoryName)
    : directoryName_(directoryName)
{
    readFilesFromDirectory();
}

DirectoryHandler::~DirectoryHandler() {}

void DirectoryHandler::readFilesFromDirectory()
{
    for (const auto& entry : fs::directory_iterator(directoryName_)) {
        if (entry.is_regular_file()) {
            const auto filenameString = entry.path().string();
            filesInDirectory_.emplace_back(filenameString);
        }
    }
}
