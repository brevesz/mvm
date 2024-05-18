#ifndef CLIENTLIST_H
#define CLIENTLIST_H
#include <iostream>
#include <fstream>

#include "client.h"

class ClientList {
    Client *clients;
    size_t siz;
public:
    ClientList() : clients(nullptr), siz(0) {}
    void add(Client& client);
    void save();
    static ClientList load();

    size_t client_count() {return siz;}
    Client& operator[](size_t idx) {
        if (idx >= siz) throw "Out of range";
        return clients[idx];
    }
};

#endif // CLIENTLIST_H
