#include <iostream>

#define TEST

void tests_main();
void main_menu();

int main() {
#ifdef TEST
    tests_main();
#else
    main_menu();
#endif // TEST
    return 0;
}
