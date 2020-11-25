# k2-dyn-tries

## 1) how to run the program:

1.1) first you need a file with a graph. in our case we will use the indochina-2004.Zorder
(or go to section 2 to see how te create a graph for testing). we are not going to upload
the indochina graph to git because is very heavy so if you make git clone probably you wont
have a test graph (again, see section 2 to create one).

1.2) compile the program in the comand line:

    g++ treeBlock.c -o treeBlock -O9
probably you will see some warnings

1.3) test the treeBlock in the comand line:

    ./treeBlock < indochina-2004.Zorder
    
the program is right if you see something like this printed in the comand line:

0

1000000

2000000

3000000

...