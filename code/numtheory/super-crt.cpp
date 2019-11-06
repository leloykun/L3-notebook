PAIR super_chinese(LL a[], LL b[], LL m[], int n) {
    PAIR ans(0, 1);
    for (int i = 0; i < n; ++i) {
        PAIR two = modsolver(a[i], b[i], m[i]);
        if (two.second == -1) return two;
        ans = chinese(ans.first, ans.second,
        two.first, two.second);
        if (ans.second == -1) break;
    }
    return ans;
}
