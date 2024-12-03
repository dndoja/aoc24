#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

namespace day_2 {

bool valid_row_(vector<int> row) {
  bool valid = true;
  bool prev_decreasing = row[1] < row[0];
  int prev = row[0];

  for (int i = 1; i < row.size(); i++) {
    int curr = row[i];
    uint diff = abs(curr - prev);
    bool decreasing = prev > curr;
    if (diff < 1 || diff > 3 || decreasing != prev_decreasing) {
      valid = false;
      break;
    }

    prev_decreasing = decreasing;
    prev = curr;
  }

  return valid;
}

uint run_pt1_(int length, vector<int> input[]) {
  int count = 0;

  for (int i = 0; i < length; i++) {
    if (valid_row_(input[i]))
      count++;
  }

  return count;
}

uint run_pt2_(int length, vector<int> input[]) {
  int count = 0;

  for (int i_row = 0; i_row < length; i_row++) {
    vector<int> row = input[i_row];
    bool valid = valid_row_(row);
    int i_ignored = 0;

    while (!valid && i_ignored < row.size()) {
      vector<int> filtered = vector<int>();
      for (int i = 0; i < row.size(); i++) {
        if (i != i_ignored) {
          filtered.push_back(row[i]);
        }
      }

      valid = valid_row_(filtered);
      i_ignored++;
    }

    if (valid) {
      count++;
    }
  }

  return count;
}

int run(vector<string> lines, bool is_part1) {
  uint line_count = lines.size();
  vector<int> rows[line_count];

  for (int i = 0; i < line_count; i++) {
    vector<string> split = utils::split(lines[i], " ");
    vector<int> values = vector<int>();
    for (string s : split) {
      values.push_back(stoi(s));
    }

    rows[i] = values;
  }

  if (is_part1) {
    return run_pt1_(line_count, rows);
  } else {
    return run_pt2_(line_count, rows);
  }
}

} // namespace day_2
