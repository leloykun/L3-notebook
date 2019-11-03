#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct cartree {
  typedef struct _Node {
    long long node_val;
    long long subtree_val;
    long long delta;
    int prio;
    int size;
    _Node *l, *r, *p;

    _Node(long long val) : node_val(val), subtree_val(val), delta(0), prio((rand()<<15)^rand()), size(1), l(NULL), r(NULL), p(NULL) {}
    ~_Node() { delete l; delete r; }

    long long get_subtree_val () {
      return this ? this->subtree_val : 0;
    }

    int get_size() {
      return this ? this->size : 0;
    }

    void apply_delta (long long delta) {
      if (this) {
        this->node_val += delta;
        this->subtree_val += delta * this->size;
        this->delta += delta;
      }
    }

    void push_delta() {
      if (this) {
        this->l->apply_delta(this->delta);
        this->r->apply_delta(this->delta);
        this->delta = 0;
      }
    }

    void update() {
      if (this) {
        this->size = this->l->get_size() + 1 + this->r->get_size();
        this->subtree_val = this->l->get_subtree_val() + this->node_val + this->r->get_subtree_val();
        if (this->l)    this->l->p = this;
        if (this->r)    this->r->p = this;
      }
    }
  } *Node;

  void split(Node v, int key, Node l, Node r) {
    v->push_delta();
    if (key <= v->l->get_size()) {
      split(v->l, key, l, v->l);
      r = v;
    } else {
      split(v->r, key - v->l->get_size() - 1, v->r, r);
      l = v;
    }
    v->update();
  }

  Node merge(Node l, Node r) {
    l->push_delta();
    r->push_delta();
    if (l->prio < r->prio) {
      l->r = merge(l->r, r);
      l->update();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->update();
      return r;
    }
  }

  Node root;
public:
  cartree() : root(NULL) {}
  ~cartree() { delete root; }

  void insert(Node v, int key) {
    Node l, r;
    split(root, key, l, r);
    root = merge(merge(l, v), r);
  }

  void insert(long long val, int key) {
    insert(new _Node(val), key);
  }

  void erase(int key) {
    Node l, m, r;
    split(root, key + 1, m, r);
    split(m, key, l, m);
    delete m;
    root = merge(l, r);
  }

  long long query(int a, int b) {
    Node l1, r1;
    split(root, b + 1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    long long res = r2->get_subtree_val();
    l1 = merge(l2, r2);
    root = merge(l1, r1);
    return res;
  }

  void modify(int a, int b, long long delta) {
    Node l1, r1;
    split(root, b + 1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    r2->apply_delta(delta);
    l1 = merge(l2, r2);
    root = merge(l1, r1);
  }
};

int main() {
  srand((unsigned)time(0));

  int Q = 1000;

  cartree treap;

  for (int q = 0; q < Q; ++q) {

  }

  return 0;
}
