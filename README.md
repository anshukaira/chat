# Chat
Simple socket - programming samples

This is the most simple and preemptive socket program >_<


  the socket program works in following manner
  
       client server model -- 

        server               client
          |                     |
        socket()             socket()
          |                     |
        bind()                  |
          |                     |    
        listen()                |    
          |                     |  
        accept()  <------    connection()
          |                     |
        read()    <------     write()
          |                     |
        write()   ------>      read()
          |                     |
        close()   <----->     close()



For talking to yourself or maybe someone else--
  1. open two terminals (on one machine or on different)
  2. make one terminal client and other server
  3. use following commands
  
    --for client
    
    gcc client.c -o client 
    ./client 127.0.0.1 <_port no_> //use ip address instead of 127.0.0.1 for two machines
    
    --for server
    gcc server.c -o server
    ./server <_port no_>
    
    //use port number greater than 1024
   4. Enjoy!!
    
