#include "utfstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UTFString::UTFString() {
  size_ = 0;
  length_ = 0;
  byte_array_ = (char*)calloc(6, sizeof(char));
  capacity_ = 6;
}

UTFString::UTFString(std::size_t capacity) {
  size_ = 0;
  length_ = 0;
  byte_array_ = (char*)calloc(capacity, sizeof(char));
  capacity_ = capacity;
}

UTFString::UTFString(const std::string& other)
  : UTFString{other.c_str()} {}

UTFString::UTFString(const char *other) {
  std::size_t other_size = strlen(other);
  size_ = other_size;
  length_ = size_;
  capacity_ = size_ + 6;
  byte_array_ = (char*)calloc(capacity_, sizeof(char));
  strcpy(byte_array_, other);
}

UTFString::UTFString(const UTFString& other) {
  size_ = other.size_;
  length_ = other.length_;
  capacity_ = other.capacity_;
  byte_array_ = (char*)calloc(capacity_, sizeof(char));
  memcpy(byte_array_, other.byte_array_, capacity_);
}

UTFString& UTFString::operator=(const std::string& other) {
  *this = UTFString(other);
  return *this;
}

UTFString& UTFString::operator=(const char* other) {
  *this = UTFString(other);
  return *this;
}

UTFString& UTFString::operator=(const UTFString& other) {
  if (this != &other) {
    *this = UTFString(other);
  }
  return *this;
}

UTFString::~UTFString() {
  free(byte_array_);
}

std::size_t UTFString::size() const { return size_; }
bool UTFString::empty() const { return length_ == 0; }
std::size_t UTFString::length() const { return length_; }
std::size_t UTFString::capacity() const { return capacity_; }

void UTFString::reserve(std::size_t capacity) {
  char* new_byte_array_ = (char*)calloc(capacity, sizeof(char));
  int count = 0;
  if (capacity >= capacity_) {
    count = capacity_;
  } else {
    count = capacity;
  }
  memcpy(new_byte_array_, byte_array_, count);
  free(byte_array_);
  byte_array_ = new_byte_array_;
  capacity_ = capacity;
}

bool UTFString::is_ascii() const {
  if (empty()) {
    return false;
  }
  for (std::size_t i = 0; i < size_; ++i) {
    if (((char)byte_array_[i] | 0) >> 7) {
      return false;
    }
  }
  return true;
}

void UTFString::to_c_str(char* buffer, std::size_t buffer_size) const {
  if (!buffer || buffer_size < size_ + 1) {
    *buffer = '\0';
  }
  strncpy(buffer, byte_array_, size_);
  buffer[size_ + 1] = '\0';
}

std::string UTFString::to_str() const {
  return std::string(byte_array_, length_);
}
  
