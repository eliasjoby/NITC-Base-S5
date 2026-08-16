#include "OpenRelTable.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

OpenRelTable::OpenRelTable(){

    // initialize relCache and attrCache with nullptr
    for (int i = 0; i < MAX_OPEN; ++i) {
        RelCacheTable::relCache[i] = nullptr;
        AttrCacheTable::attrCache[i] = nullptr;
    }




    /************ Setting up Relation Cache Table entries ************/
    // (we need to populate relation cache with entries for the relation catalog
    //  and attribute catalog.)




    /**** setting up Relation Catalog's relation in the Relation Cache Table****/
    RecBuffer relCatBlock(RELCAT_BLOCK);

    Attribute relCatRecord[RELCAT_NO_ATTRS];
    relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

    struct RelCacheEntry relCacheEntry;
    RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
    relCacheEntry.recId.block = RELCAT_BLOCK;
    relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

    // allocate this on the heap because we want it to persist outside this function
    RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;




    /**** setting up Attribute Catalog's relation in the Relation Cache Table ****/
    relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);

    // set the value at RelCacheTable::relCache[ATTRCAT_RELID]
    RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
    relCacheEntry.recId.block = RELCAT_BLOCK;
    relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

    // allocate this on the heap because we want it to persist outside this function
    RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[ATTRCAT_RELID]) = relCacheEntry;




    // Setting up the Students Relation in the Relation Catalogue Table
    relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT + 1);

    // set the value at RelCacheTable::relCache[ATTRCAT_RELID]
    RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
    relCacheEntry.recId.block = RELCAT_BLOCK;
    relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT + 1;

    // allocate this on the heap because we want it to persist outside this function
    RelCacheTable::relCache[ATTRCAT_RELID + 1] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[ATTRCAT_RELID + 1]) = relCacheEntry;







    /************ Setting up Attribute cache table entries ************/
    // (we need to populate attribute cache with entries for the relation catalog
    //  and attribute catalog.)



    /**** setting up Relation Catalog's relation in the Attribute Cache Table ****/
    RecBuffer attrCatBlock(ATTRCAT_BLOCK);
    Attribute attrCatRecord[RELCAT_NO_ATTRS];
    
    AttrCacheEntry* listHead = nullptr;
    AttrCacheEntry* attrCacheEntry;
    AttrCacheEntry* prev = nullptr;

    
    HeadInfo attrCatHeader;
    attrCatBlock.getHeader(&attrCatHeader);

    for (int j = 0; j < RELCAT_NO_ATTRS; j++ ) {
        attrCatBlock.getRecord(attrCatRecord, j);
        attrCacheEntry = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
        if ( j == 0 ) listHead = attrCacheEntry;

        AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry );
        attrCacheEntry->recId.block = ATTRCAT_BLOCK;
        attrCacheEntry->recId.slot = j;

        if ( prev!= nullptr ) prev->next = attrCacheEntry;
        prev = attrCacheEntry;
    }
    attrCacheEntry -> next = nullptr;


    AttrCacheTable::attrCache[RELCAT_RELID] = listHead;





    /**** setting up Attribute Catalog's relation in the Attribute Cache Table ****/

    
    prev = nullptr;
    attrCatBlock.getHeader(&attrCatHeader);

    for (int j = 6; j < RELCAT_NO_ATTRS + 6; j++ ) {
        attrCatBlock.getRecord(attrCatRecord, j);
        attrCacheEntry = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
        if ( j == 6 ) listHead = attrCacheEntry;

        AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry );
        attrCacheEntry->recId.block = ATTRCAT_BLOCK;
        attrCacheEntry->recId.slot = j;
        
        if ( prev!= nullptr ) prev->next = attrCacheEntry;
        prev = attrCacheEntry;
    }
    attrCacheEntry -> next = nullptr;
    AttrCacheTable::attrCache[ATTRCAT_RELID] = listHead;





        /**** setting up Student relation in the Attribute Cache Table ****/
    prev = nullptr;
    attrCatBlock.getHeader(&attrCatHeader);

    //first 6 attributes are for relcat and next 6 attributes are for attrcat, so student relation's attributes start from 12th attribute
    for (int j = 12; j < 16 ; j++ ) {
        attrCatBlock.getRecord(attrCatRecord, j);
        attrCacheEntry = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
        if ( j == 12 ) listHead = attrCacheEntry;

        AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry );
        attrCacheEntry->recId.block = ATTRCAT_BLOCK;
        attrCacheEntry->recId.slot = j;
        
        if ( prev!= nullptr ) prev->next = attrCacheEntry;
        prev = attrCacheEntry;
    }
    attrCacheEntry -> next = nullptr;
    AttrCacheTable::attrCache[ATTRCAT_RELID + 1] = listHead;

}

int OpenRelTable::getRelId(char relName[ATTR_SIZE]) {
    if (!strcmp(relName, RELCAT_RELNAME)) return RELCAT_RELID;
    if (!strcmp(relName, ATTRCAT_RELNAME)) return ATTRCAT_RELID;
    if (!strcmp(relName, "Students")) return ATTRCAT_RELID + 1 ;
    return E_RELNOTOPEN;
}

OpenRelTable::~OpenRelTable() {
  // free all the memory that you allocated in the constructor
}