#ifndef INVOICE_H
#define INVOICE_H

class Service;

class Invoice {
    int number;
    int consumption;
    Service *service_agreement;
    bool paid;
public:
    Invoice () {}
    Invoice(int n, int c, Service *s, bool p) : number(n), consumption(c), service_agreement(s), paid(p) {}
    int get_number() const {return number;}
    int get_consumption() const {return consumption;}
    bool get_paid() const {return paid;}
    void set_paid(bool tf) {paid = tf;}
    void write_invoice();
};
#endif // INVOICE_H
