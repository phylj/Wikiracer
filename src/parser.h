#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

std::unordered_map<std::string, std::vector<std::string>> parser(std::string links_file, std::string article_file);

std::set<std::string> get_articles(std::string filename);
std::unordered_map<std::string, std::vector<std::string>> clean(std::string article_file, std::unordered_map<std::string, std::vector<std::string>> links);
