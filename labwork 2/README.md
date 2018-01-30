Compile steps:

rpcgen -a -C file_transfer.x
make -f Makefile.file_transfer

For server side:
./file_transfer_server &

For client side: 
./file_transfer_client <host>
