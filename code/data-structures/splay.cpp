struct node *null;
struct node {
  node *left, *right, *parent;
  bool reverse; int size, value;
  node*& get(int d) {return d == 0 ? left : right;}
  node(int v=0): reverse(0), size(0), value(v) {
  left = right = parent = null ? null : this;
  }};
struct SplayTree {
  node *root;
  SplayTree(int arr[] = NULL, int n = 0) {
    if (!null) null = new node();
    root = build(arr, n);
  } // build a splay tree based on array values
  node* build(int arr[], int n) {
    if (n == 0) return null;
    int mid = n >> 1;
    node *p = new node(arr ? arr[mid] : 0);
    link(p, build(arr, mid), 0);
    link(p, build(arr? arr+mid+1 : NULL, n-mid-1), 1);
    pull(p); return p;
  } // pull information from children (editable)
  void pull(node *p) {
    p->size = p->left->size + p->right->size + 1;
  } // push down lazy flags to children (editable)
  void push(node *p) {
    if (p != null && p->reverse) {
      swap(p->left, p->right);
      p->left->reverse ^= 1;
      p->right->reverse ^= 1;
      p->reverse ^= 1;
    }} // assign son to be the new child of p
  void link(node *p, node *son, int d) {
    p->get(d) = son;
    son->parent = p; }
  int dir(node *p, node *son) {
    return p->left == son ? 0 : 1;}
  void rotate(node *x, int d) {
    node *y = x->get(d), *z = x->parent;
    link(x, y->get(d ^ 1), d);
    link(y, x, d ^ 1);
    link(z, y, dir(z, x));
    pull(x); pull(y);}
  node* splay(node *p) { // splay node p to root
    while (p->parent != null) {
      node *m = p->parent, *g = m->parent;
      push(g); push(m); push(p);
      int dm = dir(m, p), dg = dir(g, m);
      if (g == null) rotate(m, dm);
      else if (dm == dg) rotate(g, dg), rotate(m, dm);
      else rotate(m, dm), rotate(g, dg);
    } return root = p; }
  node* get(int k) { // get the node at index k
    node *p = root;
    while (push(p), p->left->size != k) {
        if (k < p->left->size) p = p->left;
        else k -= p->left->size + 1, p = p->right;
    }
    return p == null ? null : splay(p);
  } // keep the first k nodes, the rest in r
  void split(node *&r, int k) {
    if (k == 0) {r = root; root = null; return;}
    r = get(k - 1)->right;
    root->right = r->parent = null;
    pull(root); }
  void merge(node *r) { //merge current tree with r
    if (root == null) {root = r; return;}
    link(get(root->size - 1), r, 1);
    pull(root); }
  void assign(int k, int val) { // assign arr[k]= val
    get(k)->value = val; pull(root); }
  void reverse(int L, int R) {// reverse arr[L...R]
    node *m, *r; split(r, R + 1); split(m, L);
    m->reverse ^= 1; push(m); merge(m); merge(r);
  } // insert a new node before the node at index k
  node* insert(int k, int v) {
    node *r; split(r, k);
    node *p = new node(v); p->size = 1;
    link(root, p, 1); merge(r);
    return p; }
  void erase(int k) { // erase node at index k
    node *r, *m;
    split(r, k + 1); split(m, k);
    merge(r); delete m;}
};
