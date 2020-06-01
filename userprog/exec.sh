cd ../test
make
cd ../userprog
./nachos -r /exec
./nachos -cp ../test/exec /exec
./nachos -x /exec -rv
