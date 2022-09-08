#include "IDDFS.h"

/**
 * performs an iterative-deepening depth first search
 *
 * @param start - the starting article
 * @param target - the article being searched for
 * @param links - the graph used for search
 * @param articles - list of articles in graph
 * @return a vector of strings, which represents the shortest
 *         path from start to target
 */
std::vector<std::string> IDDFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> &links, std::set<std::string> &articles) {
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

    int max_depth = 0;
    while (max_depth < 8) {
        std::vector<std::string> path = {};
        // performs DFS at specified depth
        // returns path if found, increases depth otherwise
        if (DFS(path, start, target, links, max_depth)) {
            return path;
        }
        max_depth++;
    }
    return { "No path found." };
}

/**
 * performs depth first search, limited by depth
 *
 * @param path - the path being built through DFS recursively
 * @param start - the starting article
 * @param target - the article being searched for
 * @param links - the graph used for search
 * @param depth - the maximum depth to search
 * @param visited - tracks if node has been visited
 * @return whether a path was found
 */
bool DFS(std::vector<std::string> &path, std::string &start, std::string &target, std::unordered_map<std::string, std::vector<std::string>> &links, int depth) {
    if (start == target) {
        // std::cout << std::endl << "IDDFS looked at " << count << " articles." << std::endl;
        path.push_back(start);
        return true;
    }
    if (depth == 0 || links.find(start) == links.end()) {
        return false;
    }
    for (std::string &e : links.at(start)) {
        // perform DFS on all directionally-adjacent articles
        if (DFS(path, e, target, links, depth - 1)) {
            path.insert(path.begin(), start);
            return true;
        }
    }
    return false;
}
