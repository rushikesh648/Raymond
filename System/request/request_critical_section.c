/**
 * @brief Node routine to request access to the Critical Section.
 * @param self_id The unique ID of the current node.
 */
void request_critical_section(NodeID self_id) {
    // Set the local flag to indicate a desire for the token
    WANTS_CS = true; 

    // If the node already holds the token, it can proceed immediately.
    if (HAS_TOKEN) {
        return; // Proceeds to enter CS after this routine finishes.
    }

    // Add self to the local request queue (Q)
    enqueue(Q, self_id);

    // If the node's HOLDER pointer does not point to itself, 
    // it must send a request upstream towards the actual token holder.
    if (self_id != HOLDER) {
        // Send a REQUEST message to the node pointed to by HOLDER
        send_message(HOLDER, MSG_REQUEST, self_id);

        // Update HOLDER pointer to point to self.
        // This makes the current node the root of the new requesting sub-tree.
        HOLDER = self_id; 
    }
}
