// Global Structure: A hash table for quick lookup of cached data blocks.
struct CacheTable {
    // Key: Combination of (File Identifier + Block Number)
    // Value: Pointer to the Memory Page holding the data
    Hash_Map<FileID_BlockNum, Page_Pointer> pages;
};

// Data Structure for each page frame in the cache
struct CachePage {
    FileID_BlockNum id;
    void* memory_address;       // Actual kernel memory location
    bool is_dirty;              // True if page has been modified (needs writing back)
    bool is_locked;             // True if page is being used by a process (cannot be swapped)
    long last_access_time;      // For LRU/LFU eviction algorithm
};
