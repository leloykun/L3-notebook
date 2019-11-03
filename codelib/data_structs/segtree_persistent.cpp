#include <iostream>

struct node {
  int l, r;
  int lid, rid;
  int val;
} nodes[2000000];
int node_cnt = 0;

int build (int l, int r, int *ar) {
  if (l > r)  return -1;
  int id = node_cnt++;

  nodes[id].l = l;
  nodes[id].r = r;
  if (l == r) {
    nodes[id].lid = -1;
    nodes[id].rid = -1;
    nodes[id].val = ar[l];
  } else {
    int m = (l + r) / 2;
    nodes[id].lid = build(l, m);
    nodes[id].rid = build(m+1, r);
    nodes[id].val = nodes[nodes[id].lid].val + nodes[nodes[id].rid].val;
  }

  return id;
}

int update(int idx, int delta, int id) {
  if (id == -1)
    return -1;
  if (idx < nodes[id].l or nodes[id].r < idx)
    return id;
  int nid = node_cnt++;
  nodes[nid].l = nodes[id].l;
  nodes[nid].r = nodes[id].r;
  nodes[nid].lid = update(idx, v, nodes[id].lid);
  nodes[nid].rid = update(idx, v, nodes[id].rid);
  nodes[nid].val = nodes[id].val + delta;
  return nid;
}

int query(int id, int l, int r) {
  if (r < nodes[id].l or nodes[id].r < l)
    return 0;
  if (l <= nodes[id].l and nodes[id].r <= r)
    return nodes[id].val;
  return query(nodes[id].l, l, r) + query(nodes[id].r, l, r);
}

int main() {
  int *ar = new int[5];
  ar[0] = 1;
  ar[1] = 5;
  ar[2] = 3;
  ar[3] = 2;
  ar[4] = 4;

  root1 = build(0, 4, ar);
  root2 = update(0, 2, root1);

  return 0;
}
