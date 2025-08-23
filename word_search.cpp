#include <memory>

bool horizontal_search(
    std::unique_ptr<const char*>& puzzle_ptr, std::uint32_t rows,
    std::uint32_t columns, std::string_view word
) {
  const auto& head = *puzzle_ptr.get();
  for (std::uint32_t r = 0u; r < rows; ++r) {
    const auto start = r * columns;
    std::string_view row_view{head + start, columns};
    if (row_view.contains(word))
      return true;
  }

  return false;
}