#include "treeBlock.c"
#include "assert.h"

void testShiftTTable(){
    printf("Begin testShiftTTable Tables\n");
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

    printf("end testShiftTTable Tables\n");
}

void testMaskInitT(){
    printf("Begin testMaskInitT Tables\n");

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

    printf("end testMaskInitT Tables\n");
}

//this test is used to test if the tables are right
void testTables(){
    printf("Begin testTables Tables\n");
    testShiftTTable();
    testMaskInitT();
    printf("end testTables Tables\n");
}

int main(){
    testTables();
    return 0;
}