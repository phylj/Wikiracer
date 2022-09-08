#### Weekly Log

##### Week 1
  Our goals for this week were to set up the repository on each member's 
  machine, and to begin parsing the values in the given data to turn 
  into the two hashmaps described in our proposal for use in our algorithms.
  
  Eric did research into input parsing methods, while Phyllis set up the 
  structure of the repository and wrote the log. David began working on 
  the function that would parse the data and turn it into the two hashmaps,
  and created a Makefile. 
  
  Currently we have not run into any issues, although we
  had forgotten some things, such as reading from files, which required 
  time in order to research and understand again. 
  
  Next week, we plan to stick with what we had planned to do for the 
  second week, making the BFS using the hashmaps we create this week.
  
  ##### Week 2
  Our goal for this week was to get BFS implemented and ideally optimized.
  
  Phyllis and Eric worked on implementing BFS, and I (David), wrote this
  dev log. We ran into memory troubles, which means that the BFS can only
  run for a maximum of 5 steps away from the original article, which is
  good, but not good enough for every article.
  
  Next week, we will work on implementing the Best First Search algorithm,
  which will hopefully have better performance.

  ##### Week 3
  Our goal for this week was to clean up BFS and start Best First Search, or BeFS. 
  David, Phyllis, and I (Eric) worked on the MakeFile to resolve a linking issue which forced us 
  to store our code in header files. Phyllis and David resolved our previous week's memory troubles 
  concerning maximum steps, and I cleaned up our code for BFS to make it even more memory-efficient and readable.
  We also populated our BeFS files with our BFS code.

  Next week, we plan to modify BFS with our priority heuristic to make it a Best-First Search. We also plan to 
  further develop our makefile to declutter and organize our workspace. 
  
  ###### Week 4
  Our goals for this week were to continue working on BeFS, and begin IDDFS.
  Phyllis worked to implement IDDFS, which currently works but could probably still be further optimized. 
  Phyllis also did some informal testing of performance between BFS and IDDFS. Eric and David did further
  research into BeFS, since we had to modify our original plan of only using a BFS + heuristic for the search.
  Phyllis also changed the method of execution for the program, so that the user now has to pass in the
  start and target articles from the command line to search. We didn't encounter any issues this week, though
  performance could likely be improved somewhat for IDDFS.
  
  Next week, we plan to implement the Best-First Search. We also plan to make small test cases for the 
  implemented algorithms to ensure edge cases are covered.
  
  ###### Week 5
  Our goal for this week was to implement BeFS and make small test cases.
  We didn't get too much done this week with a lot of work from a few other classes, but Phyllis made the cleaning code for the parser and Eric and I (David) have been working on making a smaller database of articles for test cases. We have also been talking about how we will implement the BeFS.
  Next week we hope to actually implement the BeFS and some test cases.
