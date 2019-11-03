#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <utility>
#include <map>

typedef std::pair<int, int> ii;

const int MAXN = 1000;
std::string huffman_codes[MAXN];
std::vector<int> adj[MAXN];

std::string seq;

void dfs(int u) {
  if (adj[u].size() == 0) {
    huffman_codes[u] = seq;
  } else {
    seq.push_back('0');
    dfs(adj[u][0]);
    seq.pop_back();

    seq.push_back('1');
    dfs(adj[u][1]);
    seq.pop_back();
  }
}

int main() {
  std::string s;  std::getline(std::cin, s);
  int freq[256];
  memset(freq, 0, sizeof freq);
  for (int i = 0; i < s.length(); ++i)
    freq[s[i]]++;

  std::priority_queue<ii, std::vector<ii>, std::greater<ii> > pq;
  std::string chars = "";
  std::map<char, int> char_to_idx;
  for (int i = 0; i < 256; ++i) {
    if (freq[i]) {
      pq.push({freq[i], chars.size()});
      char_to_idx[char(i)] = chars.size();
      chars.push_back(char(i));
    }
  }

  int N = chars.length();
  int orig_n = N;

  while (pq.size() > 1) {
    ii u = pq.top();    pq.pop();
    ii v = pq.top();    pq.pop();
    adj[N].push_back(u.second);
    adj[N].push_back(v.second);
    pq.push({u.first + v.first, N});
    N++;
  }

  seq = "";
  dfs(N - 1);

  std::cout<<"\nhuffman codes:\n";
  std::printf("char | freq | code\n");
  for (int i = 0; i < orig_n; ++i)
    std::printf("%4c%7d%7s\n", chars[i], freq[chars[i]], huffman_codes[i].c_str());

  std::cout<<"\nencryption of the original text:\n";
  int huffman_length = 0;
  for (char c : s) {
    std::cout<<huffman_codes[char_to_idx[c]];
    huffman_length += huffman_codes[char_to_idx[c]].size();
  }
  std::cout<<"\n";

  std::cout<<"\nlength of encrypted text:\n";
  std::cout<<huffman_length;

  return 0;
}
