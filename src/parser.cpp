#include "parser.h"

#include <fstream>

/**
 * parses given file to output as an unordered map
 *
 * @param links_file - name of file for links
 * @param article_file - name of file for article title list
 * @return an unordered map of article titles as keys
 *         and their corresponding vector of links as value
 */
std::unordered_map<std::string, std::vector<std::string>> parser(std::string links_file, std::string article_file) {
    std::unordered_map<std::string, std::vector<std::string>> out;
    std::ifstream file;
    file.open(links_file);
    std::string line;
    while (std::getline(file, line)) {
        // make sure line is not blank or a comment
        if (!line.empty() && line[0] != '#' && line[0] != ' ') {
            std::string k = line.substr(0, line.find('\t'));
            std::string v = line.substr(line.find('\t') + 1);
            if (out.count(k) > 0) {
                out.at(k).push_back(v);
            } else {
                out.insert(std::pair<std::string, std::vector<std::string>>(k, { v }));
            }
        }
    }
    // cleans before returning
    return clean(article_file, out);
}

/**
 * gets the articles from file
 *
 * @param article_file - the name of file to read from
 * @return the set of article titles
 */
std::set<std::string> get_articles(std::string article_file) {
    std::set<std::string> articles;

    std::ifstream file;
    file.open(article_file);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#' && line[0] != ' ')
            articles.emplace(line);
    }
    return articles;
}

/**
 * cleans the graph - removes articles not in the articles file
 * removes articles without links out of it from keys in graph
 *
 * @param article_file - file containing article titles
 * @param links - graph to clean
 * @return cleaned graph
 */
std::unordered_map<std::string, std::vector<std::string>> clean(std::string article_file, std::unordered_map<std::string, std::vector<std::string>> links) {
    std::set<std::string> articles = get_articles(article_file);
    for (auto &page : links) {
        if (page.second.size() == 0 || articles.find(page.first) == articles.end()) {
            links.erase(page.first);
            continue;
        }
        for (size_t i = 0; i < page.second.size(); i++) {
            if (articles.find(page.second[i]) == articles.end()) {
                page.second.erase(page.second.begin() + i);
                i--;
            }
        }
        if (page.second.size() == 0) {
            links.erase(page.first);
        }
    }
    return links;
}