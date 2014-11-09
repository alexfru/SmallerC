#include <stdio.h>

struct point
{
   int x;
   int y;
};

struct point point_array[100];

int main()
{
   int my_point = 10;

   point_array[my_point].x = 12;
   point_array[my_point].y = 56;

   printf("%d, %d\n", point_array[my_point].x, point_array[my_point].y);

   return 0;
}

/* vim: set expandtab ts=4 sw=3 sts=3 tw=80 :*/
