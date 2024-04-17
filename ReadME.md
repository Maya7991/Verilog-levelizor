To build the program for the first time:
1. Delete all makefiles in the build folder

Then Run the following commands:
```
$ cd build
$ cmake ..
$ cmake --build .
```

To run the program:

```
$ cd build
$ make
$ cd src
$ ./levelizor ../../../nor_files/test_nor2.v ../../examples/gate_info.txt
```

Example: ```$ ./mac_gen ../examples/c432.txt```


