/*
  This module facilitates importing of selected SDL2.dll functions.
*/

#ifdef _WINDOWS

asm(
  "section .sdl2_hints_trailer\n"
  "dd 0" // make sure the section isn't empty
);

asm(
  "section .sdl2_iat_trailer\n"
  "dd 0" // make sure the section isn't empty
);

asm(
  "section .dll_imports\n"
  "extern __start__sdl2_hints\n"
  "extern __start__sdl2_iat\n"
  "dd __start__sdl2_hints, 0, 0, __sdl2_dll__, __start__sdl2_iat"
);

static char _sdl2_dll__[] = "SDL2.dll";
extern char _dll_imports;
static char* pimports = &_dll_imports; // pull the header & trailer for the dll imports table (section .dll_imports)

asm(
  "section .sdl2_hints\n"
  "dd _hint_SDL_Init\n"
  "dd _hint_SDL_Quit\n"
  "dd _hint_SDL_CreateWindow\n"
  "dd _hint_SDL_DestroyWindow\n"
  "dd _hint_SDL_CreateRenderer\n"
  "dd _hint_SDL_DestroyRenderer\n"
  "dd _hint_SDL_RenderClear\n"
  "dd _hint_SDL_RenderPresent\n"
  "dd _hint_SDL_SetRenderDrawColor\n"
  "dd _hint_SDL_RenderDrawPoint\n"
  "dd _hint_SDL_RenderDrawLine\n"
  "dd _hint_SDL_PollEvent\n"
  "dd _hint_SDL_Delay\n"
);

// Note that DLL importing gives us pointers to functions.
// SDL2 is compiled using the cdecl calling convention (same as in Smaller C)
// and so we can just use those pointers directly to call SDL functions.

asm(
  "section .sdl2_iat\n"
  "global _SDL_Init\n"
  "_SDL_Init: dd _hint_SDL_Init\n"
  "global _SDL_Quit\n"
  "_SDL_Quit: dd _hint_SDL_Quit\n"
  "global _SDL_CreateWindow\n"
  "_SDL_CreateWindow: dd _hint_SDL_CreateWindow\n"
  "global _SDL_DestroyWindow\n"
  "_SDL_DestroyWindow: dd _hint_SDL_DestroyWindow\n"
  "global _SDL_CreateRenderer\n"
  "_SDL_CreateRenderer: dd _hint_SDL_CreateRenderer\n"
  "global _SDL_DestroyRenderer\n"
  "_SDL_DestroyRenderer: dd _hint_SDL_DestroyRenderer\n"
  "global _SDL_RenderClear\n"
  "_SDL_RenderClear: dd _hint_SDL_RenderClear\n"
  "global _SDL_RenderPresent\n"
  "_SDL_RenderPresent: dd _hint_SDL_RenderPresent\n"
  "global _SDL_SetRenderDrawColor\n"
  "_SDL_SetRenderDrawColor: dd _hint_SDL_SetRenderDrawColor\n"
  "global _SDL_RenderDrawPoint\n"
  "_SDL_RenderDrawPoint: dd _hint_SDL_RenderDrawPoint\n"
  "global _SDL_RenderDrawLine\n"
  "_SDL_RenderDrawLine: dd _hint_SDL_RenderDrawLine\n"
  "global _SDL_PollEvent\n"
  "_SDL_PollEvent: dd _hint_SDL_PollEvent\n"
  "global _SDL_Delay\n"
  "_SDL_Delay: dd _hint_SDL_Delay\n"
);

static char hint_SDL_Init[] = "\0\0SDL_Init";
static char hint_SDL_Quit[] = "\0\0SDL_Quit";
static char hint_SDL_CreateWindow[] = "\0\0SDL_CreateWindow";
static char hint_SDL_DestroyWindow[] = "\0\0SDL_DestroyWindow";
static char hint_SDL_CreateRenderer[] = "\0\0SDL_CreateRenderer";
static char hint_SDL_DestroyRenderer[] = "\0\0SDL_DestroyRenderer";
static char hint_SDL_RenderClear[] = "\0\0SDL_RenderClear";
static char hint_SDL_RenderPresent[] = "\0\0SDL_RenderPresent";
static char hint_SDL_SetRenderDrawColor[] = "\0\0SDL_SetRenderDrawColor";
static char hint_SDL_RenderDrawPoint[] = "\0\0SDL_RenderDrawPoint";
static char hint_SDL_RenderDrawLine[] = "\0\0SDL_RenderDrawLine";
static char hint_SDL_PollEvent[] = "\0\0SDL_PollEvent";
static char hint_SDL_Delay[] = "\0\0SDL_Delay";

#endif // _WINDOWS
