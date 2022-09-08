#pragma once

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

std::vector<std::string> BFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> &links, std::set<std::string> &articles);
