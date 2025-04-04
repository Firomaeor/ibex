#include <stdatomic.h>

#include "simple_system_common.h"

static void assert(int cond) {
    if (cond) {
        puts("Pass\n");
    }
    else {
        puts("Fail\n");
    }
}




void test_stdatomic_amo(void){

    puts("Testing stdatomic.h amo functionality\n");

    int a, b, tmp;

    int fail = 0;

    extern const int test_values[];
    extern const int test_values_size;
    
    for (int i = 0; i < test_values_size; i++) {
        for (int j = 0; j < test_values_size; j++) {
            a = test_values[i];
            b = test_values[j];
            
            
            // atomic_compare_exchange_strong
            tmp = a;
            tmp = atomic_compare_exchange_strong(&a, &tmp, b);
            if (!tmp || a != b) {
                fail = 1;
                puts("atomic_compare_exchange_strong failed\n");
                break;
            }

            
            a = test_values[i];
            tmp = a + 1; // a is not equal to tmp
            tmp = atomic_compare_exchange_strong(&a, &tmp, b);
            // a remains unchanged
            if (tmp || a != test_values[i]) {
                fail = 1;
                puts("atomic_compare_exchange_strong mismatch failed\n");
                break;
            }

            
            // atomic_fetch_add
            a = test_values[i];
            tmp= atomic_fetch_add(&a, b);
            if (tmp != test_values[i] || a != test_values[i] + b) {
                fail = 1;
                puts("atomic_fetch_add failed\n");
                break;
            }


            // atomic_fetch_sub
            a = test_values[i];
            tmp = atomic_fetch_sub(&a, b);
            if (tmp != test_values[i] || a != test_values[i] - b) {
                fail = 1;
                puts("atomic_fetch_sub failed\n");
                break;
            }

            
            // atomic_fetch_or
            a = test_values[i];
            tmp = atomic_fetch_or(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] | b)) {
                fail = 1;
                puts("atomic_fetch_or failed\n");
                break;
            }

            
            // atomic_fetch_xor
            a = test_values[i];
            tmp = atomic_fetch_xor(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] ^ b)) {
                fail = 1;
                puts("atomic_fetch_xor failed\n");
                break;
            }

            
            // atomic_fetch_and
            a = test_values[i];
            tmp = atomic_fetch_and(&a, b);
            if (tmp != test_values[i] || a != (test_values[i] & b)) {
                fail = 1;
                puts("atomic_fetch_and failed\n");
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


void test_stdatomic_flag(void) {

    puts("Testing atomic flag\n");

    atomic_flag flag = ATOMIC_FLAG_INIT;

    assert(!atomic_flag_test_and_set(&flag));
    assert(atomic_flag_test_and_set(&flag));

    atomic_flag_clear(&flag);

    assert(!atomic_flag_test_and_set(&flag));
    assert(atomic_flag_test_and_set(&flag));

}

void test_stdatomic(void) {
    test_stdatomic_amo();
    test_stdatomic_flag();
}