#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vi;

//  union-find disjoint set data structure
//  with link-by-size and path compression
struct union_find {
  vi p;	union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)       return false;
    if (p[xp] > p[yp])  swap(xp, yp);
    p[xp] += p[yp];     p[yp] = xp;
    return true;
  }
  int size(int x) { return -p[find(x)]; }
};

//  tests
//
//  Problem: 	BARKADA
//  link:		https://github.com/PSHS-ECHO/NOI-Practice/blob/
//			  	master/Echo/Lessons/Union-Find/BARKADA.pdf
int main() {
  int size, unions, queries;  cin>>size>>unions>>queries;

  union_find uf(size);

  while(unions--) {
    int a, b;	cin>>a>>b;
    uf.unite(a-1, b-1);
  }

  while(queries--) {
    int a, b;	cin>>a>>b;

    if (uf.find(a-1) == uf.find(b-1))
      cout<<"Barkads!"<<endl;
    else
      cout<<"FO"<<endl;
  }

  return 0;
}
