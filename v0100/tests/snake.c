/*
  Compile:
    smlrc -seg16 -nobss snake.c snake.asm
    nasm -f bin snake.asm -o snake.com

  Run snake.com in DOS, 32-bit Windows or DosBox.
*/

asm("org 0x100");

int main(void);

void start(void)
{
  main();
}

// defines the game speed
#define DELAY 150

// video mode, video buffer segment and dimensions
#define VMODE   1 // 40x25 color text mode
#define VSEG    0xB800
#define VWIDTH  40
#define VHEIGHT 25

// foreground and background colors
#define FORE_BLACK   0x00
#define FORE_BLUE    0x01
#define FORE_GREEN   0x02
#define FORE_CYAN    0x03
#define FORE_RED     0x04
#define FORE_MAGENTA 0x05
#define FORE_BROWN   0x06
#define FORE_WHITE   0x07
#define FORE_GRAY           0x08
#define FORE_BRIGHT_BLUE    0x09
#define FORE_BRIGHT_GREEN   0x0A
#define FORE_BRIGHT_CYAN    0x0B
#define FORE_BRIGHT_RED     0x0C
#define FORE_BRIGHT_MAGENTA 0x0D
#define FORE_YELLOW         0x0E
#define FORE_BRIGHT_WHITE   0x0F
#define BACK_BLACK   0x00
#define BACK_BLUE    0x10
#define BACK_GREEN   0x20
#define BACK_CYAN    0x30
#define BACK_RED     0x40
#define BACK_MAGENTA 0x50
#define BACK_BROWN   0x60
#define BACK_WHITE   0x70

// key codes
#define KEY_ESCAPE 0x011B
#define KEY_ENTER  0x1C0D
#define KEY_UP     0x4800
#define KEY_LEFT   0x4B00
#define KEY_RIGHT  0x4D00
#define KEY_DOWN   0x5000

// snake state
#define MIN_LENGTH 6
#define MAX_LENGTH (VWIDTH * VHEIGHT)
unsigned snake[MAX_LENGTH][2]; // coordinates
unsigned length;
unsigned direction;

// target
unsigned target[2]; // coordinates

unsigned score;

int BiosKeyAvailable(void)
{
  asm("mov   ah, 1\n"
      "int   0x16\n"
      "setnz al\n"
      "cbw");
}

unsigned BiosReadKey(void)
{
  asm("mov ah, 0\n"
      "int 0x16");
}

void BiosSetGfxMode(unsigned mode)
{
  asm("mov ah, 0\n"
      "mov al, [bp + 4]\n"
      "int 0x10");
}

void pokeb(unsigned seg, unsigned ofs, unsigned char val)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bp + 8]\n"
      "mov  [bx], al\n"
      "pop  ds");
}

void poke(unsigned seg, unsigned ofs, unsigned val)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bp + 8]\n"
      "mov  [bx], ax\n"
      "pop  ds");
}

unsigned char peekb(unsigned seg, unsigned ofs)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bx]\n"
      "mov  ah, 0\n"
      "pop  ds");
}

unsigned peek(unsigned seg, unsigned ofs)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bx]\n"
      "pop  ds");
}

void BiosGetTicks(unsigned ticks[2])
{
  unsigned low, high1, high2;
  high2 = peek(0x40, 0x6E);
  do
  {
    high1 = high2;
    low = peek(0x40, 0x6C);
    high2 = peek(0x40, 0x6E);
    // make sure the top 16 bits of the ticks counter haven't changed meanwhile
  } while (high1 != high2);
  ticks[0] = low;
  ticks[1] = high2;
}

void delay(unsigned milliseconds)
{
  unsigned tcnt = (milliseconds + 27) / 55; // the 32-bit ticks counter increments every 55 ms
  unsigned ticks[2][2];
  BiosGetTicks(ticks[0]);
  for (;;)
  {
    BiosGetTicks(ticks[1]);
    // ticks[1] -= ticks[0]
    if (ticks[1][0] < ticks[0][0])
      --ticks[1][1];
    ticks[1][0] -= ticks[0][0];
    ticks[1][1] -= ticks[0][1];
    // ticks[1] >= tcnt ?
    if (ticks[1][0] >= tcnt || ticks[1][1])
      break;
  }
}

void lineh(unsigned x, unsigned y, unsigned w, unsigned chr, unsigned color)
{
  unsigned ofs = (y * VWIDTH + x) * 2;
  unsigned v = (color << 8) | chr;
  while (w--)
  {
    poke(VSEG, ofs, v);
    ofs += 2;
  }
}

void linev(unsigned x, unsigned y, unsigned h, unsigned chr, unsigned color)
{
  unsigned ofs = (y * VWIDTH + x) * 2;
  unsigned v = (color << 8) | chr;
  while (h--)
  {
    poke(VSEG, ofs, v);
    ofs += VWIDTH * 2;
  }
}

void box(unsigned x, unsigned y, unsigned w, unsigned h, unsigned chr, unsigned color, unsigned solid)
{
  if (solid)
  {
    while (h--)
      lineh(x, y++, w, chr, color);
  }
  else
  {
    lineh(x, y, w, chr, color);
    linev(x + w - 1, y, h, chr, color);
    lineh(x, y + h - 1, w, chr, color);
    linev(x, y, h, chr, color);
  }
}

void text(unsigned x, unsigned y, char* s, unsigned color)
{
  unsigned ofs = (y * VWIDTH + x) * 2;
  while (*s)
  {
    unsigned v = (color << 8) | *s++;
    poke(VSEG, ofs, v);
    ofs += 2;
  }
}

void number(unsigned x, unsigned y, unsigned n, unsigned color)
{
  char s[6];
  int i;
  for (i = 4; i >= 0; --i)
  {
    s[i] = '0' + n % 10;
    n /= 10;
  }
  s[5] = 0;
  text(x, y, s, color);
}

#define RAND_MAX 0x7FFF
unsigned rand_next[2] = { 1, 0 };
int rand(void)
{
  asm("mov  eax, [_rand_next]\n"
      "imul eax, eax, 1103515245\n"
      "add  eax, 12345\n"
      "mov  [_rand_next], eax\n"
      "shr  eax, 16\n"
      "and  ax, 0x7FFF\n");
}

void srand(unsigned seed)
{
  rand_next[0] = seed;
}

void play(void);

int main(void)
{
  unsigned ticks[2];

  BiosSetGfxMode(VMODE);

  text((VWIDTH - 20) / 2, VHEIGHT / 2, "Press a key to start", BACK_BLACK | FORE_BRIGHT_WHITE);
  while (BiosKeyAvailable()) BiosReadKey(); // clear the keyboard buffer, just in case
  BiosReadKey();

  BiosGetTicks(ticks);
  srand(ticks[0]);

  play();

  BiosSetGfxMode(3); // 80x25 color text mode
  return 0;
}

void newtarget(void)
{
  for (;;)
  {
    unsigned bit = 0, i;
    i = rand() % ((VWIDTH - 2) * (VHEIGHT - 2));
    target[0] = 1 + i % (VWIDTH - 2);
    target[1] = 1 + i / (VWIDTH - 2);
    for (i = 0; i < length; ++i)
    {
      if (target[0] == snake[i][0] &&
          target[1] == snake[i][1])
      {
        bit = 1;
        break;
      }
    }
    if (!bit)
      break;
  }
  text(target[0], target[1], "$", BACK_GREEN | FORE_YELLOW);
}

void play(void)
{
  unsigned i, key;

  // set up the field
  box(0, 0, VWIDTH, VHEIGHT, ' ', BACK_GREEN | FORE_YELLOW, 1);
  box(0, 0, VWIDTH, VHEIGHT, ' ', BACK_BROWN | FORE_BLACK, 0);
  text((VWIDTH - 12) / 2, 0, "Score: ", BACK_BROWN | FORE_BLACK);
  score = 0;
  number((VWIDTH - 12) / 2 + 7, 0, score, BACK_BROWN | FORE_BLACK);

  // set up the snake
  for (length = 0; length < MIN_LENGTH; ++length)
  {
    snake[length][0] = VWIDTH / 2;
    snake[length][1] = VHEIGHT - 1 - MIN_LENGTH + length;
    text(snake[length][0], snake[length][1], "O", BACK_GREEN | FORE_YELLOW);
  }
  direction = KEY_UP;

  // set up the target
  newtarget();

  for (;;)
  {
    key = 0;

    if (BiosKeyAvailable())
      key = BiosReadKey();

    delay(DELAY);

    // update the direction
    switch (key)
    {
    case KEY_ESCAPE:
      return;

    case KEY_LEFT:
      if (direction != KEY_RIGHT)
        direction = key;
      break;
    case KEY_RIGHT:
      if (direction != KEY_LEFT)
        direction = key;
      break;
    case KEY_UP:
      if (direction != KEY_DOWN)
        direction = key;
      break;
    case KEY_DOWN:
      if (direction != KEY_UP)
        direction = key;
      break;
    }

    // move the snake
    text(snake[length - 1][0], snake[length - 1][1], " ", BACK_GREEN | FORE_YELLOW); // erase the tail
    for (i = length - 1; i > 0; --i) // update the body position
    {
      snake[i][0] = snake[i - 1][0];
      snake[i][1] = snake[i - 1][1];
    }
    switch (direction) // update the head position
    {
    case KEY_LEFT:
      --snake[0][0];
      break;
    case KEY_RIGHT:
      ++snake[0][0];
      break;
    case KEY_UP:
      --snake[0][1];
      break;
    case KEY_DOWN:
      ++snake[0][1];
      break;
    }
    text(snake[0][0], snake[0][1], "O", BACK_GREEN | FORE_YELLOW); // draw the head

    // check the head against the boundaries
    if (snake[0][0] < 1 || snake[0][0] >= VWIDTH - 1 ||
        snake[0][1] < 1 || snake[0][1] >= VHEIGHT - 1)
      break;

    // check for self biting
    {
      unsigned bit = 0;
      for (i = 1; i < length; ++i)
      {
        if (snake[0][0] == snake[i][0] &&
            snake[0][1] == snake[i][1])
        {
          bit = 1;
          break;
        }
      }
      if (bit)
        break;
    }

    // check for hitting the target
    if (snake[0][0] == target[0] &&
        snake[0][1] == target[1])
    {
      // enlarge the snake
      snake[length][0] = snake[length - 1][0];
      snake[length][1] = snake[length - 1][1];
      ++length;

      ++score;
      number((VWIDTH - 12) / 2 + 7, 0, score, BACK_BROWN | FORE_BLACK);

      // set up the target
      newtarget();
    }
  }

  text((VWIDTH - 10) / 2, VHEIGHT / 2, "Game Over!", BACK_BLACK | FORE_BRIGHT_WHITE);
  delay(1000);
  while (BiosKeyAvailable()) BiosReadKey(); // clear the keyboard buffer
  BiosReadKey();
}
