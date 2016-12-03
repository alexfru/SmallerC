#include <stdio.h>

int main()
{
   char a;
   short b;

   printf("%d %d\n", (int)sizeof(char), (int)sizeof(a));
   printf("%d %d\n", (int)sizeof(short), (int)sizeof(b));

   return 0;
}

/* vim: set expandtab ts=4 sw=3 sts=3 tw=80 :*/
