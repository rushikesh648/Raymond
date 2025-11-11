Line,Instruction,Description
1,"DEQUEUE R1, Q",Load the next waiting node ID from the queue Q into Register 1.
2,"MOV R2, #PRIVILEGE_MSG_ID",Load the hardcoded message ID for PRIVILEGE into Register 2.
3,"SEND_NET R2, R1",Send the PRIVILEGE message (R2) to the destination node ID (R1).
4,"MOV HOLDER, R1",Update the local state: The next holder is now the destination node (R1).
5,"MOV HAS_TOKEN, #0",Update the local state: Clear the node's HAS_TOKEN flag.
