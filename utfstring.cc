#include "utfstring.h"

#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>

char_size UTFString::get_UTF_char_size(std::size_t index) const {
  if ((byte_array_[index] >> 7) == 0) {
    return char_size::ONE;
  } else if ((byte_array_[index] >> 5) == 6) {
    return char_size::TWO;
  } else if ((byte_array_[index] >> 5) == 7) {
    return char_size::FOUR;
  }
  return char_size::UNKNOWN;
}

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

UTFString::~UTFString() {
  free(byte_array_);
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

std::size_t UTFString::size() const { return size_; }
bool UTFString::empty() const { return length_ == 0; }
std::size_t UTFString::length() const { return length_; }
std::size_t UTFString::capacity() const { return capacity_; }

char32_t UTFString::operator[](std::size_t index) const {
  return at(index);
}

char32_t UTFString::at(std::size_t index) const {
  if (index < 0 || index > length_ - 1 || !length_) {
    throw std::out_of_range("index argument: expected to be less than length");
  }
  int current_index = 0;
  char *c = byte_array_;
  char_size c_size = get_UTF_char_size(current_index);
  while (index > 0) {
    c_size = get_UTF_char_size(current_index);
    if (c_size == char_size::ONE) {
      current_index += 1;
    } else if (c_size == char_size::TWO) {
      current_index += 2;
    } else if (c_size == char_size::FOUR) {
      current_index += 4;
    } else {
      throw std::logic_error("underlying data malformed");
    }
    c = &byte_array_[current_index];
    index--;
  }
  char32_t return_character;
  if (mbrtoc32(&return_character, c, 1, nullptr) < 0) {
    throw std::runtime_error("mbrtoc32 failed to convert multibyte string\n");
  }
  return return_character;  
}

char32_t UTFString::front() const {
  return at(0);
}

char32_t UTFString::back() const {
  return at(length_ - 1);
}

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
  
