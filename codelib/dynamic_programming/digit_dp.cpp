ll count(int i, int num_non_zero, bool lo) {
  if (dp[i][num_non_zero][lo] != -1)
    return dp[i][num_non_zero][lo];
  if (i == N)
    return num_non_zero <= 3;
  if (num_non_zero > 3)
    return 0;
  ll res = 0;
  for (int d = 0; d <= (lo ? 9 : digits[i]); ++d)
    res += count(i+1, num_non_zero + int(d > 0), lo || (d < digits[i]));
  return dp[i][num_non_zero][lo] = res;
}
