#include "parser.h"
#include "searches/BFS.h"
#include "searches/IDDFS.h"
#include "searches/BeFS.h"

#include <fstream>

int main(int argc, char *argv[]) {
  if (argc != 5 && argc != 6) {
    std::cout << "USAGE: ./exec [search] [starting article] [target article] [output file name] [links]?" << std::endl;
    return -1;
  }

  std::string search = argv[1];
  std::string start = argv[2];
  std::string target = argv[3];
  std::string outputFile = argv[4];

  std::fstream ifs(outputFile, std::fstream::out);
  std::string linkDir = argc == 6 ? argv[5] : "links.tsv";
  std::unordered_map<std::string, std::vector<std::string>> links = parser(linkDir, "articles.tsv");
  std::set<std::string> articles = get_articles("articles.tsv");

  std::vector< std::string> path;
  if (search == "bfs") {
    path = BFS(start, target, links, articles);
  } else if (search == "befs") {
    path = BeFS(start, target, links, articles);
  } else if (search == "iddfs") {
    path = IDDFS(start, target, links, articles);
  } else {
    std::cout << "Enter a valid search type. Valid search types include bfs, befs, iddfs" << std::endl;
    return -1;
  }
  for (auto p : path) {
    std::cout << p << ", ";
    ifs << p << ", ";
  }
  ifs << std::endl;
  std::cout << std::endl;
  ifs.close();

  return 0;
}