/*
  How to compile for DOS/DPMI:
    smlrcc -dosp vesalfb.c -o vesalfb.exe
*/
#ifndef _DPMI
#error Must be compiled as a DOS/DPMI program
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

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

uint8* screen;

void pixel(int x, int y,
           uint8 color)
{
  screen[y * 640 + x] = color;
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
    if (x >= 0 && x < 640 && y >= 0 && y < 480)
      screen[y * 640 + x] = color;

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

  if ((err = GetVbeModeInfo(&modeInfo, 0x101)) != 0x4F)
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

  if (DpmiMapPhysical(&screen, modeInfo.PhysBasePtr, 640 * 480))
  {
    printf("DpmiMapPhysical() failed!\n");
    return EXIT_FAILURE;
  }

  printf("Linear Frame Buffer at 0x%08X/0x%08X (physical/linear)\n", modeInfo.PhysBasePtr, (unsigned)screen);

  printf("Press Enter to continue.\n");
  getchar();

  // Demo time!

  // Set mode 0x101 (640 x 480 x 8bpp) with LFB
  if ((err = SetVbeMode(0x101 | (1 << 14)/*use LFB*/)) != 0 && err != 0x4F)
  {
    printf("SetVbeMode() failed (0x%08X)!\n", err);
    return EXIT_FAILURE;
  }

  // Draw something

  for (int y = 0; y < 480; y++)
    for (int x = 0; x < 640; x++)
      screen[y * 640 + x] = (x ^ y) & 0xF0;

  line(0, 0, 638, 0, 8+1);
  line(639, 0, 639, 478, 8+2);
  line(639, 479, 1, 479, 8+4);
  line(0, 479, 0, 1, 8+6);
  line(1, 1, 638, 478, 8+3);
  line(638, 1, 1, 478, 8+5);

  for (int angle = 0; angle < 1024; angle++)
  {
    double a = angle * 3.1415927 / 512;
    int x = 320 + cos(a) * 256;
    int y = 240 - sin(a) * 128;
    int c = (angle >> 7) + 8;
    pixel(x, y, c);
    pixel(x-1, y, c);
    pixel(x, y+1, c);
    pixel(x+1, y, c);
    pixel(x, y-1, c);
  }

  // All done

  printf("Press Enter to exit.\n");
  getchar();

  SetVbeMode(0x3);

  return 0;
}
