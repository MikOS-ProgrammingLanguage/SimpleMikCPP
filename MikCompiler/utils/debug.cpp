#include <debug.hpp>
#include <errors.hpp>

#ifdef DEBUG

void debug(string i) {
    cout << GREEN << "DEBUG HIT: " << i << DEFAULT << endl;
}

#endif // DEBUG

#ifndef DEBUG

void debug(string i) {
    return;
}

#endif // DEBUG
