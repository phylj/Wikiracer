#include "BeFS.h"

#include <queue>
#include <algorithm>

/**
 * Performs a Best-First Search, only searching top half
 * of articles by links
 *
 * @param start - the starting article
 * @param target - the article being searched for
 * @param links - the graph used for search
 * @param articles - list of articles in graph
 * @return a vector of strings, which represents the shortest
 *         path from start to target
 */
std::vector<std::string> BeFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> links, std::set<std::string> &articles) {

    std::queue <std::string> queue;

    // holds pair as current node and previous node
    std::unordered_map<std::string, std::string> visited;

    queue.push(start);
    visited.insert(std::make_pair(start, ""));

    // error handling if start or target article doesn't exist
    if (articles.find(target) == articles.end()) {
        return { "The target article does not exist." };
    }
    if (start == target) {
        return { start };
    }
    if (links.find(start) == links.end()) {
        return { "Starting article does not exist, or the article does not contain any links." };
    }

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if (current == target) {
            std::vector<std::string> path;
            std::string curr = current;
            while (curr != "") {
                std::string next = visited.at(curr);
                path.insert(path.begin(), curr);
                curr = next;
            }
            return path;
        }
        if (links.find(current) != links.end()) {
            // goes through each directionally-adjacent article
            std::vector<size_t> sizes;
            for (std::string &n : links.at(current)) {
                if (visited.count(n) == 0 && links.find(n) != links.end()) {
                    sizes.push_back(links.at(n).size());
                }
            }
            // finds median number of links
            std::nth_element(sizes.begin(), sizes.begin() + sizes.size() / 2, sizes.end());
            size_t median_size = 0;
            if (sizes.size() > 0)
                median_size = sizes.at((sizes.size()) / 2);

            for (std::string &n : links.at(current)) {
                if (n == target) {
                    visited.insert(std::make_pair(n, current));
                    std::vector<std::string> path;
                    std::string curr = n;
                    while (curr != "") {
                        std::string next = visited.at(curr);
                        path.insert(path.begin(), curr);
                        curr = next;
                    }
                    return path;
                }

                // only adds articles with > median links to queue
                if (visited.count(n) == 0 && links.find(n) != links.end() && links.at(n).size() >= median_size) {
                    visited.insert(std::make_pair(n, current));
                    queue.push(n);
                }
            }
        }
    }
    return { "No path found." };
}
