#pragma once

#include "JsonHandler.h"
#include "InvertedIndex.h"
#include <vector>
#include <string>
#include <unordered_map>

class SearchServer {
public:
    SearchServer(const JsonHandler::Config& config);
    std::vector<std::vector<std::string>> search(const std::vector<std::vector<std::string>>& requests);

private:
    int maxResults;
    std::vector<std::string> documents;
    InvertedIndex index;
};


