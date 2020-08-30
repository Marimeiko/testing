#include "fileHandler.hpp"

FileHandler::FileHandler(std::string fileName, FileHandler::FileAccess fileAccess)
    : fileName_(fileName), fileAccess_(fileAccess)
{
    if (fileAccess_ == FileAccess::INPUT) {
        fileStream_.open(fileName_, std::ios::in);
    }
    else {
        fileStream_.open(fileName_, std::ios::out);
    }
}

FileHandler::~FileHandler()
{
    if (isFileOpened()) {
        fileStream_.close();
    }
}

std::string FileHandler::readLine()
{
    if (!isFileOpened() || (fileAccess_ != FileAccess::INPUT)) {
        return {};
    }

    std::string lineReadFromFile{};
    do {
        if (!std::getline(fileStream_, lineReadFromFile)) {
            return {};
        }
    } while (lineReadFromFile.empty());

    return lineReadFromFile;
}

bool FileHandler::write(std::string dataToWrite)
{
    if (!isFileOpened() || (fileAccess_ != FileAccess::OUTPUT)) {
        return false;
    }

    fileStream_ << dataToWrite;
    return true;
}
