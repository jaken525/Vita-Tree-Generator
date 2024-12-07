#ifndef MYTREE_H
#define MYTREE_H

#include "point.h"
#include "color.h"
#include "random.h"
#include "vita2d.h"
#include "constants.cpp"
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
    Tree()
    {
        start.x = 960 / 2.0f;
        start.y = 500;

        Generate();
    }

    void Generate();
    void Draw();
    void ChangeValues(int _recursionDepth, float _branchProbability, float _baseAngle, int _branchPerNode)
    {
        recursionDepth = _recursionDepth;
        branchProbability = _branchProbability;
        baseAngle = _baseAngle;
        branchPerNode = _branchPerNode;
    }

private:
    point start;
    std::vector<Branch> branches;
};

#endif