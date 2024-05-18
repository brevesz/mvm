#include <iostream>
#include "clientlist.h"
#include "client.h"
#include "service.h"
#include "invoice.h"
#include "gtest_lite.h"

int main() {

// CLIENTLIST TESZTEK
    TEST(addClient, ClientList)
        ClientList clientlist;
        Client client;
        clientlist.add(client);
        EXPECT_EQ((size_t)1,clientlist.client_count());
    END

    TEST(indexClient, ClientList)
        ClientList clientlist;
        Client client;
        clientlist.add(client);
        EXPECT_EQ(client.get_name(),clientlist[0].get_name());
    END

// CLIENT TESZTEK
    TEST(new_service, Client)
        Client client;
        Service service;
        client.new_service(service);
        EXPECT_EQ((size_t)1,client.service_count());

    END

    TEST(index_service, Client)
        Client client;
        Service service;
        client.new_service(service);
        EXPECT_EQ(service.get_number(),client[0].get_number());
    END

// SERVICE TESZTEK
    TEST(new_invoice, Service)
        Service service;
        service.invoice();
        EXPECT_EQ((size_t)1,service.invoice_count());
    END

    TEST(register_consumption, Service)
        Service service;
        int consumption = 2000;
        service.register_consumption(consumption);
        EXPECT_EQ(consumption,service.get_consumption());
    END
}
