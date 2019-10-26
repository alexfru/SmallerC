/*
  This module facilitates importing of selected SDL2.dll functions.
*/

#ifdef _WINDOWS

asm(
" section .dll_import0_sdl2 write align=4\n"
"     extern __start__dll_import2_sdl2\n"
"     extern __start__dll_iat2_sdl2\n"
"     dd __start__dll_import2_sdl2, 0, 0, __sdl2_dll__, __start__dll_iat2_sdl2\n"

// .dll_import2_sdl2 section follows.

" section .dll_import2_sdl2_trailer write align=4\n"
"     dd 0\n"

// .dll_import3_sdl2 section follows.

" section .dll_import4_sdl2 write align=1\n"
"     global __sdl2_dll__\n"
" __sdl2_dll__:\n" // SDL functions will pull this file by this symbol
"     db \"sdl2.dll\", 0\n"

// .dll_iat2_sdl2 section follows.

" section .dll_iat2_sdl2_trailer write align=4\n"
"     dd 0\n"

" section .data\n"
"     extern __dll_imports\n"
"     dd __dll_imports\n" // pull srclib/dimports.c
);

#define DLL "sdl2"

#undef FXN
#define FXN "SDL_Init"
#include "dimports.h"

#undef FXN
#define FXN "SDL_Quit"
#include "dimports.h"

#undef FXN
#define FXN "SDL_CreateWindow"
#include "dimports.h"

#undef FXN
#define FXN "SDL_DestroyWindow"
#include "dimports.h"

#undef FXN
#define FXN "SDL_CreateRenderer"
#include "dimports.h"

#undef FXN
#define FXN "SDL_DestroyRenderer"
#include "dimports.h"

#undef FXN
#define FXN "SDL_RenderClear"
#include "dimports.h"

#undef FXN
#define FXN "SDL_RenderPresent"
#include "dimports.h"

#undef FXN
#define FXN "SDL_SetRenderDrawColor"
#include "dimports.h"

#undef FXN
#define FXN "SDL_RenderDrawPoint"
#include "dimports.h"

#undef FXN
#define FXN "SDL_RenderDrawLine"
#include "dimports.h"

#undef FXN
#define FXN "SDL_PollEvent"
#include "dimports.h"

#undef FXN
#define FXN "SDL_Delay"
#include "dimports.h"

#endif // _WINDOWS
