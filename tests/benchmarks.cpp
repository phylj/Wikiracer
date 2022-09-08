#include <chrono>
#include <random>
#include <sys/time.h>

#include "../src/parser.h"
#include "../src/searches/BFS.h"
#include "../src/searches/IDDFS.h"
#include "../src/searches/BeFS.h"

/**
 * Some testing to compare execution time for different searches.
 * Currently limited by path size and existence of path.
 */
int main() {
    std::unordered_map<std::string, std::vector<std::string>> map = parser("links.tsv", "articles.tsv");
    std::set<std::string> articles = get_articles("articles.tsv");

    std::vector<std::string> articles_vec;
    for (auto &str : articles)
        articles_vec.push_back(str);

    timeval tv;
    gettimeofday(&tv, NULL);
    long random_seed = tv.tv_sec * 1000000 + tv.tv_usec;
    srand(random_seed);

    std::vector<std::pair<int, size_t>> times(3);
    std::vector<std::string> path;

    auto start_num = std::rand() % articles.size();
    auto target_num = std::rand() % articles.size();
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    size_t max = 0;
    size_t skip = 0;
    size_t optimal_len = 0;
    size_t unoptimal = 0;
    std::vector<std::string> max_path;

    for (int i = 0; i < 100; i++) {
        start_num = std::rand() % articles.size();
        target_num = std::rand() % articles.size();
        start = std::chrono::high_resolution_clock::now();

        path = BFS(articles_vec[start_num], articles_vec[target_num], map, articles);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if (path.size() == 1) {
            skip++;
            continue;
        }
        if (path.size() > 5) continue; // comment this line out to test longer paths -> will take longer to execute
        times[0].first += path.size();
        times[0].second += duration.count();
        if (path.size() > max) {
            max = path.size();
            max_path = path;
        }

        optimal_len = path.size();

        start = std::chrono::high_resolution_clock::now();
        path = IDDFS(articles_vec[start_num], articles_vec[target_num], map, articles);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        times[1].first += path.size();
        times[1].second += duration.count();

        start = std::chrono::high_resolution_clock::now();
        path = BeFS(articles_vec[start_num], articles_vec[target_num], map, articles);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        times[2].first += path.size();
        times[2].second += duration.count();

        if (path.size() != optimal_len) {
            unoptimal++;
        }
    }
    std::cout << "BFS time: " << times[0].second << std::endl;
    std::cout << "IDDFS time: " << times[1].second << std::endl;
    std::cout << "BeFS time: " << times[2].second << std::endl;

    // std::cout << "Average Path Size: " << times[0].first / 100.0 << std::endl; 
    // std::cout << "Longest Path Found: " << max << std::endl;
    // for (auto p : max_path) {
    //     std::cout << p << ", ";
    // }
    // std::cout << "Skip Rate: " << skip / 100.0 << std::endl;

    // std::cout << "Times BeFS did not find best path: " << unoptimal << std::endl;
    return 0;
}