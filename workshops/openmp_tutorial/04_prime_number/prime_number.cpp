#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <string>

using namespace std;

bool is_number(const string& s);
void check_arguments(int n, char* argv[]);
bool is_prime(uint64_t x);
vector<int> find_primes(int n);
void print_primes(vector<int> a);

int main(int argc, char* argv[]) {
   check_arguments(argc, argv);
   //print_primes(find_primes(atoi(argv[1])));
   uint64_t n = strtoull(argv[1], NULL, 10);
   cout << n << endl;
   while (!is_prime(n)) n -= 1;
   cout << n << endl;
   return 0;
}

bool is_number(const string& s) {
   if (!s.empty() && s.find_first_not_of("0123456789") == string::npos) return true;
   else return false;
}

void check_arguments(int n, char* argv[]) {
   if (n != 2 || (n == 2 && !is_number(argv[1]))) {
      cerr << "Requires single integer." << endl;
      exit(1);
   }
}

bool is_prime(uint64_t x) {
   uint64_t m = uint64_t(sqrt(x));
   bool flag = true;
   #pragma omp parallel
   {
      #pragma omp for
      for (uint64_t n = 2; n <= m; n++) {
         if (flag && x % n == 0) {
            #pragma omp critical
		      flag = false;
         }
      }
   }
   return flag;
}

vector<int> find_primes(int n) {
   vector<int> a;
   #pragma omp parallel
   {
      vector<int> a_private;
      #pragma omp for nowait
      for (int i = 2; i <= n; i++) {
         if (is_prime(i)) {
            a_private.push_back(i);
         }
      }
      #pragma omp critical
      a.insert(a.end(), a_private.begin(), a_private.end());
   }
   sort(a.begin(), a.end());
   return a;
}

void print_primes(vector<int> a) {
   cout << "1" << endl;
   copy(a.begin(), a.end(), ostream_iterator<int> (cout, "\n"));
}

