#include "treeBlock.c"

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



    //int this part we print the results of creating the tree
    uint64_t msec = diff * 1000 / CLOCKS_PER_SEC;
    uint64_t count = 0;
    printf("Nodes in the root block: %d\n",B.nNodes);
    printf("Insertion time: %f microseconds per insertion\n", (float)msec*1000/nEdges);
    uint64_t treeSize = sizeTrie(t);//B.size();
    printf("Total size: %lu bytes\n", treeSize);
    printf("Bits per edge of the graph: %f\n", ((float)treeSize*8)/nEdges);
    printf("Numero de bloques en la estructura: %lu\n", totalBlocks);
    printf("Numero de nodos internos en el arbol: %lu\n", totalNodes);



    //in this part we are going to test the searching of edges
    //re read the graph file
    fseek(stdin,0,SEEK_SET);
    scanCode=scanf("%lu %lu %lu\n", &n, &n1, &nEdges);
    //diff to compute the time, found to know if an edge was found
    diff = 0;
    bool found = false;
    //we will test the first 100000000 edges in the file
    for (uint64_t i = 0; i < 100000000/*nEdges*/; ++i) {
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
        if (i%1000000 == 0) { printf("%lu %lu\n", i, count); fflush(stdout);}
        start = clock();
        //return tre if the edge is in the tree. t=trie pointer, str=morton code, 23=length of the morton code, 22=max level
        found = isEdgeTrie(t, str, 23, 22);//isEdge(&B, str, 23, 22);
        diff += clock() - start;
        if (found) count++;
    }



    // now we create an edge that not necesary is in the graph, and search it.
    str[0] = str[1] = str[2] = str[3] = str[4] = str[5] = str[6] = str[7] = str[8] = str[9] = str[10] = str[11] = 0;
    str[12] = str[13] = str[14] = str[15] = str[16] = str[17] = str[18] = str[19] = str[20] = str[21] = str[22] = 0;
    //some variables that we are going to use to iter
    uint8_t j;
    uint64_t i;
    //todo: quizas este codigo esta duplicado
    for (i = 0; i < 100000000; i++) {
        //todo: que hace esto?
        for (j = 22; j >= 0; j--) {
            if (str[j] != 3) break;
            str[j] = 0;
        }
        //todo: que hace esto?
        str[j]++;
        //each 1000000 print an edge
        if (i%1000000 == 0) {printf("%lu %lu\n", i, count); fflush(stdout);}
        start = clock();
        //return tre if the edge is in the tree. t=trie pointer, str=morton code, 23=length of the morton code, 22=max level
        found = isEdgeTrie(t, str, 23, 22); //isEdge(&B, str, 23, 22);
        diff += clock() - start;
        if (found) count++;
    }
    //print the results
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Search time: %f microseconds per query\n", (float)msec*1000/200000000);
    printf("Number of edges found: %lu\n", count);
    return 0;
}

