#include "coin.h"

void closest_coin(point a, std::vector<point> coins)
{
    for (auto const& c : coins)
    {
        point b = _closest_coin(a, coins);

        std::erase_if(coins, [&](auto const& c) { return c == b; });

        std::cout << a << " -> " << b << '\n';
        a.move_to(b);
    }
    
    std::cout << '\n';
}

void shortest_path(point a, std::vector<point> coins)
{
    auto coins_{coin_list(coins)};
    
    for (auto const& coin : _shortest_path(a, coins_))
    {
        std::cout << a << " -> " << coin.location() << '\n';
        a.move_to(coin.location());
    }
}

int main()
{
    point a{0, 1};
    std::vector<point> coins{{1, 3}, {2, 0}, {0, 2}, {4, 4}, {0, 0}};

    closest_coin(a, coins);
    shortest_path(a, coins);
}