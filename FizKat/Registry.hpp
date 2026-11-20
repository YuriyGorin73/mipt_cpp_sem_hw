#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <cstddef>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

template <typename T, int Capacity>
class Registry {
 private:
  std::vector<T> values;

 public:
  Registry() {
    values.reserve(Capacity);
  }

  bool add(T value) {
    if (values.size() >= static_cast<std::size_t>(Capacity)) {
      return false;
    }

    values.push_back(std::move(value));
    return true;
  }

  bool contains(const T& value) const {
    for (const T& current : values) {
      if (current == value) {
        return true;
      }
    }
    return false;
  }

  std::size_t size() const {
    return values.size();
  }

  T& operator[](std::size_t index) {
    return values[index];
  }

  const T& operator[](std::size_t index) const {
    return values[index];
  }

  void eraseAt(std::size_t index) {
    if (index < values.size()) {
      values.erase(values.begin() + static_cast<std::ptrdiff_t>(index));
    }
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const Registry<T, Capacity>& registry) {
    for (std::size_t i = 0; i < registry.size(); ++i) {
      out << registry[i];
      if (i + 1 < registry.size()) {
        out << '\n';
      }
    }
    return out;
  }
};

// Для строкового журнала проверяется, что номер еще не добавляли.
template <>
inline bool Registry<std::string, 100>::add(std::string value) {
  if (values.size() >= 100 || contains(value)) {
    return false;
  }

  values.push_back(std::move(value));
  return true;
}

#endif
