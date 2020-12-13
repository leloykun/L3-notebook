LL modinv(LL a, LL m) {
    LL x, y; LL g = extended_euclid(a, m, x, y);
    if (g == 1 || g == -1) return mod(x * g, m);
    return 0; // 0 if invalid
}
