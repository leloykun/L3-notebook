#include <iostream>

const int MAXN = 1e6;
int phi[MAXN];

void phi_sieve() {
  for (int i = 0; i < MAXN; ++i)
    phi[i] = i;
  for (int i = 2; i < MAXN; ++i)
    if (phi[i] == i)
      for (int j = i; j < MAXN; j += i)
        phi[j] = (phi[j]/i) * (i - 1);
}

int main() {
  phi_sieve();

  for (int i = 1; i <= 100; ++i)
    if (i % phi[i] == 0)
      std::cout<<i<<" "<<phi[i]<<"\n";

  return 0;
}
