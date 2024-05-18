#ifndef SERVICE_H
#define SERVICE_H

#include "invoice.h"

class Client;

class Service {
    int number;
    int consumption;
    string billing_address;
    Client& client;
    string signed_on;
    Invoice *invoices;
    size_t siz;
public:
    Service(int n, int c, string str, Client& cl, char* so, Invoice* i, size_t s) : number(n), consumption(c), billing_address(str), client(cl), signed_on(so), invoices(i), siz(s) {}
    int get_number() {return number;}
    int get_consumption() {return consumption;}
    string get_billing_address() {return billing_address;}
    string get_signed_on() {return signed_on;}
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
