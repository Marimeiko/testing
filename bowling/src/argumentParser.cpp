#include "argumentParser.hpp"

#include <algorithm>

ArgumentParser::ArgumentParser(int argc, const char** argv)
{
    parseArguments(argc, argv);
}

void ArgumentParser::parseArguments(const int argc, const char** argv)
{
    if (argv && (argc > 0)) {
        // Skip the first argument, i.e. program name
        for (size_t i = 1; i < argc; ++i) {
            if (argv[i]) {
                parsedArguments_.push_back(argv[i]);
            }
            else {
                parsedArguments_.clear();
                return;
            }
        }
        parsedArguments_.shrink_to_fit();
        argumentsNumber_ = (size_t)(argc - 1);
    }
}

std::string ArgumentParser::getArgument(const ArgumentNumber argumentNumber) const
{
    if (static_cast<size_t>(argumentNumber) >= argumentsNumber_) {
        return {};
    }
    return parsedArguments_[static_cast<size_t>(argumentNumber)];
}

bool ArgumentParser::checkIfArgumentExists(const std::string& argument) const
{
    auto foundIt = std::find(parsedArguments_.begin(), parsedArguments_.end(), argument);
    if (foundIt != parsedArguments_.end()) {
        return true;
    }
    return false;
}
