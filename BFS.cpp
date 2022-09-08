#include "BFS.h"
// #include "parser.h"
#include <unordered_set>
#include <string>

std::vector<std::string> BFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> links) {
    // need to do error checking to make sure strings are valid articles
    std::queue < std::string > queue; // there is definitely a better way to do this
    std::map<std::string, std::string> ancestor; //maps each article to the article that came before it
    std::vector<std::string> path = { start };
    int count = 0;
    queue.push(std::make_pair(start, path));
    visited.insert(std::make_pair(start, true));
    if (links.find(start) == links.end() || links.find(target) == links.end()) {
        return { "Article(s) does not exist." };
    }
    while (!queue.empty()) {
        std::pair<std::string, std::vector<std::string>> tmp = queue.front();
        // std::cout << tmp.first << std::endl;
        queue.pop();
        count++;
        if (tmp.first == target) {
            std::cout << std::endl << "Looked at " << count << " articles." << std::endl;
            return tmp.second;
        }
        if (links.find(tmp.first) != links.end()) {
            visited.insert(std::make_pair(tmp.first, true));
            for (std::string n : links.at(tmp.first)) {
                std::vector<std::string> copy_this_cannot_be_good = tmp.second;
                copy_this_cannot_be_good.push_back(n);
                queue.push(std::make_pair(n, copy_this_cannot_be_good));
            }
        }
    }
    return {};
}