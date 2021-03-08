#include "../materializeSuite.c"
#include "assert.h"

/*This file contain the test that create a k2 dyn tree with the indochina graph
 you need to pass the graph file as an input when you run the program*/
int main()
{
    //first we init the variables used int the tree
    //todo: creo qe estas variables estan de mas.
    treeBlock B;
    treeNode node;
    node.first = 0;
    node.second = 0;
    uint16_t curFlag = 0;
    uint16_t subTreeSize;
    uint16_t level = 0;

    //we init the trieNode that will contain all the edges
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    t->children[0] = t->children[1] = t->children[2] = t->children[3] = NULL;
    t->block = NULL;

    //scan int code
    int scanCode;



    /*int this part we create the array that contains the sizes a block can have.
    a node always has %alpha of space ocupied
    N1,Nt,S3 and sizeArray are defined in treeBloch.h*/
    double alpha = 0.99;
    //min size of a block. (the min number of nodes a block can have is n1)
    N1 = 4;
    //max size a block can have (the max number of nodes a block can have is nt) we can test with: 96, 128, 256, 512, 1024
    Nt = S3;
    /*the array of sizes is of length Nt+1
    the idea is to acces sizeArray[i] where i is the actual number of nothes
    and the array will return the size the block should have
    so is probably that sizeArray[i]=sizeArray[i+1]*/
    sizeArray = (uint16_t *) malloc(sizeof(uint16_t)*(Nt+1));
    //for each espace in the array
    for (int i = 0; i <= Nt; ++i) {
        //todo: por que 4*(((uint16_t)ceil((double)N1/alpha)+3)/4)?;
        //we fill using this rule
        if (i > N1) N1 = 4*(((uint16_t)ceil((double)N1/alpha)+3)/4);
        sizeArray[i] = N1;
    }



    /*int this part we insert the nodes in the trie
    n=rows, n1=cols, nEdges=number of edges*/
    uint64_t n, n1, nEdges;
    //this variable will contain the string in the morton code of a edge (max of the string is 50, that means 2^50 nodes)
    uint8_t str[50];
    //init a clock
    clock_t start, diff=0;
    //we read the first line of the input (wich contains the number of: rows,cols,edges)
    scanCode=scanf("%lu %lu %lu\n", &n, &n1, &nEdges);
    for (uint64_t i = 0; i < nEdges; ++i) {
        //we read the line containing the edge
        scanCode=scanf("%s\n", str);
        //todo: podemos cambiar el 23 por length thel string en el futuro.
        //for each char of the string, we need to convert it to int.
        //todo: podemos usar atoi y ahorrarnos el switch
        for (uint8_t j = 0; j < 23; ++j)
            switch(str[j]) {
                case '0': str[j] = 0;
                    break;
                case '1': str[j] = 1;
                    break;
                case '2': str[j] = 2;
                    break;
                case '3': str[j] = 3;
                    break;
            }
        //we print each 1000000 edges
        if (i%1000000 == 0) {printf("%lu\n", i); fflush(stdout);}
        //for each edge, we sum the time it cost to insert
        start = clock();
        //t=trieNode, str=mortonCode, length of str=23, maxdepth of the tree=22
        insertTrie(t, str, 23, 22);
        diff += clock() - start;
    }

    printf("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");

    fseek(stdin,0,SEEK_SET);
    scanCode=scanf("%lu %lu %lu\n", &n, &n1, &nEdges);
    //diff to compute the time, found to know if an edge was found
    diff = 0;
    //we will test the first 100000000 edges in the file
    for (uint64_t i = 0; i < nEdges/*nEdges*/; ++i) {
        scanCode=scanf("%s\n", str);
        for (uint8_t j = 0; j < 23; ++j)
            switch(str[j]) {
                case '0': str[j] = 0;
                    break;
                case '1': str[j] = 1;
                    break;
                case '2': str[j] = 2;
                    break;
                case '3': str[j] = 3;
                    break;
            }
        //each 1000000 print an edge
        if (i%1000000 == 0) { printf("%lu\n", i); fflush(stdout);}
        start = clock();
        //return true if the edge is in the tree. t=trie pointer, str=morton code, 23=length of the morton code, 22=max level
        deleteTrie(t, str, 23, 22);//isEdge(&B, str, 23, 22);
        diff += clock() - start;
    }

    printf("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");

    fseek(stdin,0,SEEK_SET);
    scanCode=scanf("%lu %lu %lu\n", &n, &n1, &nEdges);
    //diff to compute the time, found to know if an edge was found
    diff = 0;
    //we will test the first 100000000 edges in the file
    for (uint64_t i = 0; i < nEdges/*nEdges*/; ++i) {
        scanCode=scanf("%s\n", str);
        for (uint8_t j = 0; j < 23; ++j)
            switch(str[j]) {
                case '0': str[j] = 0;
                    break;
                case '1': str[j] = 1;
                    break;
                case '2': str[j] = 2;
                    break;
                case '3': str[j] = 3;
                    break;
            }
        //each 1000000 print an edge
        if (i%1000000 == 0) { printf("%lu\n", i); fflush(stdout);}
        start = clock();
        //return true if the edge is in the tree. t=trie pointer, str=morton code, 23=length of the morton code, 22=max level
        assert(!isEdgeTrie(t, str, 23, 22));
        diff += clock() - start;
    }

    printf("congratulation, all test passed\n");



    return 0;
}

