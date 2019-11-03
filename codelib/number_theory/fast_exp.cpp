#include <iostream>
using namespace std;

#define ll long long

ll fast_exp(ll base, ll pow, int mod = 1e9+7) {
  ll res = 1;
  while(pow) {
    if (pow&1)
      res = res*base % mod;
    base = base*base % mod;
    pow >>= 1;
  }
  return res % mod;
}

//  tests
int main() {
  cout<<fast_exp(19, 726)<<endl;
  cout<<fast_exp(10898, 22839)<<endl;
  cout<<fast_exp(23456, 98123412, 19)<<endl;
  cout<<fast_exp(123123, 12311, 12217)<<endl;

  cout<<1e18 + 1e18<<endl;

  return 0;
}
