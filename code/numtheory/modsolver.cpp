PAIR modsolver(LL a, LL b, LL m) {
    LL x, y; LL g = extended_euclid(a, m, x, y);
    if (b % g != 0) return PAIR(-1, -1);
    return PAIR(mod(x*b/g, m/g), abs(m/g));
}
