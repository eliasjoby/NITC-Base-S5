#include "BlockBuffer.h"

#include <cstdlib>
#include <cstring>

BlockBuffer::BlockBuffer(int blockNum){
    this->blockNum=blockNum;
}

//call parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum){}

int BlockBuffer::getHeader(struct HeadInfo *head){
    unsigned char buffer[BLOCK_SIZE];

    //read block at this.blockNum into the buffer
    Disk::readBlock(buffer,this->blockNum);

    //fill the field of the header
    memcpy(&(head->lblock),buffer+8,4);
    memcpy(&head->rblock,buffer+12,4);
    memcpy(&head->numEntries,buffer+16,4);
    memcpy(&head->numAttrs, buffer + 20, 4);
    memcpy(&head->numSlots, buffer + 24, 4);

    return SUCCESS;
}

// load the record at slotNum into the argument pointer
int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
  struct HeadInfo head;

  // get the header of the block Number associated with this RecBuffer object

  this->getHeader(&head);

  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;

  // read the block at this.blockNum into a buffer - Done
  unsigned char buffer[BLOCK_SIZE];
  Disk::readBlock(buffer, this->blockNum );

  
  int recordSize = attrCount * 16;
  unsigned char *slotPointer = buffer + HEADER_SIZE + slotCount + (recordSize * slotNum);

  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}