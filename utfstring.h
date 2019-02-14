#ifndef UTF_STRING_H
#define UTF_STRING_H

#ifdef _WIN32
# ifdef WIN_EXPORT
#  define EXPORTED __declspec( dllexport )
# else
#  define EXPORTED __declspec( dllexport )
# endif
#else
# define EXPORTED
#endif

#include <stddef.h>
#include <string>

enum class char_size { ONE, TWO, FOUR, UNKNOWN };

class UTFString {
 public:
  UTFString();
  UTFString(std::size_t capacity);
  ~UTFString();
  
  UTFString(const char *other);
  UTFString(const std::string& other);
  UTFString(const UTFString& other);

  UTFString& operator=(const std::string& other);
  UTFString& operator=(const char* other);
  UTFString& operator=(const UTFString& other);

  // Metadata accessors
  std::size_t size() const;  // byte usage
  bool empty() const;
  std::size_t length() const;  // number of distinguishable characters
  std::size_t capacity() const;

  // Character accessors
  char32_t operator[](std::size_t index) const;
  char32_t at(std::size_t index) const;
  char32_t front() const;
  char32_t back() const;

  // Memory management
  void reserve(std::size_t new_size);

  // Conversion utilities
  bool is_ascii() const;
  void to_c_str(char *buffer, std::size_t buffer_size) const;
  std::string to_str() const;
  
 private:
  char_size get_UTF_char_size(std::size_t index) const;
  
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
