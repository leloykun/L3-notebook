#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

class cartree {
  typedef struct _Node {
    int x, y, size;
    _Node *l, *r;

    _Node(int _x) : x(_x), y((rand()<<16)^rand()), size(1), l(NULL), r(NULL) {}
    ~_Node() { delete l; delete r; }

    void update() {
      size = 1;
      if (l)  size += l->size;
      if (r)  size += r->size;
    }
  } *Node;

  Node merge(Node l, Node r) {
    if (!l || !r)   return l ? l : r;
    if (l->y < r->y) {
      l->r = merge(l->r, r);
      l->update();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->update();
      return r;
    }
  }

  void split(Node v, int x, Node &l, Node &r) {
    l = r = NULL;
    if (!v) return;
    if (v->x < x) {
      split(v->r, x, v->r, r);
      l = v;
    } else {
      split(v->l, x, l, v->l);
      r = v;
    }
    v->update();
  }

  Node root;
public:
  cartree() : root(NULL) {}
  ~cartree() { delete root; }

  void insert(int x) {
    Node l, r;
    split(root, x, l, r);
    root = merge(merge(l, new _Node(x)), r);
  }

  void erase(int x) {
    Node l, m, r;
    split(root, x, l, m);
    split(m, x+1, m, r);
    assert(m);
    assert(m->size == 1);
    assert(m->x == x);
    delete m;
    root = merge(l, r);
  }

  int size() const { return root? root->size : 0; }
};

const int MAX_N = 100001;

int main() {
  srand((unsigned)time(0));

  set<int> br;
  cartree treap;

  int rnd[MAX_N];
  for (int i = 0; i < MAX_N; ++i)
    rnd[i] = i;
  random_shuffle(rnd, rnd+MAX_N);

  int now = 0;
  vector<bool> rem(MAX_N, false);

  for (int q = 0; q < MAX_N; ++q) {
    int type = rand()%2;
    if (type == 0) {
      int x = rnd[now++];

      br.insert(x);
      treap.insert(x);

      assert(br.size() == treap.size());
    } else if (type == 1 && br.size()) {
      int pos = rand()%now;
      int x = rnd[pos];
      if (rem[pos])   continue;
        rem[pos] = true;

      br.erase(br.find(x));
      treap.erase(x);

      assert(br.size() == treap.size());
    }
  }

  return 0;
}
