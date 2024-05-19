#ifndef CLIENTLIST_H
#define CLIENTLIST_H
#include <iostream>
#include <fstream>

#include "client.h"

class ClientList {
    Client *clients;
    size_t siz;
    Client* find_client(int cl_number);
    Service* find_service(int service_number);
public:
    ClientList() : clients(nullptr), siz(0) {}
    void add(Client& client);
    void save();
    void load();

    size_t client_count() const {return siz;}
    Client& operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return clients[idx];
    }

};

#endif // CLIENTLIST_H
