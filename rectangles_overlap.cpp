#include <algorithm>

struct edge
{
    float begin;
    float end;
    
    edge(float a, float b) : begin{std::min(a, b)}, end{std::max(a, b)} {}
};