/**
 * @brief Routine to handle incoming PRIVILEGE (Token) messages.
 */
void receive_privilege() {
    // 1. Acknowledge and claim the token
    HAS_TOKEN = true;
    
    // 2. Check the local state
    if (WANTS_CS) {
        // The node wanted the token: enter the critical section.
        enter_critical_section(); 
        
        // After execution, update the state
        exit_critical_section(); 
        WANTS_CS = false;
    }

    // 3. Token Release Logic: Check if there are other waiting nodes
    if (!is_queue_empty(Q)) {
        // If Q is NOT empty, the node must immediately pass the token.
        pass_privilege();
    } else {
        // If Q IS empty, the token rests at this node until a new request arrives.
        printf("Token resting at node %d.\n", MY_NODE_ID);
    }
}


/**
 * @brief Helper routine to pass the token to the next waiting node.
 */
void pass_privilege() {
    // Get the next node from the queue
    NodeID next_node = dequeue(Q); 
    
    // Send the PRIVILEGE token (message)
    send_message(next_node, MSG_PRIVILEGE, NULL);

    // Update the local state
    HAS_TOKEN = false;
    HOLDER = next_node;
    printf("Token passed to node %d.\n", next_node);
}
