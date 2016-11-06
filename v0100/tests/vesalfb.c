/*
  How to compile for DOS (unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dosu vesalfb.c -o vesalfbu.exe
    smlrcc -dosp vesalfb.c -o vesalfbp.exe
*/
#ifndef _DPMI
#ifndef __UNREAL__
#error Must be compiled as a DOS/Unreal or DOS/DPMI program
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

#ifdef _DPMI
typedef struct
{
  unsigned long  edi;
  unsigned long  esi;
  unsigned long  ebp;
  unsigned long  resrvd;
  unsigned long  ebx;
  unsigned long  edx;
  unsigned long  ecx;
  unsigned long  eax;
  unsigned short flags;
  unsigned short es;
  unsigned short ds;
  unsigned short fs;
  unsigned short gs;
  unsigned short ip;
  unsigned short cs;
  unsigned short sp;
  unsigned short ss;
} __dpmi_int_regs;

// 48KB buffer below 1MB mark
// (the library overwrites it when using BIOS/DOS interrupts for I/O,
// but it's available otherwise)
extern void* __dpmi_iobuf;

int __dpmi_int(int, __dpmi_int_regs*);
#endif

#pragma pack(push, 1)

typedef struct
{
  uint8 VbeSignature[4]; // 'VESA' VBE Signature
  uint16 VbeVersion; // 0300h VBE Version
  uint32 OemStringPtr; // VbeFarPtr to OEM String
  uint8 Capabilities[4]; // Capabilities of graphics controller
  uint32 VideoModePtr; // VbeFarPtr to VideoModeList
  uint16 TotalMemory; // Number of 64kb memory blocks  
  // Added for VBE 2.0+
  uint16 OemSoftwareRev; // VBE implementation Software revision
  uint32 OemVendorNamePtr; // VbeFarPtr to Vendor Name String
  uint32 OemProductNamePtr; // VbeFarPtr to Product Name String
  uint32 OemProductRevPtr; // VbeFarPtr to Product Revision String
  uint8 Reserved[222]; // Reserved for VBE implementation scratch
  // area
  uint8 OemData[256]; // Data Area for OEM Strings
} tVbeInfo;

typedef struct
{
  // Mandatory information for all VBE revisions
  uint16 ModeAttributes; // mode attributes
  uint8 WinAAttributes; // window A attributes
  uint8 WinBAttributes; // window B attributes
  uint16 WinGranularity; // window granularity
  uint16 WinSize; // window size
  uint16 WinASegment; // window A start segment
  uint16 WinBSegment; // window B start segment
  uint32 WinFuncPtr; // real mode pointer to window function
  uint16 BytesPerScanLine; // bytes per scan line
  // Mandatory information for VBE 1.2 and above
  uint16 XResolution; // horizontal resolution in pixels or characters
  uint16 YResolution; // vertical resolution in pixels or characters
  uint8 XCharSize; // character cell width in pixels
  uint8 YCharSize; // character cell height in pixels
  uint8 NumberOfPlanes; // number of memory planes
  uint8 BitsPerPixel; // bits per pixel
  uint8 NumberOfBanks; // number of banks
  uint8 MemoryModel; // memory model type
  uint8 BankSize; // bank size in KB
  uint8 NumberOfImagePages; // number of images
  uint8 rsvd1; // reserved for page function
  // Direct Color fields (required for direct/6 and YUV/7 memory models)
  uint8 RedMaskSize; // size of direct color red mask in bits
  uint8 RedFieldPosition; // bit position of lsb of red mask
  uint8 GreenMaskSize; // size of direct color green mask in bits
  uint8 GreenFieldPosition; // bit position of lsb of green mask
  uint8 BlueMaskSize; // size of direct color blue mask in bits
  uint8 BlueFieldPosition; // bit position of lsb of blue mask
  uint8 RsvdMaskSize; // size of direct color reserved mask in bits
  uint8 RsvdFieldPosition; // bit position of lsb of reserved mask
  uint8 DirectColorModeInfo; // direct color mode attributes
  // Mandatory information for VBE 2.0 and above
  uint32 PhysBasePtr; // physical address forflat memory frame buffer
  uint32 rsvd2; // Reserved - always set to 0
  uint16 rsvd3; // Reserved - always set to 0
  // Mandatory information for VBE 3.0 and above
  uint16 LinBytesPerScanLine; // bytes per scan line for linear modes
  uint8 BnkNumberOfImagePages; // number of images for banked modes
  uint8 LinNumberOfImagePages; // number of images for linear modes
  uint8 LinRedMaskSize; // size of direct color red mask (linear modes)
  uint8 LinRedFieldPosition; // bit position of lsb of red mask (linear modes)
  uint8 LinGreenMaskSize; // size of direct color green mask (linear modes)
  uint8 LinGreenFieldPosition; // bit position of lsb of green mask (linear modes)
  uint8 LinBlueMaskSize; // size of direct color blue mask (linear modes)
  uint8 LinBlueFieldPosition; // bit position of lsbof blue mask (linear modes)
  uint8 LinRsvdMaskSize; // size of direct color reserved mask (linear modes)
  uint8 LinRsvdFieldPosition; // bit position of lsb of reserved mask (linear modes)
  uint32 MaxPixelClock; // maximum pixel clock (in Hz) for graphics mode
  uint8 rsvd4[189]; // remainder of ModeInfoBlock
} tVbeModeInfo;

#pragma pack(pop)

#ifdef _DPMI
int GetVbeInfo(tVbeInfo* p)
{
  __dpmi_int_regs regs;
  int res;
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4F00;
  regs.edi = (unsigned)__dpmi_iobuf & 0xF;
  regs.es = (unsigned)__dpmi_iobuf >> 4;
  if ((res = __dpmi_int(0x10, &regs)) != 0)
    return res;
  memcpy(p, __dpmi_iobuf, sizeof *p);
  return regs.eax & 0xFFFF;
}

int GetVbeModeInfo(tVbeModeInfo* p, uint16 mode)
{
  __dpmi_int_regs regs;
  int res;
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4F01;
  regs.ecx = mode;
  regs.edi = (unsigned)__dpmi_iobuf & 0xF;
  regs.es = (unsigned)__dpmi_iobuf >> 4;
  if ((res = __dpmi_int(0x10, &regs)) != 0)
    return res;
  memcpy(p, __dpmi_iobuf, sizeof *p);
  return regs.eax & 0xFFFF;
}

int SetVbeMode(uint16 mode)
{
  __dpmi_int_regs regs;
  int res;
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4F02;
  regs.ebx = mode;
  if ((res = __dpmi_int(0x10, &regs)) != 0)
    return res;
  return regs.eax & 0xFFFF;
}

int DpmiMapPhysical(void** linear, uint32 physical, uint32 size)
{
  asm(
  "mov ax, 0x800\n"
  "mov bx, [ebp+12+2]\n"
  "mov cx, [ebp+12]\n"
  "mov si, [ebp+16+2]\n"
  "mov di, [ebp+16]\n"
  "int 0x31\n"
  "mov eax, [ebp+8]\n"
  "mov [eax+2], bx\n"
  "mov [eax], cx\n"
  "sbb eax, eax\n"
  );
}
#endif

#ifdef __UNREAL__
int GetVbeInfo(tVbeInfo* p)
{
  asm(
  "mov   ax, 0x4f00\n"
  "mov   edi, [bp+8]\n"
  "ror   edi, 4\n"
  "mov   es, di\n"
  "shr   edi, 28\n"
  "int   0x10\n"
  "movzx eax, ax\n"
  "push  word 0\n"
  "pop   es"
  );
}

int GetVbeModeInfo(tVbeModeInfo* p, uint16 mode)
{
  asm(
  "mov   ax, 0x4f01\n"
  "mov   cx, [bp+12]\n"
  "mov   edi, [bp+8]\n"
  "ror   edi, 4\n"
  "mov   es, di\n"
  "shr   edi, 28\n"
  "int   0x10\n"
  "movzx eax, ax\n"
  "push  word 0\n"
  "pop   es"
  );
}

int SetVbeMode(uint16 mode)
{
  asm(
  "mov   ax, 0x4f02\n"
  "mov   bx, [bp+8]\n"
  "int   0x10\n"
  "movzx eax, ax"
  );
}

enum { ONE_MB = 0x100000 };

int InEvenNumberedMegabyte(uint32 addr, uint32 size)
{
  uint32 end = addr + size - 1;
  // Zero size makes no sense.
  //
  // size larger than 1MB means the buffer lies in two or more different
  // megabytes and one of them is odd-numbered.
  //
  // size of 1MB or smaller means the buffer lies in at most two different
  // megabytes, check where the first and last bytes are.
  return (size > 0) && (size <= ONE_MB) && !((addr | end) & ONE_MB);
}

int A20Enabled(void)
{
  volatile unsigned char* p1 = (volatile unsigned char*)1;
  volatile unsigned char* p1M1 = (volatile unsigned char*)(ONE_MB + 1);
  unsigned char x1, x1M1;
  int enabled = 0;

  asm("cli");

  x1 = *p1;
  x1M1 = *p1M1;
  *p1M1 = ~x1;

  if (*p1 == x1)
  {
    *p1M1 = x1M1;
    enabled = 1;
  }
  else
  {
    *p1 = x1;
  }

  asm("sti");

  return enabled;
}

void TryEnableA20_Bios(void)
{
  asm("push ebp\n"
      "push dword 0\n"
      "mov  ax, 0x2401\n"
      "int  0x15\n"
      "pop  es\n"
      "pop  ds\n"
      "pop  ebp");
}

enum
{
  PORT_KBD_A = 0x60,
  PORT_KBD_STATUS = 0x64
};

unsigned char InPortByte(unsigned short port)
{
  asm("mov   dx, [bp+8]\n"
      "in    al, dx\n"
      "movzx eax, al");
}
void OutPortByte(unsigned short port, unsigned char value)
{
  asm("mov dx, [bp+8]\n"
      "mov al, [bp+12]\n"
      "out dx, al");
}

void KbdWaitDone2(void)
{
  while ((InPortByte(PORT_KBD_STATUS) & 2) == 2);
}
void KbdWaitDone1(void)
{
  while (!(InPortByte(PORT_KBD_STATUS) & 1));
}
void KbdSendCmd(unsigned char cmd)
{
  OutPortByte(PORT_KBD_STATUS, cmd);
}

void TryEnableA20_AtKbd(void)
{
  unsigned char x;
  asm("cli");

  KbdWaitDone2();
  KbdSendCmd(0xAD);
  KbdWaitDone2();

  KbdSendCmd(0xD0);
  KbdWaitDone1();
  x = InPortByte(PORT_KBD_A);
  KbdWaitDone2();

  KbdSendCmd(0xD1);
  KbdWaitDone2();

  OutPortByte(PORT_KBD_A, x | 2 | 1); // set bit 0 to prevent reset
  KbdWaitDone2();

  KbdSendCmd(0xAE);
  KbdWaitDone2();

  asm("sti");
}

void TryEnableA20_Ps2Fast(void)
{
  unsigned char x;
  asm("cli");
  x = InPortByte(0x92) & 0xFE; // reset bit 0 to prevent reset
  if ((x & 2) == 0)
    OutPortByte(0x92, x | 2);
  asm("sti");
}

// This A20 code is likely imperfect (no delays, no retries),
// but it appears to be working in DOSBox and VirtualBox.
// See:
// http://wiki.osdev.org/A20
// http://www.win.tue.nl/~aeb/linux/kbd/A20.html
// http://lxr.free-electrons.com/source/arch/x86/boot/a20.c
int EnableA20(void)
{
  if (A20Enabled())
  {
    puts("A20 already enabled.");
    return 1;
  }
  // Try himem.sys first? OTOH, if it's loaded, it's probably enabled A20 already.
  puts("Trying to enable A20 via BIOS...");
  TryEnableA20_Bios();
  if (A20Enabled())
  {
    puts("A20 enabled via BIOS.");
    return 1;
  }
  puts("Trying to enable A20 via keyboard controller...");
  TryEnableA20_AtKbd();
  if (A20Enabled())
  {
    puts("A20 enabled via keyboard controller.");
    return 1;
  }
  puts("Trying to enable A20 via fast method...");
  TryEnableA20_Ps2Fast();
  if (A20Enabled())
  {
    puts("A20 enabled via fast method.");
    return 1;
  }
  puts("Failed to enable A20!");
  return 0;
}
#endif

enum
{
  // Only 8bpp modes are supported.
//  VBE_MODE = 0x100, VBE_WIDTH = 640, VBE_HEIGHT = 400,
  VBE_MODE = 0x101, VBE_WIDTH = 640, VBE_HEIGHT = 480,
//  VBE_MODE = 0x103, VBE_WIDTH = 800, VBE_HEIGHT = 600,
//  VBE_MODE = 0x105, VBE_WIDTH = 1024, VBE_HEIGHT = 768,
//  VBE_MODE = 0x107, VBE_WIDTH = 1280, VBE_HEIGHT = 1024, // > 1MB in size, will need A20 in unreal mode(l)
  VBE_AREA = VBE_WIDTH * VBE_HEIGHT
};

uint8* screen;

void pixel(int x, int y,
           uint8 color)
{
  screen[y * VBE_WIDTH + x] = color;
}

void line(int x1, int y1,
          int x2, int y2,
          uint8 color)
{
  int sx, sy, dx1, dy1, dx2, dy2, x, y, m, n, k, cnt;

  sx = x2 - x1;
  sy = y2 - y1;

  if (sy < 0 || sy == 0 && sx < 0)
  {
    k = x1; x1 = x2; x2 = k;
    k = y1; y1 = y2; y2 = k;
    sx = -sx;
    sy = -sy;
  }

  if (sx > 0) dx1 = 1;
  else if (sx < 0) dx1 = -1;
  else dy1 = 0;

  if (sy > 0) dy1 = 1;
  else if (sy < 0) dy1 = -1;
  else dy1 = 0;

  m = (sx >= 0) ? sx : -sx;
  n = (sy >= 0) ? sy : -sy;
  dx2 = dx1;
  dy2 = 0;

  if (m < n)
  {
    m = (sy >= 0) ? sy : -sy;
    n = (sx >= 0) ? sx : -sx;
    dx2 = 0;
    dy2 = dy1;
  }

  x = x1; y = y1;
  cnt = m + 1;
  k = n / 2;

  while (cnt--)
  {
    if (x >= 0 && x < VBE_WIDTH && y >= 0 && y < VBE_HEIGHT)
      screen[y * VBE_WIDTH + x] = color;

    k += n;
    if (k < m)
    {
      x += dx2;
      y += dy2;
    }
    else
    {
      k -= m;
      x += dx1;
      y += dy1;
    }
  }
}

int main(void)
{
  tVbeInfo vbeInfo;
  tVbeModeInfo modeInfo;
  int err;

  // Get and check VBE info

  if ((err = GetVbeInfo(&vbeInfo)) != 0x4F)
  {
    printf("GetVbeInfo() failed (0x%08X)!\n", err);
    return EXIT_FAILURE;
  }

  printf("%.4s %u.%u \"%s\"\n",
         vbeInfo.VbeSignature,
         vbeInfo.VbeVersion >> 8, vbeInfo.VbeVersion & 0xFF,
         ((vbeInfo.OemStringPtr >> 16) << 4) + (vbeInfo.OemStringPtr & 0xFFFF));

  if (vbeInfo.VbeVersion < 0x0200)
  {
    printf("VBE 2.0+ required!\n");
    return EXIT_FAILURE;
  }

  // Get and check VBE mode info

  if ((err = GetVbeModeInfo(&modeInfo, VBE_MODE)) != 0x4F)
  {
    printf("GetVbeModeInfo() failed (0x%08X)!\n", err);
    return EXIT_FAILURE;
  }

  if ((modeInfo.ModeAttributes & 0x80) == 0 || modeInfo.PhysBasePtr == 0)
  {
    printf("Linear Frame Buffer not available!\n", err);
    return EXIT_FAILURE;
  }

  // Map the linear frame buffer into the virtual address space

#ifdef _DPMI
  if (DpmiMapPhysical(&screen, modeInfo.PhysBasePtr, VBE_AREA))
  {
    printf("DpmiMapPhysical() failed!\n");
    return EXIT_FAILURE;
  }
#else
  if (!InEvenNumberedMegabyte(modeInfo.PhysBasePtr, VBE_AREA) && !EnableA20())
  {
    printf("Linear Frame Buffer at 0x%08X (physical) needs A20 enabled!\n", modeInfo.PhysBasePtr);
    return EXIT_FAILURE;
  }
  screen = modeInfo.PhysBasePtr;
#endif

  printf("Linear Frame Buffer at 0x%08X/0x%08X (physical/linear)\n", modeInfo.PhysBasePtr, (unsigned)screen);

  printf("Press Enter to continue.\n");
  getchar();

  // Demo time!

  // Set mode VBE_MODE (VBE_WIDTH x VBE_HEIGHT x 8bpp) with LFB
  if ((err = SetVbeMode(VBE_MODE | (1 << 14)/*use LFB*/)) != 0 && err != 0x4F)
  {
    printf("SetVbeMode() failed (0x%08X)!\n", err);
    return EXIT_FAILURE;
  }

  // Draw something

  for (int y = 0; y < VBE_HEIGHT; y++)
    for (int x = 0; x < VBE_WIDTH; x++)
      screen[y * VBE_WIDTH + x] = (x ^ y) & 0xF0;

  line(0, 0, (VBE_WIDTH-2), 0, 8+1);
  line((VBE_WIDTH-1), 0, (VBE_WIDTH-1), (VBE_HEIGHT-2), 8+2);
  line((VBE_WIDTH-1), (VBE_HEIGHT-1), 1, (VBE_HEIGHT-1), 8+4);
  line(0, (VBE_HEIGHT-1), 0, 1, 8+6);
  line(1, 1, (VBE_WIDTH-2), (VBE_HEIGHT-2), 8+3);
  line((VBE_WIDTH-2), 1, 1, (VBE_HEIGHT-2), 8+5);

  for (int angle = 0; angle < 1024; angle++)
  {
    double a = angle * 3.1415927 / 512;
    int x = (VBE_WIDTH/2) + cos(a) * (VBE_WIDTH/3);
    int y = (VBE_HEIGHT/2) - sin(a) * (VBE_HEIGHT/3);
    int c = (angle >> 7) + 8;
    pixel(x, y, c);
    pixel(x-1, y, c);
    pixel(x, y+1, c);
    pixel(x+1, y, c);
    pixel(x, y-1, c);
  }

  // All done

  printf("Press Enter to exit.\n"); // This text may not be displayed.
  getchar();

  SetVbeMode(0x3);

  return 0;
}
