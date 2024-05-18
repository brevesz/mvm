#include <iostream>

#include "clientlist.h"
#include <fstream>
using namespace std;
void ClientList::add(Client& client) {
    siz++;
    Client new_clients = new Client[siz];
    for (size_t i = 0; i < siz; ++i) {
        new_clients[i] = clients[i];
    }
    new_clients[siz] = client;
    delete[] clients;
    clients = new_clients;

}

void ClientList::save() {
    for (size_t i = 0; i < siz; ++i) {
        clients[i].save();
    }
}
