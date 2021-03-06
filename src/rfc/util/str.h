/* This is free and unencumbered software released into the public domain. */

#ifndef RFC_UTIL_STR_H
#define RFC_UTIL_STR_H

/**
 * @file
 */

#include <cctype>    /* for std::is*() */
#include <cstddef>   /* for std::size_t */
#include <cstring>   /* for std::mem*(), std::str*() */
#include <stdexcept> /* for std::out_of_range */
#include <string>    /* for std::string */

namespace rfc {
  class str;
}

/**
 * C string wrapper class.
 *
 * @note Instances of this class are movable, but not copyable.
 */
class rfc::str {
  char* _data = nullptr;

public:
  /**
   * Maximum value for `std::size_t`.
   */
  static constexpr std::size_t npos = static_cast<std::size_t>(-1);

  /**
   * Default constructor.
   */
  str() noexcept {}

  /**
   * Constructor.
   */
  explicit str(const std::string& string) noexcept
    : _data(const_cast<char*>(string.data())) {}

  /**
   * Constructor.
   */
  explicit str(char* data) noexcept
    : _data(data) {}

  /**
   * Constructor.
   */
  explicit str(const char* data) noexcept
    : _data(const_cast<char*>(data)) {}

  /**
   * Copy constructor.
   */
  str(const str& other) noexcept = delete;

  /**
   * Move constructor.
   */
  str(str&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~str() noexcept = default;

  /**
   * Copy assignment operator.
   */
  str& operator=(const str& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  str& operator=(str&& other) noexcept = default;

  /**
   * @name Iterators
   */

  /**@{*/

  /**
   * Returns a const-qualified iterator to the beginning of this string.
   */
  const char* cbegin() const noexcept {
    return begin();
  }

  /**
   * Returns a const-qualified iterator to the end of this string.
   */
  const char* cend() const noexcept {
    return end();
  }

  /**
   * Returns an iterator to the beginning of this string.
   */
  char* begin() noexcept {
    return _data;
  }

  /**
   * Returns a const-qualified iterator to the beginning of this string.
   */
  const char* begin() const noexcept {
    return _data;
  }

  /**
   * Returns an iterator to the end of this string.
   */
  char* end() noexcept {
    return _data + size();
  }

  /**
   * Returns a const-qualified iterator to the end of this string.
   */
  const char* end() const noexcept {
    return _data + size();
  }

  /**@}*/

  /**
   * @name Capacity
   */

  /**@{*/

  /**
   * Tests whether this string is empty.
   *
   * The string is empty in case the data pointer is `nullptr` or the first
   * character of the string is NUL.
   */
  bool empty() const noexcept {
    return _data == nullptr || _data[0] == '\0';
  }

  /**
   * Clears this string by resetting the data pointer to `nullptr`.
   */
  void clear() noexcept {
    _data = nullptr;
  }

  /**
   * Returns the byte length of this string.
   */
  std::size_t length() const noexcept {
    return size();
  }

  /**
   * Returns the byte length of this string.
   */
  std::size_t size() const noexcept {
    return _data ? std::strlen(_data) : 0;
  }

  /**@}*/

  /**
   * @name Element access
   */

  /**@{*/

  /**
   * Alias for `data()`.
   */
  const char* c_str() const noexcept {
    return _data;
  }

  /**
   * Returns a pointer to the underlying C string data.
   */
  const char* data() const noexcept {
    return _data;
  }

  /**
   * ...
   */
  char& operator[](std::size_t pos) noexcept {
    return _data[pos];
  }

  /**
   * ...
   */
  const char& operator[](std::size_t pos) const noexcept {
    return _data[pos];
  }

  /**
   * @throws std::out_of_range if `pos` >= `size()`
   */
  char& at(std::size_t pos) {
    if (pos >= size()) throw std::out_of_range("pos >= size()");
    return _data[pos];
  }

  /**
   * @throws std::out_of_range if `pos` >= `size()`
   */
  const char& at(std::size_t pos) const {
    if (pos >= size()) throw std::out_of_range("pos >= size()");
    return _data[pos];
  }

  /**
   * ...
   */
  char& back() noexcept {
    return _data[size() - 1];
  }

  /**
   * ...
   */
  const char& back() const noexcept {
    return _data[size() - 1];
  }

  /**
   * ...
   */
  char& front() noexcept {
    return _data[0];
  }

  /**
   * ...
   */
  const char& front() const noexcept {
    return _data[0];
  }

  /**@}*/

  /**
   * @name Mutative operations
   */

  /**@{*/

  /**
   * Erases the last character of this string.
   */
  void pop_back() noexcept {
    _data[size() - 1] = '\0';
  }

  /**@}*/

  /**
   * @name String operations
   */

  /**@{*/

  /**
   * Compares this string to another sequence of characters.
   */
  int compare(const std::string& other) const noexcept {
    return compare(other.data());
  }

  /**
   * Compares this string to another sequence of characters.
   */
  int compare(const str& other) const noexcept {
    return compare(other.data());
  }

  /**
   * Compares this string to another sequence of characters.
   */
  int compare(const char* other) const noexcept {
    return std::strcmp(_data, other);
  }

  /**
   * Copies a sequence of characters into a given buffer.
   */
  void copy(char* target, std::size_t length, std::size_t pos = 0) const {
    std::strncpy(target, _data + pos, length);
  }

  bool equal(const std::string& other) const noexcept {
    return compare(other) == 0;
  }

  bool equal(const str& other) const noexcept {
    return compare(other) == 0;
  }

  bool equal(const char* other) const noexcept {
    return compare(other) == 0;
  }

  /**
   * Finds the first occurrence of the given character.
   */
  std::size_t find(char c, std::size_t pos = 0) const noexcept {
    const char* const found = std::strchr(_data + pos, c);
    return found ? found - _data : npos;
  }

  /**
   * Finds the first occurrence of the given string.
   */
  std::size_t find(const char* s, std::size_t pos = 0) const noexcept {
    const char* const found = std::strstr(_data + pos, s);
    return found ? found - _data : npos;
  }

  /**
   * Finds the last occurrence of the given character.
   */
  std::size_t rfind(char c, std::size_t pos = 0) const noexcept {
    const char* const found = std::strrchr(_data + pos, c);
    return found ? found - _data : npos;
  }

  /**
   * Returns a substring of this string.
   */
  str substr(std::size_t pos) const noexcept {
    return str(_data + pos);
  }

  /**
   * Returns a substring of this string.
   */
  str substr_from(char c) const noexcept {
    const auto pos = find(c);
    return (pos != npos) ? str(_data + pos) : str();
  }

  /**
   * Returns a substring of this string.
   */
  str substr_after(char c) const noexcept {
    const auto pos = find(c);
    return (pos != npos) ? str(_data + pos + 1) : str();
  }

  /**@}*/

  /**
   * @name Predicates
   */

  /**@{*/

  bool has_prefix(const char* prefix) const noexcept {
    return prefix && (find(prefix) == 0);
  }

  bool has_suffix(const char* suffix) const noexcept {
    const auto string_size = size();
    const auto suffix_size = suffix ? std::strlen(suffix) : 0;
    return suffix && (string_size >= suffix_size) &&
      (strcmp(_data + string_size - suffix_size, suffix) == 0);
  }

  bool is(int (*predicate)(const int chr)) const noexcept {
    const char* s = _data;
    while (*s != '\0') {
      if (!predicate(*s)) {
        return false;
      }
      s++; /* ASCII only */
    }
    return true;
  }

  bool is_alnum() const noexcept {
    return is(isalnum);
  }

  bool is_alpha() const noexcept {
    return is(isalpha);
  }

  bool is_ascii() const noexcept {
    return is(isascii);
  }

  bool is_blank() const noexcept {
    return is(isblank);
  }

  bool is_cntrl() const noexcept {
    return is(iscntrl);
  }

  bool is_digit() const noexcept {
    return is(isdigit);
  }

  bool is_graph() const noexcept {
    return is(isgraph);
  }

  bool is_lower() const noexcept {
    return is(islower);
  }

  bool is_print() const noexcept {
    return is(isprint);
  }

  bool is_punct() const noexcept {
    return is(ispunct);
  }

  bool is_space() const noexcept {
    return is(isspace);
  }

  bool is_upper() const noexcept {
    return is(isupper);
  }

  bool is_xdigit() const noexcept {
    return is(isxdigit);
  }

  /**@}*/
};

#endif /* RFC_UTIL_STR_H */
