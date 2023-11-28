#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <string>
#include "InvertedIndex.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "ConvertJSON.h"
#include <unordered_set>
#include <bits/stdc++.h>


struct RelativeIndex{
    size_t doc_id;
    Entry rank;
    bool operator ==(const RelativeIndex& other) const {
    return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:

    SearchServer(InvertedIndex& idx) : _index(idx){}

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input){
    std::vector<std::vector<RelativeIndex>> search_results;
    for (const auto& query : queries_input) {
        std::vector<RelativeIndex> relative_indices;
        std::map<size_t, size_t> doc_ranks;
        std::istringstream iss(query);
        std::string word;
        while (iss >> word) {
            auto entries = _index.GetWordCount(word);
            for (const auto& entry : entries) {
                doc_ranks[entry.doc_id] += entry.count;
            }
        }
        for (const auto& p : doc_ranks) {
            relative_indices.push_back({p.first, p.second});
        }
        std::sort(relative_indices.begin(), relative_indices.end(),[](const RelativeIndex &a,const RelativeIndex &b)
        {
            return a.rank.count > b.rank.count;
        });
        search_results.push_back(relative_indices);
      }
    return search_results;
    }
private:
    InvertedIndex _index;
};




#endif // SEARCHSERVER_H
