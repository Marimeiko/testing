#pragma once

#include <string>
#include <vector>

class DirectoryHandler {
public:
    DirectoryHandler(std::string directoryName);
    DirectoryHandler() = delete;
    ~DirectoryHandler();

    const std::vector<std::string>& getFilesInDirectory() const { return filesInDirectory_; };

private:
    std::string directoryName_{};
    std::vector<std::string> filesInDirectory_{};

    void readFilesFromDirectory();
};
