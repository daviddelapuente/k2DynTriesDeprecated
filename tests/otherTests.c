#include "treeBlock.c"
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

    uint8_t path0[50]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    insertTrie(t, path0, 23, 22);
    materializeTrie(t);
}

int main(){
    testMaterializeTrie();
    printf("congratulations, all test passed\n");
    return 0;
}