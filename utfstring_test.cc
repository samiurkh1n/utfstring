#include "utfstring.h"

#include <cassert>
#include <string.h>

namespace UTFStringTest {

  static const char* empty_c_string = "\0";
  
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
}

int main() {
  UTFStringTest::TestConstructEmptyString();
  return 0;
}
