#include "utils.h"

namespace utils {
std::vector<std::string> split(std::string str, std::string delimiter) {
  std::vector<std::string> split = std::vector<std::string>();

  if (delimiter.length() == 0) {
    split.push_back(str);
    return split;
  }

  std::string buffer;
  int i = 0;
  while (i < str.length()) {
    char ch = str[i];

    if (ch != delimiter[0]) {
      buffer += ch;
      i++;
      continue;
    }

    std::string lookahead_buf;
    int offset = 0;
    while (offset < delimiter.length()) {
      char ch = str[i + offset];
      if (ch == delimiter[offset]) {
        lookahead_buf += ch;
        offset++;
      } else {
        offset++;
        break;
      }
    }

    if (lookahead_buf.length() == delimiter.length()) {
      if (buffer.length() > 0) {
        split.push_back(buffer);
        buffer = "";
      }
    } else {
      buffer += lookahead_buf;
      buffer += str[i + offset - 1];
    }

    i += offset;
  }

  if (buffer.length() > 0) {
    split.push_back(buffer);
  }

  return split;
}
} // namespace utils
