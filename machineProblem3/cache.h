
#define BLOCK_SIZE 64
#define NUMBER_SETS 256
#define ASSOCIATIVE 2
#define OFFSET 6
#define INDEX 8
#define TAG 18

typedef struct cache_block {
  unsigned tag;
  bool valid;
  bool dirty;
} cache_block_t;

typedef struct cache_set {
  cache_block_t blocks[2];
  unsigned lru;
} cache_set_t;
  
typedef struct cache {
  cache_set_t sets[NUM_SETS];     // the sets themsleves

  // statistics
  unsigned accesses;
  unsigned hits;
  unsigned writebacks;
} cache_t;


