/*
  SDL clock demo.

  How to compile for Windows:
    smlrcc -win -gui clock.c sdl2mini.c -o clock.exe

  You will need to have SDL2.dll in the current directory or in your PATH.
  You can download SDL2.dll from https://www.libsdl.org/.
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sdl2mini.h"

#define PI 3.1415927
#define CLK_WIDTH 500
#define CLK_HEIGHT 400
#define CTR_X (CLK_WIDTH / 2)
#define CTR_Y (CLK_HEIGHT / 2)
#define SHORT_MARK_LEN (CLK_HEIGHT / 32)

int sdlInitStatus = -1;
SDL_Window* window;
SDL_Renderer* renderer;
int black = 1;

void Mark(int i)
{
  double angle = 2 * PI / 60 * i;
  double c = cos(angle);
  double s = sin(angle);
  double r = CTR_X * CTR_Y / hypot(CTR_X * s, CTR_Y * c);
  double markLen = (i % 5) ? SHORT_MARK_LEN : SHORT_MARK_LEN * 3 / 2;
  double x1 = CTR_X + c * r;
  double y1 = CTR_Y + s * r;
  double x2 = x1 - c * markLen;
  double y2 = y1 - s * markLen;
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Arm(int nom, int den, int excess)
{
  double angle = 2 * PI * (nom - den / 4) / den;
  double c = cos(angle);
  double s = sin(angle);
  double r = CTR_X * CTR_Y / hypot(CTR_X * s, CTR_Y * c);
  double x = CTR_X + c * (r - excess);
  double y = CTR_Y + s * (r - excess);
  SDL_RenderDrawLine(renderer, CTR_X, CTR_Y, x, y);
}

void Render(time_t t)
{
  struct tm tm = *localtime(&t);

  if (black)
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
  else
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  SDL_RenderClear(renderer);

  // dial marks
  if (black)
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0);
  else
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0);
  for (int i = 0; i < 60; i++)
    Mark(i);

  // arms
  if (black)
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0);
  else
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
  Arm(tm.tm_hour * 60 + tm.tm_min, 720, 8 * SHORT_MARK_LEN);
  Arm(tm.tm_min, 60, 3 * SHORT_MARK_LEN);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0);
  Arm(tm.tm_sec, 60, 2 * SHORT_MARK_LEN);

  SDL_RenderPresent(renderer);
}

int main(void)
{
  int status = EXIT_FAILURE;
  int quit = 0;

  if ((sdlInitStatus = SDL_Init(SDL_INIT_EVERYTHING)) != 0)
  {
    goto ldone;
  }

  if ((window = SDL_CreateWindow("Smaller C - SDL Clock",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 CLK_WIDTH,
                                 CLK_HEIGHT,
                                 SDL_WINDOW_SHOWN)) == NULL)
  {
    goto ldone;
  }

  if ((renderer = SDL_CreateRenderer(window,
                                     -1,
                                     0)) == NULL)
  {
    goto ldone;
  }

  while (!quit)
  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
      case SDL_MOUSEBUTTONDOWN:
        // toggle the clock body color between black and white
        black = 1 - black;
        break;
      }
    }

    Render(time(NULL));
    SDL_Delay(250);
  }

  status = 0;

ldone:

  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  if (sdlInitStatus == 0)
    SDL_Quit();
  return status;
}
