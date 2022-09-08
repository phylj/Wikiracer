#include "./catch/catch.hpp"

#include "../src/parser.h"
#include "../src/searches/BFS.h"
#include "../src/searches/IDDFS.h"
#include "../src/searches/BeFS.h"

#include <iostream>

TEST_CASE("Parser & Cleaner", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");
    // uncomment below to see links
    // for (auto p : map) {
    //     std::cout << p.first << ": ";
    //     for (auto u : p.second) {
    //         std::cout << u << ", ";
    //     }
    //     std::cout << std::endl;
    // }
    REQUIRE(articles.size() == 10);
    REQUIRE(map["five"][0] == "six"); // only a single element in five's vector
    REQUIRE(map["one"].size() == 3); // 3 elements in one's vector
    REQUIRE(map.find("seven") == map.end()); // seven should have been cleaned since not in articles list
}

TEST_CASE("BFS - Starting article doesn't exist or has no links", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");
    std::vector<std::string> path = BFS("fifteen", "one", map, articles); // fifteen doesn't exist
    std::string expected = "Starting article does not exist, or the article does not contain any links.";
    REQUIRE(path[0] == expected);

    path = BFS("six", "one", map, articles); // six has no links
    REQUIRE(path[0] == expected);
}

TEST_CASE("BFS - Ending article doesn't exist", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "fifteen", map, articles); // fifteen doesn't exist
    std::string expected = "The target article does not exist.";
    REQUIRE(path[0] == expected);

}

TEST_CASE("BFS - No path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "five", map, articles);
    std::string expected = "No path found.";
    REQUIRE(path[0] == expected);

    path = BFS("three", "six", map, articles);
    REQUIRE(path[0] == expected);
}

TEST_CASE("BFS - start == target", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "one", map, articles);
    std::string expected = "one";
    REQUIRE(path[0] == expected);

    path = BFS("five", "five", map, articles);
    expected = "five";
    REQUIRE(path[0] == expected);

    path = BFS("six", "six", map, articles);
    expected = "six";
    REQUIRE(path[0] == expected);
}

TEST_CASE("BFS - short path: len 1", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "eight", map, articles);
    std::vector<std::string> expected = { "one", "eight" };
    REQUIRE(path == expected);

    path = BFS("two", "three", map, articles);
    expected = { "two", "three" };
    REQUIRE(path == expected);

    path = BFS("two", "one", map, articles);
    expected = { "two", "one" };
    REQUIRE(path == expected);
}

TEST_CASE("BFS - short path: len 2", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "three", map, articles);
    std::vector<std::string> expected = { "one", "two", "three" };
    REQUIRE(path == expected);

    path = BFS("three", "eight", map, articles);
    expected = { "three", "one", "eight" };
    REQUIRE(path == expected);

    path = BFS("two", "four", map, articles);
    expected = { "two", "one", "four" };
    REQUIRE(path == expected);
}

TEST_CASE("BFS - longer paths finds shortest possible path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BFS("one", "eleven", map, articles);
    // one -> eight -> nine -> ten -> eleven
    REQUIRE(path.size() == 5);

    path = BFS("two", "ten", map, articles);
    // two -> one -> eight -> nine -> ten
    REQUIRE(path.size() == 5);

    path = BFS("nine", "two", map, articles);
    // nine -> three -> one -> two
    REQUIRE(path.size() == 4);
}




TEST_CASE("IDDFS - Starting article doesn't exist or has no links", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("fifteen", "one", map, articles); // fifteen isn't a real number
    std::string expected = "Starting article does not exist, or the article does not contain any links.";
    REQUIRE(path[0] == expected);

    path = IDDFS("six", "one", map, articles); // six doesn't have any links
    REQUIRE(path[0] == expected);
}

TEST_CASE("IDDFS - Ending article doesn't exist", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "fifteen", map, articles); // fifteen isn't real
    std::string expected = "The target article does not exist.";
    REQUIRE(path[0] == expected);

}

TEST_CASE("IDDFS - No path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "five", map, articles);
    std::string expected = "No path found.";
    REQUIRE(path[0] == expected);

    path = IDDFS("three", "six", map, articles);
    REQUIRE(path[0] == expected);
}

TEST_CASE("IDDFS - start == target", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "one", map, articles);
    std::string expected = "one";
    REQUIRE(path[0] == expected);

    path = IDDFS("five", "five", map, articles);
    expected = "five";
    REQUIRE(path[0] == expected);

    path = IDDFS("six", "six", map, articles);
    expected = "six";
    REQUIRE(path[0] == expected);
}

TEST_CASE("IDDFS - short path: len 1", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "eight", map, articles);
    std::vector<std::string> expected = { "one", "eight" };
    REQUIRE(path == expected);

    path = IDDFS("two", "three", map, articles);
    expected = { "two", "three" };
    REQUIRE(path == expected);

    path = IDDFS("two", "one", map, articles);
    expected = { "two", "one" };
    REQUIRE(path == expected);
}

TEST_CASE("IDDFS - short path: len 2", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "three", map, articles);
    std::vector<std::string> expected = { "one", "two", "three" };
    REQUIRE(path == expected);

    path = IDDFS("three", "eight", map, articles);
    expected = { "three", "one", "eight" };
    REQUIRE(path == expected);

    path = IDDFS("two", "four", map, articles);
    expected = { "two", "one", "four" };
    REQUIRE(path == expected);
}

TEST_CASE("IDDFS - long paths find shortest path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = IDDFS("one", "eleven", map, articles);
    // one -> eight -> nine -> ten -> eleven
    REQUIRE(path.size() == 5);

    path = IDDFS("two", "ten", map, articles);
    // two -> one -> eight -> nine -> ten
    REQUIRE(path.size() == 5);

    path = IDDFS("nine", "two", map, articles);
    // nine -> three -> one -> two
    REQUIRE(path.size() == 4);
}





TEST_CASE("BeFS - Starting article doesn't exist or has no links", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("fifteen", "one", map, articles); // fifteen isn't a real number
    std::string expected = "Starting article does not exist, or the article does not contain any links.";
    REQUIRE(path[0] == expected);

    path = BeFS("six", "one", map, articles); // six doesn't have any links
    REQUIRE(path[0] == expected);
}

TEST_CASE("BeFS - Ending article doesn't exist", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "fifteen", map, articles); // fifteen isn't real
    std::string expected = "The target article does not exist.";
    REQUIRE(path[0] == expected);

}

TEST_CASE("BeFS - No path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "five", map, articles);
    std::string expected = "No path found.";
    REQUIRE(path[0] == expected);

    path = BeFS("three", "six", map, articles);
    REQUIRE(path[0] == expected);
}

TEST_CASE("BeFS - start == target", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "one", map, articles);
    std::string expected = "one";
    REQUIRE(path[0] == expected);

    path = BeFS("five", "five", map, articles);
    expected = "five";
    REQUIRE(path[0] == expected);

    path = BeFS("six", "six", map, articles);
    expected = "six";
    REQUIRE(path[0] == expected);
}

TEST_CASE("BeFS - short path: len 1", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "eight", map, articles);
    std::vector<std::string> expected = { "one", "eight" };
    REQUIRE(path == expected);

    path = BeFS("two", "three", map, articles);
    expected = { "two", "three" };
    REQUIRE(path == expected);

    path = BeFS("two", "one", map, articles);
    expected = { "two", "one" };
    REQUIRE(path == expected);
}

TEST_CASE("BeFS - short path: len 2", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "three", map, articles);
    std::vector<std::string> expected = { "one", "two", "three" };
    REQUIRE(path == expected);

    path = BeFS("three", "eight", map, articles);
    expected = { "three", "one", "eight" };
    REQUIRE(path == expected);

    path = BeFS("two", "four", map, articles);
    expected = { "two", "one", "four" };
    REQUIRE(path == expected);
}

TEST_CASE("BeFS - long paths find shortest path", "") {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("./tests/test-links.tsv", "./tests/test-articles.tsv");
    std::set<std::string> articles = get_articles("./tests/test-articles.tsv");

    std::vector<std::string> path = BeFS("one", "eleven", map, articles);
    // one -> eight -> nine -> ten -> eleven
    REQUIRE(path.size() == 5);

    path = BeFS("two", "ten", map, articles);
    // two -> one -> eight -> nine -> ten
    REQUIRE(path.size() == 5);

    path = BeFS("nine", "two", map, articles);
    // nine -> three -> one -> two
    REQUIRE(path.size() == 1); // no path found because the 'three' path was pruned
}
