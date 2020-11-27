#include "treeBlock.c"
#include "assert.h"

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

int main(){
    testTables();
    testTreeNode();
    printf("congratulations, all test passed\n");
    return 0;
}