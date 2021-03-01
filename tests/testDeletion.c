#include "../materializeSuite.c"
#include "assert.h"

//much nodes to test deletion manualy (that means this is not a big test)

uint8_t paths[25][30]={
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0},

};


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

    insertTrie(t, paths[0], 23, 22);
    assert(isEdgeTrie(t,paths[0],23,22));

    deleteTrie(t, paths[0], 23, 22);
    assert(!isEdgeTrie(t,paths[0],23,22));

    insertTrie(t, paths[0], 23, 22);
    insertTrie(t, paths[1], 23, 22);
    insertTrie(t, paths[2], 23, 22);
    insertTrie(t, paths[3], 23, 22);
    insertTrie(t, paths[4], 23, 22);

    assert(isEdgeTrie(t,paths[0],23,22));
    assert(isEdgeTrie(t,paths[1],23,22));
    assert(isEdgeTrie(t,paths[2],23,22));
    assert(isEdgeTrie(t,paths[3],23,22));
    assert(isEdgeTrie(t,paths[4],23,22));

    assert(!isEdgeTrie(t,paths[5],23,22));
    assert(!isEdgeTrie(t,paths[6],23,22));
    assert(!isEdgeTrie(t,paths[7],23,22));
    assert(!isEdgeTrie(t,paths[8],23,22));
    assert(!isEdgeTrie(t,paths[9],23,22));


    deleteTrie(t, paths[0], 23, 22);
    deleteTrie(t, paths[1], 23, 22);
    deleteTrie(t, paths[2], 23, 22);
    deleteTrie(t, paths[3], 23, 22);

    assert(!isEdgeTrie(t,paths[0],23,22));
    assert(!isEdgeTrie(t,paths[1],23,22));
    assert(!isEdgeTrie(t,paths[2],23,22));
    assert(!isEdgeTrie(t,paths[3],23,22));
    assert(isEdgeTrie(t,paths[4],23,22));

    assert(!isEdgeTrie(t,paths[5],23,22));
    assert(!isEdgeTrie(t,paths[6],23,22));
    assert(!isEdgeTrie(t,paths[7],23,22));
    assert(!isEdgeTrie(t,paths[8],23,22));
    assert(!isEdgeTrie(t,paths[9],23,22));

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


    insertTrie(t, paths[0], 23, 22);
    insertTrie(t, paths[1], 23, 22);
    insertTrie(t, paths[2], 23, 22);
    insertTrie(t, paths[3], 23, 22);
    insertTrie(t, paths[4], 23, 22);

    insertTrie(t, paths[5], 23, 22);
    insertTrie(t, paths[6], 23, 22);
    insertTrie(t, paths[7], 23, 22);
    insertTrie(t, paths[8], 23, 22);
    insertTrie(t, paths[9], 23, 22);

    insertTrie(t, paths[10], 23, 22);
    insertTrie(t, paths[11], 23, 22);
    insertTrie(t, paths[12], 23, 22);
    insertTrie(t, paths[13], 23, 22);
    insertTrie(t, paths[14], 23, 22);

    insertTrie(t, paths[15], 23, 22);
    insertTrie(t, paths[16], 23, 22);
    insertTrie(t, paths[17], 23, 22);
    insertTrie(t, paths[18], 23, 22);
    insertTrie(t, paths[19], 23, 22);

    insertTrie(t, paths[20], 23, 22);
    insertTrie(t, paths[21], 23, 22);
    insertTrie(t, paths[22], 23, 22);
    insertTrie(t, paths[23], 23, 22);
    insertTrie(t, paths[24], 23, 22);

    assert(isEdgeTrie(t,paths[0],23,22));
    assert(isEdgeTrie(t,paths[1],23,22));
    assert(isEdgeTrie(t,paths[2],23,22));
    assert(isEdgeTrie(t,paths[3],23,22));
    assert(isEdgeTrie(t,paths[4],23,22));

    assert(isEdgeTrie(t,paths[5],23,22));
    assert(isEdgeTrie(t,paths[6],23,22));
    assert(isEdgeTrie(t,paths[7],23,22));
    assert(isEdgeTrie(t,paths[8],23,22));
    assert(isEdgeTrie(t,paths[9],23,22));

    assert(isEdgeTrie(t,paths[10],23,22));
    assert(isEdgeTrie(t,paths[11],23,22));
    assert(isEdgeTrie(t,paths[12],23,22));
    assert(isEdgeTrie(t,paths[13],23,22));
    assert(isEdgeTrie(t,paths[14],23,22));

    assert(isEdgeTrie(t,paths[15],23,22));
    assert(isEdgeTrie(t,paths[16],23,22));
    assert(isEdgeTrie(t,paths[17],23,22));
    assert(isEdgeTrie(t,paths[18],23,22));
    assert(isEdgeTrie(t,paths[19],23,22));

    assert(isEdgeTrie(t,paths[20],23,22));
    assert(isEdgeTrie(t,paths[21],23,22));
    assert(isEdgeTrie(t,paths[22],23,22));
    assert(isEdgeTrie(t,paths[23],23,22));
    assert(isEdgeTrie(t,paths[24],23,22));



    deleteTrie(t, paths[12], 23, 22);

    assert(isEdgeTrie(t,paths[0],23,22));
    assert(isEdgeTrie(t,paths[1],23,22));
    assert(isEdgeTrie(t,paths[2],23,22));
    assert(isEdgeTrie(t,paths[3],23,22));
    assert(isEdgeTrie(t,paths[4],23,22));

    assert(isEdgeTrie(t,paths[5],23,22));
    assert(isEdgeTrie(t,paths[6],23,22));
    assert(isEdgeTrie(t,paths[7],23,22));
    assert(isEdgeTrie(t,paths[8],23,22));
    assert(isEdgeTrie(t,paths[9],23,22));

    assert(isEdgeTrie(t,paths[10],23,22));
    assert(isEdgeTrie(t,paths[11],23,22));
    assert(!isEdgeTrie(t,paths[12],23,22));
    assert(isEdgeTrie(t,paths[13],23,22));
    assert(isEdgeTrie(t,paths[14],23,22));

    assert(isEdgeTrie(t,paths[15],23,22));
    assert(isEdgeTrie(t,paths[16],23,22));
    assert(isEdgeTrie(t,paths[17],23,22));
    assert(isEdgeTrie(t,paths[18],23,22));
    assert(isEdgeTrie(t,paths[19],23,22));

    assert(isEdgeTrie(t,paths[20],23,22));
    assert(isEdgeTrie(t,paths[21],23,22));
    assert(isEdgeTrie(t,paths[22],23,22));
    assert(isEdgeTrie(t,paths[23],23,22));
    assert(isEdgeTrie(t,paths[24],23,22));



    deleteTrie(t, paths[6], 23, 22);
    deleteTrie(t, paths[22], 23, 22);
    assert(isEdgeTrie(t,paths[0],23,22));
    assert(isEdgeTrie(t,paths[1],23,22));
    assert(isEdgeTrie(t,paths[2],23,22));
    assert(isEdgeTrie(t,paths[3],23,22));
    assert(isEdgeTrie(t,paths[4],23,22));

    assert(isEdgeTrie(t,paths[5],23,22));
    assert(!isEdgeTrie(t,paths[6],23,22));
    assert(isEdgeTrie(t,paths[7],23,22));
    assert(isEdgeTrie(t,paths[8],23,22));
    assert(isEdgeTrie(t,paths[9],23,22));

    assert(isEdgeTrie(t,paths[10],23,22));
    assert(isEdgeTrie(t,paths[11],23,22));
    assert(!isEdgeTrie(t,paths[12],23,22));
    assert(isEdgeTrie(t,paths[13],23,22));
    assert(isEdgeTrie(t,paths[14],23,22));

    assert(isEdgeTrie(t,paths[15],23,22));
    assert(isEdgeTrie(t,paths[16],23,22));
    assert(isEdgeTrie(t,paths[17],23,22));
    assert(isEdgeTrie(t,paths[18],23,22));
    assert(isEdgeTrie(t,paths[19],23,22));

    assert(isEdgeTrie(t,paths[20],23,22));
    assert(isEdgeTrie(t,paths[21],23,22));
    assert(!isEdgeTrie(t,paths[22],23,22));
    assert(isEdgeTrie(t,paths[23],23,22));
    assert(isEdgeTrie(t,paths[24],23,22));


}

void testDeletion3(){


    int miniTests=(int) pow(2,25);
    for(int i=miniTests/3;i<miniTests;i++){
        printf("%i\n",i);
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

        for (int i=0;i<25;i++){
            insertTrie(t, paths[i], 23, 22);
        }

        for (int i=0;i<25;i++){
            assert(isEdgeTrie(t, paths[i], 23, 22));
        }

        //delete some nodes

        int n=i;
        int c=24;
        while (c>=0) {
            if (n & 1) {
                deleteTrie(t, paths[c], 23, 22);
            }
            n >>=1;
            c--;
        }

        //assert all nodes
        n=i;
        c=24;
        while (c>=0) {
            if (n & 1) {
                assert(!isEdgeTrie(t,paths[c],23,22));
            }else{
                assert(isEdgeTrie(t,paths[c],23,22));
            }
            n >>=1;
            c--;
        }

        //insert those nodes;
        n=i;
        c=24;
        while (c>=0) {
            if (n & 1) {
                insertTrie(t,paths[c],23,22);
            }
            n >>=1;
            c--;
        }
        //asert all nodes
        n=i;
        c=24;
        while (c>=0) {
            assert(isEdgeTrie(t,paths[c],23,22));
            n >>=1;
            c--;
        }

    }
}



void testDeletion4(){
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

    for (int i=0;i<25;i++){
        insertTrie(t, paths[i], 23, 22);
    }

    for (int i=0;i<25;i++){
        assert(isEdgeTrie(t, paths[i], 23, 22));
    }

    int miniTests=(int) pow(2,25);
    for(int i=0;i<miniTests;i++){
        printf("%i\n",i);


        //delete some nodes

        int n=i;
        int c=24;
        while (c>=0) {
            if (n & 1) {
                deleteTrie(t, paths[c], 23, 22);
            }
            n >>=1;
            c--;
        }

        //assert all nodes
        n=i;
        c=24;
        while (c>=0) {
            if (n & 1) {
                assert(!isEdgeTrie(t,paths[c],23,22));
            }else{
                assert(isEdgeTrie(t,paths[c],23,22));
            }
            n >>=1;
            c--;
        }

        //insert those nodes;
        n=i;
        c=24;
        while (c>=0) {
            if (n & 1) {
                insertTrie(t,paths[c],23,22);
            }
            n >>=1;
            c--;
        }
        //asert all nodes
        n=i;
        c=24;
        while (c>=0) {
            assert(isEdgeTrie(t,paths[c],23,22));
            n >>=1;
            c--;
        }

    }
}

void testDeletionx(){
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

    for (int i=0;i<25;i++){
        insertTrie(t, paths[i], 23, 22);
    }

    for (int i=0;i<25;i++){
        assert(isEdgeTrie(t, paths[i], 23, 22));
    }


    deleteTrie(t,paths[19],23,22);
    deleteTrie(t,paths[18],23,22);
    deleteTrie(t,paths[17],23,22);
    deleteTrie(t,paths[16],23,22);

    char srcFolder2[] = "../materializeField/A2/";
    materializeTrie(t,srcFolder2);
}

void testDeletiony(){
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

    for (int i=0;i<25;i++){
        if(i!=19 && i!=18 && i!=17 && i!=16){
            insertTrie(t, paths[i], 23, 22);
        }
    }

    for (int i=0;i<25;i++){
        if(i!=19 && i!=18 && i!=17 && i!=16) {
            assert(isEdgeTrie(t, paths[i], 23, 22));
        }else{
            assert(!isEdgeTrie(t, paths[i], 23, 22));
        }
    }

    char srcFolder2[] = "../materializeField/A1/";
    materializeTrie(t,srcFolder2);

}

int main(){
    testDeletion1();
    testDeletion2();
    testDeletion3();
    //testDeletion4();
    //testDeletiony();
    //testDeletionx();
    printf("congratulations, all test passed\n");
    return 0;
}