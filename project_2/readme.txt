Ryan Pascal 2932732
Algorithms Project 2

Running the project:
    To compile source use make command: `make all`
    Then to run the program execute this command: `./convexHull435 <algorithm type> <input file>`
        For example: `./convexHull435 Q test.txt` to run quick hull on test.txt

High-level:
    Project 2's purpose is to execute various convex hull algorithms of data sets of varying sizes/shapes.
    Then comparing the runtimes of each of these datasets to see how the different algorithms
    perform under each circumstance. 

Unusual:
    The program can also be excuted to run on many datasets all at once and output the runtimes to a text file. 
    This funcinality was implemented to easily get the runtimes of all the different datasets.
    To run this funcinality once compiled execute `./convexHull435 testRuntimes` however
    there would need to be additional setting up to point to where the data files are located.