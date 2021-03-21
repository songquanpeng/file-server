//
// Created by song on 3/21/21.
//

#ifndef HTTP_SERVER_RENDER_H
#define HTTP_SERVER_RENDER_H

#include <string>
#include <vector>
#include <fstream>

const std::string part1 = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "    <meta charset=\"UTF-8\">\n"
                          "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                          "    <title>File Server</title>\n"
                          "    <style>a {text-decoration: none;color: #368ccb;}</style>\n"
                          "</head>\n"
                          "<body style=\"font-family: Verdana, serif;\">\n"
                          "<div style=\"max-width: 960px;margin: auto;\"><h3>Content of folder: ";
const std::string part2 = "</h3><ul>";
const std::string part3 = "</ul></div></body></html>";

std::string renderList(const std::string &path, const std::vector<std::string>& files) {
    std::string html = part1 + path + part2;
    for (auto & file : files) {
        auto newPath = path + '/' + file;
        if (path == "/") {
            newPath = path + file;
        }
        html += "<li><a href=\"" + newPath + "\">" + file + "</a></li>";
    }
    html += part3;
    return html;
}

// You must delete the buffer manually!
char * readFile(const std::string &path, int* bufSize) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    if (size < 0) {
        return nullptr;
    }
    *bufSize = size;
    file.seekg(0, std::ios::beg);
    auto buffer = new char[size];
    file.read(buffer, size);
    return buffer;
}


#endif //HTTP_SERVER_RENDER_H
