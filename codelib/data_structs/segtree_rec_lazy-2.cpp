#include <iostream>
using namespace std;

#define ll long long

struct segtree {
  int i, j;
  int val, tempVal;
  segtree *l, *r;
  segtree(ll *a, int _i, int _j) {
    i = _i;
    j = _j;
    tempVal = 0;
    if (i == j) {
      val = a[i];		//  eq to:  val = a[j];
      l = r = NULL;
    } else {
      int k = (i+j) / 2;
      l = new segtree(a, i, k);
      r = new segtree(a, k+1, j);
      val = l->val + r->val;
    }
  }

  void visit() {
    if (tempVal) {
      val += tempVal * (j - i + 1);
      if (l) {
        l->tempVal += tempVal;
        r->tempVal += tempVal;
      }
      tempVal = 0;
    }
  }

  void increase(int _i, int _j, ll val) {
    this->visit();
    if (_i <= i && j <= _j) {
      tempVal += val;
      this->visit();
    } else if (j < _i || _j < i) {
      //  do nothing
    } else {
      l->increase(_i, _j, val);
      r->increase(_i, _j, val);
      this->val = l->val + r->val;
    }
  }

  ll sum(int _i, int _j) {
    this->visit();
    if (_i <= i && j <= _j) {
      return val;
    } else if (j < _i || _j < i) {
      return 0;
    } else {
      return l->sum(_i, _j) + r->sum(_i, _j);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  int n;      cin >> n;
  ll *a = new ll[n];

  for (int i = 0; i < n; i++)
    cin>>a[i];

  segtree *root = new segtree(a, 0, n-1);

  int queries;    cin >> queries;
  while (queries--) {
    string word;  cin >> word;
    // assume zero-indexing
    if (word[0] == 'I') {
      int i, j;   cin>>i>>j;
      ll v;       cin>>v;
      root->increase(i, j, v);
    } else if (word[0] == 'S') {
      int i, j;   cin>>i>>j;
      ll res = root->sum(i, j);
      cout << res << "\n";
    }
  }

  return 0;
}
