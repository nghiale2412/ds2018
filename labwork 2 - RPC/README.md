# Compile steps:

## To create a fresh client and server 
`rpcgen -a -C file_transfer.x`

### To update and compile all the codes
`make -f Makefile.file_transfer`

#### For server side:
`./file_transfer_server &`

##### For client side: 
`./file_transfer_client <host>`
