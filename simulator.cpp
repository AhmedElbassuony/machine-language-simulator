#include "machine.h"
int main()
{
    machine s;
    s.take_instructions();
    while (s.make_cycle());
}