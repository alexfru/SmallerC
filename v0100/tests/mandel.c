/*
  Generates an image of the Mandelbrot set and saves it as "mandel.ppm".

  Adapted from http://rosettacode.org/wiki/Mandelbrot_set#JavaScript
  Original author unknown (the name must be buried somewhere in the page history).
  GNU Free Documentation License, version 1.2.

  How to compile for DOS (huge/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dosh mandel.c -o mandelh.exe
    smlrcc -dosp mandel.c -o mandelp.exe

  How to compile for Windows:
    smlrcc -win mandel.c -o mandelw.exe

  How to compile for Linux:
    smlrcc -linux mandel.c -o mandell
*/
#include <stdio.h>
#include <math.h>

int mandelIter(double cx, double cy, int maxIter)
{
  double x = 0;
  double y = 0;
  double xx = 0;
  double yy = 0;
  double xy = 0;
  int i = maxIter;
  while (i-- && xx + yy <= 4)
  {
    xy = x * y;
    xx = x * x;
    yy = y * y;
    x = xx - yy + cx;
    y = xy + xy + cy;
  }
  return maxIter - i;
}
 
void mandelbrot(FILE* f,
                int width, int height,
                double xmin, double xmax, double ymin, double ymax,
                int iterations)
{
  int ix, iy;
  for (iy = 0; iy < height; ++iy)
  {
    for (ix = 0; ix < width; ++ix)
    {
      double x = xmin + (xmax - xmin) * ix / (width - 1);
      double y = ymin + (ymax - ymin) * iy / (height - 1);
      int i = mandelIter(x, y, iterations);
      unsigned char pix[3];

      if (i > iterations)
      {
        pix[0] = 0;
        pix[1] = 0;
        pix[2] = 0;
      }
      else
      {
        double c = 3 * log(i) / log(iterations - 1.0);
        if (c < 1)
        {
          pix[0] = 255 * c;
          pix[1] = 0;
          pix[2] = 0;
        }
        else if (c < 2)
        {
          pix[0] = 255;
          pix[1] = 255 * (c - 1);
          pix[2] = 0;
        }
        else
        {
          pix[0] = 255;
          pix[1] = 255;
          pix[2] = 255 * (c - 2);
        }
      }

      fwrite(pix, 1, sizeof pix, f);
    }
  }
}
 
int main(void)
{
  FILE* f = fopen("mandel.ppm", "wb");
  if (f)
  {
    enum
    {
      WIDTH = 640, HEIGHT = 428
//      WIDTH = 800, HEIGHT = 534
//      WIDTH = 900, HEIGHT = 600
    };
    fprintf(f, "P6\n %s\n %d\n %d\n %d\n", "#Mandelbrot Set", WIDTH, HEIGHT, 255);
    mandelbrot(f, WIDTH, HEIGHT, -2, 1, -1, 1, 1000);
    fclose(f);
  }
  return 0;
}
