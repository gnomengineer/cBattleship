cBattleship
===========

A implementation of the classic Battleship game in C++, playable over network. (work in progress)

## How To Compile

```bash
$ cd cBattleship
$ mkdir build    # create build directory for an out of source build
$ cd build
$ cmake ..       # configure the source, generate the Makefiles
$ make           # build it!
```

You need to have `cmake` installed to be able to generate the Makefiles. Alternatively, you can also generate other things than Makefiles to compile the source (see the `-G` switch of `cmake`), if you don't have `make` available, like Visual Studio Project files. Only Makefiles have been tested yet. Please let us know if you compile this project on other plattforms and if any changes are needed (send us a pull request on GitHub).

The C++ `boost` libraries are used extensively in this project, you also need to have them installed (including the development headers).

To be able to compile the cBattleshipClient you also need to have `ncurses` installed. If you don't want the `ncurses` client you can also omit it during compilation:

```bash
make cBattleshipSimpleClient cBattleshipServer
```
 
## Run It

```bash
# execute these commands inside the your build directory
# run the server
$ ./cBattleshipServer 
# run the ncurses-client
$ ./cBattleshipClient <server-ip-or-hostname>
# run the text based client
$ ./cBattleshipSimpleClient <server-ip-or-hostname>
```

## Running The Tests

CppUnit is being used for Unit Testing.
 
To run the Tests type the following command inside your build directory:

```bash
$ ./cBattleshipTest
```

Alternatively you can also use the make target `test` to run the tests.
By running the tests this way you don't see all the information if a test fails.

```bash
$ make test
```

