#include "treeBlock.c"
#include <sys/stat.h>

void writeTrieInfoFile(trieNode *t, char *filePath){
    char fileInfoStr[8]="       ";

    for(int i=0;i<4;i++){
        if(t->children[i]!=NULL){
            fileInfoStr[2*i]=1+'0';
        }else{
            fileInfoStr[2*i]=0+'0';
        }
    }

    FILE *fp;
    fp=fopen(filePath, "w+");
    fprintf(fp,"%s",fileInfoStr);
    fclose(fp);

}

void writeBlockInfoFile(treeBlock *block,char *filePath){
    FILE *fp;
    fp=fopen(filePath, "w+");

    fprintf(fp,"rootDepth = %u \n",block->rootDepth);
    fprintf(fp,"N nodes = %u \n", block->nNodes);
    fprintf(fp,"max nodes = %u \n", block->maxNodes);
    fprintf(fp,"nPtrs = %u \n", block->nPtrs);

    fprintf(fp,"\n");

    fprintf(fp,"dfuds =\n");

    //print the dfuds in file
    for(int i=0;i< (block->nNodes+3)/4;i++){



        uint16_t n=block->dfuds[i];
        uint16_t mask=0x8000;
        uint16_t mask2=0x7fff;
        int c=16;
        while (c) {
            if (n & mask) {
                fprintf(fp, "1");
            }else {
                fprintf(fp, "0");
            }
            n = n&mask2;
            mask >>=1;
            mask2 >>=1;
            c--;
        }
        fprintf(fp," ");
    }

    fprintf(fp,"\n");
    fprintf(fp,"\n");
    fprintf(fp,"frontier =\n");

    blockPtr *ptr=(blockPtr*)block->ptr;
    for (int i=0;i<block->nPtrs;i++){
        fprintf(fp,"%u ",ptr[i].flag);
    }

    fclose(fp);
}

void materializeBlock(treeBlock * t,char *srcFolder){
    char tempSrcFolder[strlen(srcFolder)];
    strcpy(tempSrcFolder, srcFolder);

    char aux[strlen(tempSrcFolder)];
    strcpy(aux, tempSrcFolder);
    strcat(aux,"/blockInfo");
    writeBlockInfoFile((treeBlock *) t,aux);


    blockPtr* ptr= (blockPtr*) ((treeBlock*) t)->ptr;
    for(int i=0;i< ((treeBlock*) t)->nPtrs;i++ ){
        //transform int to string

        int n2 = ptr[i].flag;
        int aux2=n2;
        int c2=1;
        while(aux2>9){
            aux2=aux2/10;
            c2++;
        }
        char s2[c2+2];
        for (int i2=0;i2<c2;i2++){
            int a2=1;
            for(int j2=0;j2<c2-1-i2;j2++){
                a2=a2*10;
            }
            int x2=n2/a2;
            s2[i2]=x2+'0';
            n2=n2%a2;
        }
        s2[c2]='/';
        s2[c2+1] = '\0';

        strcpy(tempSrcFolder, srcFolder);
        strcpy(aux, tempSrcFolder);
        strcat(aux,s2);
        mkdir(aux,0777);
        materializeBlock(ptr[i].P,aux);
    }
}

void materializeTrie(trieNode *t, char *srcFolder){
    if(t==NULL){
        printf("cant materialize empty trie\n");
    }else if(t->block!=NULL){
        materializeBlock((treeBlock*)t->block,srcFolder);
    }else{
        //inita temp srcFolder string
        char tempSrcFolder[strlen(srcFolder)];
        strcpy(tempSrcFolder, srcFolder);

        //now we create the trie root infoFile
        //aux will help managing the strings
        char aux[strlen(tempSrcFolder)];

        strcpy(aux, tempSrcFolder);
        strcat(aux,"/trieInfo");
        writeTrieInfoFile(t,aux);


        //now we create the folders that will contain the other levels
        char auxname[]="x/";
        for(int i=0;i<4;i++){
            auxname[0]=i+'0';

            strcpy(tempSrcFolder, srcFolder);
            strcpy(aux, tempSrcFolder);
            strcat(aux,auxname);
            mkdir(aux,0777);

            if(t->children[i]!=NULL){
                materializeTrie(t->children[i],aux);
            }
        }

    }
}