#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

struct HttpRequest {
    std::map<std::string, std::string> headerMap;

    explicit HttpRequest(char *buffer) {
        printf("%s", buffer);
        std::stringstream stream(buffer);
        std::vector<std::string> lines;
        std::string line;
        if (buffer != nullptr) {
            while (std::getline(stream, line, '\n')) {
                line = line.substr(0, line.size() - 1);
                if (line.length() > 0) {
                    lines.push_back(line);
                }
            }
        }
        for (int i = 0; i < lines.size(); i++) {
            if (i == 0) {
                auto firstSplitIndex = lines[i].find(' ');
                auto secondSplitIndex = lines[i].find(' ', firstSplitIndex + 1);
                headerMap["Method"] = lines[i].substr(0, firstSplitIndex);
                headerMap["Path"] = lines[i].substr(firstSplitIndex + 1, secondSplitIndex - firstSplitIndex - 1);
                headerMap["Protocol"] = lines[i].substr(secondSplitIndex + 1);

            } else {
                auto splitIndex = lines[i].find(':');
                headerMap[lines[i].substr(0, splitIndex)] = lines[i].substr(splitIndex + 2);
            }
        }

        auto requestString = std::string(buffer);

    }
};

struct HttpResponse {
    explicit HttpResponse(char *buffer) {

    }
};

// Process the request and return the response.
void httpController(char *reqBuffer, char *resBuffer) {
    auto req = new HttpRequest(reqBuffer);
}

#endif //HTTP_SERVER_HTTP_H
