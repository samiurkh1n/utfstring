#include "utfstring.h"

#include <cassert>
#include <string.h>

static const char* empty_c_string = "\0";

static std::string hello_as_cppstr = "hello";
static const char* hello_as_cstr = "hello";

// Checking data about a default constructed string
void TestConstructEmptyString() {
  UTFString s;
  assert(s.length() == 0);
  assert(s.size() == 0);
  assert(s.capacity() == 6);
  assert(s.empty());
    
  assert(!s.is_ascii());
  char s_as_c_str[2];
  s.to_c_str(s_as_c_str, 2);
  assert(!strcmp(s_as_c_str, empty_c_string));
    
  std::string s_as_string = s.to_str();
  assert(s_as_string == "");
}

void TestConstructReservedString() {
  UTFString s(/*size=*/10);
  assert(s.capacity() == 10);

  assert(!s.is_ascii());
  char s_as_c_str[2];
  s.to_c_str(s_as_c_str, 2);
  assert(!strcmp(s_as_c_str, empty_c_string));
}

void TestReserveEmptyString() {
  UTFString s;
  assert(s.capacity() == 6);
  s.reserve(/*size=*/10);
  assert(s.capacity() == 10);

  assert(!s.is_ascii());
  char s_as_c_str[2];
  s.to_c_str(s_as_c_str, 2);
  assert(!strcmp(s_as_c_str, empty_c_string));
}

void TestCopyFromAnotherCppString() {
  UTFString hello_message(hello_as_cppstr);
  assert(!hello_message.empty());
  assert(hello_message.size() == 5);
  assert(hello_message.length() == 5);
  assert(hello_message.capacity() == hello_as_cppstr.size() + 6);
  assert(hello_message.is_ascii());
  std::string hello_message_recovered = hello_message.to_str();
  assert(hello_as_cppstr == hello_message_recovered);
  char hello_message_buffer[6];
  hello_message.to_c_str(hello_message_buffer, 6);
  assert(!strcmp(hello_message_buffer, hello_as_cppstr.c_str()));
}

void TestCopyFromAnotherCString() {
  UTFString hello_message(hello_as_cstr);
  assert(!hello_message.empty());
  assert(hello_message.size() == 5);
  assert(hello_message.length() == 5);
  assert(hello_message.capacity() == strlen(hello_as_cstr) + 6);
  assert(hello_message.is_ascii());
  std::string hello_message_recovered = hello_message.to_str();
  assert(hello_as_cppstr == hello_message_recovered);
  char hello_message_buffer[6];
  hello_message.to_c_str(hello_message_buffer, 6);
  assert(!strcmp(hello_message_buffer, hello_as_cstr));
}

void TestCopyFromAnotherAsciiOnlyUTFString() {
  UTFString hello_message(hello_as_cppstr);
  UTFString another_hello_message(hello_message);
  assert(!another_hello_message.empty());
  assert(another_hello_message.size() == 5);
  assert(another_hello_message.length() == 5);
  assert(another_hello_message.capacity() == hello_as_cppstr.size() + 6);
  assert(another_hello_message.is_ascii());
  std::string another_hello_message_recovered = another_hello_message.to_str();
  assert(hello_as_cppstr == another_hello_message_recovered);
  char another_hello_message_buffer[6];
  another_hello_message.to_c_str(another_hello_message_buffer, 6);
  assert(!strcmp(another_hello_message_buffer, hello_as_cppstr.c_str()));
}

void TestAssignmentFromCppString() {
  UTFString hello_message = hello_as_cppstr;
  assert(!hello_message.empty());
  assert(hello_message.size() == 5);
  assert(hello_message.length() == 5);
  assert(hello_message.capacity() == hello_as_cppstr.size() + 6);
  assert(hello_message.is_ascii());
  std::string hello_message_recovered = hello_message.to_str();
  assert(hello_as_cppstr == hello_message_recovered);
  char hello_message_buffer[6];
  hello_message.to_c_str(hello_message_buffer, 6);
  assert(!strcmp(hello_message_buffer, hello_as_cppstr.c_str()));
}
void TestAssignemntFromCString() {
  UTFString hello_message = hello_as_cstr;
  assert(!hello_message.empty());
  assert(hello_message.size() == 5);
  assert(hello_message.length() == 5);
  assert(hello_message.capacity() == hello_as_cppstr.size() + 6);
  assert(hello_message.is_ascii());
  std::string hello_message_recovered = hello_message.to_str();
  assert(hello_as_cppstr == hello_message_recovered);
  char hello_message_buffer[6];
  hello_message.to_c_str(hello_message_buffer, 6);
  assert(!strcmp(hello_message_buffer, hello_as_cppstr.c_str()));
}

void TestAssignmentFromAsciiOnlyUTFString() {
  UTFString hello_message(hello_as_cppstr);
  UTFString another_hello_message = hello_message;
  assert(!another_hello_message.empty());
  assert(another_hello_message.size() == 5);
  assert(another_hello_message.length() == 5);
  assert(another_hello_message.capacity() == hello_as_cppstr.size() + 6);
  assert(another_hello_message.is_ascii());
  std::string another_hello_message_recovered = another_hello_message.to_str();
  assert(hello_as_cppstr == another_hello_message_recovered);
  char another_hello_message_buffer[6];
  another_hello_message.to_c_str(another_hello_message_buffer, 6);
  assert(!strcmp(another_hello_message_buffer, hello_as_cppstr.c_str()));
}

int main() {
  TestConstructEmptyString();
  TestConstructReservedString();
  TestReserveEmptyString();
  TestCopyFromAnotherCppString();
  TestCopyFromAnotherCString();
  TestCopyFromAnotherAsciiOnlyUTFString();
  TestAssignmentFromCppString();
  TestAssignemntFromCString();
  TestAssignmentFromAsciiOnlyUTFString();
  return 0;
}
