#ifndef CONVERTJSON_H
#define CONVERTJSON_H
#include <iostream>
#include<nlohmann/json.hpp>
#include <fstream>
#include <vector>

using json = nlohmann::json;

class ConverterJSON {
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments() {
        std::vector<std::string> documents;
        std::ifstream configFile("config.json");

        if(!(configFile.is_open())){
            std::cout<<"Config fie is missing!!!"<<std::endl;
        }

        json config;
        configFile >> config;

        if(config.empty()){
            std::cout<<"Config file is empty!!!"<<std::endl;
        }

        for (const auto& doc : config["documents"]) {
            documents.push_back(doc.get<std::string>());
        }

        return documents;
    }


    int GetResponsesLimit() {
        std::ifstream configFile("config.json");
        json config;
        configFile >> config;

        return config["max_responses"].get<int>();
    }

    std::vector<std::string> GetRequests() {
        std::vector<std::string> requests;
        std::ifstream requestsFile("requests.json");
        json requestsJson;
        requestsFile >> requestsJson;

        for (const auto& req : requestsJson) {
            requests.push_back(req.get<std::string>());
        }

        return requests;
    }

    void putAnswers(std::vector<std::vector<std::pair<int, float>>>
                        answers){
        json answersJson = answers;
        std::ofstream answersFile("answers.json");
        answersFile << answersJson.dump(4);
    }

};


#endif // CONVERTJSON_H
