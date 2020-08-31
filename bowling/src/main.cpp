#include <filesystem>
#include <iostream>

#include "argumentParser.hpp"
#include "bowlingGame.hpp"
#include "directoryHandler.hpp"
#include "fileHandler.hpp"
#include "lane.hpp"
#include "singleGame.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    const fs::path pathToShow{argc >= 2 ? argv[1] : fs::current_path()};
    std::vector<std::string> test{};

    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            std::cout << "dir:  " << filenameStr << '\n';
        }
        else if (entry.is_regular_file()) {
            std::cout << "file: " << filenameStr << '\n';
        }
        else
            std::cout << "??    " << filenameStr << '\n';

        test.push_back(filenameStr);
    }

    std::cout << "\n\nMy\n\n";
    for (auto el : test) {
        std::cout << el << '\n';
    }

    std::cout << "\n\nMy end\n\n";

    if (argc >= 2) {
        DirectoryHandler dh(argv[1]);
        for (auto el : dh.getFilesInDirectory()) {
            std::cout << el << '\n';
        }
        std::cout << "\n\nMy 2 end\n\n";
    }

    return 0;
}
