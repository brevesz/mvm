#include <iostream>
#include "clientlist.h"
#include "client.h"
#include "service.h"
#include "invoice.h"
#include "gtest_lite.h"

int tests_main() {

/*

    2. létrehoz egy klienst, egy servicet, egy fizetetlen invoicet, aztan befizeti azt,
         ellenorzi hogy az invoiceok között be van fizetve
*/

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
        client.add_service(service);
        EXPECT_EQ((size_t)1,client.service_count());

    END

    TEST(index_service, Client)
        Client client;
        Service service;
        client.add_service(service);
        EXPECT_EQ(service.get_number(),client[0].get_number());
    END

// SERVICE TESZTEK
    TEST(new_invoice, Service)
        Service service;
        service.generate_invoice();
        EXPECT_EQ((size_t)1,service.invoice_count());
    END

    TEST(register_consumption, Service)
        Service service;
        int consumption = 2000;
        service.register_consumption(consumption);
        EXPECT_EQ(consumption,service.get_consumption());
    END

// INVOICE TESZTEK
    TEST(pay, Invoice)
        ClientList clientlist;
        Client _c(100, "Kovacs Aladar", "1111 Budapest, Virag u. 1");
        clientlist.add(_c);
        Client &client = clientlist[0];

        Service _s(222, 500, "1112 Budapest, Level u. 2", &client);
        client.add_service(_s);
        Service &service = client[0];
        Invoice _i(3000, 20000, &service, false);
        service.add_invoice(_i);

        Invoice &invoice = service[0];
        service.pay_invoice(invoice);
        EXPECT_TRUE(invoice.get_paid());
    END

// SAVE AND LOAD
    TEST(save_and_load, ClientList)
        {
            ClientList clientlist;
            Client _c(100, "Kovacs Aladar", "1111 Budapest, Virag u. 1");
            clientlist.add(_c);
            Client &client = clientlist[0];

            Service _s(222, 500, "1112 Budapest, Level u. 2", &client);
            client.add_service(_s);
            Service &service = client[0];
            Invoice invoice(3000, 20000, &service, false);
            service.add_invoice(invoice);

            clientlist.save();
        }
        {
            ClientList clientlist;
            clientlist.load();

            EXPECT_EQ((size_t)1, clientlist.client_count());

            Client &client = clientlist[0];
            EXPECT_EQ(100, client.get_number());
            EXPECT_EQ(string("Kovacs Aladar"), client.get_name());
            EXPECT_EQ(string("1111 Budapest, Virag u. 1"), client.get_billing_address());
            EXPECT_EQ((size_t)1, client.service_count());

            Service &service = client[0];
            EXPECT_EQ(222, service.get_number());
            EXPECT_EQ(500, service.get_consumption());
            EXPECT_EQ(string("1112 Budapest, Level u. 2"), service.get_billing_address());
            EXPECT_EQ((size_t)1, service.invoice_count());

            Invoice &invoice = service[0];
            EXPECT_EQ(3000, invoice.get_number());
            EXPECT_EQ(20000, invoice.get_consumption());
            EXPECT_EQ(false, invoice.get_paid());
        }
    END

    return 0;
}
