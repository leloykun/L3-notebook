struct hasher {
  std::vector<ll> p1_pow;
  std::vector<ll> p2_pow;
  std::vector<ll> h1_ans;
  std::vector<ll> h2_ans;
  hash(std::vector<int> &s, ll p1, ll p2) {
    p1_pow = std::vector<ll>(MAXN);
    p2_pow = std::vector<ll>(MAXN);

    p1_pow[0] = 1;
    for (int i = 1; i < MAXN; ++i)
      p1_pow[i] = (p1_pow[i-1] * p1) % MOD;
    p2_pow[0] = 1;
    for (int i = 1; i < MAXN; ++i)
      p2_pow[i] = (p2_pow[i-1] * p2) % MOD;
    h1_ans.push_back(0);
    h2_ans.push_back(0);
    for (int i = 0; i < s.size(); ++i) {
      h1_ans.push_back((h1_ans[i] + s[i] * p1_pow[i]) % MOD);
      h2_ans.push_back((h2_ans[i] + s[i] * p2_pow[i]) % MOD);
    }
  }
};
