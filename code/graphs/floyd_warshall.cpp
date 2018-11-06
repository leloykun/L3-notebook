void floyd_warshall() {
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (mat[i][k] + mat[k][j] < mat[i][j])
          mat[i][j] = mat[i][k] + mat[k][j];  }
