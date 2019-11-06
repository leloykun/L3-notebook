typedef long long LL;
typedef pair<LL, LL> PAIR;
LL mod(LL x, LL m) { // use this instead of x % m
    if (m == 0) return 0;
    if (m < 0) m *= -1;
    return (x%m + m) % m; // always nonnegative
}
LL extended_euclid(LL a, LL b, LL &x, LL &y) {
    if (b==0) {x = 1; y = 0; return a;}
    LL g = extended_euclid(b, a%b, x, y);
    LL z = x - a/b*y;
    x = y; y = z; return g;
}
