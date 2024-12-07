#include "random.h"

float Range(int start, int end)
{
    return (rand() % (end - start + 1) + start);
}