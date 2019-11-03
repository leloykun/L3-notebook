#include <iostream>
#include <random>
#include <ctime>

struct cartree {
  typedef struct _Node {
    long long val;
    long long delta;
    long long subtree_val;
    int prio;
    int size;
    _Node *l, *r;
    _Node(long long val) {
      this->val = val;
      delta = 0;
      subtree_val = val;
      prio = std::rand();
      size = 1;
    }
    ~_Node() { delete l; delete r; }
  } *Node;

  long long get_subtree_val(Node v) {
    return v ? v->subtree_val : 0;
  }

  int get_size(Node v) {
    return v ? v->size : 0;
  }

  void pull(Node v) {
    if (!v) return;
    v->subtree_val = get_subtree_val(v->l) + v->val + get_subtree_val(v->r);
    v->size = get_size(v->l) + 1 + get_size(v->r);
  }

  void push(Node v) {
    if (!v) return;
    if (v->delta) {
      v->val += v->delta;
      v->subtree_val += v->delta * v->size;
      if (v->l) {
        v->l->delta += v->delta;
        v->r->delta += v->delta;
      }
      v->delta = 0;
    }
  }

  Node merge(Node l, Node r) {
    push(l);
    push(r);
    if (!l or !r) return l ? l : r;
    if (l->prio < r->prio) {
      l->r = merge(l->r, r);
      pull(l);
      return l;
    } else {
      r->l = merge(l, r->l);
      pull(r);
      return r;
    }
  }

  void split(Node v, int key, Node &l, Node &r) {
    push(v);
    l = r = NULL;
    if (!v) return;
    if (key <= get_size(v->l)) {
      split(v->l, key, l, v->l);
      r = v;
      pull(r);
    } else {
      split(v->r, key - get_size(v->l) - 1, v->r, r);
      l = v;
      pull(l);
    }
  }

  Node root;
  cartree() : root(NULL) {}
  ~cartree() { delte root; }

  void insert(Node v, int key) {
    Node l, r;
    split(root, key, l, r);
    root = merge(merge(l, v), r);

  }

  void insert(long long val, int key) {
    insert(new _Node(val), key);
  }
};

int main() {

  return 0;
}
