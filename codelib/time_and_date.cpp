#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

struct date {
  ll y, m, d, v;

  date(ll _y, ll _m, ll _d) : y(_y), m(_m), d(_d) {
    v = dateToVal(y, m, d);
  }

  ll dateToVal(ll _y, ll _m, ll _d) {
    return 1461 * (_y + 4800 + (_m - 14) / 12) / 4  +
           367 * (_m - 2 - (_m - 14) / 12 * 12) / 12 -
           3 * ((_y + 4900 + (_m - 14) / 12) / 100) / 4  +
           _d - 32075;
  }

  void valToDate(ll _v, ll &_y, ll &_m, ll &_d) {
    ll x, n, i, j;
    x = _v + 68569;
    n = 4 * x / 146097;
    x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447;
    _d = x - 2447 * j / 80;
    x = j / 11;
    _m = j + 2 - 12 * x;
    _y = 100 * (n - 49) + i + x;
  }

  ll operator-(date then) {
    return v - then.v;
  }

  void operator+=(ll days) {
    valToDate(v + days, y, m, d);
  }

  date operator+(ll days) {
    date temp(y, m, d);
    temp += days;
    return temp;
  }

  bool operator==(date then) {
    if (y == then.y && m == then.m && d == then.d)
      return true;
    return false;
  }
};

bool isValidDate(date data) {
  date temp = data;
  temp += 0;
  return temp == data;
}

string mon_string(int m) {
  string mon[] = {"January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"};
  return mon[m-1];
}

string to_string(date data) {
  string temp = mon_string(data.m) + " " + to_string(data.d) + ", " + to_string(data.y);
  return temp;
}

/***********
*  Tests  *
***********
*  Field Tests:				Remarks:
*      NOI PP:	Fridays				OK
*  	UVA:  893: Y3K Problem		OK
* 		    11356: Dates			OK
*
*
**/
int main() {

  //	NOI Practice Page : Fridays
  int N;	cin>>N;

  while(N--) {
    date badDay(2012, 12, 21);
    ll w;	cin>>w;

    badDay += w*7;

    cout<<to_string(badDay)<<endl;
  }
  //

  return 0;
}
