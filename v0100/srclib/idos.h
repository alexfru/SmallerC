/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __IDOS_H
#define __IDOS_H
#ifdef _DOS

void __DosGetVect(int, unsigned short*);
void __DosSetVect(int, unsigned short*);

extern unsigned short __Int00DE[2];
//extern unsigned short __Int01DB[2];
//extern unsigned short __Int03BP[2];
extern unsigned short __Int04OF[2];
extern unsigned short __Int06UD[2];

#ifdef __SMALLER_C_16__
void __ExcIsr(void);
void __CtrlCIsr(void);
#endif
#ifdef __HUGE__
void __interrupt __ExcIsr(void);
void __interrupt __CtrlCIsr(void);
#endif

#endif
#endif
