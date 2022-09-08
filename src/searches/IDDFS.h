#pragma once

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>


std::vector<std::string> IDDFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> &links, std::set<std::string> &articles);

bool DFS(std::vector<std::string> &path, std::string &start, std::string &target, std::unordered_map<std::string, std::vector<std::string>> &links, int depth);
