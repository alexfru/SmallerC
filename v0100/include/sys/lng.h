/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __LNG_H
#define __LNG_H
void __lngFromUnsigned(unsigned short l[2], unsigned n);
void __lngFromSigned(unsigned short l[2], int n);
unsigned __lngToUnsigned(unsigned short l[2]);
int __lngToSigned(unsigned short l[2]);
void __lngAdd(unsigned short acc[2], unsigned short addend[2]);
void __lngSub(unsigned short acc[2], unsigned short subtrahend[2]);
int __lngEq(unsigned short a[2], unsigned short b[2]);
int __lngUnsignedLess(unsigned short a[2], unsigned short b[2]);
int __lngSignedLess(unsigned short a[2], unsigned short b[2]);
int __lngLessThan0(unsigned short l[2]);
#endif
