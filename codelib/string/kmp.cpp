#include <iostream>
#include <string>
#include <vector>

std::vector<int> kmp_prep(std::string &needle) {
  std::vector<int> table(needle.size() + 1, -1);
  for (int i = 1; i <= needle.size(); ++i) {
    int pos = table[i - 1];
    while (pos != -1 and needle[pos] != needle[i - 1])
      pos = table[pos];
    table[i] = pos + 1;
  }
  return table;
}

std::vector<int> kmp_search(std::string &needle, std::string &haystack, std::vector<int> &table) {
  std::vector<int> matches;
  int ni = 0;
  int hi = 0;
  int ns = needle.size();
  int hs = haystack.size();
  while (hi < hs) {
    while (ni != -1 and (ni == ns || needle[ni] != haystack[hi]))
      ni = table[ni];
    ni++;
    hi++;
    if (ni == ns)
      matches.push_back(hi - ni);
  }

  return matches;
}

int main() {

  return 0;
}
