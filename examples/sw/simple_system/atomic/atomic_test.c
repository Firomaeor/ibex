// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <stdatomic.h>

#include "simple_system_common.h"
#include "amo.h"
#include "lrsc.h"
#include "stdatomic_test.h"
#include "lock.h"


int main(int argc, char **argv) {
    test_amo();
    puts("\n");
    test_lrsc();
    puts("\n");
    test_stdatomic();
    puts("\n");
    // test_misaligned_load();
}

