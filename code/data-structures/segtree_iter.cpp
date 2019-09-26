struct segtree {
  int n;
  int *vals;
  segtree(int *ar, int n) {
    this->n = n;
    vals = new int[2*n];
    for (int i = 0; i < n; ++i)
      vals[n+i] = ar[i];
    for (int i = n-1; i > 0; --i)
      vals[i] = vals[i<<1] + vals[i<<1|1];
  }
  void update(int i, int v) {
    for (vals[i += n] = v; i > 1; i >>= 1)
      vals[i>>1] = vals[i] + vals[i^1];
  }
  int query(int l, int r) {
    r++;    // without this, the range is [l,r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1)  res += vals[l++];
      if (r&1)  res += vals[--r];
    }
    return res;
  }
};
