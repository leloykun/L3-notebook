struct segtree {
  int i, j, val;
  segtree *l, *r;
  segtree(int _i, int _j) : i(_i), j(_j) {}
  segtree(vi &ar, int _i, int _j) : i(_i), j(_j) {
    if (i == j) {
      val = ar[i];
      l = r = NULL;
    } else {
      int k = (i+j) >> 1;
      l = new segtree(ar, i, k);
      r = new segtree(ar, k+1, j);
      val = l->val + r->val;
    }
  }
  segtree* update(int _i, int _val) {
    if (_i <= i and j <= _i) {
      segtree *new_node = new segtree(i, j);
      new_node->l = l;
      new_node->r = r;
      new_node->val = val + _val;
      return new_node;
    } else if (_i < i or j < _i) {
      return this;
    } else {
      segtree *new_node = new segtree(i, j);
      new_node->l = l->update(_i, _val);
      new_node->r = r->update(_i, _val);
      new_node->val = new_node->l->val + new_node->r->val;
      return new_node;
    }
  }
  int query(int _i, int _j) {
    if (_i <= i and j <= _j) {
      return val;
    } else if (_j < i or j < _i) {
      return 0;
    } else {
      return l->query(_i, _j) + r->query(_i, _j);
    }
  }
};
