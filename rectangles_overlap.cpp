#include <algorithm>

struct edge
{
    float begin;
    float end;
    
    edge(float a, float b) : begin{std::min(a, b)}, end{std::max(a, b)} {}
};

struct rectangle
{
    edge width_;
    edge height_;
    
    rectangle(edge width, edge height) : width_{width}, height_{height} {}
};