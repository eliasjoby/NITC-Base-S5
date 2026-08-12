#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;


  for (int i = 0; i < 2 ; i ++ ){
        RelCatEntry relCatBuf;
        int response = RelCacheTable::getRelCatEntry(i, &relCatBuf);
        if (response != SUCCESS){
            printf("Relation Catalogue Entry Not found.");
            exit(1);
        }
        printf("Relation: %s\n", relCatBuf.relName);
        for (int j=0 ; j < relCatBuf.numAttrs; j ++ ){
            AttrCatEntry attrCatBuf;
            response = AttrCacheTable::getAttrCatEntry(i, j, &attrCatBuf);
            if (response != SUCCESS)
            {
                printf("Relation Catalogue Entry Not found.");
                exit(1);
            }
            printf("  %s: %s\n", attrCatBuf.attrName, attrCatBuf.attrType==NUMBER?"NUM":"STR");
        }

  }
  /*
  for i = 0 and i = 1 (i.e RELCAT_RELID and ATTRCAT_RELID)

      get the relation catalog entry using RelCacheTable::getRelCatEntry()
      printf("Relation: %s\n", relname);

      for j = 0 to numAttrs of the relation - 1
          get the attribute catalog entry for (rel-id i, attribute offset j)
           in attrCatEntry using AttrCacheTable::getAttrCatEntry()

          printf("  %s: %s\n", attrName, attrType);
  */

  return 0;





















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
            printf(" %s: %s\n",attrCatRecord[1].sVal,attrType);
            }
        }

        if(attrCatHeader.rblock==-1)break;
        else blockNum=attrCatHeader.rblock;
        }
        printf("\n");
    }

    return 0;
}