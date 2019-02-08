#include "utfstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UTFString::UTFString() {
  size_ = 0;
  length_ = 0;
  byte_array_ = (char*)malloc(6 * sizeof(char));
  byte_array_ = 0;
  capacity_ = 6;
}

UTFString::~UTFString() {
  free(byte_array_);
}

std::size_t UTFString::size() const { return size_; }
bool UTFString::empty() const { return length_ == 0; }
std::size_t UTFString::length() const { return length_; }
std::size_t UTFString::capacity() const { return capacity_; }

bool UTFString::is_ascii() const {
  if (empty()) {
    return false;
  }
  for (int i = 0; i < size_; ++i) {
    if ((byte_array_[i] | 127) > 7) {
      return false;
    }
  }
  return true;
}

void UTFString::to_c_str(char* buffer, int buffer_size) const {
  if (!buffer || buffer_size < size_ + 1) {
    *buffer = '\0';
  }
  strncpy(buffer, byte_array_, size_);
  buffer[size_ + 1] = '\0';
}

std::string UTFString::to_str() const {
  return std::string(byte_array_, length_);
}
  
