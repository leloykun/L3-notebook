#include <iostream>
#include <vector>
#include <utility>

typedef long long ll;

ll fast_inverse(ll base, ll exp, ll mod) {
  ll res = 1;
  while (exp) {
    if (exp & 1)  res = (res * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res % mod;
}

ll mod_inverse(ll x, ll mod) {
  return fast_inverse(x, mod-2, mod);
}

ll chinese_remainder_theorem(std::vector<std::pair<ll, ll>> data) {
  ll M = 1;
  for (int i = 0; i < data.size(); ++i)
    M *= data[i].second;
  ll res = 0;
  for (int i = 0; i < data.size(); ++i) {
    ll Mi = M/data[i].second;
    res = (res + data[i].first * Mi * mod_inverse(Mi, data[i].second)) % M;
  }
  return res;
}

int main() {
  int N;  std::cin>>N;
  std::vector<std::pair<ll, ll> > data;
  for (int i = 0; i < N; ++i) {
    ll c, m;  std::cin>>c>>m;
    data.push_back({c, m});
  }

  std::cout << chinese_remainder_theorem(data) << '\n';

  return 0;
}
