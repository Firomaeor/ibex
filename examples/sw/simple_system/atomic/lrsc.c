#include "lrsc.h"
#include "simple_system_common.h"

int load_reserved(int *addr) {
    int ret;
    __asm__ volatile("lr.w %0, (%1)" : "=r"(ret) : "r"(addr) : "memory");
    return ret;
}

int store_conditional(int *addr, int val) {
    int ret;
    __asm__ volatile("sc.w %0, %1, (%2)" : "=r"(ret) : "r"(val), "r"(addr) : "memory");
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

void test_lrsc(void) {

    int a, b, lr, sc;


    puts("Testing lr/sc\n");

    puts("lr correctly loads from memory\n");
    
    a = 1;
    
    lr = load_reserved(&a);
    
    assert(lr == 1);
    puts("Successful sc\n");

    sc = store_conditional(&a, 2);

    assert(sc == 0 && a == 2);

    puts("Successful sc cancels reservation\n");

    sc = store_conditional(&a, 3);

    assert(sc == 1 && a == 2);

    puts("Failed sc to address not in reservation set\n");

    lr = load_reserved(&a);
    b = 1;
    sc = store_conditional(&b, 2);

    assert(sc == 1 && b == 1);

    puts("Failed sc cancels reservation\n");

    sc = store_conditional(&a, 2);
    assert(sc == 1 && a == 2);

    puts("Regular store doesn't cancel reservation\n");

    lr = load_reserved(&a);
    a = 0;
    sc = store_conditional(&a, 2);

    assert(sc == 0 && a == 2);
}

void test_misaligned_load(void) {

    puts("Testing misaligned load\n");
    puts("This throws an exception\n");

    int a = 1;
    int *b = &a;

    b = (int*)((int)b + 1);

    load_reserved(b);
}