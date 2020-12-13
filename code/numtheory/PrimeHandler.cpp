#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
class prime_handler {
  static const LL N = (1<<20);
  static const LL BIG_N = (1LL<<60LL);
  LL mod_mult(LL a, LL b, LL MOD) {
    if(b==0) return 0;
    if(b&1) return (a+mod_mult(a,b-1,MOD))%MOD;
    else return mod_mult((a+a)%MOD,b/2,MOD);
  }
  LL mod_pow(LL base, LL exp, LL MOD) {
    if(exp==0) return 1;
    if(exp&1) return mod_mult(base,mod_pow(base,exp-1,MOD),MOD);
    else return mod_pow(mod_mult(base,base,MOD),exp/2,MOD);
  }
  vector<LL> good_bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  bool sieve[N+1];
  vector<LL> primes;
  //deterministic up to 2^64
  bool witness(LL a,LL n) {
    LL t = 0, u = n-1;
    while(u % 2 == 0) {
      u >>= 1;
      t += 1;
    }
    LL xp = 1, xi = mod_pow(a,u,n);
    for(int i = 0; i < t; i++) {
      xp = xi;
      xi = mod_mult(xi,xi,n);
      if(xi==1 && !(xp == 1 || xp == n-1)) return true ;
    }
    if(xi!=1) return true;
    else return false;
  }
public:
  prime_handler() {
    memset(sieve,true,sizeof sieve);
    sieve[0] = sieve[1] = false;
    for (LL p = 2; p <= N; p++)
      if(sieve[p]) {
        if(p!=2)
          primes.push_back(p);
        for(LL k = p*p; k <=N; k+=p)
          sieve[k] = false;
      }
  }
  bool is_prime(LL n) {
    if(n<=1) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    if(n <= N) return sieve[n];
    for( const LL& x : good_bases) {
      LL a = x;
      a = a%n;
      if(a==0) return true;
      if(witness(a,n)) return false;
    }
    return true;
  }
  LL next_prime(LL n, LL step=1) {
    for(LL x = n; x >= 1; x += step)
      if(is_prime(x))
        return x;
    return -1;
  }
  LL next_prime(double d, LL step=1) {
    return next_prime((LL)(floor(d+1e-7)+(step > 0)),step);
  }
  LL kth_prime(int k) {
    return primes[k-1];
  }
};
prime_handler primo;
int main() {
  int k;
  LL lim = 1e18;
  cin >> k;
  cout << primo.next_prime(pow(lim,1.0/k),-1)<<endl;
  return 0;
}
