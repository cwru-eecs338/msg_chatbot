Unix System V Message Queues
============================

Getting the files:
------------------

On the lab computers, use the command:
<pre><code>git clone git://github.com/cwru-eecs338/msg_chatbot.git</code></pre>

Running the program:
--------------------
1. Use <code>make</code> to compile the program
2. Start the server in the background using <code>./server.o &</code> (note the process id)
3. Start the client using <code>./client.o 12345</code>, except replace '12345' with the process id of the server
4. Type <code>exit</code> in the client to quit
5. Stop the server by sending it an interrupt signal via the command <code>kill -INT 12345</code>, where '12345' is the process id of the server

Lessons:
--------
- Using Unix message queues
- Using <code>ftok()</code> to generate keys for unrelated processes to share resources
- Handling signals with the <code>signal()</code> call

Notes:
------
- Multiple clients can use the same server
- The message type is used in the program to designate the recipient process id; that is, a process should only receive messages of a type equal to its process id
