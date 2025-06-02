#include <bit>
#include <random>

struct usr_data {
  char name[13]{};
  char location[15]{};
  unsigned age = 0;
};

int main() {
  std::uint8_t data[sizeof(usr_data)];
  std::mt19937 gen{std::random_device{}()};
  std::uniform_int_distribution<std::uint8_t> dist{0, UINT8_MAX};

  for (auto& d : data) {
    d = dist(gen);
  }

  auto info = std::bit_cast<usr_data>(data);

  std::puts(info.name);
  std::puts(info.location);
  printf("%d\n", info.age);

  return sizeof usr_data{};
}