#include "SearchServer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

SearchServer::SearchServer(const JsonHandler::Config& config) : maxResults(config.maxResults) {
    for (const auto& file : config.files) {
        std::ifstream inFile(file);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        index.addDocument(buffer.str(), documents.size());
        documents.push_back(file);
    }
}

std::vector<std::vector<std::string>> SearchServer::search(const std::vector<std::vector<std::string>>& requests) {
    std::vector<std::vector<std::string>> results;

    for (const auto& request : requests) {
        std::unordered_map<int, int> docCount;
        for (const auto& word : request) {
            const auto& docs = index.getDocuments(word);
            for (const auto& docId : docs) {
                docCount[docId]++;
            }
        }

        std::vector<std::pair<int, int>> sortedResults(docCount.begin(), docCount.end());
        std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
            return b.second < a.second;
        });

        std::vector<std::string> result;
        for (size_t i = 0; i < sortedResults.size() && i < maxResults; ++i) {
            result.push_back(documents[sortedResults[i].first]);
        }

        results.push_back(result);
    }

    return results;
}
