#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

std::unique_ptr<std::vector<int>> best_sum(
    int target, std::vector<int> const& v,
    std::unordered_map<int, std::vector<int>>&& m = {}
) {
  if (m.count(target))
    return std::make_unique<std::vector<int>>(m[target]);
  if (!target)
    return std::make_unique<std::vector<int>>();
  if (target < 0)
    return nullptr;

  std::unique_ptr<std::vector<int>> shortest_c{};

  for (int elem : v) {
    if (auto current_c = best_sum(target - elem, v, std::move(m)); current_c) {
      current_c->push_back(elem);
      if (!shortest_c || current_c->size() < shortest_c->size()) {
        shortest_c = std::move(current_c);
      }
    }
  }

  m[target] = *shortest_c;
  return shortest_c;
}

int main() {
  auto v{best_sum(8, {1, 2, 4, 25})};

  if (!v) {
    std::cout << "could not sum up...\n";
    return 0;
  }

  for (int elem : *v)
    std::cout << elem << ' ';

  std::cout << std::endl;
}