#include <algorithm>
#include <iostream>
#include <cassert>
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
    _Node *l, *r;

    _Node(long long val) : node_val(val), subtree_val(val), delta(0), prio((rand()<<16)^rand()), size(1), l(NULL), r(NULL) {}
    ~_Node() { delete l; delete r; }

    long long get_subtree_val() {
      return this ? this->subtree_val : 0;
    }

    int get_size() {
      return this ? this->size : 0;
    }

    void apply_delta(long long delta) {
      if (this) {
        this->delta += delta;
        this->node_val += delta;
        this->subtree_val += delta * this->get_size();
      }
    }

    void push_delta() {
      if (this) {
        l->apply_delta(this->delta);
        r->apply_delta(this->delta);
        this->delta = 0;
      }
    }

    void update() {
      if (this) {
        subtree_val = l->get_subtree_val() + this->node_val + r->get_subtree_val();
        size = l->get_size() + 1 + r->get_size();
      }
    }

    void print() {
      if (this) {
        this->push_delta();
        this->l->print();
        cout<<"node_val:"<<this->node_val<<" | ";
        cout<<"subtree_val:"<<this->subtree_val<<" | ";
        cout<<"delta:"<<this->delta<<" | ";
        cout<<"size:"<<this->size<<" | ";
        cout<<"prio:"<<this->prio<<"\n";
        this->r->print();
      }
    }
  } *Node;

  Node merge(Node l, Node r) {
    l->push_delta();
    r->push_delta();
    if (!l || !r)   return l ? l : r;
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

  void split(Node v, int key, Node &l, Node &r) {
    v->push_delta();
    l = r = NULL;
    if (!v)     return;
    if (key <= v->l->get_size()) {
      split(v->l, key, l, v->l);
      r = v;
    } else {
      split(v->r, key - v->l->get_size() - 1, v->r, r);
      l = v;
    }
    v->update();
  }

  Node root;
public:
  cartree() : root(NULL) {}
  ~cartree() { delete root; }

  long long get(Node v, int key) {
    v->push_delta();
    if (key < v->l->get_size())
      return get(v->l, key);
    else if (key > v->l->get_size())
      return get(v->r, key - v->l->get_size() - 1);
    return v->node_val;
  }

  long long get(int key) {
    return get(root, key);
  }

  void insert(Node item, int key) {
    Node l, r;
    split(root, key, l, r);
    root = merge(merge(l, item), r);
  }

  void insert(int key, long long val) {
    insert(new _Node(val), key);
  }

  void erase(int key) {
    Node l, m, r;
    split(root, key + 1, m, r);
    split(m, key, l, m);
    assert(m);
    assert(m->size == 1);
    delete m;
    root = merge(l, r);
  }

  long long query(int a, int b) {
    Node l1, r1;
    split(root, b+1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    long long res = r2->get_subtree_val();
    l1 = merge(l2, r2);
    root = merge(l1, r1);
    return res;
  }

  long long modify(int a, int b, long long delta) {
    Node l1, r1;
    split(root, b+1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    r2->apply_delta(delta);
    merge(l2, r2);
    merge(l1, r1);
  }

  int size() {
    return root->get_size();
  }

  void print() {
    root->print();
  }
};

void test_alone(int times) {
  cartree treap;

  for (int q = 0; q < times; ++q) {
    int type = rand() % 6;
    if (type < 2 && treap.size() < 100000) {
      int pos = rand() % (treap.size() + 1);
      long long val = rand();

      treap.insert(pos, val);
    } else if (type < 3 && treap.size()) {
      int pos = rand() % treap.size();

      treap.erase(pos);
    } else if (type < 4 && treap.size()) {
      int b = rand() % treap.size();
      int a = rand() % (b + 1);

      long long res2 = treap.query(a, b);
    } else if (type < 5 && treap.size()) {
      int b = rand() % treap.size();
      int a = rand() % (b + 1);
      long long delta = rand();

      treap.modify(a, b, delta);
    } /*else {
      for (int i = 0; i < treap.size(); ++i)
      assert(treap.query(i, i) == treap.get(i));
    }*/
  }
}

void test_compare(int times) {
  vector<long long> list;
  cartree treap;

  for (int q = 0; q < times; ++q) {
    int type = rand() % 6;
    if (type < 2 && list.size() < 1000) {
      int pos = rand() % (list.size() + 1);
      long long val = rand();

      list.insert(list.begin() + pos, val);

      treap.insert(pos, val);
    } else if (type < 3 && list.size()) {
      int pos = rand() % list.size();

      list.erase(list.begin() + pos);

      treap.erase(pos);
    } else if (type < 4 && list.size()) {
      int b = rand() % list.size();
      int a = rand() % (b + 1);

      long long res1 = 0;
      for (int i = a; i <= b; ++i)
        res1 += list[i];

      long long res2 = treap.query(a, b);

      assert(res1 == res2);
    } else if (type < 5 && list.size()) {
      int b = rand() % list.size();
      int a = rand() % (b + 1);
      long long delta = rand();

      for (int i = a; i <= b; ++i)
        list[i] += delta;

      treap.modify(a, b, delta);
    } else {
      assert(list.size() == treap.size());
      for (int i = 0; i < list.size(); ++i)
        assert(treap.query(i, i) == treap.get(i));
    }
  }
}

int main() {
  srand((unsigned)time(0));

  //test_alone(1000000);    //3.48333
  test_compare(1000);

  return 0;
}
