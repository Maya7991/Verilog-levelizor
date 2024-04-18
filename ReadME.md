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
$ ./levelizor <verilog_filename> <gate_filename>
```

Example: ```$ ./levelizor ../../../nor_files/test_nor2.v ../../examples/gate_info.txt```


Arguments are:
1. verilog filename- This file contains the gate level verilog design that needs to be levelized.
2. Gate filename- This file contains the name of gates in the gate library used to synthesize the design.


