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





/*Is important to free the memory.
This is a recursive function. first we free the dfuds.
and then recursively we free the children blocks, finally
we free the array with the children pointers and this*/
//todo: cuando se usa, me refiero a que la primera capa trieNode tambien deberia tener una funcion que borre para llamar a es??? como testear??
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
//todo: pq ese + 3 / 4?
void treeBlock::grow(uint16_t extraNodes){
     dfuds = (uint16_t *) realloc(dfuds, sizeof(uint16_t)*((sizeArray[nNodes+extraNodes] + 3)/4));
     //the new max is sizeArray[nNodes+extraNodes]
     maxNodes = 4*((sizeArray[nNodes+extraNodes]+3)/4);
}

/*this method, realloc dfuds in a smaller array
the idea is that the new size of the block should be sizeArray[nNodes-extraNodes]
remember that sizeArray is an array of max sizes per blocks.*/
//todo: pq ese + 3/4?
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

//return a treeNode where the subtree begin (the end is in subTreeSize)
treeNode treeBlock::selectSubtree2(uint16_t maxDepth, uint16_t & subTreeSize, uint16_t & depthSelectN){

    // depth is the depth of the root of the block
    uint16_t depth= rootDepth + 1;

    //curFlag=0 means that we are in the first fronteir node
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
            //if we run out of fronteir nodes, we set nextFlag to -1 to distinguish it
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





//dumyroot=tuple 0,0
treeNode dummyRootBlockNode(0,0);

//todo: que hace?
void treeBlock::insert(treeNode node, uint8_t str[], uint64_t length, uint16_t level,uint64_t maxDepth, uint16_t curFlag){

    //todo: talvez podemos sacarlo de aqui y ponerlo en los ifs que si aparece?
    treeNode nodeAux = node;

    //first we determine the max size of the blocks depending on the deepth
    if (rootDepth < L1) {
        //todo: esto se puede eliminar? pq los nodos bajo L1 no son blockes
        //shorters nodes are at the begining
        Nt = S1;
    }else if (rootDepth <= L2) {
        //medium size blocks are at the medium
        Nt = S2;
    }
    else {
        //biggers nodes are in the deeper levels
        Nt = S3;
    }


    //the insertion occurs in a frontier node, so we insert in a child block
    if (ptr!=NULL && curFlag < nPtrs && absolutePosition(node) == ((blockPtr *)ptr)[curFlag].flag) {
        // insertion must be carried out in the root of a child block

        //get the codification of the node we want to insert
        uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;

        //todo:porque un register?
        /*the idea of aux is to shiftleft a 16bit to mask our node.
        for example if we have xxxx xxxx 1101 xxxx, node.second is = 2 (the x means that value is a 0 or 1, we only mind about node.second)
        so if we have the 16bit mask = 0xF = 0000 0000 0000 1111, we will want to shift it 4 times to left
        that is 4*(3-node.second) so the mask will be mask<<aux = 0000 0000 1111 0000
        and if we negate it it will be 1111 1111 0000 1111, so our new codification will be xxxx xxxx 0000 xxxx*/
        register uint64_t aux = 4*(3-node.second);
        dfuds[node.first] = dfuds[node.first] & ~(0xF << aux);

        /*so we have the node 1101 and we insert in the morton code 2 (str[0]=2)
        that will leave the node as 1111 we use the inserT table to compute thar (see test.c)
        then we shift right aux times to set it at the same position of the previous mask
        and then we or them xxxx xxxx 0000 xxxx or 0000 0000 1111 0000*/
        dfuds[node.first] = dfuds[node.first] | (insertT[cNodeCod][str[0]] << aux);

        //we insert the str in the corresponding child block, using dummyRootBlockNode <0,0> for codification
        ((blockPtr *)ptr)[curFlag].P->insert(dummyRootBlockNode, str, length, level, maxDepth, 0);
        return;


    /*if the length of str is 1 (this means that we only need to insert one node
    we dont need to filter if the block has reached the max size, because int the next else if, we
    ensure that, when inserting in a block, we dont reach maxSize-1 (to reach this else if)*/
    }else if (length == 1) {

        //we get the node codification
        uint8_t cNodeCod = (dfuds[node.first]>>shiftT[node.second]) & 0x000f;
        //get the offset for the mask (exactly as the previus if statment)
        register uint64_t aux = 4*(3-node.second);
        /*then update the node codification
        notice that because we are in the last level, we dont need to actualize the number of nodes. becaese the node is
        represented with a bit*/
        dfuds[node.first] = dfuds[node.first] & ~(0xF << aux);
        dfuds[node.first] = dfuds[node.first] | (insertT[cNodeCod][str[0]] << aux);
        return;

    //there is room in current block for new nodes
    }else if (nNodes + length - 1 <= maxNodes) {

        /*in this part we will modify de dfus array. inserting all tho new nodes in the middle
        so we move all the nodes in the right half
        for example if we have [a,b,c,d,e,-,-,-,-,-,-] (where - are empty spaces)
        and wi want to insert three nodes: 1, 2 and 3 between c and d
        first we move d and e 3 spaces -> [a,b,c,-,-,-d,e,-,-,-]
        and then we insert the nodes -> [a,b,c,1,2,3,d,e,-,-,-]*/

        //first we substract one from length because this node is already inserted (but maybe we need to insert some childs)
        --length;
        /*then we move the pointer node to the its child position with str[0] (this is where the new descendants will be inserted)
        this node will represent the first node we will move (the first node of the right half, or in our example this node is d)*/
        node = skipChildrenSubtree(node, str[0], level, maxDepth, curFlag);


        //we create some auxiliar nodes that will help with the insertion, this node will be used to move the nodes in the right half
        treeNode origNode, destNode;
        //origNode will represent the last node in the right half that is not empty (in out example this node is e)
        origNode.first = (nNodes - 1)/4;
        origNode.second = (nNodes - 1)%4;
        //destNode will represent the last position of the new right half (in our example, the position will be where is e after moving the array [a,b,c,1,2,3,d,e,-,-,-])
        destNode.first =  (nNodes + length - 1)/4;
        destNode.second = (nNodes + length - 1)%4;


        //this are the positions of the previous nodes in the dfuds
        uint16_t preorderNode = absolutePosition(node);
        uint16_t preorderOrigNode = absolutePosition(origNode);
        uint16_t preorderDestNode =  absolutePosition(destNode);


        //registers to mask the updates of the nodes. (see the first if statement of this if-else)
        register uint64_t aux, aux2;

        /*what this does is to copy all from [preorderNode,preorderOrigNode] to [preorderOriginNode,preorderDestNode]
        in our example is when we do [a,b,c,d,e,-,-,-,-,-,-] -> [a,b,c,-,-,-d,e,-,-,-]*/
        while (preorderOrigNode >= preorderNode) {
            aux = 4*(3-(preorderDestNode & 0x3) );
            aux2 = preorderDestNode >> 2;
            //prerare the node in the new right half to be updated
            dfuds[aux2] = dfuds[aux2] & ~(0xF << aux);
            //update the node with the node where origNode is pointing
            dfuds[aux2] = dfuds[aux2]| (((dfuds[preorderOrigNode>>2 ] >> 4*(3-(preorderOrigNode & 0x3) ))& 0x000F) << aux) ;
            //go to the next node from right to left
            --preorderDestNode;
            --preorderOrigNode;
        }


        //in this part we insert the original node (this means only editing the bits in that position)
        uint8_t cNodeCod = (dfuds[nodeAux.first]>>shiftT[nodeAux.second]) & 0x000f;
        dfuds[nodeAux.first] = dfuds[nodeAux.first] & ~(0xF << 4*(3-nodeAux.second));
        dfuds[nodeAux.first] = dfuds[nodeAux.first] | (insertT[cNodeCod][str[0]] << 4*(3-nodeAux.second));
        //we dont want to copy this node. si we go to the next node in preorder
        ++preorderOrigNode;


        /*what this does is to insert the new nodes
        in our example is when we do [a,b,c,-,-,-d,e,-,-,-]->[a,b,c,1,2,3,d,e,-,-,-]*/
        for (uint16_t i = 1; i <= length; i++) {
            //prepare the mask to insert the node
            aux = 4*(3-(preorderOrigNode & 0x3));
            aux2 = preorderOrigNode >> 2;
            dfuds[aux2] = dfuds[aux2] & ~(0xF << aux);
            /*actualize what dfuds has in that position. the new node will by a secuence of 4 bits with only one (because the node is new)
            for example if we are inserting a 2 in the morton code the number will be 0010*/
            dfuds[aux2] = dfuds[aux2] | (symbol2NodeT[str[i]] << aux);
            //sum 1 to number of nodes of the blocks
            ++nNodes;
            //go to next node in preorder
            ++preorderOrigNode;
        }


        // Now updates the flags (if required), as new nodes have been added
        if (ptr){
            for (uint16_t i = curFlag; i < nPtrs; ++i){
                //we only need to move the flags length spaces to the right
                ((blockPtr *)ptr)[i].flag += length;
            }
        }

        //todo: agrege un return
        return;


    }else {

        // there is no room for the new nodes

        // block can still grow
        if (nNodes + length - 1 <= Nt) {
            // we grow it
            grow(length-1);
            // After growing, recursively inserts the node
            insert(node, str, length, level, maxDepth, curFlag);


        }else {

            //this part will consist in spliting the node in a child block



            //todo:revisar si lo que dije aca es cierto
            //calculate the subtree (the node were beging the subtree is stored in originalSelectedNode and selectedNode. And the end of the subtree is stored in subTreeSize)
            treeNode selectedNode, originalSelectedNode;
            uint16_t subTreeSize, depthSelectedNode;
            originalSelectedNode = selectedNode = selectSubtree2(maxDepth, subTreeSize, depthSelectedNode);

            //now we will copy the subtree in a new block

            //first we ask for memory for dfuds
            uint16_t *new_dfuds = (uint16_t *)calloc((sizeArray[subTreeSize]+4-1)/4, sizeof(uint16_t));

            //then we search the first flag (fronteirnode) with a preorder grater than our selected node preorder
            uint16_t preorderSelectedNode = absolutePosition(selectedNode);
            uint16_t flag;
            for (flag = 0; flag < nPtrs; ++flag){
                if (((blockPtr *)ptr)[flag].flag > preorderSelectedNode) {
                    break;
                }
            }

            //keep the first flag that is > than selected node. this is for later. to know where to put the flag in the selected node
            uint16_t flagSelectedNode = flag;

            //we create a new ptr of blocks for the new block (here we will store the frontier nodes that goes into the new block)
            blockPtr *new_ptr;
            if (nPtrs > 0) {
                //first we make with equal size than blockPtr (then we will adjust this)
                //todo: ver si lo que dije aqui arriba es cieto
                new_ptr = (blockPtr *)malloc(sizeof(blockPtr)*nPtrs);
            }else {
                new_ptr = NULL;
            }



            //keep count of copiedNodes and copiedFlags in the new block
            uint16_t copiedNodes=0, copiedFlags = 0;
            //bool var to say if the insertion will be in the new block we are creating (true) or in the original block (false)
            bool insertionInNewBlock = false;
            //a pointer to the node were the insertion will ocurr
            treeNode insertionNode = node;
            //this will be the first flag in the new node
            uint16_t auxFlag=0;
            //we will use curFlagNewBlock to save the flag we will insert in the new block (if we insert in the new block)
            uint16_t curFlagNewBlock;
            //bool var that is true when the insertion ocurrs in the root of the new block
            bool isInRoot = false;
            //node that will point to the new dfuds (start in the root)
            treeNode destNode(0,0);
            //this will be the preorder in new_defuds of the destNode (will init in 0)
            uint16_t preorderDestNode = absolutePosition(destNode);

            //copy the subtree in the new dfuds
            while (copiedNodes < subTreeSize) {

                //if selectedNode=node, this means that the insertion will ocurr in the new block
                if (selectedNode == node) {
                    /*the original node where insertion must be carried out
                    is stored in the child (new) block*/
                    insertionInNewBlock = true;

                    //we want to keep a treeNode tuple to point to the node where the insertion will be
                    if (destNode != treeNode(0,0)) {
                        // if the destNode is != of (0,0) that means that the insertion isnt in the root and the insertion node is in the actual destNode
                        insertionNode = destNode;
                    }else {
                        //but if the destNode is (0,0) that means that the insertion will ocurr in the root of the new block
                        insertionNode = node;
                        isInRoot = true;
                    }
                    //the flag wich we will use to insert in the new block is the one saved in the newptr[copiedFlags].flag=newptr[curFlagNewBlock].flag
                    curFlagNewBlock = copiedFlags;
                }

                //we are copying a frontier node
                //todo: que hay en ptr[flag].flag?
                if (ptr!=NULL && flag < nPtrs && preorderSelectedNode == ((blockPtr *)ptr)[flag].flag) {
                    //copy the pointer for the new block
                    new_ptr[auxFlag].P = ((blockPtr *)ptr)[flag].P;
                    //the flag is the preorder of the actual node
                    new_ptr[auxFlag].flag = preorderDestNode;

                    //go to the next flag
                    ++flag;
                    //increments the flags in the new block
                    ++auxFlag;
                    //increments the copiedFlags
                    ++copiedFlags;
                }


                //actualize the bits in the new dfuds
                register uint64_t aux = 4*(3-selectedNode.second);
                //use the destNode to index the new_dfuds and copy the node that is indexed by selectedNode in dfuds
                new_dfuds[destNode.first] = new_dfuds[destNode.first] | (((dfuds[selectedNode.first] >> aux) & 0x000F) << 4*(3-destNode.second));

                //todo: me tinca que esto borra los nodos qe estan en dfuds, que estan en el subtree. pero hay que verlo con calma
                if (selectedNode != originalSelectedNode){
                    dfuds[selectedNode.first] =  dfuds[selectedNode.first] & ~(0xF << aux);
                }

                //go to next node in new_defuds
                nextNode(destNode);
                ++preorderDestNode;
                //go to next node in the subtree
                nextNode(selectedNode);
                ++preorderSelectedNode;
                //add 1 to copied nodes
                ++copiedNodes;
            }



            /* we want to know if the insertion will be before the selected subtree. [before,subtree,after]
             at first we will asume that the insertion will be before*/
            //todo: me imagino qe es before U subtree
            bool insertionBeforeSelectedTree = true;


            /*if insertionInNewBlock is false that means that the insertion is in before or in after [before,       ,after]
            in the other hand. we know that flag lives in subtree [before, flag  ,after], if flag <=curFlag, but insertion isnt in new block
            that means that curFlag must be in after*/
            //todo:que es curFlag? me imagino que es como un indice qe lleva la cuenta de en qe frontera estamos
            if (!insertionInNewBlock && flag <= curFlag){
                //the insertion point is after the selected subtree
                insertionBeforeSelectedTree = false;
            }

            //now we instantiate the new block
            treeBlock *new_block = (treeBlock *)malloc(sizeof(treeBlock));
            new_block->nNodes = subTreeSize;
            //todo: estaba este comentario: OJO con este valor, definir bien
            new_block->maxNodes = sizeArray[subTreeSize];
            new_block->dfuds = new_dfuds;
            new_block->rootDepth = depthSelectedNode;



            //auxFlag==0 => there arent child blocks in new block
            if (auxFlag == 0) {
                //so we free new_ptr (we wont use it)
                if (new_ptr != NULL) {
                    free((void *)new_ptr);
                }
                //and set the ptr array to null in the new block
                new_block->ptr = NULL;
                new_block->nPtrs = 0;

                /*now we need to increment the ptr block in the actual block
                there is a new pointer in the current block*/
                ptr = realloc(ptr, sizeof(blockPtr)*(nPtrs+1));

                //we correr move all the frontier nodes from flagselectednode to nptrs, one space to de right
                for (uint16_t i = nPtrs; i > flagSelectedNode; --i) {
                    ((blockPtr *)ptr)[i].P = ((blockPtr *)ptr)[i-1].P;
                    ((blockPtr *)ptr)[i].flag = ((blockPtr *)ptr)[i-1].flag - subTreeSize + 1;
                }

                //the flag of the new ptr block is the preorder of the root of the subtree
                ((blockPtr *)ptr)[flagSelectedNode].flag = absolutePosition(originalSelectedNode);
                // pointer to the new child block
                ((blockPtr *)ptr)[flagSelectedNode].P = new_block;

                //increment the number of pointers
                nPtrs++;

            }else{
                //auxFlag=number of frontier nodes in the new block, so we create the array
                new_ptr = (blockPtr *)realloc(new_ptr, sizeof(blockPtr)*auxFlag);
                new_block->ptr = new_ptr;
                new_block->nPtrs = auxFlag;

                //add the new child block to the current block ptr array
                //todo: ver si borramos los demas nodos de ptr
                ((blockPtr *)ptr)[flagSelectedNode].flag = absolutePosition(originalSelectedNode);
                ((blockPtr *)ptr)[flagSelectedNode].P = new_block;

                //we move all the frontier nodes int the right part of the ptr array, that are not in the subtree (starting in flag) to the left
                for (uint16_t i = flagSelectedNode+1; flag < nPtrs; ++i, ++flag) {
                    ((blockPtr *)ptr)[i].P = ((blockPtr *)ptr)[flag].P;
                    ((blockPtr *)ptr)[i].flag = ((blockPtr *)ptr)[flag].flag - subTreeSize + 1;
                }

                //now the number of pointers is nPtrs+1 minus the number of copiedFlags
                nPtrs = nPtrs - copiedFlags + 1;
                //realloc the new ptr
                ptr = realloc(ptr, sizeof(blockPtr)*nPtrs);
            }



            /*now we will move the nodes that are at the right of the subtree (in after) [before,subtree,after]
            so the new dfuds will be [before,after,trash] (then we will shrink)*/

            //we go to the next node, because we will keep the original selected node in the current block (and also in the new block)
            nextNode(originalSelectedNode);
            //selectedNode is pointing to the first node in after. so preorderSelectedNode is the position of the first node in after
            preorderSelectedNode = absolutePosition(selectedNode);

            //this will iter in all the nodes inf after
            while (preorderSelectedNode < nNodes) {

                //mask for the node we want to errase
                register uint64_t auxOriginalS = 4*(3-originalSelectedNode.second);
                //mask for the node we want to copy
                register uint64_t auxS = 4*(3-selectedNode.second);

                //we errase the node in dfuds with the index of originalselectednode
                dfuds[originalSelectedNode.first] =  dfuds[originalSelectedNode.first] & ~(0xF << auxOriginalS);
                //we copy in dfuds the node in selectedNode, to originalSelectedNode
                dfuds[originalSelectedNode.first] = dfuds[originalSelectedNode.first] | (((dfuds[selectedNode.first] >> auxS) & 0x000F) << auxOriginalS);
                //we errase the node in selected node
                dfuds[selectedNode.first] =  dfuds[selectedNode.first] & ~(0xF << auxS);

                //if the insertion node is in after. we update the insertionNode to the current originalSelectedNode
                if (selectedNode == node) {
                    insertionNode = originalSelectedNode;
                }

                //go to the next node in dfuds
                nextNode(originalSelectedNode);
                //go to the next node we will errase
                nextNode(selectedNode);
                ++preorderSelectedNode;
            }



            //now we shrink the actual block. considering the number of nodes we remove (subTreeSize)
            //todo: -length?
            if (subTreeSize > length) {
                shrink(subTreeSize - 1 - length + 1);
            }else {
                shrink(subTreeSize - 1);
            }

            //actualize the number of nodes
            nNodes -= (subTreeSize - 1);

            //actualize the current flag of the current block
            //this will hapend only if the insertion ocurs after the subtree (because some of the frontier nodes will go to the new block)
            //notice that if the insertion ocurs before the subtree, we dont need to actualize the cur flag (it wont be afected)
            if (!insertionBeforeSelectedTree) {
                curFlag -= copiedFlags;
            }


            //if the insertion is in the new block
            if (insertionInNewBlock) {
                //if the insertion is in the root of the new block
                if (isInRoot) {
                    //we insert in the actual block but with the promise that then the node will be inserted in a frontier node (the new block we created) check the first if statement
                    insert(insertionNode, str, length, level, maxDepth, curFlag);
                }else{
                    //if the node is not inserted in the root, the we insert in the new block
                    new_block->insert(insertionNode, str, length, level, maxDepth, curFlagNewBlock);
                }
            }else{
                // insertion continues in the original block
                insert(insertionNode, str, length, level, maxDepth, curFlag);
            }

        }
    }
}





//return the pointer to a treeBlock pointer, in function of the current flag (fronteir node)
treeBlock *treeBlock::getPointer(uint16_t curFlag){
    return ((blockPtr *)ptr)[curFlag].P;
}

//todo: qe hace ?
int8_t stack[100];

//takes me to the position in dfuds, where is the child of the node with symbol (this function is a wrapper of skipChildrenSubtree but identificate when a child is in the block or in a child block)
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





//tnumber of blocks and number of nodes
uint64_t totalBlocks = 0, totalNodes = 0;

//this function calculate the size of the whole tree
uint64_t treeBlock::size(){

    //for each block we increment the number of blocks and sum its nodes
    totalBlocks++;
    totalNodes += nNodes;

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


/*here goes the deletion part*/

//todo: this should be of size L1
//this stack will contain the first L1 nodes from the path we want to delete
trieNode delTrieNodeStack[4096];
uint8_t delPathStack[4096];
//this index will tell us in wich part of the stack we should insert.
int delTrieNodeIndex=0;

/*this will delete the path of the node
 first we insert the trie nodes on the stack. and trigger "borrar" that will delete
 the nodes in a bottom up strategy*/
void deleteTrie(trieNode *t, uint8_t *str, uint64_t length, uint16_t maxDepth){

    //insert t in the stack
    delTrieNodeStack[delTrieNodeIndex]=t;

    //this will consume the string inserting the nodes of the path in the stack
    //if a node does not exist, that means that the path does not exist so we return
    uint64_t i ;
    for(i=0;i<L1;i++){
        if (t->children[str[i]]){
            //add the trieNode to the stack
            delPathStack[i]=str[i];
            delTrieNodeIndex++;
            delTrieNodeStack[delTrieNodeIndex]=t->children[str[i]];

            t=t->children[str[i]];
        }else{
            //the path does not exist, so there is nothing to delete
            delTrieNodeIndex=0;
            return;
        }
    }


    //if t->block==NULL that means that the path does not exist
    treeBlock *p;
    if (t->block == NULL) {
        //the path does not exist, so there is nothing to delete
        delTrieNodeIndex=0;
        return;
    }else{
        //if the block exist, we assign it to p
        p = (treeBlock *) t->block;
    }

    //we call "borrar", that delete the remaining path str[i...length(str)} in treeBlocks
    //todo: crear borrar
    bool continueDelete=borrar(p, &str[i], length-i, i, maxDepth);

    if(continueDelete){
        //if continueDelete is true, that means that we should check the delTrieNodeStack to continue deleting until the path is forked
        //get the last trieNode in the stack
        trieNode *taux=delTrieNodeStack[delTrieNodeIndex];

        //the last trieNode has null childs but not null block, so if continueDelete is true, that means that the block is now null
        taux->block.freeTreeBlock();
        taux->block=NULL;

        //now go to the next trieNode and delete the last one
        delTrieNodeIndex--;
        taux=delTrieNodeStack[delTrieNodeIndex];


        while(delTrieNodeIndex>0){
            //todo:quizas hay que hacer un free para esa estructura tambien
            taux->children[delPathStack[delTrieNodeIndex]]=NULL;

            if( taux->children[0]==NULL && taux->children[1]==NULL && taux->children[2]==NULL && taux->children[3]==NULL ){
                delTrieNodeIndex--;
                taux=delTrieNodeStack[delTrieNodeIndex];
            }else{
                delTrieNodeIndex=0;
                return;
            }

        }

        //todo: si implementqamos un free para trieNode, faltaria poner un free aca para delTrieNodeStack[0]
        return;

    }else{
        //if continueDelete is false, that means that this part of the path is still in use
        delTrieNodeIndex=0;
        return;
    }
    return;

}

