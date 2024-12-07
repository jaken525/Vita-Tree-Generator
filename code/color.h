#ifndef MYCOLOR_H
#define MYCOLOR_H

struct color
{
    int r;
    int g;
    int b;

    color()
    {
        r = 0;
        g = 0;
        b = 0;
    }

    color(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    ~color()
    {}
};

#endif