/**
 * @brief Routine to handle incoming REQUEST messages.
 * @param sender_id The ID of the node that sent the request.
 */
void receive_request(NodeID sender_id) {
    
    // Add the sender's ID to the local request queue (Q)
    enqueue(Q, sender_id);
    
    // Check if the current node satisfies the token-passing condition.
    // The node will pass the token (PRIVILEGE) if it has the token 
    // AND it doesn't currently want the critical section itself.
    if (HAS_TOKEN && !WANTS_CS) {
        // Condition met: Pass the token to the next node in Q.
        pass_privilege();
    } 
    // If the node doesn't have the token, but it needs the token (or is already waiting)
    else if (!HAS_TOKEN && WANTS_CS) {
        // The node acts as a relay: it re-sends a request upstream (towards its HOLDER)
        // to retrieve the token on behalf of the waiting nodes in its subtree.
        // This is done using the same logic as the initial request.
        request_critical_section(MY_NODE_ID);
    }
}
