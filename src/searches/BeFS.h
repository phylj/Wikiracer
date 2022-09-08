#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

std::vector<std::string> BeFS(std::string start, std::string target, std::unordered_map<std::string, std::vector<std::string>> links, std::set<std::string> &articles);
