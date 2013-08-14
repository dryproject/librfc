/* This is free and unencumbered software released into the public domain. */

#ifndef RFC_RFC4627_JSON_WRITER_H
#define RFC_RFC4627_JSON_WRITER_H

/**
 * @file
 */

#include <cstdio> /* for FILE */

namespace rfc4627 {
  class json_writer;
}

/**
 * A simple JSON serializer.
 */
class json_writer {
public:
  json_writer(FILE* stream) : _stream(stream) {}

protected:
  inline void write(const int c) {
    fputc(c, _stream);
  }

  inline void write(const char* const s) {
    fputs(s, _stream);
  }

  enum class state {
    none = 0,
  };

private:
  state _state  = state::none;
  FILE* _stream = nullptr;
};

#endif /* RFC_RFC4627_JSON_WRITER_H */
