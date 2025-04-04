#include "amo.h"
#include "simple_system_common.h"

int amoadd(int *a, int b) {
    int ret;
    __asm__ volatile("amoadd.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amoand(int *a, int b) {
    int ret;
    __asm__ volatile("amoand.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amoor(int *a, int b) {
    int ret;
    __asm__ volatile("amoor.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amoxor(int *a, int b) {
    int ret;
    __asm__ volatile("amoxor.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amoswap(int *a, int b) {
    int ret;
    __asm__ volatile("amoswap.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amomin(int *a, int b) {
    int ret;
    __asm__ volatile("amomin.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amomax(int *a, int b) {
    int ret;
    __asm__ volatile("amomax.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amominu(int *a, int b) {
    int ret;
    __asm__ volatile("amominu.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

int amomaxu(int *a, int b) {
    int ret;
    __asm__ volatile("amomaxu.w %0, %1, (%2)" : "=r"(ret) : "r"(b), "r"(a) : "memory");
    return ret;
}

static void assert(int cond) {
    if (cond) {
        puts("Pass\n");
    }
    else {
        puts("Fail\n");
    }
}


void test_amo(void) {
    puts("Testing atomic memory operations\n");

    int a, b, tmp;

    int fail = 0;

    extern const int test_values[];
    extern const int test_values_size;

    for (int i = 0; i < test_values_size; i++) {
        for (int j = 0; j < test_values_size; j++) {
            a = test_values[i];
            b = test_values[j];

            // amoadd
            tmp = amoadd(&a, b);

            if (tmp != test_values[i] || a != test_values[i] + b) {
                fail = 1;
                break;
            }

            // amoand
            a = test_values[i];
            tmp = amoand(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] & b)) {
                fail = 1;
                break;
            }

            // amoor
            a = test_values[i];
            tmp = amoor(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] | b)) {
                fail = 1;
                break;
            }

            // amoxor
            a = test_values[i];
            tmp = amoxor(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] ^ b)) {
                fail = 1;
                break;
            }

            // amoswap
            a = test_values[i];
            tmp = amoswap(&a, b);
            if (tmp != test_values[i] || a != test_values[j]) {
                fail = 1;
                break;
            }

            // amomin
            a = test_values[i];
            tmp = amomin(&a, b);
            if (tmp != test_values[i] || a != ((test_values[i] < b) ? test_values[i] : b)) {
                fail = 1;
                break;
            }

            // amomax
            a = test_values[i];
            tmp = amomax(&a, b);
            if (tmp != test_values[i] || a != ((test_values[i] > b) ? test_values[i] : b)) {
                fail = 1;
                break;
            }

            // amominu
            a = test_values[i];
            tmp = amominu(&a, b);
            if (tmp != test_values[i] || a != (((unsigned int)test_values[i] < (unsigned int)b) ? test_values[i] : b)) {
                fail = 1;
                break;
            }
            // amomaxu
            a = test_values[i];
            tmp = amomaxu(&a, b);
            if (tmp != test_values[i] || a != (((unsigned int)test_values[i] > (unsigned int)b) ? test_values[i] : b)) {
                fail = 1;
                break;
            }
        }
        if (fail) {
            break;
        }
    }
    if (!fail) {
        puts("All tests passed\n");
        return;
    }
    else {
        puts("Test failed\n");
        return;
    }
}