#include "treeBlock.c"
#include "assert.h"

void pf(uint16_t u){
    printf("%u\n",u);
}
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

//this test is used to test if the tables are right
void testTables(){
    testShiftTTable();
    testMaskInitT();
}

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

void testTreeBlock(){
    testTreeBlockGrow();
    testTreeBlockShrink();
}

int main(){
    testTables();
    testTreeNode();
    testTreeBlock();
    printf("congratulations, all test passed\n");
    return 0;
}