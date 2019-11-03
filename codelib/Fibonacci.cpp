#include <utility>
#include <iostream>
using namespace std;

#define MP(a, b) make_pair((a), (b))
typedef long long ll;

pair<ll, ll> fast_fib(ll n, ll mod) {
  if (n == 0)
    return MP(0, 1);
  else {
    pair<int, int> temp = fast_fib(n/2, mod);
    ll a = temp.first;
    ll b = temp.second;

    ll c = a * (2*b - a) % mod;
    ll d = (a*a + b*b) % mod;

    if (n % 2 == 0)
      return MP(c, d);
    else
      return MP(d, c+d);
  }
}

int main() {

  ll n, m;

  while(cin>>n>>m) {
    /*if (n == 0)
    cout<<0<<endl;
    else if (n == 1)
    cout<<1<<endl;
    else*/
    cout<<fast_fib(n, 1<<m).first<<endl;
  }

  return 0;
}
