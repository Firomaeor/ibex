#ifndef LOCK_H
#define LOCK_H

void lock_amoswap(int *lock);
void unlock_amoswap(int *lock);

void lock_lrsc(int *lock);
void unlock_lrsc(int *lock);

void test_locks(void);

#endif // LOCK_H