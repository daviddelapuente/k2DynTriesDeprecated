#include "treeBlock.h"

// Transform a node from it pair <NODE_TYPE,OFFSET_TYPE> to it absolute representation (position) in DFUDS
uint16_t absolutePosition(treeNode &node){
    return 4*node.first + node.second;
}

//todo: por que inline?
/*give the next node in the dfuds.
for example, if your node is <1,1> it absolute position will be 5
then the next node will be <1,2> because it absolute position will be 6*/
inline void nextNode(treeNode &node){
    //this is like (second+1)%4
    node.second = (node.second+1) & 0x3;
    //this sum 1 <=> node.second=0, and will sum 0 in an ohter case
    node.first += !node.second;
}

/*give the previous node in the dfuds.
for example, if your node is <1,0> it absolute position will be 4
then the next node will be <0,3> because it absolute position will be 3*/
inline void prevNode(treeNode &node){
    //only subtract 1 if node.second=0
    node.first -= !node.second;
    //this is like (second-1)%4
    node.second = (node.second-1) & 0x3;
}

//todo: crear tests de esta estrucutura cuando sepas lo que hace
//struct to retreive some data of the nodes
struct nodeInfo{
    //preorder: give the preorder of the node in the topology
    uint16_t preorder;
    //give the number of children the node have from 1 to 4
    uint16_t nChildren;
    //constructors
    nodeInfo() {};
    nodeInfo(uint16_t _preorder, uint16_t _nChildren){
        preorder = _preorder;
        nChildren = _nChildren;
    };
};

//todo: crear tests de esta estructura cuando sepas lo que hace
//struct to rereive some data of the subtrees of a node
struct subtreeInfo{
    //the preorder of a subtree
    uint16_t preorder;
    //the size of the subtree
    uint16_t subtreeSize;
    //constructors
    subtreeInfo() {};
    subtreeInfo(uint16_t _preorder, uint16_t _subtreeSize){
        preorder = _preorder;
        subtreeSize = _subtreeSize;
    };
};





/*Is important to free the memory.
This is a recursive function. first we free the dfuds.
and then recursively we free the children blocks, finally
we free the array with the children pointers and this*/
//todo: testear esto
void treeBlock::freeTreeBlock(){
    free((void *)dfuds);
    for (uint16_t i = 0; i < nPtrs; ++i){
        ((blockPtr *) ptr)[i].P->freeTreeBlock();
    }
    free((void*)ptr);
    free(this);
}

/*this method, realloc dfuds in a bigger array
the idea is that the new size of the block should be sizeArray[nNodes+extraNodes]
remember that sizeArray is an array of max sizes per blocks.*/
//todo: testear esto, pq ese + 3 / 4?
void treeBlock::grow(uint16_t extraNodes){
     dfuds = (uint16_t *) realloc(dfuds, sizeof(uint16_t)*((sizeArray[nNodes+extraNodes] + 3)/4));
     //the new max is sizeArray[nNodes+extraNodes]
     maxNodes = 4*((sizeArray[nNodes+extraNodes]+3)/4);
}

/*this method, realloc dfuds in a smaller array
the idea is that the new size of the block should be sizeArray[nNodes-extraNodes]
remember that sizeArray is an array of max sizes per blocks.*/
//todo: testear esto, pq ese + 3/4?
void treeBlock::shrink(uint16_t deletedNodes){
    dfuds = (uint16_t *) realloc(dfuds, sizeof(uint16_t)*((sizeArray[nNodes-deletedNodes] + 3)/4));
    //the new max is sizeArray[nNodes+extraNodes]
    maxNodes = 4*((sizeArray[nNodes-deletedNodes]+3)/4);
}





//todo: ver si el 4096 se puede generalizar
//all of these sizes are 4096, becouse are the maximum number of subtrees a block can have
//array of subtree info
nodeInfo stackSS[4096];
//this array contains all the subtrees
subtreeInfo subtrees[4096];
//array of deepth of every subtree
uint16_t depthVector[4096];

//todo: elimine selectSubtree

treeNode treeBlock::selectSubtree2(uint16_t maxDepth, uint16_t & subTreeSize, uint16_t & depthSelectN){

    // depth is the depth of the root of the block
    uint16_t depth= rootDepth + 1;

    //curFlago=0 means that we are in the first fronteir node
    uint16_t curFlag = 0;
    //initialize a nextFlag
    int32_t nextFlag;

    //current node codification
    uint8_t cNodeCod = (*dfuds>>12) & 0x000f;

    //init the index of the 3 arrays (stackSS,subtrees,depthVector)
    uint16_t ssTop=0, subtreeTop = 0, depthTop = 0;
    //the first node preorder is 0 and the number of children is a number between 0 and 4 and is given by the table nChildernT and de cNodeCod codification
    stackSS[ssTop].preorder = 0;
    stackSS[ssTop++].nChildren =  nChildrenT[cNodeCod];

    //this will keep a finger on the frontier
    if (nPtrs == 0 || curFlag >= nPtrs){
        //there arent more flags (fronteir nodes), we set the nextFlago to -1 to distinguish it
        nextFlag = -1;
    }else{
        //we continue with the next flag (this is the current flag in our ptr array)
        nextFlag = ((blockPtr *)ptr)[curFlag].flag;
    }

    //we iter for each node in the block to calculeta the subtrees sizes
    for (uint16_t i=1; i < nNodes; ++i) {
        //if we are in a frontier
        if (i == nextFlag) {

            //go to the next fronteir node
            ++curFlag;
            //if we run out of fronteir nodes, we set nextFlag to -1 to distinguis it
            if (nPtrs == 0 || curFlag >= nPtrs){
                nextFlag = -1;
            }else{
                //we continue with the next fronteir node
                nextFlag = ((blockPtr *)ptr)[curFlag].flag;
            }

            //substract 1 from the childrens that are not visited yet in the node (this is stackSS[sstop-1])
            --stackSS[ssTop-1].nChildren;

        //if we are not a fronteir node (and still we dont pass the max Depth)
        }else if (depth < maxDepth) {
            //in this part we fill the nodeInfo i
            //fill the preorder of the nodeInfo
            stackSS[ssTop].preorder = i;
            //get the node code
            cNodeCod = (dfuds[i>>2]>>shiftT[i & 0x3]) & 0x000f;
            //fill the childrens of the node info, and then sstop++
            stackSS[ssTop++].nChildren = nChildrenT[cNodeCod];
            depth++;
        }else {
            //we only actualize that we visited this node and continue with the next
            --stackSS[ssTop-1].nChildren;
        }

        //now we fill the subtrees info
        //this ssTop~i so this is O(n^2)
        //todo: necesito mas orientacion de como se hace esto :(
        while (ssTop > 0 && stackSS[ssTop-1].nChildren == 0) {
            subtrees[subtreeTop].preorder = stackSS[ssTop-1].preorder;
            subtrees[subtreeTop++].subtreeSize = i-stackSS[ssTop-1].preorder+1;
            --ssTop;
            depthVector[depthTop++] = --depth;
            if (ssTop == 0) {
                break;
            }else {
                stackSS[ssTop-1].nChildren--;
            }
        }
    }


    // Now we iter the subtree vector to choose the better subbtree
    int16_t  nodemin, min, posmin;
    uint16_t leftmost = MAX_UINT_16;
    for (uint16_t i = 0; i < subtreeTop; ++i) {
        //of all the subtrees we will prefer the ones that it sizes is between 25% and 75% of the actual block.
        //and from all of those, we will prefer the left most (in preorder)
        if (((float)nNodes/4) <= subtrees[i].subtreeSize && subtrees[i].subtreeSize <= ((float)3*nNodes/4) && subtrees[i].preorder < leftmost) {
            leftmost = nodemin = subtrees[i].preorder;
            posmin = i;
        }
    }


    //border case, this menas, that the last filter didn choose any candidate, so we will use another metric
    //and the new subtree is the one that minimize nNodes-2*subtreeSize.
    if (leftmost == MAX_UINT_16) {
        int16_t diff;
        nodemin = subtrees[0].preorder,
        min = nNodes - subtrees[0].subtreeSize - subtrees[0].subtreeSize,
        posmin = 0;

        for (uint16_t i = 1; i < subtreeTop; ++i) {
            diff = nNodes - 2*subtrees[i].subtreeSize;
            if (diff < 0){
                diff = -diff;
            }
       
            if (diff < min) {
                min = diff;
                nodemin = subtrees[i].preorder;
                posmin = i;
            }
        }
    }


    //actualize the subTreesize and its depth
    subTreeSize = subtrees[posmin].subtreeSize;
    depthSelectN = depthVector[posmin];

    //return the tuple in function of nodemin
    return treeNode(nodemin >> 2,nodemin & 0x3);
}



































int8_t stack[100];

treeNode dummyRootBlockNode(0,0);


void treeBlock::insert(treeNode node, uint8_t str[], uint64_t length, uint16_t level, 
                       uint64_t maxDepth, uint16_t curFlag)
 {
    treeNode nodeAux = node;
    
    if (rootDepth </*=*/ L1) Nt = S1;
    else if (rootDepth <= L2) Nt = S2;
    else Nt = S3;
    
    if (ptr!=NULL && curFlag < nPtrs && absolutePosition(node) == ((blockPtr *)ptr)[curFlag].flag) {
       // insertion must be carried out in the root of a child block
        uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;
        
        register uint64_t aux = 4*(3-node.second);        
        
        dfuds[node.first] = dfuds[node.first] & ~(0xF << aux); 
           
        dfuds[node.first] = dfuds[node.first] | (insertT[cNodeCod][str[0]] << aux);
        
        ((blockPtr *)ptr)[curFlag].P->insert(dummyRootBlockNode, str, length, level, maxDepth, 0);

        return;
    }
    else
    if (length == 1) {
       uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;
       
       register uint64_t aux = 4*(3-node.second);       
       
       dfuds[node.first] = dfuds[node.first] & ~(0xF << aux); 
          
       dfuds[node.first] = dfuds[node.first] | (insertT[cNodeCod][str[0]] << aux);
       return;            
    }
    else 
    if (nNodes + length - 1 <= maxNodes) {
       // there is room in current block for new nodes
                 
       // Se coloca en la posicion donde se insertaran los nuevos descendientes de node
       node = skipChildrenSubtree(node, str[0], level, maxDepth, curFlag);
       
       treeNode origNode, destNode;
       
       --length; 
       
       destNode.first =  (nNodes + length - 1)/4;
       destNode.second = (nNodes + length - 1)%4;
             
       origNode.first = (nNodes - 1)/4;
       origNode.second = (nNodes - 1)%4;
       
       uint16_t preorderNode = absolutePosition(node);       
       uint16_t preorderOrigNode = absolutePosition(origNode);
       uint16_t preorderDestNode =  absolutePosition(destNode);
       
       register uint64_t aux, aux2;       
       
       while (preorderOrigNode >= preorderNode) {
          aux = 4*(3-(preorderDestNode & 0x3) /*destNode.second*/);
          aux2 = preorderDestNode >> 2;
         
          dfuds[aux2/*destNode.first*/] = dfuds[aux2/*destNode.first*/] & ~(0xF << aux);
                                 
          dfuds[aux2/*destNode.first*/] = dfuds[aux2/*destNode.first*/] 
                                 | (((dfuds[preorderOrigNode>>2/*origNode.first*/] >> 4*(3-(preorderOrigNode & 0x3)/*origNode.second*/)) 
                                 & 0x000F) << aux) ;            
          //prevNode(destNode);
          --preorderDestNode;          
          //prevNode(origNode);
          --preorderOrigNode;
       }

       uint8_t cNodeCod = (dfuds[nodeAux.first]>>shiftT[nodeAux.second]) & 0x000f;
        
       dfuds[nodeAux.first] = dfuds[nodeAux.first]
                              & ~(0xF << 4*(3-nodeAux.second)); 
         
       dfuds[nodeAux.first] = dfuds[nodeAux.first] 
                             | (insertT[cNodeCod][str[0]] << 4*(3-nodeAux.second));
       
       //nextNode(origNode);
       ++preorderOrigNode;
    
       for (uint16_t i = 1; i <= length; i++) {
          aux = 4*(3-(preorderOrigNode & 0x3)/*origNode.second*/);
          aux2 = preorderOrigNode >> 2;

          dfuds[aux2/*origNode.first*/] = dfuds[aux2/*origNode.first*/] & ~(0xF << aux); 
          
          dfuds[aux2/*origNode.first*/] = dfuds[aux2/*origNode.first*/] 
                                 | (symbol2NodeT[str[i]] << aux);
          ++nNodes;          
          //nextNode(origNode);
          ++preorderOrigNode;
       }
    
       // Now updates the flags, as new nodes have been added
       if (ptr)
          for (uint16_t i = curFlag; i < nPtrs; ++i)
             ((blockPtr *)ptr)[i].flag += length;
    }
    else {
       // there is no room for the new nodes

       if (nNodes + length - 1 <= Nt) { // block can still grow
          // if the block can still grow, grow it.
          grow(length-1);
          // After growing, recursively inserts the node 
          insert(node, str, length, level, maxDepth, curFlag);
       
       }
       else {
          treeNode selectedNode, originalSelectedNode;
          
          uint16_t subTreeSize, depthSelectedNode;
          
          originalSelectedNode = selectedNode = selectSubtree2(maxDepth, subTreeSize, depthSelectedNode);
                   
          // Ahora copio el subarbol seleccionado a un nuevo bloque
          
          uint16_t *new_dfuds = (uint16_t *)calloc((sizeArray[subTreeSize]+4-1)/4, sizeof(uint16_t));
          
          treeNode destNode(0,0);
          
          uint16_t copiedNodes=0, copiedFlags = 0;
                    
          bool insertionInNewBlock = false;
          
          treeNode insertionNode = node;
          
          uint16_t flag, auxFlag=0, flagSelectedNode;
          
          uint16_t preorderSelectedNode = absolutePosition(selectedNode);    
          
          for (flag = 0; flag < nPtrs; ++flag)
             if (((blockPtr *)ptr)[flag].flag > preorderSelectedNode) break;
          
          flagSelectedNode = flag; // almacena el primer flag que es > al selected node
                                   // esto es para saber despues donde poner el flag del selected
                                   // node
          
          blockPtr *new_ptr;
          
          if (nPtrs > 0) new_ptr = (blockPtr *)malloc(sizeof(blockPtr)*nPtrs);
          else new_ptr = NULL;          
          
          uint16_t curFlagNewBlock; // flag en el nuevo bloque, por si la insercion continua en ese bloque          
             
          bool isInRoot = false;          
          
          uint16_t preorderDestNode = absolutePosition(destNode);          
          
          while (copiedNodes < subTreeSize) {
          
             if (selectedNode == node) {
                // the original node where insertion must be carried out
                // is stored in the child (new) block
                insertionInNewBlock = true;
                
                if (destNode != treeNode(0,0))                
                   insertionNode = destNode; // this will be the node where insertion must be
                                             // carried out in the new block
                else { insertionNode = node; isInRoot = true;}              
                
                curFlagNewBlock = copiedFlags;
             
             }
             
             if (ptr!=NULL && flag < nPtrs && preorderSelectedNode == ((blockPtr *)ptr)[flag].flag) {
               //Copiar puntero para el nuevo bloque
                new_ptr[auxFlag].flag = preorderDestNode;
                new_ptr[auxFlag].P = ((blockPtr *)ptr)[flag].P;
                ++flag;
                ++auxFlag;
                ++copiedFlags;
             }
             
             register uint64_t aux = 4*(3-selectedNode.second);             
             
             new_dfuds[destNode.first] = new_dfuds[destNode.first]
                                       | (((dfuds[selectedNode.first] >> aux/*4*(3-selectedNode.second)*/)
                                       & 0x000F) << 4*(3-destNode.second));

             if (selectedNode != originalSelectedNode)                 
                dfuds[selectedNode.first] =  dfuds[selectedNode.first]
                                            & ~(0xF << aux/*4*(3-selectedNode.second)*/);             
                    
             nextNode(destNode);
             ++preorderDestNode;
             nextNode(selectedNode);
             ++preorderSelectedNode;
             ++copiedNodes;
          }
          
          bool insertionBeforeSelectedTree = true;
          
          if (!insertionInNewBlock && flag <= curFlag)
          	 // el punto de insercion esta despues del subarbol seleccionado
             insertionBeforeSelectedTree = false;   
                    
          treeBlock *new_block = (treeBlock *)malloc(sizeof(treeBlock));
          
          new_block->nNodes = subTreeSize;
          new_block->maxNodes = sizeArray[subTreeSize]; // OJO con este valor, definir bien
          new_block->dfuds = new_dfuds;
          new_block->rootDepth = depthSelectedNode;
          
          if (auxFlag == 0) {
             if (new_ptr != NULL) free((void *)new_ptr);
             new_block->ptr = NULL;
             new_block->nPtrs = 0;
             
             ptr = realloc(ptr, sizeof(blockPtr)*(nPtrs+1)); // there is a new pointer 
                                                             // in the current block
             
             for (uint16_t i = nPtrs; i > flagSelectedNode; --i) {
                ((blockPtr *)ptr)[i].P = ((blockPtr *)ptr)[i-1].P;
                ((blockPtr *)ptr)[i].flag = ((blockPtr *)ptr)[i-1].flag - subTreeSize + 1;
             }
             
             ((blockPtr *)ptr)[flagSelectedNode].flag = absolutePosition(originalSelectedNode);
             
             ((blockPtr *)ptr)[flagSelectedNode].P = new_block;  // pointer to the new child block
             
             nPtrs++;
          }
          else {
             new_ptr = (blockPtr *)realloc(new_ptr, sizeof(blockPtr)*auxFlag);
          
             new_block->ptr = new_ptr; 
    
             new_block->nPtrs = auxFlag;
             
             ((blockPtr *)ptr)[flagSelectedNode].flag = absolutePosition(originalSelectedNode);
             
             ((blockPtr *)ptr)[flagSelectedNode].P = new_block;
            
             for (uint16_t i = flagSelectedNode+1; flag < nPtrs; ++i, ++flag) {
                ((blockPtr *)ptr)[i].P = ((blockPtr *)ptr)[flag].P;
                ((blockPtr *)ptr)[i].flag = ((blockPtr *)ptr)[flag].flag - subTreeSize + 1;
             }
             
             nPtrs = nPtrs - copiedFlags + 1;
             ptr = realloc(ptr, sizeof(blockPtr)*nPtrs); // reajusta tamaño de arreglo de punteros 
          }   
       
          // Ahora hay que borrar el subarbol copiado al hijo
          flag = flagSelectedNode+1;
          
          nextNode(originalSelectedNode);
          
          preorderSelectedNode = absolutePosition(selectedNode);
                   
          
          while (preorderSelectedNode/*absolutePosition(selectedNode)*/ < nNodes) {
             register uint64_t auxOriginalS = 4*(3-originalSelectedNode.second);
             register uint64_t auxS = 4*(3-selectedNode.second);             
             
             dfuds[originalSelectedNode.first] =  dfuds[originalSelectedNode.first]
                                    & ~(0xF << auxOriginalS/*4*(3-originalSelectedNode.second)*/); 
                                    
             dfuds[originalSelectedNode.first] = dfuds[originalSelectedNode.first] 
                                       | (((dfuds[selectedNode.first] >> auxS/*4*(3-selectedNode.second)*/)
                                       & 0x000F) << auxOriginalS /*4*(3-originalSelectedNode.second)*/);  

             dfuds[selectedNode.first] =  dfuds[selectedNode.first]
                                    & ~(0xF << auxS/*4*(3-selectedNode.second)*/);             
            
            if (selectedNode == node) insertionNode = originalSelectedNode; 
            
            nextNode(selectedNode);
            nextNode(originalSelectedNode);
            ++preorderSelectedNode;
          }
           
          if (subTreeSize > length)         
             shrink(subTreeSize-1-length+1);
          else           
             shrink(subTreeSize-1);
          nNodes -= (subTreeSize - 1); 
          
          if (!insertionBeforeSelectedTree)
             curFlag -= copiedFlags;          
          
          if (insertionInNewBlock) { 
             // insertion continues in the new block              
            if (isInRoot)
               insert(insertionNode, str, length, level, maxDepth, curFlag);           
            else              
               new_block->insert(insertionNode, str, length, level, maxDepth, curFlagNewBlock);
          }          
          else
             // insertion continues in the original block
             insert(insertionNode, str, length, level, maxDepth, curFlag);
       }         
    }
 }




























//return the pointer to a treeBlock pointer, in function of the current flag (fronteir node)
treeBlock *treeBlock::getPointer(uint16_t curFlag){
    return ((blockPtr *)ptr)[curFlag].P;
}



//takes me to the position in dfuds, where is the child of the node with symbol
treeNode treeBlock::skipChildrenSubtree(treeNode &node, uint8_t symbol, uint16_t &curLevel,uint16_t maxLevel, uint16_t &curFlag){

    //cant skip childs if you are at the max level
    if (curLevel == maxLevel){
        return node;
    }

    //this give us the codification of the current node
    uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;
    //a table that computes the number of childs to skip in function of the codification and the symbol (0,1,2,3), see testChildSkipT in tests.c
    uint8_t skipChild = (uint8_t) childSkipT[cNodeCod][symbol];
    //number of childrens of the current node in function of the node codification
    uint8_t nChildren = nChildrenT[cNodeCod];

    //initialize the current node, and go to the next node
    treeNode currNode = node;
    nextNode(currNode);
    uint16_t curPreorder = absolutePosition(currNode);

    //if there exist another frointeir node after me
    if (ptr != NULL && curFlag < nPtrs && curPreorder > ((blockPtr *)ptr)[curFlag].flag){
       ++curFlag;
    }


    //we want to instantiate the next fronteir node
    uint16_t nextFlag;
    //if there isnt a next flag, we mark it with a -1
    if (nPtrs == 0 || curFlag >= nPtrs){
        nextFlag = -1;
    }else{
        //else, the next flag is the at the curFlag position (remember that before we did ++curFlag
        nextFlag = ((blockPtr *)ptr)[curFlag].flag;
    }
    //and increase a level, because we are going down in the tree
    ++curLevel;


    //this two lines are like stack[0]=nChildrens
    int16_t sTop = -1;
    stack[++sTop] = nChildren;
    //diference between the number of childrens and the skiped childrens
    uint8_t diff = nChildren - skipChild;

    //we traverse the tree in preorder
    while(curPreorder < nNodes && sTop >= 0 && diff < stack[0])  {

        //we are at a fronteir node
        if (curPreorder == nextFlag) {
            //go to next flag
            ++curFlag;
            if (nPtrs == 0 || curFlag >= nPtrs){
                nextFlag = -1;
            }else{
                nextFlag = ((blockPtr *)ptr)[curFlag].flag;
            }
            //we substrac 1 from the current top, because this node is checked and its childrens are in another block
            --stack[sTop];
        }else if (curLevel < maxLevel) {
            //we are not in a fronteir node
            //calculate the code of the next node, using its preorder number on dfuds
            cNodeCod = (dfuds[curPreorder >> 2]>>shiftT[curPreorder & 0x3]) & 0x000f;
            //at the number of childrens of the current node, to the stack
            stack[++sTop] = nChildrenT[cNodeCod];
            //go down in the tree
            ++curLevel;
        }else {
            //todo: esto ocurre realmente?
            --stack[sTop];
        }

        //go to next node
        ++curPreorder;

        //this will set stop to thee previus node in preorder (is like going back)
        while (sTop >= 0 && stack[sTop] == 0) {
            --sTop;
            --curLevel;
            if (sTop >= 0){
                --stack[sTop];
            }
        }

    }

    currNode.first = curPreorder >> 2;
    currNode.second = curPreorder & 0x3;
    return currNode;
}



//null node
treeNode NULL_NODE = treeNode((NODE_TYPE)-1, 0);
//return the next child in function of the symbol
treeNode treeBlock::child(treeBlock *&p, treeNode & node, uint8_t symbol, uint16_t &curLevel, uint16_t maxLevel,uint16_t &curFlag){

    //get codification of current node
    uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;
    //the rank of the node
    uint8_t soughtChild = (uint8_t) childT[cNodeCod][symbol];
    //if the rank is -1, it has now childrens in that position so we return a null node
    if (soughtChild == (uint8_t)-1){
        return NULL_NODE;
    }
    //if we are in a max level, we return the same node
    //todo: pq lo anterior? esto pasa?
    if (curLevel == maxLevel && soughtChild != (uint8_t)-1) {
        return node;
    }


    treeNode currNode;
    //if we are a fronteir node
    if (ptr != NULL && curFlag < nPtrs && absolutePosition(node) == ((blockPtr *)ptr)[curFlag].flag) {
        //get the fronteir pointer
        p = ((blockPtr *)ptr)[curFlag].P;

        //set a dummy node to start searching in the next block
        curFlag = 0;
        treeNode auxNode;
        auxNode.first = auxNode.second = 0;

        //we search the child in the block of the fronteir node
        currNode = p->skipChildrenSubtree(auxNode, symbol, curLevel, maxLevel, curFlag);
    }    
    else{
        //if we are not a fronteir node, we search the child in this block
        currNode = skipChildrenSubtree(node, symbol, curLevel, maxLevel, curFlag);
    }
    return currNode;
}



/*this function consume the string that represent the morton code, until the path it represent finished
finally call a function that insert the new path in a block*/
//todo: consideraria cambiarle el nombre a esta funcion, y a las demas inserts
void insertar(treeBlock *root, uint8_t *str, uint64_t length, uint16_t level, uint16_t maxDepth){

    //curBlock is pointing to the root because we will start in that point. curBlockAux is a pointer we will use to decend the tree
    treeBlock *curBlock = root, *curBlockAux;
    //set a dummy treeNode, and an aux pointer to descend the tree
    treeNode curNode(0,0), curNodeAux;
    //dummy flag
    uint16_t curFlag = 0;

    //for every char of the string (the morton code) until we find the part were the path does not exist
    uint64_t i;
    for (i = 0; i < length; ++i) {

        //we get the child using the morton code char (str[i])
        curBlockAux = curBlock;
        curNodeAux = curBlock->child(curBlock, curNode, str[i], level, maxDepth, curFlag);

        //if the child function returned a treeNode with a -1, that means that the path does not exist. so we break here.
        if (curNodeAux.first == (NODE_TYPE)-1) {
            break;
        }
        else {
            //else, we update the curNode
            curNode = curNodeAux;
        }

        //if we are in a fronteir node
        if (curBlock->nPtrs > 0 && absolutePosition(curNode) == curFlag) {
            // we go to the block where the flag is pointing
            curBlock = curBlock->getPointer(curFlag);
            //and reset the treeNode (because we will start in a new block)
            curNode.first = 0;
            curNode.second = 0;
        }
    }
    
    /*
    the for cycle will stop at some i where the path does not exist
    so we have to inserts str[i..length-1] starting from the current node
    The new nodes inserted will descend from curNode*/
    curBlock->insert(curNode, &str[i], length-i, level, maxDepth, curFlag);
}



//this will create and insert the respective nodes in the trie and in the treeBlocks
void insertTrie(trieNode *t, uint8_t *str, uint64_t length, uint16_t maxDepth){

    //this will consume the string until a children does not exist.
    //this will leave i as the position in str from where the path does not exist or if the path continue in a treeBlock
    uint64_t i = 0;
    while (t->children[str[i]]){
        t = t->children[str[i++]];
    }


    //if i<L1 we insert it uncompressed
    while (i < L1) {
        //create a new trieNode
        t->children[str[i]] = (trieNode *)malloc(sizeof(trieNode));
        t = t->children[str[i]];
        //go to next i
        i++;
        t->children[0] = t->children[1] = t->children[2] = t->children[3] = NULL;
        t->block = NULL;
    }


    //border case: we have that t (with i>L) is null (because that block was create recently)
    // this always pass when the previous while stop when i=L1
    treeBlock *p;
    if (t->block == NULL) {
        //we create the treeBlock
        t->block = malloc(sizeof(treeBlock));
        p = (treeBlock*)t->block;
        p->dfuds = (uint16_t *)calloc(2, sizeof(uint16_t));
        p->rootDepth = L1;
        p->nNodes = 1;
        p->ptr = NULL;
        p->nPtrs = 0;
        p->maxNodes = 4;
    }else{
        //if the block exist, we assign it to p
        p = (treeBlock *) t->block;
    }

    //we call insertar, that will insert the remaining string str[i...length(str)}
    //in treeBlocks
    insertar(p, &str[i], length-i, i, maxDepth); 
}





//return true if the string str is a path in a block
bool isEdge(treeBlock *root, uint8_t *str, uint64_t length, uint16_t level, uint16_t maxDepth){

    //curBlock is pointing to the root because we will start in that point. curBlockAux is a pointer we will use to decend the tree
    treeBlock *curBlock = root, *curBlockAux;
    //set a dummy treeNode, and an aux pointer to descend the tree
    treeNode curNode(0,0), curNodeAux;
    //dummy flag
    uint16_t curFlag = 0;

    //for each char in the string
    uint64_t i;
    for (i = 0; i < length; ++i) {
        //we will get the child in function of the simbol str[i}
        curBlockAux = curBlock;
        curNodeAux = curBlock->child(curBlock, curNode, str[i], level, maxDepth, curFlag);

        //if the child is a -1, that means that the path does not exist, so we break
        if (curNodeAux.first == (NODE_TYPE)-1){
            break;
        }
        else {
          //if not, we continue
          curNode = curNodeAux;
        }

        //if we are in a frontier node, we need to go down to the corresponding block
        if (curBlock->nPtrs > 0 && absolutePosition(curNode) == curFlag) {
            // Goes down to a child block
            curBlock = curBlock->getPointer(curFlag);
            curNode.first = 0;
            curNode.second = 0;
        }
    }

    /*finally we return i==length that means: if we broke the previous cycle, the path does not exist*/
    return length == i;
}



//todo: consideraria cambiarle el nombre
//return true if the path represented with the str, is in the trie (and in the tree)
bool isEdgeTrie(trieNode *t, uint8_t *str, uint64_t length, uint16_t maxDepth) {

    //this will consume the string until a children does not exist.
    //this will leave i as the position in str from where the path does not exist or if the path continue in a treeBlock
    uint64_t i = 0;
    while (t->children[str[i]] && !t->block) {
        t = t->children[str[i++]];
    }

    /*instantiate p as the block of t (if it does not exist, then return false, but if exist, that means that exist in a treeBlock so we call
    isEdge to continue searching in the blocks)*/
    treeBlock *p= (treeBlock *) t->block;
    if (p) {
        return isEdge(p, &str[i], length - i, i, maxDepth);
    } else {
        return false;
    }
}





//todo: borre uint64_t totalBlocks = 0, totalNodes = 0;

//this function calculate the size of the whole tree (but only considering the treeBlocks)
uint64_t treeBlock::size(){

    //calculate the size of the block
    uint64_t totalSize = sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t *) + sizeof(blockPtr *) + sizeof(uint16_t) + nPtrs*(sizeof(treeBlock *) + sizeof(uint16_t));
    totalSize += sizeof(uint16_t)*((maxNodes + 3) / 4); // dfuds array

    //for each fronteir node, calculate each size
    for(uint16_t i = 0; i < nPtrs; ++i) {
        //todo: cambiar el nombre de ptr a algo mas relacionado con la frontera
        totalSize += ((blockPtr *) ptr)[i].P->size();
    }
    //return the total size
    return totalSize;
}


//return the size of the whole trie
uint64_t sizeTrie(trieNode *t){

    //base case: if the pointer is null return 0
    if (!t) {
 	    return 0;
 	}

    //if we use up to 8 levels of pointers. the pointers can implemented with 16 bits
    //todo: me tinca que podemos cambiar esta parte para que la funcion size venga de la estructura, y que no este harcodeada
    //this is the size of the actual trie
    uint64_t totalSize = 4*sizeof(uint16_t);

    //if we are not a treeBlock
    if (!t->block) {
        //we sum the the size of the children tries
        totalSize += sizeTrie(t->children[0]);
        totalSize += sizeTrie(t->children[1]);
        totalSize += sizeTrie(t->children[2]);
        totalSize += sizeTrie(t->children[3]);
    }else{
        //if we are a treeBlock, we sum the size of the treeBlock
  	    totalSize += ((treeBlock *)t->block)->size();
  	}
    //return the total sum
  	return totalSize;
}