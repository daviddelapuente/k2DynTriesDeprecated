#include "treeBlock.c"
#include "assert.h"

void pf(uint16_t u){
    printf("%u\n",u);
}


//test tables

void testShiftTTable(){
    assert(shiftT[0]==12);
    assert(shiftT[1]==8);
    assert(shiftT[2]==4);
    assert(shiftT[3]==0);

    //0000111100000000
    uint16_t a=3840;

    //0000111100000000
    assert(a>>shiftT[3]==3840);
    //0000000011110000
    assert(a>>shiftT[2]==240);
    //0000000000001111
    assert(a>>shiftT[1]==15);

}

void testMaskInitT(){
    assert(maskInitT[0]==0xf000);
    assert(maskInitT[1]==0x0f00);
    assert(maskInitT[2]==0x00f0);
    assert(maskInitT[3]==0x000f);

    //1001110010110010
    uint16_t a=40114;

    //1001000000000000
    assert((a & maskInitT[0])==36864);
    //0000110000000000
    assert((a & maskInitT[1])==3072);
    //0000000010110000
    assert((a & maskInitT[2])==176);
    //0000000000000010
    assert((a & maskInitT[3])==2);

}

void testNChildrenT(){
    //0000 has 0 childrens
    assert(nChildrenT[0x0000]==0);

    //0001, 0010, 0100, 1000 has only one children
    assert(nChildrenT[0x0001]==1);
    assert(nChildrenT[0x0002]==1);
    assert(nChildrenT[0x0004]==1);
    assert(nChildrenT[0x0008]==1);

    assert(nChildrenT[0x0003]==2);
    assert(nChildrenT[0x0005]==2);
    assert(nChildrenT[0x0006]==2);
    assert(nChildrenT[0x0009]==2);
}

void testChildSkipT(){
    // 0000 does not has childrens, so it doesnot has childrens to skip
    assert(childSkipT[0x0000][0]==0);
    assert(childSkipT[0x0000][1]==0);
    assert(childSkipT[0x0000][2]==0);
    assert(childSkipT[0x0000][3]==0);

    //0001 the only children is right most, so it will never be skiped
    assert(childSkipT[0x0001][0]==0);
    assert(childSkipT[0x0001][1]==0);
    assert(childSkipT[0x0001][2]==0);
    assert(childSkipT[0x0001][3]==0);

    //0010 has  only one 1 at position 2, son when 3 is inserted, it has to skip it
    assert(childSkipT[0x0002][0]==0);
    assert(childSkipT[0x0002][1]==0);
    assert(childSkipT[0x0002][2]==0);
    assert(childSkipT[0x0002][3]==1);

    //1101 has  only one 1 at position 2, son when 3 is inserted, it has to skip it
    assert(childSkipT[0x000d][0]==0);
    assert(childSkipT[0x000d][1]==1);
    assert(childSkipT[0x000d][2]==2);
    assert(childSkipT[0x000d][3]==2);
}

void testChildT(){
    // 0000 does not has childrens, so we mark its soughts Childrens with a -1
    assert(childT[0x0000][0]==-1);
    assert(childT[0x0000][1]==-1);
    assert(childT[0x0000][2]==-1);
    assert(childT[0x0000][3]==-1);

    // 0101 has two childrens, so in position one, it has sought 1 children, and in position three, it has sought two childrens
    assert(childT[0x0005][0]==-1);
    assert(childT[0x0005][1]==1);
    assert(childT[0x0005][2]==-1);
    assert(childT[0x0005][3]==2);
}

void testInsertT(){
    assert(insertT[0x000d][0]==0xd);
    assert(insertT[0x000d][1]==0xd);
    assert(insertT[0x000d][2]==0xf);
    assert(insertT[0x000d][3]==0xd);
}

void testSymbol2NodeT(){
    assert(symbol2NodeT[0]==0x8);
    assert(symbol2NodeT[1]==0x4);
    assert(symbol2NodeT[2]==0x2);
    assert(symbol2NodeT[3]==0x1);
}
//this test is used to test if the tables are right
void testTables(){
    testShiftTTable();
    testMaskInitT();
    testNChildrenT();
    testChildSkipT();
    testChildT();
    testInsertT();
    testSymbol2NodeT();
}





//test treeNode functions
void testAbsolutePosition(){
    treeNode tn;
    tn.first=0;
    tn.second=0;
    assert(absolutePosition(tn)==0);
    tn.first=1;
    tn.second=2;
    assert(absolutePosition(tn)==6);
}

void testNextNode(){
    treeNode tn;
    tn.first=1;
    tn.second=1;
    assert(absolutePosition(tn)==5);
    nextNode(tn);
    assert(absolutePosition(tn)==6);
    nextNode(tn);
    assert(absolutePosition(tn)==7);
    nextNode(tn);
    assert(absolutePosition(tn)==8);
    nextNode(tn);
    assert(absolutePosition(tn)==9);
    nextNode(tn);
    assert(absolutePosition(tn)==10);

    //checking the second line of the function
    tn.second=0;
    assert(!tn.second==1);
    tn.second=1;
    assert(!tn.second==0);
    tn.second=2;
    assert(!tn.second==0);
    tn.second=3;
    assert(!tn.second==0);

}

void testPrevNode(){
    treeNode tn;
    tn.first=1;
    tn.second=1;
    assert(absolutePosition(tn)==5);
    prevNode(tn);
    assert(absolutePosition(tn)==4);
    prevNode(tn);
    assert(absolutePosition(tn)==3);
    prevNode(tn);
    assert(absolutePosition(tn)==2);
    prevNode(tn);
    assert(absolutePosition(tn)==1);
    prevNode(tn);
    assert(absolutePosition(tn)==0);
}

void testTreeNode(){
    testAbsolutePosition();
    testNextNode();
    testPrevNode();
}





//test for tree block
void testTreeBlockGrow(){
    //first we create an array of sizes
    double alpha = 0.99;
    N1 = 4;
    Nt = S3;
    sizeArray = (uint16_t *) malloc(sizeof(uint16_t)*(Nt+1));
    for (int i = 0; i <= Nt; ++i) {
        if (i > N1) N1 = 4*(((uint16_t)ceil((double)N1/alpha)+3)/4);
        sizeArray[i] = N1;
    }

    for(uint16_t i=12;i<100;i++){
        for(uint16_t j=1;j<100;j++){
            //we create the block
            treeBlock *block = (treeBlock *)malloc(sizeof(treeBlock));

            //instantiate the max nodes and the defuds
            block->maxNodes = sizeArray[i];
            block->dfuds = (uint16_t *)calloc((sizeArray[i]+4-1)/4, sizeof(uint16_t));
            block->nNodes=block->maxNodes;

            //grow by j
            block->grow(j);

            //the assert is withsizeArray[sizeArray[i]+j] because sizeArray[i] is the max nodes beforw adding j
            assert(block->maxNodes==sizeArray[sizeArray[i]+j]);
        }
    }
}

void testTreeBlockShrink(){
    //first we create an array of sizes
    double alpha = 0.99;
    N1 = 4;
    Nt = S3;
    sizeArray = (uint16_t *) malloc(sizeof(uint16_t)*(Nt+1));
    for (int i = 0; i <= Nt; ++i) {
        if (i > N1) N1 = 4*(((uint16_t)ceil((double)N1/alpha)+3)/4);
        sizeArray[i] = N1;
    }

    for(uint16_t i=20;i<100;i++){
        for(uint16_t j=1;j<i;j++){
            //we create the block
            treeBlock *block = (treeBlock *)malloc(sizeof(treeBlock));

            //instantiate the max nodes and the defuds
            block->maxNodes = sizeArray[i];
            block->dfuds = (uint16_t *)calloc((sizeArray[i]+4-1)/4, sizeof(uint16_t));
            block->nNodes=block->maxNodes;

            //grow by j
            block->shrink(j);

            //the assert is withsizeArray[sizeArray[i]-j] because sizeArray[i] is the max nodes before removing j
            assert(block->maxNodes==sizeArray[sizeArray[i]-j]);
        }
    }
}

//in this test we only focus on the first levels
void testInsertTrie(){
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

    uint64_t n, n1, nEdges;
    uint8_t str[50];

    int scanCode;
    FILE* ptr = fopen("testGraphs/exampleGraph1.txt","r");

    if (ptr==NULL){
        printf("no such file.");
        assert(1==0);
    }

    scanCode=fscanf(ptr,"%lu %lu %lu\n", &n, &n1, &nEdges);
    for (uint64_t i = 0; i < nEdges; ++i) {
        scanCode=fscanf(ptr,"%s\n", str);
        for (uint8_t j = 0; j < 23; ++j) {
            switch (str[j]) {
                case '0':
                    str[j] = 0;
                    break;
                case '1':
                    str[j] = 1;
                    break;
                case '2':
                    str[j] = 2;
                    break;
                case '3':
                    str[j] = 3;
                    break;
            }
        }

        insertTrie(t, str, 23, 22);
    }


    trieNode *tAux1=t;
    //first level
    assert(tAux1->children[0]==NULL);
    assert(tAux1->children[1]!=NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);


    //second level, notice that here we have to childrens, so from now we will test both childrens (in BFS)
    tAux1=tAux1->children[1];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]!=NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    trieNode *tAux2=t;
    tAux2=tAux1->children[1];

    //3 level
    tAux1=tAux1->children[0];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]==NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    assert(tAux2->children[0]!=NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]==NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

    //4 level
    tAux1=tAux1->children[0];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]==NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    tAux2=tAux2->children[0];
    assert(tAux2->children[0]!=NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]==NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

    //5 level
    tAux1=tAux1->children[0];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]==NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    tAux2=tAux2->children[0];
    assert(tAux2->children[0]!=NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]==NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

    //6 level
    tAux1=tAux1->children[0];
    assert(tAux1->children[0]==NULL);
    assert(tAux1->children[1]!=NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    tAux2=tAux2->children[0];
    assert(tAux2->children[0]==NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]!=NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

    //7 level
    tAux1=tAux1->children[1];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]==NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    tAux2=tAux2->children[2];
    assert(tAux2->children[0]!=NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]==NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

    //8 level
    tAux1=tAux1->children[0];
    assert(tAux1->children[0]!=NULL);
    assert(tAux1->children[1]==NULL);
    assert(tAux1->children[2]==NULL);
    assert(tAux1->children[3]==NULL);
    assert(tAux1->block==NULL);

    tAux2=tAux2->children[0];
    assert(tAux2->children[0]!=NULL);
    assert(tAux2->children[1]==NULL);
    assert(tAux2->children[2]==NULL);
    assert(tAux2->children[3]==NULL);
    assert(tAux2->block==NULL);

}

//todo:
void testInsert(){

}

//todo:
void testSelectSubtree2(){

}

void testTreeBlock(){
    testTreeBlockGrow();
    testTreeBlockShrink();

    testInsertTrie();
    testInsert();
    testSelectSubtree2();
}





int main(){
    testTables();
    testTreeNode();
    testTreeBlock();
    printf("congratulations, all test passed\n");
    return 0;
}