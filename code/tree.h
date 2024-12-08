#ifndef MYTREE_H
#define MYTREE_H

#include "point.h"
#include "color.h"
#include "random.h"
#include "vita2d.h"
#include "algorithm"
#include <vector>
#include <cmath>

struct Branch
{
    point start = point(0, 0);
    point end = point(0, 0);
    color _color;

    void Generate(std::vector<Branch> &branches, float angle, float length, int level);
};

class Tree
{
public:
    Tree();
    void Generate();
    void Draw();

private:
    point start;
    std::vector<Branch> branches;
};

#endif