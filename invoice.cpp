#include "invoice.h"
#include "memtrace.h"
#include <iostream>

void Invoice::write_invoice() {
    std::cout << "Szamla adatai:\n" << "Szolgaltasi szerzodes azonositoja: " << number
                 << "\n" << "Bejegyzett fogyasztas: " << consumption << "Ft\n";
    if (paid) {
            std::cout << "Fizetve";
    }
    else {
            std::cout << "Nincs fizetve";
    }
}
