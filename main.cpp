/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>
#include <model.h>


int main(int argc, char **argv) {
    Model m = Model();

    m.loadFile(argv[1]);
    m.printVertex();

    return 0;
}



