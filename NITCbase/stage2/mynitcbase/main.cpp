#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
  Disk disk_run;

  //objects for reln and attrib catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  //load headers
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);

  for(int i=0;i<relCatHeader.numEntries;i++){
    Attribute relCatRecord[6];

    relCatBuffer.getRecord(relCatRecord,i);

    printf("Relation: %s\n",relCatRecord[0].sVal);

    //loop thru all psbl attrCat blocks
    int blockNum=ATTRCAT_BLOCK;
    while(1){
      
      RecBuffer attrCatBuffer(blockNum);
      HeadInfo attrCatHeader;
      attrCatBuffer.getHeader(&attrCatHeader);

      for(int j=0;j<attrCatHeader.numEntries;j++){
        Attribute attrCatRecord[6];
        attrCatBuffer.getRecord(attrCatRecord,j);

        if(!strcmp(attrCatRecord[0].sVal,relCatRecord[0].sVal)){
          const char *attrType= (attrCatRecord[2].nVal==NUMBER)? "NUM":"STR";
          printf(" %s: %s\n",attrCatRecord[0].sVal,attrType);
        }
      }

      if(attrCatHeader.rblock==-1)break;
      else blockNum=attrCatHeader.rblock;
    }

  }

  return 0;
}