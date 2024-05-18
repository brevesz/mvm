#ifndef CLIENT_H
#define CLIENT_H

#include "service.h"
using namespace std;

class Client {
    int number {-1};
    string name;
    string billing_address;
    Service *services {nullptr};
    size_t siz {0};
public:
    Client() {}
    Client(int num, string n, string b_a) : number(num), name(n), billing_address(b_a) {} // a maradék?
    ~Client();
    string get_name(){return name;}
    string get_billing_address(){return billing_address;}
    size_t service_count() {return siz;}
    void add_service(const Service& service);

    Client &operator=(const Client &other);

    Service &operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return services[idx];
    }

};
#endif // CLIENT_H
