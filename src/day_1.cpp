#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.h"

using namespace std;

namespace day_1 {

uint run_pt1_(uint length, uint values_l[], uint values_r[]) {
  sort(values_l, values_l + length);
  sort(values_r, values_r + length);

  int diff = 0;
  for (int i = 0; i < length; i++) {
    int l = values_l[i];
    int r = values_r[i];
    diff += abs(r - l);
  }

  return diff;
}

uint run_pt2_(uint length, uint values_l[], uint values_r[]) {
  unordered_map<uint, uint> r_counts = unordered_map<uint, uint>();
  for (int i = 0; i < length; i++) {
    uint val = values_r[i];
    r_counts[val] += 1;
  }

  uint similarity = 0;
  for (int i = 0; i < length; i++) {
    uint val = values_l[i];
    uint count = r_counts[val];
    similarity += val * count;
  }

  return similarity;
}

int run(vector<string> lines, bool is_part1) {
  uint line_count = lines.size();
  uint values_r[line_count];
  uint values_l[line_count];

  for (int i = 0; i < line_count; i++) {
    vector<string> split = utils::split(lines[i], " ");
    values_l[i] = stoi(split[0]);
    values_r[i] = stoi(split[1]);
  }

  if (is_part1) {
    return run_pt1_(line_count, values_l, values_r);
  } else {
    return run_pt2_(line_count, values_l, values_r);
  }
}

} // namespace day_1
