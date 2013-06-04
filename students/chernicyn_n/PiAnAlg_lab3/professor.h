#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <iostream>

class Professor
{
public:
    Professor(int transistor, int floor, int crash_floor);
    int make_test(int floor, int divider);
    void print();
private:
    int way_length;
    int new_transistors, discarded_transistors, crash;
    int low,high;
};

#endif // PROFESSOR_H
