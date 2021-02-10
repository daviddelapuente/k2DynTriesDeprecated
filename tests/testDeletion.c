#include "../materializeSuite.c"
#include "assert.h"

//much nodes to test deletion manualy (that means this is not a big test)

uint8_t path1[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t path2[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
uint8_t path3[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
uint8_t path4[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3};
uint8_t path5[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};

uint8_t path6[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
uint8_t path7[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2};
uint8_t path8[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3};
uint8_t path9[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0};
uint8_t path10[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1};

uint8_t path11[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2};
uint8_t path12[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3};
uint8_t path13[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0};
uint8_t path14[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1};
uint8_t path15[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2};

uint8_t path16[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3};
uint8_t path17[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
uint8_t path18[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1};
uint8_t path19[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2};
uint8_t path20[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3};

uint8_t path21[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0};
uint8_t path22[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1};
uint8_t path23[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2};
uint8_t path24[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3};
uint8_t path25[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0};


//this function will test the materialization of a Trie
void testDeletion(){
    //first we instanciate the trie
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
    //now we inert the first 65536 points (in fourth base)
    long long c=0;
    while(c<2){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        //uint8_t path[30]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        insertTrie(t, path, 23, 22);
        c++;
    }

    //now we materialize the trie in ../materializeFie/A1
    char srcFolder[] = "../materializeField/A1/";
    materializeTrie(t,srcFolder);

    c=0;
    while(c<1){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        //uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,2,3};
        deleteTrie(t, path, 23, 22);
        c++;
    }

    char srcFolder2[] = "../materializeField/A2/";
    materializeTrie(t,srcFolder2);

}

void testDeletion1(){
    //first we instanciate the trie
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

    insertTrie(t, path1, 23, 22);
    assert(isEdgeTrie(t,path1,23,22));

    deleteTrie(t, path1, 23, 22);
    assert(!isEdgeTrie(t,path1,23,22));

    insertTrie(t, path1, 23, 22);
    insertTrie(t, path2, 23, 22);
    insertTrie(t, path3, 23, 22);
    insertTrie(t, path4, 23, 22);
    insertTrie(t, path5, 23, 22);

    assert(isEdgeTrie(t,path1,23,22));
    assert(isEdgeTrie(t,path2,23,22));
    assert(isEdgeTrie(t,path3,23,22));
    assert(isEdgeTrie(t,path4,23,22));
    assert(isEdgeTrie(t,path5,23,22));

    assert(!isEdgeTrie(t,path6,23,22));
    assert(!isEdgeTrie(t,path7,23,22));
    assert(!isEdgeTrie(t,path8,23,22));
    assert(!isEdgeTrie(t,path9,23,22));
    assert(!isEdgeTrie(t,path10,23,22));


    deleteTrie(t, path1, 23, 22);
    deleteTrie(t, path2, 23, 22);
    deleteTrie(t, path3, 23, 22);
    deleteTrie(t, path4, 23, 22);

    assert(!isEdgeTrie(t,path1,23,22));
    assert(!isEdgeTrie(t,path2,23,22));
    assert(!isEdgeTrie(t,path3,23,22));
    assert(!isEdgeTrie(t,path4,23,22));
    assert(isEdgeTrie(t,path5,23,22));

    assert(!isEdgeTrie(t,path6,23,22));
    assert(!isEdgeTrie(t,path7,23,22));
    assert(!isEdgeTrie(t,path8,23,22));
    assert(!isEdgeTrie(t,path9,23,22));
    assert(!isEdgeTrie(t,path10,23,22));

}


void testDeletion2(){
    //first we instanciate the trie
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


    insertTrie(t, path1, 23, 22);
    insertTrie(t, path2, 23, 22);
    insertTrie(t, path3, 23, 22);
    insertTrie(t, path4, 23, 22);
    insertTrie(t, path5, 23, 22);

    insertTrie(t, path6, 23, 22);
    insertTrie(t, path7, 23, 22);
    insertTrie(t, path8, 23, 22);
    insertTrie(t, path9, 23, 22);
    insertTrie(t, path10, 23, 22);

    insertTrie(t, path11, 23, 22);
    insertTrie(t, path12, 23, 22);
    insertTrie(t, path13, 23, 22);
    insertTrie(t, path14, 23, 22);
    insertTrie(t, path15, 23, 22);

    insertTrie(t, path16, 23, 22);
    insertTrie(t, path17, 23, 22);
    insertTrie(t, path18, 23, 22);
    insertTrie(t, path19, 23, 22);
    insertTrie(t, path20, 23, 22);

    insertTrie(t, path21, 23, 22);
    insertTrie(t, path22, 23, 22);
    insertTrie(t, path23, 23, 22);
    insertTrie(t, path24, 23, 22);
    insertTrie(t, path25, 23, 22);

    assert(isEdgeTrie(t,path1,23,22));
    assert(isEdgeTrie(t,path2,23,22));
    assert(isEdgeTrie(t,path3,23,22));
    assert(isEdgeTrie(t,path4,23,22));
    assert(isEdgeTrie(t,path5,23,22));

    assert(isEdgeTrie(t,path6,23,22));
    assert(isEdgeTrie(t,path7,23,22));
    assert(isEdgeTrie(t,path8,23,22));
    assert(isEdgeTrie(t,path9,23,22));
    assert(isEdgeTrie(t,path10,23,22));

    assert(isEdgeTrie(t,path11,23,22));
    assert(isEdgeTrie(t,path12,23,22));
    assert(isEdgeTrie(t,path13,23,22));
    assert(isEdgeTrie(t,path14,23,22));
    assert(isEdgeTrie(t,path15,23,22));

    assert(isEdgeTrie(t,path16,23,22));
    assert(isEdgeTrie(t,path17,23,22));
    assert(isEdgeTrie(t,path18,23,22));
    assert(isEdgeTrie(t,path19,23,22));
    assert(isEdgeTrie(t,path20,23,22));

    assert(isEdgeTrie(t,path21,23,22));
    assert(isEdgeTrie(t,path22,23,22));
    assert(isEdgeTrie(t,path23,23,22));
    assert(isEdgeTrie(t,path24,23,22));
    assert(isEdgeTrie(t,path25,23,22));


    deleteTrie(t, path13, 23, 22);

    assert(isEdgeTrie(t,path1,23,22));
    assert(isEdgeTrie(t,path2,23,22));
    assert(isEdgeTrie(t,path3,23,22));
    assert(isEdgeTrie(t,path4,23,22));
    assert(isEdgeTrie(t,path5,23,22));

    assert(isEdgeTrie(t,path6,23,22));
    assert(isEdgeTrie(t,path7,23,22));
    assert(isEdgeTrie(t,path8,23,22));
    assert(isEdgeTrie(t,path9,23,22));
    assert(isEdgeTrie(t,path10,23,22));

    assert(isEdgeTrie(t,path11,23,22));
    assert(isEdgeTrie(t,path12,23,22));
    assert(!isEdgeTrie(t,path13,23,22));
    assert(isEdgeTrie(t,path14,23,22));
    assert(isEdgeTrie(t,path15,23,22));

    assert(isEdgeTrie(t,path16,23,22));
    assert(isEdgeTrie(t,path17,23,22));
    assert(isEdgeTrie(t,path18,23,22));
    assert(isEdgeTrie(t,path19,23,22));
    assert(isEdgeTrie(t,path20,23,22));

    assert(isEdgeTrie(t,path21,23,22));
    assert(isEdgeTrie(t,path22,23,22));
    assert(isEdgeTrie(t,path23,23,22));
    assert(isEdgeTrie(t,path24,23,22));
    assert(isEdgeTrie(t,path25,23,22));



    deleteTrie(t, path7, 23, 22);
    deleteTrie(t, path23, 23, 22);

    assert(isEdgeTrie(t,path1,23,22));
    assert(isEdgeTrie(t,path2,23,22));
    assert(isEdgeTrie(t,path3,23,22));
    assert(isEdgeTrie(t,path4,23,22));
    assert(isEdgeTrie(t,path5,23,22));

    assert(isEdgeTrie(t,path6,23,22));
    assert(!isEdgeTrie(t,path7,23,22));
    assert(isEdgeTrie(t,path8,23,22));
    assert(isEdgeTrie(t,path9,23,22));
    assert(isEdgeTrie(t,path10,23,22));

    assert(isEdgeTrie(t,path11,23,22));
    assert(isEdgeTrie(t,path12,23,22));
    assert(!isEdgeTrie(t,path13,23,22));
    assert(isEdgeTrie(t,path14,23,22));
    assert(isEdgeTrie(t,path15,23,22));

    assert(isEdgeTrie(t,path16,23,22));
    assert(isEdgeTrie(t,path17,23,22));
    assert(isEdgeTrie(t,path18,23,22));
    assert(isEdgeTrie(t,path19,23,22));
    assert(isEdgeTrie(t,path20,23,22));

    assert(isEdgeTrie(t,path21,23,22));
    assert(isEdgeTrie(t,path22,23,22));
    assert(!isEdgeTrie(t,path23,23,22));
    assert(isEdgeTrie(t,path24,23,22));
    assert(isEdgeTrie(t,path25,23,22));

}

int main(){
    //testDeletion();
    testDeletion1();
    testDeletion2();
    printf("congratulations, all test passed\n");
    return 0;
}