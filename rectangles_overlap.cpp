#include <algorithm>
#include <cassert>

struct edge
{
    float begin;
    float end;
    
    edge(float a, float b) : begin{std::min(a, b)}, end{std::max(a, b)} {}
};

struct rectangle
{
    edge width;
    edge height;
    
    rectangle(edge w, edge h) : width{w}, height{h} {}
};

bool edges_overlap(edge a, edge b)
{
    return a.begin <= b.begin ? b.begin <= a.end : a.begin <= b.end;
}

bool rectangles_overlap(rectangle a, rectangle b)
{
    return edges_overlap(a.width, b.width) && edges_overlap(a.height, b.height);
}

int main()
{
    assert(rectangles_overlap({{2, 10}, {2, 5}}, {{4, 16}, {1, 5}}));
}