#include "../materializeSuite.c"
#include "assert.h"

void testMaterializeTrie(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    t->children[0] = t->children[1] = t->children[2] = t->children[3] = NULL;
    t->block = NULL;

    double alpha = 0.99;
    N1 = 4;
    Nt = S3;
    sizeArray = (uint16_t *) malloc(sizeof(uint16_t)*(Nt+1));
    for (int i = 0; i <= Nt; ++i) {
        if (i > N1) N1 = 4*(((uint16_t)ceil((double)N1/alpha)+3)/4);
        sizeArray[i] = N1;
    }

    uint64_t n, n1;
    n=7414866;
    n1=7414866;

    long long c=0;

    while(c<65536){


        uint8_t path[30]={1,2,3,0,1,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(t, path, 23, 22);

        c++;
    }

    char srcFolder[] = "../materializeField/";

    materializeTrie(t,srcFolder);
}

int main(){
    testMaterializeTrie();
    printf("congratulations, all test passed\n");
    return 0;
}