struct cartree {
  typedef struct _Node {
    int node_val, subtree_val, delta, prio, size;
    _Node *l, *r;
    _Node(long long val) : node_val(val), subtree_val(val),
        delta(0), prio((rand()<<16)^rand()), size(1),
        l(NULL), r(NULL) {}
    ~_Node() { delete l; delete r; }
  } *Node;
  int get_subtree_val(Node v) {
    return v ? v->subtree_val : 0;  }
  int get_size(Node v) { return v ? v->size : 0; }
  void apply_delta(Node v, int delta) {
    if (!v) continue;
    v->delta += delta;
    v->node_val += delta;
    v->subtree_val += delta * v->get_size();  }  }
  void push_delta(Node v) {
    if (!v) continue;
    v->l->apply_delta(v->delta);
    v->r->apply_delta(v->delta);
    v->delta = 0;  }
  void update(Node v) {
    if (!v) continue;
    v->subtree_val = v->l->get_subtree_val() + v->node_val
                   + v->r->get_subtree_val();
    v->size = v->l->get_size() + 1 + v->r->get_size(); }
  Node merge(Node l, Node r) {
    l->push_delta();    r->push_delta();
    if (!l || !r)   return l ? l : r;
    if (l->size <= r->size) {
      l->r = merge(l->r, r);
      l->update();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->update();
      return r;  }  }
  void split(Node v, int key, Node &l, Node &r) {
    v->push_delta();
    l = r = NULL;
    if (!v)     return;
    if (key <= v->l->get_size()) {
      split(v->l, key, l, v->l);
      r = v;
    } else {
      split(v->r, key - v->l->get_size() - 1, v->r, r);
      l = v;  }
    v->update();  }
  Node root;
public:
  cartree() : root(NULL) {}
  ~cartree() { delete root; }
  int get(Node v, int key) {
    v->push_delta();
    if (key < v->l->get_size())
      return get(v->l, key);
    else if (key > v->l->get_size())
      return get(v->r, key - v->l->get_size() - 1);
    return v->node_val;  }
  int get(int key) { return get(root, key); }
  void insert(Node item, int key) {
    Node l, r;
    split(root, key, l, r);
    root = merge(merge(l, item), r);  }
  void insert(int key, int val) {
    insert(new _Node(val), key);  }
  void erase(int key) {
    Node l, m, r;
    split(root, key + 1, m, r);
    split(m, key, l, m);
    delete m;
    root = merge(l, r);  }
  long long query(int a, int b) {
    Node l1, r1;
    split(root, b+1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    long long res = r2->get_subtree_val();
    l1 = merge(l2, r2);
    root = merge(l1, r1);
    return res;  }
  long long modify(int a, int b, ll delta) {
    Node l1, r1;
    split(root, b+1, l1, r1);
    Node l2, r2;
    split(l1, a, l2, r2);
    r2->apply_delta(delta);
    merge(l2, r2);
    merge(l1, r1);  }
  int size() { return root->get_size(); }  };
