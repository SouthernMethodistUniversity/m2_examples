#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

double random_double(void);
double monte_carlo_pi(long long int points);

int main(int argc, char *argv[]) {
  if (argc == 2) {
    printf("%f\n", monte_carlo_pi(atoi(argv[1])));
  }
  else {
    printf("Enter number of points.\n");
  }
  return 0;
}

double random_double(void) {
   double n = rand();
   return n / (double)RAND_MAX;
}

double monte_carlo_pi(long long int points) {
   long long int i, total;
  total = 0;
  #pragma omp parallel
  {
  srand(pow((unsigned int)time(NULL), omp_get_thread_num()));
  #pragma omp for private(i) reduction(+:total)
   for (i = 0; i < points; i++) {
      if (pow(random_double(), 2) + pow(random_double(), 2) < 1) {
         total++;
      }
   }
  }
  printf("%i\n", total);
   return 4 * total / (double)points;
}
