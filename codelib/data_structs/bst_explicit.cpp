#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
  int key;
  struct node *left, *right;

  node(int _key) : key(_key), left(NULL), right(NULL) {}
};

node* insert(node* now, int key) {
  if (now == NULL)
    return new node(key);
  if (key < now->key)
    now->left = insert(now->left, key);
  else
    now->right = insert(now->right, key);
  return now;
}

node* search(node* now, int key) {
  if (now == NULL || now->key == key)
    return now;
  else if (now->key > key)
    return search(now->left, key);
  else
    return search(now->right, key);
}

void print(node *now) {
  if (now != NULL) {
    print(now->left);
    cout<<now->key<<"\n";
    print(now->right);
  }
}

int main() {

  node *root = new node(30);
  root = insert(root, 40);

  print(root);

  node *now = search(root, 40);
  print(now);

  return 0;
}
