#include "clientlist.h"
#include "memtrace.h"
#include <iostream>
#include <fstream>
#include <string>
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
        for (size_t i = 0; i < siz; ++i) {
            clients_of << clients[i].get_number() << "\n" << clients[i].get_name() << "\n" << clients[i].get_billing_address() << endl;
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
                services_of << clients[i][j].get_number() << "\n" << clients[i][j].get_consumption() << "\n" << clients[i][j].get_billing_address() << "\n" << clients[i].get_number() << endl;
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
                    invoices_of << clients[i][j][k].get_number() << "\n" << clients[i][j][k].get_consumption() << "\n" << clients[i][j].get_number() << "\n" << clients[i][j][k].get_paid() << endl;
                }
            }
        }
        invoices_of.close();
    }
    else {
        cout << "Can't open file";
    }
}
// ennel a ket fuggvenynel hibakezeles kene? NEM JÓK, talán global? így nem jó hogy osztályba vannak
Client* ClientList::find_client(int cl_number) {
    for (size_t i = 0; i < client_count(); ++i) {
        if (clients[i].get_number() == cl_number) {
            return &clients[i];
        }
    }
    return nullptr;
}

Service* ClientList::find_service(int service_number) {
    for (size_t i = 0; i < siz; ++i) {
        for (size_t j = 0; j < clients[i].service_count(); ++j) {
            if (clients[i][j].get_number() == service_number) {
                return &clients[i][j];
            }
        }
    }
    return nullptr;
}

void ClientList::load() { // sajat magat tolti fel
    ifstream clients_if;
    clients_if.open("clients.txt");
    if (clients_if.is_open()) {
        int number;
        string name, billing_address,temp;

        while(clients_if.peek() != EOF) { // fajl vegeig olvasunk
            getline(clients_if,temp);
            number = stoi(temp);
            getline(clients_if,name);
            getline(clients_if,billing_address);

            Client client(number,name,billing_address);
            this->add(client); // ez mar megnoveli a ClientList siz-t
        }
        clients_if.close();
    }
    else {
        cout << "Can't open file";
    }

    ifstream services_if;
    services_if.open("services.txt");
    if (services_if.is_open()) {
        int number, consumption, client_number;
        string billing_address, temp;

        while(services_if.peek() != EOF) {
            getline(services_if,temp);
            number = stoi(temp);
            getline(services_if,temp);
            consumption = stoi(temp);
            getline(services_if,billing_address);
            getline(services_if,temp);
            client_number = stoi(temp);

            Service service(number,consumption,billing_address,find_client(client_number));
            for (size_t i = 0; i < this->siz; ++i) {
                if (clients[i].get_number() == client_number) {
                    clients[i].add_service(service);
                }
            }
        }
        services_if.close();
    }
    else {
        cout << "Can't open file";
    }

    ifstream invoices_if;
    invoices_if.open("invoices.txt");
    if (invoices_if.is_open()) {
        int number, consumption, service_number;
        bool paid;
        string temp;

        while(invoices_if.peek() != EOF) {
            getline(invoices_if,temp);
            number = stoi(temp);
            getline(invoices_if,temp);
            consumption = stoi(temp);
            getline(invoices_if,temp);
            service_number = stoi(temp);
            getline(invoices_if,temp);
            paid = stoi(temp);

            Invoice invoice(number,consumption,find_service(service_number),paid);
            for (size_t i = 0; i < this->siz; ++i) {
                for (size_t j = 0; j < clients[i].service_count(); ++j) {
                    clients[i][j].add_invoice(invoice);
                }
            }
        }
        invoices_if.close();
    }
    else {
        cout << "Can't open file";
    }
}


