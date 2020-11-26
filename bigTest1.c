#include "treeBlock.c"

int main()
{
    treeBlock B;
    treeNode node;
    uint16_t curFlag = 0;
    uint16_t subTreeSize;
    uint16_t level = 0;

    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    t->children[0] = t->children[1] = t->children[2] = t->children[3] = NULL;
    t->block = NULL;


    double alpha = 0.99;


    N1 = 4;

    // Tamaño maximo del bloque, probar con 96, 128, 256, 512, 1024
    Nt = S3;

    sizeArray = (uint16_t *) malloc(sizeof(uint16_t)*(Nt+1));

    for (int i = 0; i <= Nt; ++i) {
        if (i > N1) N1 = 4*(((uint16_t)ceil((double)N1/alpha)+3)/4);
        sizeArray[i] = N1;
    }


    node.first = 0;
    node.second = 0;

    uint64_t n, n1, nEdges;

    uint8_t str[50];

    clock_t start, diff=0;

    scanf("%lu %lu %lu\n", &n, &n1, &nEdges);

    for (uint64_t i = 0; i < nEdges; ++i) {
        scanf("%s\n", str);
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

        if (i%1000000 == 0) {printf("%lu\n", i); fflush(stdout);}

        start = clock();

        insertTrie(t, str, 23, 22);

        diff += clock() - start;

    }

    uint64_t msec = diff * 1000 / CLOCKS_PER_SEC;
    uint64_t count = 0;

    printf("Nodes in the root block: %d\n",B.nNodes);

    printf("Insertion time: %f microseconds per insertion\n", (float)msec*1000/nEdges);

    uint64_t treeSize = sizeTrie(t);//B.size();

    printf("Total size: %lu bytes\n", treeSize);

    printf("Bits per edge of the graph: %f\n", ((float)treeSize*8)/nEdges);

    printf("Numero de bloques en la estructura: %lu\n", totalBlocks);

    printf("Numero de nodos internos en el arbol: %lu\n", totalNodes);

    bool found = false;

    fseek(stdin,0,SEEK_SET);

    scanf("%lu %lu %lu\n", &n, &n1, &nEdges);

    diff = 0;

    for (uint64_t i = 0; i < 100000000/*nEdges*/; ++i) {
        scanf("%s\n", str);
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

        if (i%1000000 == 0) { printf("%lu %lu\n", i, count); fflush(stdout);}

        start = clock();

        found = isEdgeTrie(t, str, 23, 22);//isEdge(&B, str, 23, 22);

        diff += clock() - start;
        if (found) count++;
    }


    // Ahora genero arcos que no necesariamente están en el grafo y los busco

    str[0] = str[1] = str[2] = str[3] = str[4] = str[5] = str[6] = str[7] = str[8] = str[9] = str[10] = str[11] = 0;
    str[12] = str[13] = str[14] = str[15] = str[16] = str[17] = str[18] = str[19] = str[20] = str[21] = str[22] = 0;


    uint8_t j;

    uint64_t i;

    for (i = 0; i < 100000000; i++) {

        for (j = 22; j >= 0; j--) {
            if (str[j] != 3) break;
            str[j] = 0;
        }

        str[j]++;

        if (i%1000000 == 0) {printf("%lu %lu\n", i, count); fflush(stdout);}

        start = clock();

        found = isEdgeTrie(t, str, 23, 22); //isEdge(&B, str, 23, 22);

        diff += clock() - start;

        if (found) count++;

    }

    msec = diff * 1000 / CLOCKS_PER_SEC;

    printf("Search time: %f microseconds per query\n", (float)msec*1000/200000000);

    printf("Number of edges found: %lu\n", count);

    return 0;
}

