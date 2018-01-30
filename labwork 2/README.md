# Compile steps:

## To create a fresh client and server code
==rpcgen -a -C file_transfer.x==

### To update and compile all the code
==make -f Makefile.file_transfer==

#### For server side:
==./file_transfer_server &==

##### For client side: 
==./file_transfer_client <host>==
