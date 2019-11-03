#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <ctime>
using namespace std;

const int MAX_N = 100001;

struct treap {
  long long node_val;
  long long subtree_val;
  long long delta;
  int size;
  int prio;
  treap *l, *r;
};

treap nodes[MAX_N];
int N = 0;
int rnd[MAX_N];

int get_size(treap *root) {
  return root ? root->size : 0;
}

long long get_subtree_val(treap *root) {
  return root ? root->subtree_val : 0;
}

void update(treap *root) {
  if (root) {
    root->subtree_val = get_subtree_val(root->l) + root->node_val + get_subtree_val(root->r);
    root->size = get_size(root->l) + 1 + get_size(root->r);
  }
}

void apply_delta(treap *root, long long delta) {
  if (root) {
    root->delta += delta;
    root->node_val += delta;
    root->subtree_val += delta * root->size;
  }
}

void push_delta(treap *root) {
  if (root) {
    apply_delta(root->l, root->delta);
    apply_delta(root->r, root->delta);
    root->delta = 0;
  }
}

void merge(treap* &t, treap* l, treap* r) {
  push_delta(l);
  push_delta(r);
  if (!l)
    //  left subtree is NULL
    t = r;
  else if (!r)
    //  right subtree is NULL
    t = l;
  else if (l->prio < r->prio)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  update(t);
}

//  split treap t to treaps l and r on key
void split(treap* t, treap* &l, treap* &r, int key) {
  push_delta(t);
  if (!t)
    l = r = NULL;
  else if (key <= get_size(t->l))
    split(t->l, l, t->l, key), r = t;
  else
    split(t->r, t->r, r, key - get_size(t->l) - 1), l = t;
  update(t);
}

long long get(treap *t, int index) {
  push_delta(t);
  if (index < get_size(t->l))
    return get(t->l, index);
  else if (index > get_size(t->l))
    return get(t->r, index - get_size(t->l) - 1);
  return t->node_val;
}

void insert(treap *&t, treap *item, int index) {
  push_delta(t);
  if (!t)
    t = item;
  else if (item->prio < t->prio)
    split(t, item->l, item->r, index), t = item;
  else if (index <= get_size(t->l))
    insert(t->l, item, index);
  else
    insert(t->r, item, index - get_size(t->l) - 1);
  update(t);
}

void insert(treap *&root, int index, long long val) {
  treap *item = &nodes[N];
  item->node_val = val;
  item->subtree_val = val;
  item->delta = 0;
  item->size = 1;
  item->prio = rnd[N++];
  insert(root, item, index);
}

void remove(treap* &t, int index) {
  push_delta(t);
  if (index == get_size(t->l))
    merge(t, t->l, t->r);
  else if (index < get_size(t->l))
    remove(t->l, index);
  else
    remove(t->r, index - get_size(t->l) - 1);
  update(t);
}

long long query(treap* &root, int a, int b) {
  treap *l1, *r1;
  split(root, l1, r1, b+1);
  treap *l2, *r2;
  split(l1, l2, r2, a);
  long long res = get_subtree_val(r2);
  treap *t;
  merge(t, l2, r2);
  merge(root, t, r1);
  return res;
}

void modify(treap* &root, int a, int b, long long delta) {
  treap *l1, *r1;
  split(root, l1, r1, b+1);
  treap *l2, *r2;
  split(l1, l2, r2, a);
  apply_delta(r2, delta);
  treap *t;
  merge(t, l2, r2);
  merge(root, t, r1);
}

void print(treap *t) {
  if (t) {
    push_delta(t);
    print(t->l);
    cout<<t->node_val<<" ";
    print(t->r);
  }
}

int main() {
  srand((unsigned)time(0));

  for (int i = 0; i < MAX_N; ++i)
    rnd[i] = i;
  random_shuffle(rnd, rnd + MAX_N);

  treap *t = NULL;
  vector<long long> list;

  for (int q = 0; q < 3000; ++q) {
    int type = rand() % 6;
    if (type < 2 && list.size() < 1000) {
      int pos = rand() % (list.size() + 1);
      long long delta = rand() % 100;

      list.insert(list.begin() + pos, delta);

      insert(t, pos, delta);
    } else if (type < 3 && list.size() > 0) {
      int pos = rand() % list.size();

      list.erase(list.begin() + pos);

      remove(t, pos);
    } else if (type < 4 && list.size() > 0) {
      int b = rand() % list.size();
      int a = rand() % (b+1);

      long long res1 = 0;
      for (int i = a; i <= b; ++i)
        res1 += list[i];

      long long res2 = query(t, a, b);

      if (res1 != res2) {
        cout<<a<<" "<<b<<"\n";
        cout<<res1<<" "<<res2<<"\n";
        for(int i = 0; i < list.size(); i++) cout << list[i] << " ";
          cout<<"\n";
        print(t);
        return 0;
      }
    } else if (type < 5 && list.size() > 0) {
      int b = rand() % list.size();
      int a = rand() % (b+1);
      long long delta = rand() % 100;

      for (int i = a; i <= b; ++i)
        list[i] += delta;

      modify(t, a, b, delta);
    } else {
      assert(list.size() == get_size(t));
      for (int i = 0; i < list.size(); ++i) {
        long long res1 = query(t, i, i);
        long long res2 = get(t, i);
        assert(res1 == res2);
      }
    }
  }

  return 0;
}
