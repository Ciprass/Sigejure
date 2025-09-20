#ifndef TESTLIB_H
#define TESTLIB_H

class xStar
{
    int blink_count;

public:

    xStar();

    int blink();
    int blink(int times);

    int age() const;
};

#endif