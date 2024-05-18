#include <iostream>

#include "invoice.h"

void Invoice::write_invoice() {
    std::ostream << "Szamla adatai:\n" << "Szolgaltasi szerzodes azonositoja: " << number
                 << "\n" << "Bejegyzett fogyasztas: " << consumption << "Ft\n";
    if (paid) {std::ostream << "Fizetve"}
    else {std::ostream << "Nincs fizetve"}
}
