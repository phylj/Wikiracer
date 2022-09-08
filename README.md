# pjwang3-davidrw3-esliu3

## Becoming the Fastest Wikipedia Racer

Our program finds the shortest path between two Wikipedia articles in the shortest amount of steps, that is, the least number of links necessary to click on Wikipedia articles, beginning from the given starting page, to navigate to the given target page. For example, navigating from the Wikipedia page for Kleptocracy to the page for Crime would require two clicks ([Kleptocracy](https://en.wikipedia.org/wiki/Kleptocracy) -> [Corruption](https://en.wikipedia.org/wiki/Corruption) -> [Crime](https://en.wikipedia.org/wiki/Crime)). We also want our best algorithm to find the shortest path with the highest efficiency we can, that is, visiting the fewest articles to find said path. 

The database that we are using is an outdated version of Wikipedia, so some paths may no longer be reflective of the current site.

### Compiling
Run ```make``` from the command line.

### Running - add option for input dataset?
Run ```./exec [search] [starting article] [target article] [output file name] [links]?```. \[links] is an optional field that allows the user to pass in a dataset of their own. 

Replace [search] with the desired search, without the brackets. The options are: ```bfs```, ```befs```, ```iddfs```.

Replace [starting article] and [target article] with the **exact** title of the respective articles, without the brackets. If no articles matching the arguments are found, or no path is found, the program will indicate such. 

Otherwise, the path from the two articles, given by the connecting articles, will be output into the given output file name.

Example command: ```./exec iddfs Gravitation Photon path.csv```

### Testing

#### Compiling
Run ```make tests``` from the command line.

#### Running
Run ```./test```.

To make other test cases, edit "test-articles.tsv" and "test-links.tsv" found in the tests folder, along with tests.cpp. Adding more paths will probably break the existing tests since the optimal paths may be changed. Also ensure that the articles and links are separated by **tabs**, not spaces like many IDEs change it to.

### Linkage and Location
- The src folder contains main.cpp, the parser header and source files, and the searches folder, which contains the three search's header and source files.

- Tests and testing data are found in the tests folder.

- The database of Wikipedia articles and their links are found in articles.tsv and links.tsv, respectively.

- All documents (contract, proposal, log, results, video) are found in the documents folder.

### Inspiration & Sources
