#include <iostream>
#include <cstdlib>
using namespace std;
#include "clientlist.h"
#include "client.h"
#include "service.h"
#include "invoice.h"
#include <string.h>

#ifndef CPORTA

Client interactive_client() {
    cout << "Adja meg az ugyfel adatait! Az egyes szolgaltatasokat az ugyfelek listazasa nezetben adhatja hozza.\n";
    cout << "====\n";

    string name;
    string b_address;

    cout << "Ugyfel neve: ";
    std::getline(cin, name);

    cout << "Szamlazasi cime: ";
    std::getline(cin, b_address);

    int random = rand() % 900 + 100;

    Client client(random, name, b_address);

    return client;

}
void pay_invoice(Service& service) {
    int input;
    cout << "Adja meg a befizetni kivant szamla azonosito szamat!\n";
    cin >> input;
    for (size_t i = 0; i < service.invoice_count(); ++i) {
        if (service[i].get_number() == input) {
            service[i].set_paid(true);
            cout << "Befizetve!" << endl;
            return;
        }
    }
    cout << "Nem talalhato ilyen szamlaszam." << endl;
}

void write_service(Service& service) {
    int input;
    cout << "[0] Vissza [1] Uj szamla [2] Egyenleg lekerdezes [3] Fogyasztas bejelentese [4] Befizetes\n";
    cout << "====\n";
    cout << service.get_number() << endl;
    cout << "A szolgaltatashoz tartozo szamlak:\n";
    for (size_t i = 0; i < service.invoice_count(); ++i) {
        cout << service[i].get_number() <<
            (service[i].get_paid() ? " fizetve" : " nincs fizetve") << endl;
    }
    cin >> input;
    switch (input) {
        case 0:
            return;
        case 1:
            service.generate_invoice();
            cout << "Uj szamla hozzaadva.";
            break;

        case 2:
            cout << "Az egyenleg: " << service.get_consumption() << "Ft.\n";
            break;
        case 3:
            int new_consumption;
            cout << "Adja meg a fogyasztast!\n";
            cin >> new_consumption;
            service.register_consumption(new_consumption);
            cout << "Fogyasztas bejelentve.\n";
            break;
        case 4:
            pay_invoice(service);
            break;
    }
}

Service interactive_service(Client& client){
    string billing_address;
    cout << "Adja meg a szolgaltatas cimet: ";
    std::getline(cin,billing_address);
    int random = rand() % 900 + 100;
    Service new_service(random, 0, billing_address, &client);
    return new_service;
}

void write_client(Client& client) {
    while (true) {
        cout << "[0] Vissza\n";
        cout << "Valasszon a megfelelelo szambillentyu lenyomasaval!\n";
        cout << "Uj szolgaltatasi szerzodes: irja be, hogy n!\n";
        cout << "====\n";
        cout << "Ugyfel neve: " << client.get_name() << endl;
        cout << "Szamlazasi cime: " << client.get_billing_address() << endl;
        cout << "Szolgaltatasok:\n";
        for (size_t i = 0; i < client.service_count(); ++i) {
            cout << "[" << i+1 << "] " << client[i].get_number() << " " << client[i].get_billing_address() << endl;
        }
        string input;
        cin >> input;
        cin.ignore();
        if (input == "n") {
            client.add_service(interactive_service(client));
            cout << "Uj szolgaltatas mentve.\n";
            return;
        }

        int selection = stoi(input);
        switch (selection) {
        case 0:
            return;
        default:
            {
                auto service = client[selection - 1];
                write_service(service);
                break;
            }
        }
    }
}
void write_clientlist(ClientList& clientlist) {
    while (true) {
        cout << "Valasszon a megfelelo szambillentyu lenyomasaval!\n";
        cout << "====\n";
        cout << "[0] Vissza\n";
        for (size_t i = 0; i < clientlist.client_count(); ++i) {
            cout << "[" << i+1 << "] " << clientlist[i].get_name() << endl;
        }
        int input;
        cin >> input;
        if (input == 0) return;

        auto &client = clientlist[input-1];
        write_client(client);
    }
}

void main_menu() {
    int input;
    bool kilepes = false;
    ClientList clientlist;
    clientlist.load();

    cout << "Meseorszagi Villamos Muvek\n";
    while (!kilepes) {
        cout << "Valasszon a menupontokbol!\n";
        cout << "====\n";
        cout << "[1] Ugyfelek listazasa\n";
        cout << "[2] Uj ugyfel\n";
        cout << "[3] Mentes\n";
        cout << "[0] Kilepes\n";

        cin >> input;
        cin.ignore();
        switch (input) {
            case 0:
                kilepes = true;
                break;
            case 1:
                write_clientlist(clientlist);
                break;
            case 2:
                {
                    auto client = interactive_client();
                    clientlist.add(client);
                    cout << "Uj ugyfel mentve.";
                    break;
                }
            case 3:
                clientlist.save();
                break;
        }
    }
}

#endif
