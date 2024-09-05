# Laboratory work for University

### Client and Server, backdoor defence 

During the work two programs were developed and tested in Ubuntu WSL.

#### Client

    1.  Sneaking to the system folder
    2.  Adds itself to the crontab to launch at startup
    3.  Creating socket and connecting to the server
    4.  After estabilishing a connection, it wait for the server message
    5.  After receiving message, closing connection

#### Server

    1.  Creating socket and trying to connect to the client
    2.  After estabilishing a connection, it sends name of the 
        file thats need to be deleted
    3.  After sending message, closing connection

### ACCEPTED!
