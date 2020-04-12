#include <iostream>
#include <vector>
#include <string>

const int MAX_KIDS = 2;
const char BASE = '0';  // 'a' or 'A'

struct trie {
  int val, cnt;
  std::vector<trie*> kids;
  trie () : val(-1), cnt(0), kids(MAX_KIDS, NULL) {}
  trie (int val) : val(val), cnt(0), kids(MAX_KIDS, NULL) {}
  trie (int val, int cnt, std::vector<trie*> n_kids) :
    val(val), cnt(cnt), kids(n_kids) {}
  trie *insert(std::string &s, int i, int n) {
    trie *n_node = new trie(val, cnt+1, kids);
    if (i == n) return n_node;
    if (!n_node->kids[s[i] - BASE])
      n_node->kids[s[i] - BASE] = new trie(s[i]);
    n_node->kids[s[i] - BASE] = n_node->kids[s[i] - BASE]->insert(s, i+1, n);
    return n_node;
  }
  void print(int dep) {
    std::cout << dep << " | " << char(val) << " | " << cnt << "\n";
    for (int i = 0; i < MAX_KIDS; ++i)
      if (kids[i])
        kids[i]->print(dep+1);
  }
};

int main() {
  trie *root1 = new trie();
  std::string s1 = "01010";
  trie *root2 = root1->insert(s1, 0, 5);
  std::string s2 = "01011";
  trie *root3 = root2->insert(s2, 0, 5);
  std::string s3 = "0101100";
  trie *root4 = root3->insert(s3, 0, 7);
  std::string s4 = "0101001";
  trie *root5 = root4->insert(s4, 0, 7);

  root1->print(0);
  std::cout << "----\n";
  root2->print(0);
  std::cout << "----\n";
  root3->print(0);
  std::cout << "----\n";
  root4->print(0);
  std::cout << "----\n";
  root5->print(0);


  return 0;
}
