#include <iostream>

#include "service.h"

void Service::write_agreement() {
    std::ostream << "Szolgaltatasi szerzodes:\n" << "Ugyfel neve: " << client.name <<
                    "\n" << "Szerzodes azonositoja: " << number << "\n" << "Fogyasztas: "
                    << consumption << "\n" << "Alairva: " << signed_on << "\n";
}

void Service::register_consumption(int price) {
    consumption += price;
}

void Service::invoice() {
    Invoice new_invoice;
    int random = rand() % 900 + 100; // csak egyszer kéne használni
    new_invoice(random,consumption,*this,false); // még nincs kifizetve


    siz++;
    Invoice new_invoices = new Invoice[siz];
    for (size_t i = 0; i < siz; ++i) {
        new_invoices = invoices[i];
    }
    new_invoices[siz] = new_invoice;
    delete[] invoices;
    invoices = new_invoices;
}

void Service::pay_invoice(Invoice &selected) {
    for (size_t i = 0; i < siz; ++i) {
        if (invoices[i] == selected) invoices[i].set_paid(true);
    }
}
