#include <iostream>
#include "client.h"
using namespace std;

void Client::new_service(Service& service) {
    siz++;
    Service new_services = new Service[siz];
    for (size_t i = 0; i < siz; ++i) {
        new_services[i] = services[i];
    }
    new_services[siz] = service;
    delete[] services;
    services = new_services;
}

void Client::save() {
    ofstream o_f(name);
    if (o_f.is_open()){
        o_f << "Ugyfel neve: " << name << "\n" << "Szamlazasi cime: " << billing_address << "\n" << "Igenybe vett szolgaltatasok: " << siz << endl;
        o_f.close();
    }
    else{
        cout << "Can't open file.";
    }
}

void Client::load() {
    ifstream i_f(name);
    // kell a fileba az a szoveg, vagy csak az adatok és akkor meg lehet normálisan
    // csinálni ezt a load függvényt? egyébként ezt a clientlistbe minden clientre meghívni
    // amikor elindítjuk a programot

}
