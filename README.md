cBattleship
===========

A BattleShip implementation in C++, playable over network.

## How To Compile

You need to have cmake installed to compile this.

    $ cd cBattleship
    # create build directory
    $ mkdir build
    # configure the source & build
    $ cmake ..
    $ make

 
# Run It

    # execute these commands inside the your build directory
    # run the server
    $ ./cBattleshipServer 
    # run the ncurses-client
    $ ./cBattleshipClient <server-ip-or-hostname>
    # run the text based client
    $ ./cBattleshipSimpleClient <server-ip-or-hostname>

 # Running The Tests

 CppUnit is being used for Unit Tests.
 
 To run the Tests type the following command inside your build directory:

    $ make test

Alternatively you can run the test-executable directly:

    $ ./cBattleshipTest
