#include <iostream>
#include <cstdlib>
using namespace std;
#include "clientlist.h"
#include "client.h"
#include "service.h"
#include "invoice.h"
#include <string.h>

void main_menu() {
    int input;
    bool kilepes = false;

    cout << "Meseorszagi Villamos Muvek\n";
    while (!kilepes) {
        cout << "Valasszon a menupontokbol!\n";
        cout << "====\n";
        cout << "[1] Ugyfelek listazasa\n";
        cout << "[2] Uj ugyfel\n";
        cout << "[0] Kilepes\n";

        cin >> input;
        switch (input) {
            case 0:
                kilepes = true;
                break;
            case 1:
                //write_clientlist();
                break;
            case 2:
                //clientlist.add(interactive_client());
                break;

        }

    }

}

Client interactive_client() {
    cout << "Adja meg az ugyfel adatait! Az egyes szolgaltatasokat az ugyfelek listazasa nezetben adhatja hozza.\n";
    cout << "====\n";
    string name;
    string b_address;
    cout << "Ugyfel neve: "; std::getline(cin, name);
    cout << "\nSzamlazasi cime: "; std::getline(cin,b_address);
    int random = rand() % 900 + 100;
    Client client(random, name, b_address);
    return client;

}


void write_service(Service& service) {
    int input;
    bool kilepes = false;
    while (!kilepes) {
        cout << "[0] Vissza [1] Uj szamla [2] Egyenleg lekerdezes [3] Fogyasztas bejelentese [4] Befizetes\n";
        cout << "====\n";
        cout << service.get_number() << endl;
        cout << "A szolgaltatashoz tartozo szamlak:\n";
        for (size_t i = 0; i < service.invoice_count(); ++i) {
            if (service[i].get_paid()) {cout << "-" << service[i].get_number() << ", fizetve";}
            else {
                cout << "-" << service[i].get_number() << ", nincs fizetve";
            }
        }
        cin >> input;
        switch (input) {
            case 0:
                kilepes = true;
                break;
            case 1:
                service.invoice();
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
                cout << "Fogyasztas bejelentve.";
            break;
        case 4:
            // a feladat a szolgáltatási díjat (tehát az egészet) írja, nem egyenként a számlák kifizetését, idk
            break;
        }
    }
}

Service interactive_service(Client& client){
    string new_service_name;
    std::getline(cin,new_service_name);
    int random = rand() % 900 + 100; // csak egyszer kéne használni
    Service new_service(random,0,new_service_name, &client);
    return new_service;
}

void write_client(Client& client) {
    cout << "[0] Vissza\n";
    cout << "Valasszon a megfelelelo szambillentyu lenyomasaval!\n";
    cout << "Uj szolgaltatasi szerzodes: irja be, hogy n! Torles: irja be, hogy d!\n";
    cout << "====\n";
    cout << "Ugyfel neve: " << client.get_name() << endl;
    cout << "Szamlazasi cime: " << client.get_billing_address() << endl;
    cout << "Szolgaltatasok:\n";
    for (size_t i = 0; i < client.service_count(); ++i) {
        cout << "[" << i << "] " << client[i].get_number() << " " << client[i].get_billing_address() << endl;
    }
    char input;
    cin >> input;


    switch (input) {
    case '0':
        return;
    case 'n':
        client.add_service(interactive_service(client));
        break;
    case 'd':
        //delete függvény
        break;
    }

    write_service(client[int(input)]);
}
void write_clientlist(ClientList& clientlist) {
    cout << "Valasszon a megfelelo szambillentyu lenyomasaval!\n";
    cout << "====\n";
    cout << "[0] Vissza\n";
    for (size_t i = 1; i < clientlist.client_count()+1; ++i) {
        cout << "[" << i << "] " << clientlist[i].get_name() << endl;
    }
    int input;
    cin >> input;
    if (input == 0) return;

    write_client(clientlist[input]);
}

