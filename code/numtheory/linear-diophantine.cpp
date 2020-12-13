PAIR null(-1, -1); // needs extended euclidean
PAIR diophantine(LL a, LL b, LL c) {
    if (!a && !b) return c ? null : PAIR(0, 0);
    if (!a) return c % b ? null : PAIR(0, c / b);
    if (!b) return c % a ? null : PAIR(c / a, 0);
    LL x, y; LL g = extended_euclid(a, b, x, y);
    if (c % g) return null;
    y = mod(y * (c/g), a/g);
    if (y == 0) y += abs(a/g); // prefer positive sol.
    return PAIR((c - b*y)/a, y);
}
