#include <iostream>
#include <fstream>
#include "client.h"
using namespace std;

Client::~Client() {
    if (services) {
        delete[] services;
    }
}

Client &Client::operator=(const Client &other) {
    number = other.number;
    name = other.name;
    billing_address = other.billing_address;
    siz = other.siz;
    services = new Service[siz];
    for (size_t i=0; i<siz; ++i) {
        services[i] = other.services[i];
    }

    return *this;
}

void Client::add_service(const Service& service) {
    siz++;
    Service *new_services = new Service[siz];
    for (size_t i = 0; i < siz - 1; ++i) {
        new_services[i] = services[i];
    }
    new_services[siz-1] = service;
    delete[] services;
    services = new_services;
}

/*
void Client::load() {
    ifstream i_f(name);
    // kell a fileba az a szoveg, vagy csak az adatok �s akkor meg lehet norm�lisan
    // csin�lni ezt a load f�ggv�nyt? egy�bk�nt ezt a clientlistbe minden clientre megh�vni
    // amikor elind�tjuk a programot

}
*/
