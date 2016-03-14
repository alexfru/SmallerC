#include <stdio.h>
#include <math.h>

int main()
{
   // variables
   float a = 12.34 + 56.78;
   printf("%g\n", a);

   // infix operators
   printf("%g\n", 12.34 + 56.78);
   printf("%g\n", 12.34 - 56.78);
   printf("%g\n", 12.34 * 56.78);
   printf("%g\n", 12.34 / 56.78);

   // comparison operators
   printf("%d %d %d %d %d %d\n", 12.34 < 56.78, 12.34 <= 56.78, 12.34 == 56.78, 12.34 >= 56.78, 12.34 > 56.78, 12.34 != 56.78);
   printf("%d %d %d %d %d %d\n", 12.34 < 12.34, 12.34 <= 12.34, 12.34 == 12.34, 12.34 >= 12.34, 12.34 > 12.34, 12.34 != 12.34);
   printf("%d %d %d %d %d %d\n", 56.78 < 12.34, 56.78 <= 12.34, 56.78 == 12.34, 56.78 >= 12.34, 56.78 > 12.34, 56.78 != 12.34);

   // assignment operators
   a = 12.34;
   a = a + 56.78; // a += 56.78;
   printf("%g\n", a);

   a = 12.34;
   a = a - 56.78; // a -= 56.78;
   printf("%g\n", a);

   a = 12.34;
   a = a * 56.78; // a *= 56.78;
   printf("%g\n", a);

   a = 12.34;
   a = a / 56.78; // a /= 56.78;
   printf("%g\n", a);

   // prefix operators
   printf("%g\n", +12.34);
   printf("%g\n", -12.34);

   // type coercion
   a = 2;
   printf("%g\n", a);
   printf("%g\n", sin(2));

   return 0;
}

/* vim: set expandtab ts=4 sw=3 sts=3 tw=80 :*/
