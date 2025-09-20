#include "testlib.h"

#include <cstdio>

xStar::xStar() : blink_count(0) {}

int xStar::blink()
{
    puts("Blink once.");
    blink_count++;

    return blink_count;
}

int xStar::blink(int times)
{
    printf("Blinked %d times again.\n", times);
    blink_count += times;

    return blink_count;
}

int xStar::age() const
{
    return blink_count;
}