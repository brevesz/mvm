#ifndef CLIENT_H
#define CLIENT_H

#include "service.h"
using namespace std;

class Client {
    string name;
    string billing_address;
    Service *services;
    size_t siz;
public:
    Client(string n, string b_a) : name(n), billing_address(b_a) {} // a maradék?
    string get_name(){return name;}
    string get_billing_address(){return billing_address;}
    size_t service_count() {return siz;}
    void new_service(Service& service);

    void save();
    void load(); // static?

    Service &operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return services[idx];
    }

};
#endif // CLIENT_H
