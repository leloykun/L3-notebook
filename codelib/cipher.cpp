#include <iostream>
#include <string>

char rot(char c, int k) {
  return (c - 'a' + k) % 26 + 'a';
}

std::string cipher_a(std::string s, int key) {
  for (char &c : s)
    if ('a' <= c and c <= 'z')
      c = rot(c, key);
  return s;
}

char xor_c(char c, int key) {
  //std::cout<<c<<" "<<(c - 'a')<<" "<<((c - 'a') ^ key)<<" "<<char(((c - 'a') ^ key) + 'a')<<"\n";
  return ((c - 'a') ^ key) + 'a';
}

std::string cipher_b(std::string s, int key) {
  for (char &c : s)
    if (c != ' ')
      c = xor_c(c, key);
  return s;
}

int main() {
  std::cout<<cipher_a("dear future me", 13)<<"\n";
  for (int k = 1; k <= 10; ++k)
    std::cout<<cipher_b("qwertyuiopasdfghjklzxcvbnm", k)<<"\n";
  std::cout<<cipher_b("when youve already lost all hope", 1)<<"\n";
  std::cout<<cipher_b("just believe in me who believes in you", 1)<<"\n";
  std::cout<<cipher_b("btw are you still with joan", 1)<<"\n";

  return 0;
}
