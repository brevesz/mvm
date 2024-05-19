#ifndef SERVICE_H
#define SERVICE_H

#include "invoice.h"
#include <string>

class Client;
using std::string;

class Service {
    int number {-1};
    int consumption {0};
    string billing_address;
    Client *client {nullptr};
    Invoice * invoices {nullptr};
    size_t siz {0};
public:
    Service() {}
    Service(int number, int consumption, string billing_address, Client* cl) : number(number), consumption(consumption), billing_address(billing_address), client(cl) {}
    ~Service();
    int get_number() const {return number;}
    int get_consumption() const {return consumption;}
    string get_billing_address() const {return billing_address;}
    size_t invoice_count() const {return siz;}
    void write_agreement();
    void register_consumption(int price); // növeli az akkumuláló consumptiont, ami majd a generate_invoicenál lenullázódik, és megkapja egy invoice
    void generate_invoice();
    void add_invoice(const Invoice& invoice); // nemtom az invoice sima fuggvennyel nem tudtam
    void pay_invoice(Invoice& selected);

    Invoice &operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return invoices[idx];
    }

    Service &operator=(const Service &other);

};
#endif // SERVICE_H
