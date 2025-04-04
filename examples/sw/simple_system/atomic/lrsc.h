#ifndef LRSC_H
#define LRSC_H

int load_reserved(int *addr);

int store_conditional(int *addr, int val);

void test_lrsc(void);

void test_misaligned_load(void);

#endif // LRSC_H