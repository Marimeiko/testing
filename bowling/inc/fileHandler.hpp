#pragma once

#include <fstream>
#include <string>

class FileHandler {
public:
    enum class FileAccess {
        INPUT,
        OUTPUT
    };

    FileHandler(std::string fileName, FileAccess fileAccess);
    FileHandler() = delete;
    ~FileHandler();

    bool isFileOpened() const { return fileStream_.is_open(); };
    std::string readLine();
    bool write(std::string dataToWrite);

private:
    std::string fileName_{};
    FileAccess fileAccess_{FileAccess::INPUT};
    std::fstream fileStream_{};
};
