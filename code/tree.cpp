#include "tree.h"
#include "settings.h"

Tree::Tree()
{
    start.x = 960 / 2.0f;
    start.y = 500;

    Generate();
}

void Tree::Generate()
{
    branches.clear();

    //for (int i = 0; i < recursionDepth; i++)
    //{
        Branch branch;
        branch.start = start;
        branch.Generate(branches, -90, 100, 0);
        branches.push_back(branch);
    //}
    std::reverse(branches.begin(), branches.end());
}

void Tree::Draw()
{
    for (int i = 0; i < branches.size(); i++)
        vita2d_draw_line(branches[i].start.x, branches[i].start.y, branches[i].end.x, branches[i].end.y, RGBA8(branches[i]._color.r, branches[i]._color.g, branches[i]._color.b, 255));
}

void Branch::Generate(std::vector<Branch> &branches, float angle, float length, int level)
{
    if (level > recursionDepth || length < 5)
        return;

    end.x = start.x + std::cos(angle * 3.14f / 180) * length;
    end.y = start.y + std::sin(angle * 3.14f / 180) * length;

    _color = level < 3 ? color(139, 69, 19) : color(0, 255, 0);

    if (Range(0, 1) > branchProbability)
        return;

    for (int i = 0; i < branchPerNode; i++)
    {
        float branchingPoint = Range(0, 1);
        point newStart = point(start.x + (end.x - start.x) * branchingPoint, start.y + (end.y - start.y) * branchingPoint);
        
        float totalAngleSpread = baseAngle * 2;
        float angleStep = totalAngleSpread / (branchPerNode - 1);
        float newAngle = angle - baseAngle + i * angleStep;

        newAngle += Range(0, 1) * 10 - 5;
        float lengthReduction = Range(0, 1) * 0.2f + 0.6f;

        Branch branch;
        branch.start = newStart;
        branch.Generate(branches, newAngle, length * lengthReduction, level + 1);
        if (branch.end.x != 0 && branch.end.y != 0)
            branches.push_back(branch);
    }
}