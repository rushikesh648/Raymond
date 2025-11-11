CachePage* run_eviction_algorithm() {
    // LRU selects the page that hasn't been accessed for the longest time.
    CachePage* victim = NULL;
    long lowest_time = MAX_LONG;

    // Iterate through all cached pages to find the oldest one.
    for (CachePage* page : CacheTable.all_pages) {
        // Skip pages currently locked by a process
        if (page->is_locked) {
            continue;
        }
        
        if (page->last_access_time < lowest_time) {
            lowest_time = page->last_access_time;
            victim = page;
        }
    }
    return victim;
}
