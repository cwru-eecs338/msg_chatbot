Unix System V Message Queues
============================

Getting the files:
------------------

On the lab computers, use the command:

    git clone git://github.com/cwru-eecs338/msg_chatbot.git

Running the program:
--------------------
1. Use `make` to compile the program
2. Start the server in the background using `./server.o &` (note the process id)
3. Start the client using `./client.o 12345`, except replace '12345' with the process id of the server
4. Type `exit` in the client to quit
5. Stop the server by sending it an interrupt signal via the command `kill -INT 12345`, where '12345' is the process id of the server

Lessons:
--------
- Using Unix message queues
- Using `ftok()` to generate keys for unrelated processes to share resources
- Handling signals with the `signal()` call

Notes:
------
- Multiple clients can use the same server
- The message type is used in the program to designate the recipient process id; that is, a process should only receive messages of a type equal to its process id
