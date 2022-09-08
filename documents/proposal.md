# Ever wanted to be the speediest Wikipedia racer?

## Leading Question 
Ever wanted to be the speediest [Wikipedia](https://en.wikipedia.org/wiki/Wikipedia) racer? Many have dreamed of showing off to their [friends](https://en.wikipedia.org/wiki/friend) their prowess in navigating the [forest](https://en.wikipedia.org/wiki/forest) of links in a [Wikipedia](https://en.wikipedia.org/wiki/Wikipedia) page, but have fallen short in [embarrassment](https://en.wikipedia.org/wiki/embarrassment) as they get stuck on the wikipedia link to [Bongbong Marcos](https://en.wikipedia.org/wiki/Bongbong_Marcos), unable to find their desired page. Our goal is to prevent such [failures](https://en.wikipedia.org/wiki/failure) from ever occurring again, ensuring that we will always get from page A to B in the shortest [time](https://en.wikipedia.org/wiki/time) possible.

Our goal is to find the shortest path between two Wikipedia articles in the shortest amount of steps, that is, the least number of links necessary to click on Wikipedia articles, beginning from the given starting page, to navigate to the given target page. For example, navigating from the Wikipedia page for [Kleptocracy](https://en.wikipedia.org/wiki/kleptocracy) to the page for [Crime](https://en.wikipedia.org/wiki/crime) would require two clicks ([Kleptocracy](https://en.wikipedia.org/wiki/kleptocracy) -> [Corruption](https://en.wikipedia.org/wiki/corruption) -> [Crime](https://en.wikipedia.org/wiki/crime)). We also want our best algorithm to find the shortest path with the highest efficiency we can, that is, visiting the fewest articles to find said path. 

Some additional things, or stretch goals, that we might implement, could include the longest shortest path between any two pages, and also possibly quantifying the “usefulness” of an article, i.e. how much it facilitates the shortest path between all possible articles.

## Dataset acquisition and processing 
**Data Format:** 
We are getting our data from [Stanford’s SNAP database of Wikispeedia](http://snap.stanford.edu/data/wikispeedia.html) data. Wikispeedia is a game which requires humans to navigate from one Wikipedia page to another in as quick a time as possible. The game uses a condensed version of Wikipedia, in which there are only 4,604 articles, which contain 119,882 total links. As the dataset is already condensed, we plan to use all of the data provided.

We only are interested in using a subset of SNAP’s Wikispeedia data, specifically the links.tsv file. This file contains a tab-separated, 119,882 x 2 table. Each row represents a different link The first column contains the article the link appears in, and the second column contains the article the link directs to. 
	
**Data correction:**
In processing the data, we must omit links that lead to the same page that the link itself appears on. Furthermore, it may be possible that a link listed on a page has no corresponding page in the first column of our dataset. In this case, we can store the data in our usual manner, but handle empty links as an edge case in our traversals. We may do this by simply ending the iteration of the traversal if a find operation to retrieve the given page for a certain link ends up being empty. 

**Data storage:**
We will store the data into a hashmap, with article titles as keys, and a vector of links present on that article as corresponding values. We will also store a separate hashmap with article titles as keys and number of links present as values. To do this, we will iterate through each row of the dataset, adding each row as a pair into our article-title/link-vector hashmap. We will also compute the number of links for each article title and add that pair to our article-title/number-of-links hashmap. 

Worst-case total storage costs of our article-title/link-vector hashmap will be O(n²), where n is the number of article titles in our dataset. This is because theoretically, each article could link to every other article, resulting in n links per article. Storing these n links for each of the n articles would result in n² stored links. However, because each article contains a very small number of links compared to n, our storage costs will likely be O(n), as we can place a small finite upper bound on the number of links in each article that is arbitrarily small compared to n. Total storage cost for our article-title/number-of-links hashmap will be O(n), where n is the number of article titles in our dataset. This is because we need to store one and only one value representing the number of links for each article. 

## Graph algorithms 
1. Traversal Algorithm: Breadth First Search (BFS)
  - Function Inputs: Our BFS inputs will be the article-title/link-vector hashmap, as well as the names of the desired starting and ending article titles. It shouldn’t be necessary to convert the hashmap into anything else, as all necessary processing and data correction will have been done in the data processing stage. 
  - Function outputs: The function will output a vector containing the articles in the shortest path between the start and end articles, as well as the number of articles the algorithm needed to visit to find the shortest path, so as to compare the efficiency of the algorithms to others. 
  - Function Efficiency: O(n + m), where n is the number of nodes and m is the number of edges. Given our data, the number of nodes is the total number of articles, which is approximately 5,000, and the total number of edges is represented by the total number of links, which is approximately 120,000. Our target goal for the Big O efficiency of our algorithm runtime is O(n+m). Our target goal for efficiency of memory is O(n).
2. Graph Data Algorithm: Best First Search using number of links on page as weight heuristic
  - Function inputs: article-title/link-vector hashmap, as well as article-title/number-of-links hashmap
  - Function outputs: Same as BFS (1)
  - Function Efficiency: O(n + m), where n is the number of nodes and m is the number of edges.
3. Graph Data Algorithm: Iterative Deepening Depth-First Search (IDDFS)
  - Function inputs: Same as BFS (1)
  - Function outputs: Same as BFS (1)
  - Function Efficiency: The runtime complexity is the same as BFS, O(n+m). The space complexity of IDDFS differs from BFS, as it is O(d), where d is the depth of the target, which would also be the length of the shortest path. Our target goal for runtime is O(n+m), while the goal for memory O(d).

## Timeline: 
**Tasks (to be completed by end of stated date)**
1. Week 1: (April 1)
  - Acquire data & process data
    - Implement article-title/number-of-links hashmap
    - Implement article-title/link-vector hashmap
2. Week 2: (April 8)
  - Breadth First Search
    - Implement algorithm
    - Optimize to get to as close to target goal as possible
    - Create and run tests
3. Week 3: (April 15)
  - Best First Search
    - Begin implementation
4. Week 4: (April 22)
  - Best First Search
    - Finish and optimize algorithm
    - Create and run tests
  - Iterative Deepening Depth-First Search
    - Begin implementation
5. Week 5: (April 29)
  - Iterative Deepening Depth-First Search
    - Finish and optimize algorithm
    - Create and run tests
  - Create descriptive README
6. Week 6: (May 6)
  - Clean up code to make more readable
  - Make code execution easier
  - Write report in results.md
  - Record final presentation
