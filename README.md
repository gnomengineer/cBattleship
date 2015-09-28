cBattleship
===========

Let's start off with a little [Haiku](https://de.wikipedia.org/wiki/Haiku):

> We C Battleships  
> Battleships are on the C  
> Hit, Sink, and triumph

A implementation of the classic Battleship game in C++. Includes a server program, and multiple different client programs. The server program wait's until two client program connected to start a game. The server dictates the rules of the game.

## Features

 * playable over network
 * old-school terminal client
 * ascii-art (more ascii art is always a possibility)
 * ncurses client (work in progress)
 * gtk client (work in progress)
 * configure how exactly you want to play the game (work in progress)
 * Enemy A.I. for singleplayer mode (? work in progress)
 * not written in PHP
 * written in C++
 * GPL'd

## How To Compile

We don't provide any builds but you can easily build this project yourself on basically any linux machine. Maybe even most unix machines (Let us know). You can build it with Cygwin if you are on windows.

```bash
% git clone https://github.com/troopa/cBattleship.git
% cd cBattleship
% mkdir build    # create build directory for an out of source build
% cd build
% cmake ..       # configure the source, generate the Makefiles
% make           # build it!
```

You need to have `cmake` installed to be able to generate the Makefiles. Alternatively, you can also generate other things than Makefiles to compile the source (see the `-G` switch of `cmake`), if you don't have `make` available, like Visual Studio Project files. Only Makefiles have been tested yet. Please let us know if you compile this project on other plattforms and if any changes are needed (send us a pull request on GitHub).

The C++ `boost` libraries are used extensively in this project, you also need to have them installed (including the development headers).

To be able to compile the cbattleship-curses-client you also need to have `ncurses` installed. If you don't want the `ncurses` client you can also omit it during compilation:

```bash
make cbattleship-text-client cbattleship-server
```

The same thing is true for the `cbattleship-gtk-client`. You need the `gtkmm3.0` development headers, including the `pkg-config` and `glib-compile-resources` programs.
 
## Run It

```bash
# execute these commands inside the your build directory
# run the server
% ./cbattleship-server 
# run the ncurses-client
% ./cbattleship-curses-client <server-ip-or-hostname>
# run the text based client
% ./cbattleship-text-client <server-ip-or-hostname>
```

## Running The Tests

CppUnit is being used for Unit Testing.
 
To run the Tests type the following command inside your build directory:

```bash
% ./cbattleship-unit-tests
```

Alternatively you can also use the make target `test` to run the tests.
By running the tests this way you don't see all the information if a test fails.

```bash
% make test
```

