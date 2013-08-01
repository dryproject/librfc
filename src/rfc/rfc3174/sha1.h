/* This is free and unencumbered software released into the public domain. */

#ifndef RFC3174_SHA1_H
#define RFC3174_SHA1_H

/**
 * @file
 */

#include <cstddef> /* for std::size_t */
#include <cstdint> /* for std::uint8_t */
#include <cstring> /* for std::memcmp(), std::memset() */
#include <utility> /* for std::swap() */

namespace rfc3174 {
  struct sha1;
}

/**
 * Represents a SHA-1 digest.
 */
struct rfc3174::sha1 {
public:
  static constexpr std::size_t size = 20; /* 20 bytes (160 bits) */

  /**
   * Computes the SHA-1 digest of the given NUL-terminated input string.
   */
  static sha1 compute(const char* data) noexcept;

  /**
   * Computes the SHA-1 digest of the given input data.
   */
  static sha1 compute(const std::uint8_t* data, std::size_t size) noexcept;

  /**
   * Default constructor. The structure is all zeroes after construction.
   */
  sha1() noexcept {}

  /**
   * Constructor.
   */
  sha1(const std::uint8_t* const data) noexcept {
    *_data = *data;
  }

  /**
   * Copy constructor.
   */
  sha1(const sha1& other) noexcept {
    *_data = *other._data;
  }

  /**
   * Move constructor.
   */
  sha1(sha1&& other) noexcept {
    std::swap(_data, other._data);
  }

  /**
   * Destructor.
   */
  ~sha1() noexcept {}

  /**
   * Copy assignment operator.
   */
  sha1& operator=(sha1 other) noexcept {
    std::swap(_data, other._data);
    return *this;
  }

  /**
   * Move assignment operator.
   */
  sha1& operator=(sha1&& other) noexcept {
    std::swap(_data, other._data);
    return *this;
  }

  /**
   * Equality operator.
   */
  bool operator==(const sha1& other) const {
    return compare(other) == 0;
  }

  /**
   * Inequality operator.
   */
  bool operator!=(const sha1& other) const {
    return compare(other) != 0;
  }

  /**
   * Less-than operator.
   */
  bool operator<(const sha1& other) const {
    return compare(other) < 0;
  }

  /**
   * Less-than-or-equal-to operator.
   */
  bool operator<=(const sha1& other) const {
    return compare(other) <= 0;
  }

  /**
   * Greater-than operator.
   */
  bool operator>(const sha1& other) const {
    return compare(other) > 0;
  }

  /**
   * Greater-than-or-equal-to operator.
   */
  bool operator>=(const sha1& other) const {
    return compare(other) >= 0;
  }

  /**
   * Returns a reference to the byte at the given position.
   */
  std::uint8_t& operator[](const std::size_t position) noexcept {
    return _data[position];
  }

  /**
   * Returns a reference to the byte at the given position.
   */
  const std::uint8_t& operator[](const std::size_t position) const noexcept {
    return _data[position];
  }

  /**
   * Returns a pointer to the digest data.
   */
  std::uint8_t* data() {
    return _data;
  }

  /**
   * Returns a pointer to the digest data.
   */
  const std::uint8_t* data() const {
    return _data;
  }

  /**
   * Returns a reference to the first byte of the digest data.
   */
  std::uint8_t& front() {
    return operator[](0);
  }

  /**
   * Returns a reference to the first byte of the digest data.
   */
  const std::uint8_t& front() const {
    return operator[](0);
  }

  /**
   * Returns a reference to the last byte of the digest data.
   */
  std::uint8_t& back() {
    return operator[](size - 1);
  }

  /**
   * Returns a reference to the last byte of the digest data.
   */
  const std::uint8_t& back() const {
    return operator[](size - 1);
  }

  /**
   * Compares this digest to the given other digest.
   */
  inline int compare(const sha1& other) const noexcept {
    return std::memcmp(_data, other._data, sizeof(_data));
  }

  /**
   * Clears the digest data to be all zeroes.
   */
  void clear() noexcept {
    std::memset(_data, 0, sizeof(_data));
  }

  /**
   * Exchanges the digest data with the given other digest.
   */
  void swap(sha1& other) noexcept {
    std::swap(_data, other._data);
  }

protected:
  std::uint8_t _data[size] = {};
};

#endif /* RFC3174_SHA1_H */
