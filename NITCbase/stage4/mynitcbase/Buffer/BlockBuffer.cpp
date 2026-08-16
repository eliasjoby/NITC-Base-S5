#include "BlockBuffer.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>

BlockBuffer::BlockBuffer(int blockNum){
    this->blockNum=blockNum;
}

//call parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum){}

int BlockBuffer::getHeader(struct HeadInfo *head){
    unsigned char buffer[BLOCK_SIZE];

    //read block at this.blockNum into the buffer
    //Disk::readBlock(buffer,this->blockNum);

    //use loadBlockAndGetBufferPtr to get pointer to the buffer
    unsigned char *bufferPtr;
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);
    if (ret != SUCCESS) {
        return ret;   // return any errors that might have occured in the process
    }   

    //fill the field of the header
    // memcpy(&(head->lblock),buffer+8,4);
    // memcpy(&head->rblock,buffer+12,4);
    // memcpy(&head->numEntries,buffer+16,4);
    // memcpy(&head->numAttrs, buffer + 20, 4);
    // memcpy(&head->numSlots, buffer + 24, 4);

    // fill the entires in the *head
    memset(head, 0, sizeof(struct HeadInfo));

    memcpy(&head->blockType,  bufferPtr + 0,  4);
    memcpy(&head->pblock,     bufferPtr + 4,  4);
    memcpy(&head->lblock,     bufferPtr + 8,  4);
    memcpy(&head->rblock,     bufferPtr + 12, 4);
    memcpy(&head->numEntries, bufferPtr + 16, 4);
    memcpy(&head->numAttrs,   bufferPtr + 20, 4);
    memcpy(&head->numSlots,   bufferPtr + 24, 4);
    memcpy(&head->reserved,   bufferPtr + 28, 4);

    return SUCCESS;
}

// load the record at slotNum into the argument pointer
int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
    struct HeadInfo head;

    // get the header of the block Number associated with this RecBuffer object

    this->getHeader(&head);

    int attrCount = head.numAttrs;
    int slotCount = head.numSlots;

        // Use loadBlockAndGetBufferPtr to retrieve pointer to buffer
    unsigned char *bufferPtr;
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);
    if (ret != SUCCESS) {
        return ret;
    }

  
    int recordSize = attrCount * 16;
    unsigned char *slotPointer = bufferPtr + HEADER_SIZE + slotCount + (recordSize * slotNum);

    memcpy(rec, slotPointer, recordSize);

    return SUCCESS;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// <stage4>


/* 
  Used to get the slotmap from a record block
  NOTE: this function expects the caller to allocate memory for `*slotMap`
*/
int RecBuffer::getSlotMap(unsigned char *slotMap) {
    unsigned char *bufferPtr;

    // get the starting address of the buffer containing the block using loadBlockAndGetBufferPtr().
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);
    if (ret != SUCCESS) {
        return ret;
    }

    struct HeadInfo head;
    this->getHeader(&head);

    int slotCount = head.numSlots;

    // get a pointer to the beginning of the slotmap in memory by offsetting HEADER_SIZE
    unsigned char *slotMapInBuffer = bufferPtr + HEADER_SIZE;

    // copy the values from `slotMapInBuffer` to `slotMap` (size is `slotCount`)
    for (int i = 0; i < slotCount; i ++ ){
        slotMap[i] = slotMapInBuffer[i];
    }

    return SUCCESS;
}

/*
Load a block to the buffer and get a pointer to it.
NOTE: this function expects the caller to allocate memory for the argument
*/
int BlockBuffer::loadBlockAndGetBufferPtr(unsigned char **buffPtr) {
    // check whether the block is already present in the buffer using StaticBuffer.getBufferNum()
    int bufferNum = StaticBuffer::getBufferNum(this->blockNum);

    if (bufferNum == E_BLOCKNOTINBUFFER) {
        bufferNum = StaticBuffer::getFreeBuffer(this->blockNum);

        if (bufferNum == E_OUTOFBOUND) {
            return E_OUTOFBOUND;
        }
        // Do readblock if required block is not present in buffer
        Disk::readBlock(StaticBuffer::blocks[bufferNum], this->blockNum);
    }
    // store the pointer to this buffer (blocks[bufferNum]) in *buffPtr
    *buffPtr = StaticBuffer::blocks[bufferNum];
    // printf("debug2: %u\n",buffPtr);

    return SUCCESS;
}


// ---------------------------------------------------------------------------
// --------------------------------------------------------------------------

// Used to perform operations and comparisons in SQL queries
int compareAttrs(union Attribute attr1, union Attribute attr2, int attrType) {

    double diff;
    if (attrType == STRING)
        diff = strcmp(attr1.sVal, attr2.sVal);
    else
        diff = attr1.nVal - attr2.nVal;

    if (diff > 0) return 1;
    else if (diff < 0) return -1;
    else return 0;
}