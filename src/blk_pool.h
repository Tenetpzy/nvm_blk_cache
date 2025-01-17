#ifndef NVM_CACHE_BLK_POOL
#define NVM_CACHE_BLK_POOL

#include "defs.h"
#include "access.h"

typedef struct NvmCache NvmCache;
typedef struct NvmTransaction NvmTransaction;

// 空闲缓存池管理结构
// 根据设计，可以是NVM上统一的缓存池，也可以是每个resource_id私有的缓存池、或公共缓存池
typedef struct NvmCacheBlkPool {
    // TODO
} NvmCacheBlkPool;

// NVM上的一个缓冲块的引用
typedef struct NvmCacheBlk {
    NvmObj obj;
    // TODO
} NvmCacheBlk;

/***********************public API***********************/

int blk_pool_init(NvmCacheBlkPool *blk_pool, NvmCache *cache);
void blk_pool_destruct(NvmCacheBlkPool *self);

int blk_pool_alloc(NvmCacheBlkPool *self, NvmCacheBlkId *new_id, NvmTransaction *txn);
int blk_pool_free(NvmCacheBlkPool *self, NvmCacheBlkId id, NvmTransaction *txn);

// 缓存淘汰时，选择出被淘汰的一项。注意并发问题，返回后evict_id还没有free，调用者可能继续操作这个缓存块
int blk_pool_evict(NvmCacheBlkPool *self, NvmCacheBlkId *evict_id, NvmTransaction *txn);

// 把缓存块全部刷下去。TODO: 指定刷的范围？
int blk_pool_flush(NvmCacheBlkPool *self, NvmTransaction *txn);

// 获取id对应的缓冲块，当blk还在使用时，blk不应该被淘汰。活跃信息应该在内存中维护，所以也不需要事务
int blk_pool_get(NvmCacheBlkPool *self, NvmCacheBlkId id, NvmCacheBlk *blk);

/***********************public API***********************/

#endif