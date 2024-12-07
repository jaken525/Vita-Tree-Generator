#ifndef MYPOINT_H
#define MYPOINT_H

struct point
{
    float x;
    float y;

    point()
    {
        x = 0;
        y = 0;
    }

    ~point()
    {}

    point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif