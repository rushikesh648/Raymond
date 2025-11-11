Page_Data read_block_from_file(FileID file_id, int block_num) {
    FileID_BlockNum key = create_key(file_id, block_num);

    // --- 1. CHECK FOR CACHE HIT ---
    if (CacheTable.contains(key)) {
        // Cache Hit! The data is already in fast memory.
        
        // Retrieve the page pointer
        CachePage* page = CacheTable.get(key);

        // Update the access time for the eviction policy (e.g., LRU)
        page->last_access_time = get_current_time();

        log("CACHE HIT: Returning data from Page Cache.");
        return page->memory_address;
    }
    
    // --- 2. CACHE MISS: Data must be loaded ---
    else {
        log("CACHE MISS: Data not found. Initiating disk read.");
        
        // A. Find an available memory page (CachePage)
        CachePage* new_page = find_available_page_frame();

        if (new_page == NULL) {
            // No free pages: Must evict a page using a policy (LRU, FIFO, etc.)
            new_page = run_eviction_algorithm();
            
            // If the evicted page was modified, write it back to disk first ("write-back" policy)
            if (new_page->is_dirty) {
                write_page_to_disk(new_page);
                new_page->is_dirty = false;
            }
            // Remove the old entry from the CacheTable
            CacheTable.remove(new_page->id);
        }

        // B. Read the requested block from the slow disk into the new page's memory
        new_page->id = key;
        read_from_disk_to_memory(file_id, block_num, new_page->memory_address);
        new_page->is_locked = false;
        new_page->last_access_time = get_current_time();

        // C. Add the new page to the CacheTable
        CacheTable.add(key, new_page);

        log("Data loaded. Returning data.");
        return new_page->memory_address;
    }
}
