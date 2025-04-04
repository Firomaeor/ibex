#ifndef AMO_H
#define AMO_H

int amoadd(int *a, int b);

int amoand(int *a, int b);

int amoor(int *a, int b);

int amoxor(int *a, int b);

int amoswap(int *a, int b);

int amomin(int *a, int b);

int amomax(int *a, int b);

int amominu(int *a, int b);

int amomaxu(int *a, int b);

void test_amo(void);

#endif // AMO_H