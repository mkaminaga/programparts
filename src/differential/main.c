#include <stdio.h>
#include <math.h>
#include "../../lib/differential.h"

int main() {
   double h = 0;
   double x = 0;

   x = 1.8;

   /* 0.1 */
   h = 0.1;
   printf("h = %2.5lf, f(%2.5lf + %2.5lf) = %10.5lf, f' = %10.5lf\n",
       h, x, h, log(x + h), differential(log, h, x));

   /* 0.01 */
   h = 0.01;
   printf("h = %2.5lf, f(%2.5lf + %2.5lf) = %10.5lf, f' = %10.5lf\n",
       h, x, h, log(x + h), differential(log, h, x));

   /* 0.001 */
   h = 0.001;
   printf("h = %2.5lf, f(%2.5lf + %2.5lf) = %10.5lf, f' = %10.5lf\n",
       h, x, h, log(x + h), differential(log, h, x));

   return 0;
}
