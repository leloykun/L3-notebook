bool kth_permutation(int arr[], int n, LL k) {
    factoradic(arr, n); // values from 0 to n-1
    for (int i = n-1; i >= 0 && k > 0; --i){
        LL temp = arr[i] + k;
        arr[i] = temp % (n - i);
        k = temp / (n - i);
    }
    permute(arr, n);
    return k == 0; }