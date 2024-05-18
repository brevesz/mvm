#ifndef INVOICE_H
#define INVOICE_H

class Service;

class Invoice {
    int number;
    int consumption;
    Service& service_agreement;
    bool paid;
public:
    Invoice(int n, int c, Service& s, bool p) : number(n), consumption(c), service_agreement(s), payed(p);
    int get_number() {return number;}
    bool get_paid() {return paid;}
    void set_paid(bool tf) {paid = tf;}
    void write_invoice();
};
#endif // INVOICE_H
