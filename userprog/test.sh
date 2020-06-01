cd ../test
make
cd ../userprog
./nachos -r /fileA
./nachos -r /test1
./nachos -cp ../test/fileA /fileA
./nachos -x /fileA -rv