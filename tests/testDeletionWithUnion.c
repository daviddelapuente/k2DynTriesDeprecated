#include "../materializeSuite.c"
#include "assert.h"

void test100Deterministic1(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));

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

    long long c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }


    c=0;
    while(c<=50){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=50){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=50){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=78;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }
    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=78){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=78;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=31;
    while(c<=63){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(31<=c && c<=63){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=31;
    while(c<=63){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

}

void test1000Deterministic1(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));
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

    long long c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=213){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=213){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=213){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=967;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=967){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=967;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=99;
    while(c<=859){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(99<=c && c<=859){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=99;
    while(c<=859){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

}

void test10000Deterministic1(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));
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

    long long c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=9999){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=9999){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=9999){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=1;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=1){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=1;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=100;
    while(c<=900){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(100<=c && c<=900){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=100;
    while(c<=900){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }



}


void test100000Deterministic1(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));
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

    long long c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=57328){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=57328){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=57328){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=65532;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=65532){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=65532;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=2;
    while(c<=99998){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(2<=c && c<=99998){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=2;
    while(c<=99998){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

}


void test1000000Deterministic1(){

    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));
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

    long long c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=327888){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=327888){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=327888){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=388999;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=388999){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=388999;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=177356;
    while(c<=555777){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(177356<=c && c<=555777){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=177356;
    while(c<=555777){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=1000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }



}

























void test5MDeterministic1(){



    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));

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

    long long c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=3485955){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c<=3485955){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=0;
    while(c<=3485955){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=1000000;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(c>=1000000){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=1000000;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=200000;
    while(c<=4800000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        if(200000<=c && c<=4800000){
            assert(!isEdgeTrie(g,t,path,23,22));
        }else{
            assert(isEdgeTrie(g,t,path,23,22));
        }
        c++;
    }

    c=200000;
    while(c<=4800000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(isEdgeTrie(g,t,path,23,22));
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=5000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        assert(!isEdgeTrie(g,t,path,23,22));
        c++;
    }
}



void test10MDeterministic1(){



    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));

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

    long long c=0;
    while(c<=10000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=10000000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }





}


















void dummyTest(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));
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

    long long c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=1;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }
    c=1;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }
    c=0;
    while(c<=10000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }



}


void testDeletion(){
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g=(treeGenoma*) malloc(sizeof(treeGenoma));

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

    long long c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g,t, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g,t, path, 23, 22);
        c++;
    }

    trieNode *t2 = (trieNode *) malloc(sizeof(trieNode));
    treeGenoma *g2=(treeGenoma*) malloc(sizeof(treeGenoma));


    t2->children[0] = t2->children[1] = t2->children[2] = t2->children[3] = NULL;
    t2->block = NULL;

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        insertTrie(g2,t2, path, 23, 22);
        c++;
    }

    c=0;
    while(c<=100000){
        uint8_t path[30]={0,0,0,0,0,0,0,0,0,0,0,(uint8_t) ((c/4194304)%4),(uint8_t) ((c/1048576)%4),(uint8_t) ((c/262144)%4),(uint8_t) ((c/65536)%4),(uint8_t) ((c/16384)%4),(uint8_t) ((c/4096)%4),(uint8_t) ((c/1024)%4),(uint8_t) ((c/256)%4),(uint8_t) ((c/64)%4),(uint8_t) ((c/16)%4),(uint8_t) ((c/4)%4),(uint8_t) (c%4)};
        deleteTrie2(g2,t2, path, 23, 22);
        c++;
    }

}

int main(){
    testDeletion();
    test100Deterministic1();
    test1000Deterministic1();
    test10000Deterministic1();
    test100000Deterministic1();
    test1000000Deterministic1();
    test5MDeterministic1();
    test10MDeterministic1();
    printf("congratulations, all test passed in\n");
    return 0;
}