#include <bits/stdc++.h>
using namespace std;


/*************
*  Header  *
*************
*
**/
const int    INF = ~(1<<31);
const double EPS = 1e-9;
const double pi  = acos(-1);

typedef long long      ll;
typedef pair<int, int> ii;
typedef vector<int>   vi;
typedef vector<ii>	  vii;
typedef vector<vi>	 vvi;
typedef vector<vii>  vvii;


/*************************
*  Succeesive Squaring  *
*************************
*  in ~ O(log(AB))
*
*  Works if:
*      a, b >= 0
**/
int gcd(int a, int b) {
  return(b==0? a : gcd(b, a%b));
}
ll gcd(ll a, ll b) {
  return(b==0? a : gcd(b, a%b));
}
template<class T> T gcd(T a, T b) {
  return(b==0? a : gcd(b, a%b));
}


/*************************
*  Succeesive Squaring  *
*************************
*	in ~ O(log(p))
*
*  Computes (base^pow) % mod
*  Works if:
*      b, p, m >= 0
**/
ll powmod(ll b, int p, int mod) {
  ll res = 1;
  while(p) {
    if (p&1)
      res = res*b % mod;
    b = b*b % mod;
    p >>= 1;
  }
  return res % mod;
}

template<class Int>
Int powmod(Int b, Int p, Int mod = 0) {
  vector<bool> bits;
  while(p) {
    Int np = p / 2;
    bits.push_back(np+np != p);
    p = np;
  }

  Int res = 1;
  for (int i = bits.size()-1; i >= 0; --i) {
    res *= res;
    if (mod)
      res %= mod;
    if (bits[i]) {
      res *= b;
      if (mod)
        res %= mod;
    }
  }
  return res;
}


/********************
*  Primality Test  *
********************
*	in ~ O(sqrt(n))
*     ~ 11.06 secs  if  n == 1e7
*
*  A very crude primality test
*
*  #include <cmath>
**/
bool isPrime(int n) {
  if (n < 2)
    return false;
  int sq = sqrt(n);
  for (int i = 2; i <= sq; ++i)
    if (!(n%i))
      return false;
  return true;
}

/*  ~ 3 times faster than isPrime()
*	~ 3.75 secs  if  n == 1e7
**/
bool fast_isPrime(int n) {
  if (n < 2)
    return false;
  if (n < 4)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  if (n < 25)
    return true;
  for (int i = 5; i*i <= n; i+= 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  return true;
}

/****************************
*  Sieve of Erathosthenes  *  (with bitmask)
****************************
*	in ~ O(log(log(n)))
*
*  Does some magic:
*  chkC(N) checks if N is NOT prime
*  setC(N) marks     N as NOT prime
**/

/**************************
* Sieve of Erastosthenes * (fast, memory efficient version)
**************************
*  in ~ O(n * log(log(n))) 		(?)
*     ~ 0.6 secs  if  MAX_PRIME = 51_000_000
*
*  Does some magic, after which gP(n) is non-zero iff n is
*  prime. N is the value of the largest prime you will need.
*  Requires N / 16 bytes of memory.
*  WARNING! Only works for odd numbers; deal with even numbers
*  yourself!
*  If that is unacceptable, add "n==2||(n&1)&&" after the
*  first bracket in the gP() macro.
*  #include <string.h>
*  #include <math.h>
**/
#define MAX_PRIME 51000000
unsigned int prime[MAX_PRIME / 64];
#define gP(n) (n==2||(n&1)&&prime[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (prime[n>>6]&=~(1<<((n>>1)&31)))
void fast_sieve() {
  memset( prime, -1, sizeof( prime ) );

  unsigned int i;
  unsigned int sq = ( unsigned int )sqrt( ( double )MAX_PRIME ) + 1;
  for( i = 3; i < sq; i += 2 ) if( gP( i ) ) {
    unsigned int i2 = i + i;
    for( unsigned int j = i * i; j < MAX_PRIME; j += i2 ) rP( j );
  }
}


/*************************************
*  Modified Sieve of Erathosthenes  *
*************************************
*	crude:	~ O(n * sqrt(n))		(?)
*     		~ 0.1 secs  if  MAX_MOD_PRIME = 1_000_000
*  fast:	~ O(n * log(log(n)))
*
*  minfac[N] saves the least factor of N
*  works if:
*      N <= 1000000     (1 million)
**/
#define MAX_MOD_PRIME 1000000
int minfac[MAX_MOD_PRIME + 1];
void mod_sieve() {
  minfac[0] = 0;
  minfac[1] = 1;

  for (int i = sqrt(MAX_MOD_PRIME); i >= 2; --i)
    for (int j = 1; i*j <= MAX_MOD_PRIME; ++j)
  minfac[i*j] = i;
}

/*  REQUIRES: fast_sieve
*/
void mod_fast_sieve() {
  minfac[0] = 0;
  minfac[1] = 1;

  for (int i = sqrt(MAX_MOD_PRIME); i >= 2; --i)
    if (gP(i))
      for (int j = 1; i*j <= MAX_MOD_PRIME; ++j)
  minfac[i*j] = i;
}


/*************
* Factoring *
*************
*  crude:  ~ O(sqrt(n))
*  fast:   ~ O(log(n))
*
*  appends the factors of N to vector V
*
*  #include <cmath>
*  #include <vector>
*  REQUIRES: mod_sieve()		<- fast_factor
**/
void crude_factor(int n, vector<int> &v) {
  int sq = sqrt(n);
  for (int i = 2; i <= sq; ++i) {
    if (n % i)	continue;
    v.push_back(i);
    n /= i--;
    sq = sqrt(n);
  }
  if (n > 1)	v.push_back(n);
}

void fast_factor(int n, vector<int> &v) {
  while(n != 1) {
    v.push_back(minfac[n]);
    n /= minfac[n];
  }
}


/****************************
*  Euler Totient Function  *
****************************
*  as efficient as the factoring algorithm used
*
*  Returns the number of positive integers that are
*  relatively prime to n.
*
*  #include <vector>
*  REQUIRES: crude_factor()
*  REQUIRES: fast_factor()
*  	      mod_sieve()
*/
int phi(int n) {
  vector<int> p;
  fast_factor(n, p);
  for (int i = 0; i < p.size(); ++i) {
    if (i && p[i] == p[i-1]) continue;
    n /= p[i];
    n *= p[i] - 1;
  }
  return n;
}


//  tests
int main() {
  //mod_sieve();
  //fast_sieve();
  //mod_fast_sieve();
  //vector<int> p;
  //fast_factor(72, p);

  //for (int val : p)
  //	cout<<val<<" ";
  //cout<<endl;

  //cout<<phi(80)<<endl;

  cout<<isPrime(50999999)<<endl;
  cout<<isPrime(97)<<endl;

  //for (int i = 50999999; i >= 2; --i) {
  //	if (gP(i)) {
  //		cout<<i<<endl;
  //		break;
  //	}
  //}

  return 0;
}
