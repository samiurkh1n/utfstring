#ifndef UTF_STRING_H
#define UTF_STRING_H

#include <stddef.h>
#include <string>

class UTFString {
 public:
  UTFString();
  UTFString(std::size_t capacity);
  
  UTFString(const char *other);
  UTFString(const std::string& other);
  UTFString(const UTFString& other);

  UTFString& operator=(const std::string& other);
  UTFString& operator=(const char* other);
  UTFString& operator=(const UTFString& other);

  std::size_t size() const;  // byte usage
  bool empty() const;
  std::size_t length() const;  // number of distinguishable characters
  std::size_t capacity() const;

  void reserve(std::size_t new_size);

  ~UTFString();

  bool is_ascii() const;
  void to_c_str(char *buffer, std::size_t buffer_size) const;
  std::string to_str() const;
  
 private:
  // type is char because it is one byte
  char* byte_array_;

  // Number of bytes allocated to byte_array_
  std::size_t capacity_;

  // Number of UTF/human readable characters
  std::size_t length_;
  
  // Number of bytes *used* in byte_array_ 
  std::size_t size_;
};

#endif  // UTF_STRING_H
