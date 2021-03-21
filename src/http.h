#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

struct HttpRequest {
    std::map<std::string, std::string> header;

    explicit HttpRequest(char *buffer) {
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
                header["Method"] = lines[i].substr(0, firstSplitIndex);
                header["Path"] = lines[i].substr(firstSplitIndex + 1, secondSplitIndex - firstSplitIndex - 1);
                header["Protocol"] = lines[i].substr(secondSplitIndex + 1);

            } else {
                auto splitIndex = lines[i].find(':');
                header[lines[i].substr(0, splitIndex)] = lines[i].substr(splitIndex + 2);
            }
        }

        auto requestString = std::string(buffer);

    }
};

struct HttpResponse {
    std::string statusText;
    std::string contentType;
    int contentLength;
    const char *content{};

    HttpResponse() {
        contentLength = 0;
        setContentType();
        setStatus();
    }

    void setContent(const char *buffer, int bufferLength) {
        content = buffer;
        contentLength = bufferLength;
    }

    void setStatus(int status = 200) {
        switch (status) {
            case 200:
                statusText = "200 OK";
                break;
            case 403:
                statusText = "403 Forbidden";
                break;
            case 404:
                statusText = "404 Not Found";
                break;
            default:
                statusText = "500 Internal Server Error";
        }

    }

    void setContentType(const std::string &type = "text/html") {
        contentType = type;
    }

    char *toBuffer() const {
        std::ostringstream stream;
        // Build header.
        stream << HTTP_VERSION << " " << statusText << "\n"
               << "Server: " << SERVER_NAME << "\n"
               << "Content-Type: " << contentType << "\n"
               << "Content-Length: " << contentLength << "\n\n";
        auto header = stream.str();
        auto header_str = header.c_str();
        int headerLength = strlen(header_str);
        char *buffer = new char[headerLength + contentLength];
        memcpy(buffer, header_str, headerLength);
        memcpy(buffer + headerLength, content, contentLength);
        return buffer;
    }
};

// Process the request and return the response.
char *httpController(char *reqBuffer) {
    auto req = HttpRequest(reqBuffer);
    auto res = HttpResponse();

    const char *resText = "<h2>Hi, This is a http server.</h2>";
    res.setContent(resText, strlen(resText));

    char *resBuffer = res.toBuffer();
    return resBuffer;
}

#endif //HTTP_SERVER_HTTP_H
