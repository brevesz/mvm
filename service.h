#ifndef SERVICE_H
#define SERVICE_H

#include "invoice.h"

class Client;
using std::string;

class Service {
    int number;
    int consumption;
    string billing_address;
    Client *client;
    Invoice *invoices;
    size_t siz;
public:
    Service() {}
    Service(int number, int consumption, string billing_address, Client* cl) : number(number), consumption(consumption), billing_address(billing_address), client(cl) {}
    int get_number() {return number;}
    int get_consumption() {return consumption;}
    string get_billing_address() {return billing_address;}
    size_t invoice_count() {return siz;}
    void write_agreement();
    void register_consumption(int price);
    void invoice();
    void pay_invoice(Invoice& selected);

    Invoice &operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return invoices[idx];
    }
};
#endif // SERVICE_H
