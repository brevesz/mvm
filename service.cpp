#include "service.h"
#include "client.h"
#include "memtrace.h"
#include <iostream>

Service::~Service() {
    if (invoices) {
        delete[] invoices;
    }
}

Service &Service::operator=(const Service &other) {
    number = other.number;
    consumption = other.consumption;
    billing_address = other.billing_address;
    client = other.client;
    siz = other.siz;
    invoices = new Invoice[siz];
    for (size_t i=0; i<siz; ++i) {
        invoices[i] = other.invoices[i];
    }

    return *this;
}

void Service::write_agreement() {
    std::cout << "Szolgaltatasi szerzodes:\n" << "Ugyfel neve: " << client->get_name() <<
                    "\n" << "Szerzodes azonositoja: " << number << "\n" << "Fogyasztas: "
                    << consumption << "\n";
}

void Service::register_consumption(int price) {
    consumption += price;
}

void Service::generate_invoice() {
    int random = rand() % 900 + 100;
    Invoice new_invoice(random,consumption,this,false); // még nincs kifizetve
    consumption = 0;
    add_invoice(new_invoice);
}

void Service::add_invoice(const Invoice& invoice) {
    siz++;
    Invoice *new_invoices = new Invoice[siz];
    for (size_t i = 0; i < siz - 1; ++i) {
        new_invoices[i] = invoices[i];
    }
    new_invoices[siz-1] = invoice;
    delete[] invoices;
    invoices = new_invoices;
}

void Service::pay_invoice(Invoice &selected) {
    for (size_t i = 0; i < siz; ++i) {
        if (invoices[i].get_number() == selected.get_number()) invoices[i].set_paid(true);
    }
}
