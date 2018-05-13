#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

// initialize the cache by allocating space for all of the cache
// blocks and initializing them to be invalid and with 0 last access
// times.

void
init_cache(cache_t *cache) {
  // initialize the cache blocks to invalid
  for (int i = 0 ; i < NUMBER_SETS ; i ++) {
	 for (int j = 0 ; j < 2 ; j ++) {
		cache->sets[i].blocks[j].valid = false;
		cache->sets[i].blocks[j].dirty = false;
	 }
	 cache->sets[i].lru = 0;
  }

  cache->accesses = 0;
  cache->hits = 0;
  cache->writebacks = 0;
}



// given an address, extract the tag field 
unsigned 
address_to_tag(unsigned address) {
    unsigned tag = address >> (OFFSET + INDEX); //tag from address
  return tag;
}



// given an address, extract the index field 
unsigned 
address_to_index(unsigned address) {
    unsigned x = (1 << INDEX) -1;
    unsigned y = address >> OFFSET; 
    return (x & y);
}

// Given an address, look up in cache "cache" to see if that
// address hits.  If it does update the LRU.
// Include necessary updates to the access, hit, writeback counters
bool
find_block_and_update_lru(cache_t *cache, unsigned address, bool write) {
  unsigned tag = address_to_tag(address);
  unsigned index = address_to_index(address);
    
    cache -> accesses++; //update accesses
    
    for (unsigned i = 0 ; i < ASSOCIATIVE; i++) { //loop through
        cache_block_t* block = &cache->sets[index].blocks[i];
        cache->hits++; //update hits
        cache->sets[index].lru = 1 - i;
        if(write) {
        block->dirty = true; //set true
        return true;
        }
    }

  return false;
}

// This function should find the LRU block of the correct set and replace it 
// with one that contains "address," updating the LRU appropriately.
// Include necessary updates to the access, hit, writeback counters
void
fill_cache_with_block(cache_t *cache, unsigned address, bool write) {
  unsigned tag = address_to_tag(address);
  unsigned index = address_to_index(address);
    
  cache_block_t* lru_block = &cache->sets[index].blocks[cache->sets[index].lru];
  cache->writebacks++; //writebacks from cache
  lru_block->tag = tag; //tag from lru block
  lru_block->valid = true; //set true
  lru_block->dirty = write; //then write
  cache->sets[index].lru = 1 - cache->sets[index].lru;

}





