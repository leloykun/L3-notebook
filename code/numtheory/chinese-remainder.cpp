PAIR chinese(LL b1, LL m1, LL b2, LL m2) {
    LL x, y; LL g = extended_euclid(m1, m2, x, y);
    if (b1 % g != b2 % g) return PAIR(-1, -1);
    LL M = abs(m1 / g * m2);
    return PAIR(mod(mod(x*b2*m1+y*b1*m2, M*g)/g,M),M);
}
PAIR chinese_remainder(LL b[], LL m[], int n) {
    PAIR ans(0, 1);
    for (int i = 0; i < n; ++i) {
        ans = chinese(b[i],m[i],ans.first,ans.second);
        if (ans.second == -1) break;
        }
    return ans;
}
