#include "egcd"

ll mod_inverse(ll a, ll m) {
  ll x, y;
  ll g = gcde(a, m, &x, &y);
  if (g != 1)
    return -1;
  else
    return (x % m + m) % m;
}
