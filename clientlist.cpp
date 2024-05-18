#include <iostream>

#include "clientlist.h"
#include <fstream>
using namespace std;
void ClientList::add(Client& client) {
    siz++;
    Client *new_clients = new Client[siz];
    for (size_t i = 0; i < siz-1; ++i) {
        new_clients[i] = clients[i];
    }
    new_clients[siz-1] = client;
    delete[] clients;
    clients = new_clients;

}

void ClientList::save() {
    ofstream clients_of;
    clients_of.open("clients.txt");
    if (clients_of.is_open()) {
        cout << "writing file clients.txt" << endl;
        for (size_t i = 0; i < siz; ++i) {
            clients_of << clients[i].get_name() << "\n" << clients[i].get_billing_address() << "\n" << clients[i].service_count() << endl;
        }
        clients_of.close();
    }
    else {
        cout << "Can't open file";
    }

    ofstream services_of;
    services_of.open("services.txt");
    if (services_of.is_open()) {
        for (size_t i = 0; i < siz; ++i) {
            for (size_t j = 0; j < clients[i].service_count(); ++j) {
                services_of <<clients[i][j].get_number() << "\n" << clients[i][j].get_consumption() << "\n" << clients[i][j].get_billing_address() << "\n" << clients[i][j].invoice_count() << endl;
            }
        }
        services_of.close();
    }
    else {
        cout << "Can't open file";
    }

    ofstream invoices_of;
    invoices_of.open("invoices.txt");
    if (invoices_of.is_open()) {
        for (size_t i = 0; i < siz; ++i) {
            for (size_t j = 0; j < clients[i].service_count(); ++j) {
                for (size_t k = 0; k < clients[i][j].invoice_count(); ++k) {
                    invoices_of << clients[i][j][k].get_number() << "\n" << clients[i][j][k].get_consumption() << "\n" << clients[i][j][k].get_paid() << endl;
                }
            }
        }
        invoices_of.close();
    }
    else {
        cout << "Can't open file";
    }
}
