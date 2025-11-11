#include <stdbool.h>
#include <stdio.h>

// --- HARDCODED STATE VARIABLES (Managed by the OS Kernel) ---

// Q: Request Queue (List of nodes waiting for the token)
NodeID request_queue[MAX_NODES]; 
int queue_size = 0;

// HOLDER: ID of the node currently holding the token, or the next node towards it
NodeID holder_id; 

// HAS_TOKEN: Boolean state of the current node
bool has_token = false; 

// --- THE TOGGLE VARIABLE ---

// This toggle tracks whether the node currently desires access to the critical section.
bool wants_critical_section = false; 

// --- CORE RAYMOND ALGORITHM LOGIC ---

/**
 * @brief Routine executed by a node when it decides it needs the critical section.
 * @param self_id The unique ID of the current node.
 */
void request_critical_section(NodeID self_id) {
    printf("\nNode %d: Initiating request for Critical Section.\n", self_id);
    
    // 1. TOGGLE: Set the local flag indicating the node's desire
    wants_critical_section = true; 
    printf("  --> TOGGLE ON: wants_critical_section is now TRUE.\n");

    // 2. Check Local State
    if (!has_token) {
        // If the node does NOT have the token, it must request it.

        // Add self to the local request queue (Q)
        request_queue[queue_size++] = self_id;
        printf("  --> Added self (%d) to local request queue (Q).\n", self_id);

        // Check if the request must be sent upstream (towards the holder)
        if (self_id != holder_id) {
            // 3. Send Request Message
            
            // The request is sent to the node pointed to by the HOLDER variable.
            // (This function would be hardcoded in the kernel network stack)
            send_message(holder_id, MESSAGE_TYPE_REQUEST, self_id);
            printf("  --> Sent REQUEST message to holder_id: %d.\n", holder_id);
            
            // The node then updates its holder pointer to point to itself, 
            // as it is now the new head of the requesting path.
            update_holder(self_id);
            printf("  --> Updated local HOLDER to self: %d (new root of request path).\n", self_id);
        }
    } else {
        // If the node HAS the token, it can proceed directly to the critical section
        printf("  --> Node already holds the token. Preparing to enter CS.\n");
    }
}

// --- SIMPLIFIED MOCK SYSTEM FUNCTIONS ---

void send_message(NodeID dest, int type, NodeID payload) {
    // Conceptual network send function
    // In a real OS, this involves kernel network stack calls
}

void update_holder(NodeID new_holder) {
    // Conceptual kernel state update
    holder_id = new_holder;
}


// --- MAIN EXECUTION (MOCKUP) ---
typedef int NodeID;
#define MESSAGE_TYPE_REQUEST 1
#define MAX_NODES 10

int main() {
    // Initial State Mockup
    NodeID current_node = 3;
    holder_id = 1; // Assume the token holder is Node 1 initially
    has_token = false;

    // Node 3 decides it needs the CS
    request_critical_section(current_node);

    // --- Critical Section Execution and Release (Conceptual) ---
    // If the node receives the token later...
    // The node enters CS, executes its task, and then releases:
    
    // When finished, the toggle is turned OFF
    wants_critical_section = false;
    printf("\nNode %d: Exiting Critical Section.\n", current_node);
    printf("  --> TOGGLE OFF: wants_critical_section is now FALSE.\n");

    // The release routine would then check Q and pass the token if Q is not empty.

    return 0;
}
