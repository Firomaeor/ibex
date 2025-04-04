#include "lock.h"
#include "simple_system_common.h"

void lock_amoswap(int *lock) {
    int tmp;
    do {
        __asm__ volatile("amoswap.w.aq %0, %1, (%2)" 
                            : "=r"(tmp) 
                            : "r"(1), "r"(lock) 
                            : "memory"
                        );
    } while (tmp);
}

void unlock_amoswap(int *lock) {
    __asm__ volatile("amoswap.w.rl zero, zero, (%0)" 
                        : 
                        : "r"(lock) 
                        : "memory"
                    );
}

void lock_lrsc(int *lock) {
    int tmp;
    do {
        __asm__ volatile("lr.w.aq %0, (%1)" 
                            : "=r"(tmp) 
                            : "r"(lock) 
                            : "memory"
                        );
    } while (tmp);
    do {
        __asm__ volatile("sc.w.aqrl %0, %1, (%2)" 
                            : "=r"(tmp) 
                            : "r"(1), "r"(lock) 
                            : "memory"
                        );
    } while (tmp);
}

void unlock_lrsc(int *lock) {
    __asm__ volatile("fence rw, w"); 
    __asm__ volatile("sw zero, 0(%0)" : : "r"(lock) : "memory");
}

void test_locks(void) {
    int lock = 0;

    puts("Testing locks\n");

    puts("Testing amoswap lock\n");

    lock_amoswap(&lock);
    unlock_amoswap(&lock);

    puts("Pass\n");

    puts("Testing lrsc lock\n");

    lock_lrsc(&lock);
    unlock_lrsc(&lock);

    puts("Pass\n");
}