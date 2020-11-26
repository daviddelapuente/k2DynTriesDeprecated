# k2-dyn-tries

## 1) how to run the program:

1.1) first you need a file with a graph. in our case we will use the indochina-2004.Zorder
(or go to section 2 to see how te create a graph for testing). we are not going to upload
the indochina graph to git because is very heavy so if you make git clone probably you wont
have a test graph (again, see section 2 to create one).

1.2) compile the program in the comand line:

    g++ bigTest1.c -o bigTest1 -O9

probably you will see some warnings

1.3) test the treeBlock in the comand line:

    ./bigTest1 < indochina-2004.Zorder
    
the program is right if you see something like this printed in the comand line:

0

1000000

2000000

3000000

...

## 2) how to create your own graph

1) create a file with any name, for example exampleGraph.txt

2) in the first line write 3 numbers: numberOfRows, numberOfCols, numberOfEdges

3) then write numberOfEdges lines with a string of length 23.
This string should only have the cars '0', '1', '2', '3'. This string represent
an edge in the morton code.

4) an example of the file could be:

7414866 7414866 5

10000100003000002320000

11000000000320000002000

12321321321321000000000

01000003210000000000000

00222000030011110000000

and this represent a graph of 7414866 nodes and 5 edges.