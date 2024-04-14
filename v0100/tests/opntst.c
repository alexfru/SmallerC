/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost opntst.c -o opntstdt.com
    smlrcc -doss opntst.c -o opntstds.exe
    smlrcc -dosh opntst.c -o opntstdh.exe
    smlrcc -dosu opntst.c -o opntstdu.exe
    smlrcc -dosp opntst.c -o opntstdp.exe

  How to compile for Windows:
    smlrcc -win opntst.c -o opntstw.exe

  How to compile for Linux:
    smlrcc -linux opntst.c -o opntstl

  How to compile for MacOS:
    smlrcc -macos opntst.c -o opntstm
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_LEN (10+26)
const char tstdata[DATA_LEN] = "0123456789abcdefghijklmnopqrstuvwxyz";
const char fname[] = "opntst.dat";
int fhandle;
char data[DATA_LEN];

void write_data(void)
{
  ssize_t ssz = write(fhandle, tstdata, DATA_LEN);
  assert(ssz == DATA_LEN);
}

int read_data(int compare_not_empty)
{
  ssize_t ssz;
  memset(data, 0, DATA_LEN);
  ssz = read(fhandle, data, DATA_LEN);
  return compare_not_empty ? !memcmp(data, tstdata, DATA_LEN) : !ssz;
}

int main(void)
{
  // Test simple O_CREAT

  remove(fname);
  fhandle = open(fname, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);

  // Test simple O_CREAT | O_EXCL

  remove(fname);
  fhandle = open(fname, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle == -1);

  // Test simple open

  remove(fname);
  fhandle = open(fname, O_RDONLY);
  assert(fhandle == -1);
  fhandle = open(fname, O_WRONLY);
  assert(fhandle == -1);
  fhandle = open(fname, O_RDWR);
  assert(fhandle == -1);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_RDONLY);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_WRONLY);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_RDWR);
  assert(fhandle >= 0);
  close(fhandle);

  // Test simple O_TRUNC

  remove(fname);
  fhandle = open(fname, O_TRUNC | O_RDWR);
  assert(fhandle == -1);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  close(fhandle);
  fhandle = open(fname, O_TRUNC | O_RDWR);
  assert(fhandle >= 0);
  close(fhandle);

  // Test with read/write

  remove(fname);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  write_data();
  close(fhandle);
  fhandle = open(fname, O_RDONLY);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/1));
  close(fhandle);
  fhandle = open(fname, O_RDWR);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/1));
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/1));
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/1));
  close(fhandle);

  // Test with read/write and truncate

  remove(fname);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  write_data();
  close(fhandle);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/0));
  close(fhandle);

  remove(fname);
  fhandle = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  write_data();
  close(fhandle);
  fhandle = open(fname, O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  assert(fhandle >= 0);
  assert(read_data(/*compare_not_empty*/0));
  close(fhandle);

  puts("open() test passed!");
  return 0;
}
