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
    // kell a fileba az a szoveg, vagy csak az adatok �s akkor meg lehet norm�lisan
    // csin�lni ezt a load f�ggv�nyt? egy�bk�nt ezt a clientlistbe minden clientre megh�vni
    // amikor elind�tjuk a programot

}
