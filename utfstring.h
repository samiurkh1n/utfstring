#ifndef UTF_STRING_H
#define UTF_STRING_H

// EXPLORE: string_view

#include <stddef.h>
#include <string>

enum class CharSize { ONE, TWO, FOUR };

class UTFString {
 public:
  UTFString();
  UTFString(std::size_t capacity);
  UTFString(CharSize char_size);
  UTFString(std::size_t capacity, CharSize char_size);
  
  UTFString(const std::string& other);
  UTFString(const char* string);
  const char *to_c_str();  // Warning doesnt make sense
  std::string to_str();

  UTFString(const UTFString& other);
  UTFString& operator=(const UTFString& other);

  ~UTFString();

  char32_t at(std::size_t index) const;
  char32_t operator[](std::size_t index) const;
  char32_t front() const;
  char32_t back() const;
  UTFString substr(std::size_t start_index, std::size_t offset);
  UTFString substr(std::size_t start_index, std::size_t end_index);

  std::size_t size();  // byte usage
  bool empty();
  std::size_t length();  // number of distinguishable characters
  std::size_t capacity();

  void reserve(std::size_t size);
  // maybe add append_with_size()
  void append(const UTFString& other);
  void append(const std::string& other);
  void append(const char* other);
  // TODO: operator& to replace????
  void replace(std::size_t index, const UTFString& replacement);
  void replace(std::size_t index, const std::string& replacement);
  void replace(std::size_t index, const char *replacement);
  void replace(std::size_t index, const char *replacement, std::size_t size);
  void pop();
  
 private:
  void *string_;
  std::size_t size_;
  CharSize char_size_;
};

#endif  // UTF_STRING_H
