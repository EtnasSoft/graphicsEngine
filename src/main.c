#include "../lib/conio/conio.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


// TYPEDEFS
// ////////////////////////////////////////////////////////////////////
typedef uint8_t byte;
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define memcpy_P memcpy

// GRAPHICS MODE
// ////////////////////////////////////////////////////////////////////
//
// MODE 0   No scroll
// MODE 1   Infinite Scroll vertical
// MODE 2   Infinite Scroll horizontal
// MODE 3   Infinite Scroll vertical and horizontal
// MODE 4   Scroll vertical (not infinite)
// MODE 5   Scroll horizontal (not infinite)
// MODE 6   Scroll vertical and horizontal (not infinite)
//
#define MODE_3

// DEFINES
// ////////////////////////////////////////////////////////////////////
#define DEBUG
#define INCREASE 43 // ASCII CODE for +
#define DECREASE 45 // ASCII CODE for -

// Screen resolution 128x64px
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MODULE 8 // Module for tiles (bits) used for screen division / pages
#define EDGES 2 // Used only for pseudo buffer screen purposes

#define VIEWPORT_HEIGHT SCREEN_HEIGHT / MODULE // 8
#define VIEWPORT_WIDTH SCREEN_WIDTH / MODULE // 16

// MAXIMUM: 16rows x 18cols => 288 byte + 128 byte (SSD1306 page)
#define PLAYFIELD_HEIGHT (VIEWPORT_HEIGHT + EDGES) // 10
#define PLAYFIELD_WIDTH (VIEWPORT_WIDTH + EDGES) // 18
#define PLAYFIELD_SIZE (PLAYFIELD_HEIGHT * PLAYFIELD_WIDTH) // 180

#define TILEMAP_HEIGHT 8 //32 // x<<5
#define TILEMAP_WIDTH 128//32 // x<<5
#define TILEMAP_SIZE (TILEMAP_HEIGHT * TILEMAP_WIDTH) // 1024
#define TILEMAP_MAX_HEIGHT_SCROLL ((TILEMAP_HEIGHT - 1) * MODULE) // 248
#define TILEMAP_MAX_WIDTH_SCROLL ((TILEMAP_WIDTH - 1) * MODULE) // 248


// VARS
// ////////////////////////////////////////////////////////////////////
const byte ucTiles[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Empty  (0)
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Fill   (1)
};

/*const byte tileMap[TILEMAP_SIZE] = {
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,
  0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,
  0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,1,1,1,0,0,1,
  0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,
  0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,
  0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,
  0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,1,
  0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,
  0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,1,1,0,0,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  0,0,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,1,
  0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,1,
  0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,1,
  0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,0,1,
  0,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,
  0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,
  0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,
  0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,
  0,1,0,1,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};*/

const byte tileMap[TILEMAP_SIZE] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,
  1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

static byte bPlayfield[PLAYFIELD_SIZE];
int iScrollX, iScrollY;
const char *BLANK = "-";
const char *FILL = "@";


// PROTOTYPES
// ////////////////////////////////////////////////////////////////////
void cls(void);
void reloadPlayField(void);
void adjustPlayFieldRows(void);
void adjustPlayFieldCols(void);
void DrawPlayfield(uint16_t bScrollX, uint16_t bScrollY);
void DrawShiftedChar(byte *s1, byte *s2, byte *d, byte bXOff, byte bYOff);
void PrintRow(byte data[], uint16_t dataLength, byte y, byte ty);
void PrintPlayFieldRow(byte row, uint16_t bScrollX, uint16_t bScrollY);
void PrintPlayField(void);
void delay(int t);


// MAIN
// ////////////////////////////////////////////////////////////////////
int main(void) {
  cls();
  c_textcolor(11); // Light cyan color :)

  // Init the screen position and load the tilemap accordingly
  iScrollX = 0;
  iScrollY = 0;
  reloadPlayField();

  DrawPlayfield(iScrollX, iScrollY);

  // DEMO FUNCTIONALITY
  char ch = 0, k = 0, flag = 0, run = 1;

  while (run == 1) {
    ch = c_getch();
    if (ch == 27)
      k = 1;

    //printf("\n%i\n", ch);

    if (ch == 91 && k == 1)
      k = 2;

    if (ch == 72) { // UP
      iScrollY += MODULE;
      flag = 1;
    }

    if (ch == 80) { // DOWN
      iScrollY -= MODULE;
      flag = 1;
    }

    if (ch == 77) { // RIGHT
      iScrollX += MODULE;
      flag = 1;
    }

    if (ch == 75) { // LEFT
      iScrollX -= MODULE;
      flag = 1;
    }

    if (ch == 8) { // BACKSPACE - RESET
      iScrollX = 0;
      iScrollY = 0;
      reloadPlayField();
      flag = 1;
    }

    if (ch == 112) { // P
        run = 0;
    }

    if (ch != 27 && ch != 91) {
      k = 0;
    }

    // Limits
    if (flag) {
      if (iScrollX >= TILEMAP_MAX_WIDTH_SCROLL) {
        iScrollX = 0;
        reloadPlayField();
      } else if (iScrollX < 0) {
        iScrollX = TILEMAP_MAX_WIDTH_SCROLL;
        reloadPlayField();
      }

      if (iScrollY > TILEMAP_MAX_HEIGHT_SCROLL) {
        iScrollY = 0;
        reloadPlayField();
      } else if (iScrollY < 0) {
        iScrollY = TILEMAP_MAX_HEIGHT_SCROLL;
        reloadPlayField();
      }

      flag = 0;

      cls();
      DrawPlayfield(iScrollX, iScrollY);
    }
  }

  return 0;
}

void DrawShiftedChar(byte *s1, byte *s2, byte *d, byte bXOff, byte bYOff) {
  byte c, c2, z;

  for (z = 0; z < (8 - bXOff); z++) {
    c = *s1++;    //pgm_read_byte(s1++);
    c >>= bYOff;  // shift over
    c2 = *s2++;   //pgm_read_byte(s2++);
    c2 <<= (8 - bYOff);
    *d++ = (c | c2);
  }
}

void DrawPlayfield(uint16_t bScrollX, uint16_t bScrollY) {
  byte x, y, tx, c, *s, *sNext, *d,
    bTemp[SCREEN_WIDTH];

  int ty, bXOff, bYOff, iOffset, iOffset2;

  bXOff = bScrollX & (MODULE - 1);
  bYOff = bScrollY & (MODULE - 1);

  ty = (bScrollY >> 3);

#ifdef DEBUG
  printf("TILING MAP DEMO:\n-----------------------------------------------------\n\n");
  printf("PLAYFIELD_HEIGHT:\t%3i\tTILEMAP_HEIGHT:\t %i\tTILEMAP_MAX_HEIGHT:\t%i\n",
    PLAYFIELD_HEIGHT, TILEMAP_HEIGHT, TILEMAP_MAX_HEIGHT_SCROLL);
  printf("PLAYFIELD_WIDTH:\t%3i\tTILEMAP_WIDTH:\t %i\tTILEMAP_MAX_WIDTH:\t%i\n\n",
    PLAYFIELD_WIDTH, TILEMAP_WIDTH, TILEMAP_MAX_WIDTH_SCROLL);

  printf("SCREEN_HEIGHT:\t\t%3i\tVIEWPORT_HEIGHT:%3i\n", SCREEN_HEIGHT, VIEWPORT_HEIGHT);
  printf("SCREEN_WIDTH:\t\t%3i\tVIEWPORT_WIDTH:\t%3i\n\n", SCREEN_WIDTH, VIEWPORT_WIDTH);

  printf("iScrollX:\t%3i\t(%2i)\tbXOff:\t\t%3i\tty: \t%3i\n",
  iScrollX, (iScrollX / MODULE), bXOff, ty);
  printf("iScrollY:\t%3i\t(%2i)\tbYOff:\t\t%3i\n", iScrollY, (iScrollY / MODULE), bYOff);

  printf("\n%s\n", bYOff ? "bYOff Mode (step between block complete)" : "NON bYOff (Scroll block completed)");
  printf("\nSCREEN REPRESENTATION:\n----------------------\n\n");
#endif

  //adjustPlayFieldRows();
  adjustPlayFieldCols();

  // draw the 8 rows
  for (y = 0; y < VIEWPORT_HEIGHT; y++) {
    memset(bTemp, 0, sizeof(bTemp));

    ty = ty % PLAYFIELD_HEIGHT;
    tx = (bScrollX >> 3);

    // Draw the playfield characters at the given scroll position
    d = bTemp;

    if (bYOff) {
      // printf("BYOFF!\n");
      for (x = 0; x < VIEWPORT_WIDTH; x++) {
        if (tx >= PLAYFIELD_WIDTH) {
          tx -= PLAYFIELD_WIDTH; // wrap around
        }

        iOffset = tx + (ty * PLAYFIELD_WIDTH);

        if (iOffset >= PLAYFIELD_SIZE) {    // past bottom
          iOffset -= PLAYFIELD_SIZE;
        }

        iOffset2 = (iOffset + PLAYFIELD_WIDTH); // next line

        if (iOffset2 >= PLAYFIELD_SIZE) {    // past bottom
          iOffset2 -= PLAYFIELD_SIZE;
        }

        c = bPlayfield[iOffset];
        s = (byte *)&ucTiles[(c * MODULE) + bXOff];
        //printf("\niScrollY: %3i, iOffset: %3i, iOffset2: %3i", iScrollY, iOffset, iOffset2);

        c = bPlayfield[iOffset2];
        sNext = (byte *)&ucTiles[(c * MODULE) + bXOff];
        //printf("\niOffset2: %3i", iOffset2);

        DrawShiftedChar(s, sNext, d, bXOff, bYOff);

        d += (MODULE - bXOff);
        bXOff = 0;
        tx++;
      }

      // partial character left to draw
      if (d != &bTemp[SCREEN_WIDTH]) {
        bXOff = (byte)(&bTemp[SCREEN_WIDTH] - d);

        if (tx >= PLAYFIELD_WIDTH) {
          tx -= PLAYFIELD_WIDTH;
        }

        iOffset = tx + ty * PLAYFIELD_WIDTH;
        iOffset2 = iOffset + PLAYFIELD_WIDTH; // next line

        if (iOffset2 >= PLAYFIELD_SIZE) {    // past bottom
          iOffset2 -= PLAYFIELD_SIZE;
        }

        c = bPlayfield[iOffset];
        s = (byte *)&ucTiles[c * MODULE];

        c = bPlayfield[iOffset2];
        sNext = (byte *)&ucTiles[c * MODULE];

        DrawShiftedChar(s, sNext, d, MODULE - bXOff, bYOff);
      }
    // simpler case of vertical offset of 0 for each character
    } else {
      //printf("NON BYOFF!\n");
      //-----------------------------------
      // NON BYOFF; SCROLL BLOCK COMPLETED!
      //-----------------------------------

      // Filling each col of the SCREEN_WIDTH
      for (x = 0; x < VIEWPORT_WIDTH; x++) {
        if (tx >= PLAYFIELD_WIDTH) {
          tx %= PLAYFIELD_WIDTH;
        }

        iOffset = tx + (ty * PLAYFIELD_WIDTH);

        if (iOffset >= PLAYFIELD_SIZE) {    // past bottom
          iOffset %= PLAYFIELD_SIZE;
        }

        //printf("iOffset: %3i \n", iOffset);

        c = bPlayfield[iOffset];
        s = (int *)&ucTiles[(c * MODULE) + bXOff];
        memcpy_P(d, s, MODULE - bXOff);

        d += (MODULE - bXOff);
        bXOff = 0;

        tx++;
      }

      // printf("\n");

      // partial character left to draw
      if (d != &bTemp[SCREEN_WIDTH]) {
        printf("\n\nPARTIAL CHARACTER LEFT \n\n");
        bXOff = (byte)(&bTemp[SCREEN_WIDTH] - d);

        if (tx >= PLAYFIELD_WIDTH) {
          tx -= PLAYFIELD_WIDTH;
        }

        iOffset = tx + ty * PLAYFIELD_WIDTH;

        c = bPlayfield[iOffset];
        s = (byte *)&ucTiles[c * MODULE];
        memcpy_P(d, s, bXOff);
      }
    }

    // Send it to the display
    //oledSetPosition(0, y);
    //I2CWriteData(bTemp, SCREEN_WIDTH);

    PrintRow(bTemp, SCREEN_WIDTH, y, ty);
    ty++;
  }

  printf("\n\n\n");
  PrintPlayField();
}

void reloadPlayField(void) {
  byte x, y, currentPlayFieldByte, nextPlayFieldByte,
    currentRow = iScrollY >> 3,
    currentCol = iScrollX >> 3,
    offsetCol = currentCol % PLAYFIELD_WIDTH;

  uint16_t nextTileByte;

  for (y = 0; y < PLAYFIELD_HEIGHT; y++) {
    currentPlayFieldByte = ((currentRow + y) * PLAYFIELD_WIDTH) % PLAYFIELD_SIZE;
    currentPlayFieldByte += offsetCol;

    nextPlayFieldByte = currentPlayFieldByte;

    // Use the fact that 32 * x = x << 5
    nextTileByte = ((currentRow + y) % TILEMAP_HEIGHT) * TILEMAP_WIDTH;
    nextTileByte += currentCol;

    /*printf("currentPlayFieldByte: %3i, nextTileByte from: %3i\n",
        currentPlayFieldByte, nextTileByte);*/

    for (x = 0; x < PLAYFIELD_WIDTH; x++) {
      memcpy_P(&bPlayfield[nextPlayFieldByte++], &tileMap[nextTileByte++], 1);

      if ((nextPlayFieldByte % PLAYFIELD_WIDTH) == 0) {
        nextPlayFieldByte -= PLAYFIELD_WIDTH;
      }

      if ((nextTileByte % TILEMAP_WIDTH) == 0) {
        nextTileByte -= TILEMAP_WIDTH;
      }

      /*printf("nextPlayFieldByte: %3i, nextTileByte from: %3i\n",
          nextPlayFieldByte, nextTileByte);*/
    }
  }
}

void adjustPlayFieldRows(void) {
  int currentRow = iScrollY >> 3,
    currentCol = iScrollX >> 3,
    offsetCol = currentCol % PLAYFIELD_WIDTH,
    offsetRow = currentRow % PLAYFIELD_HEIGHT,

    prevPlayFieldRow = (offsetRow == 0 ? PLAYFIELD_HEIGHT : offsetRow) - 1,
    nextPlayFieldRow = (offsetRow + VIEWPORT_HEIGHT) % PLAYFIELD_HEIGHT,
    prevPlayFieldByte = prevPlayFieldRow * PLAYFIELD_WIDTH,
    nextPlayFieldByte = nextPlayFieldRow * PLAYFIELD_WIDTH;

  // Tiles
  int prevTileRow = ((currentRow == 0 ? TILEMAP_HEIGHT : currentRow) - 1) * TILEMAP_WIDTH,
    nextTileRow = ((currentRow + VIEWPORT_HEIGHT) % TILEMAP_HEIGHT) * TILEMAP_WIDTH,
    nextTileByte,
    prevTileByte,
    carry;


  if (prevPlayFieldByte >= PLAYFIELD_SIZE) {
    prevPlayFieldByte -= PLAYFIELD_SIZE;
  }

  if (nextPlayFieldByte >= PLAYFIELD_SIZE) {
    nextPlayFieldByte -= PLAYFIELD_SIZE;
  }

  prevPlayFieldByte += offsetCol;
  nextPlayFieldByte += offsetCol;

  printf("prevPlayFieldByte: %3i nextPlayFieldByte: %3i\n", prevPlayFieldByte, nextPlayFieldByte);
  printf("prevTileRow: %3i, nextTileRow: %3i\n\n", prevTileRow, nextTileRow);

  for (byte x = 0; x < PLAYFIELD_WIDTH; x++) {
    carry = (currentCol + x) % TILEMAP_WIDTH;
    nextTileByte = (nextTileRow + carry);
    prevTileByte = (prevTileRow + carry);

    memcpy_P(&bPlayfield[prevPlayFieldByte++], &tileMap[prevTileByte], 1);
    memcpy_P(&bPlayfield[nextPlayFieldByte++], &tileMap[nextTileByte], 1);

    if (nextPlayFieldByte % PLAYFIELD_WIDTH == 0) {
      prevPlayFieldByte -= PLAYFIELD_WIDTH;
      nextPlayFieldByte -= PLAYFIELD_WIDTH;
    }
  }
}

void adjustPlayFieldCols(void) {
  byte currentRow = iScrollY >> 3,
    currentCol = iScrollX >> 3,
    offsetRow = currentRow % PLAYFIELD_HEIGHT,
    offsetCol = currentCol % PLAYFIELD_WIDTH,
    currentPlayFieldByte = offsetRow * PLAYFIELD_WIDTH;

  // Use the fact that 32 * x = x << 5
  int nextTileByte,
    prevTileByte,
    currentTileByte = currentRow * TILEMAP_WIDTH,
    nextPlayFieldByte = currentPlayFieldByte + ((offsetCol + VIEWPORT_WIDTH) % PLAYFIELD_WIDTH),
    prevPlayFieldByte = offsetCol == 0
      ? currentPlayFieldByte + PLAYFIELD_WIDTH - 1
      : currentPlayFieldByte + (offsetCol - 1);

  if (prevPlayFieldByte < 0) {
    prevPlayFieldByte += PLAYFIELD_WIDTH;
  }

  nextTileByte = currentTileByte + ((currentCol + VIEWPORT_WIDTH) % TILEMAP_WIDTH);
  prevTileByte = currentCol == 0
    ? currentTileByte + PLAYFIELD_WIDTH - 1
    : currentTileByte + (currentCol -1);

  printf("currentPlayFieldByte: %3i, prevPlayFieldByte: %3i nextPlayFieldByte: %3i\n",
    currentPlayFieldByte, prevPlayFieldByte, nextPlayFieldByte);
  // printf("currentTileByte: %3i, nextTileByte: %3i, prevTileByte: %3i\n",
  //   currentTileByte, nextTileByte, prevTileByte);

  for (byte x = 0; x < PLAYFIELD_HEIGHT; x++) {
    printf("currentTileByte: %3i, nextTileByte: %3i, prevTileByte: %3i\n",
    currentTileByte, nextTileByte, prevTileByte);

    memcpy_P(&bPlayfield[nextPlayFieldByte], &tileMap[nextTileByte], 1);
    memcpy_P(&bPlayfield[prevPlayFieldByte], &tileMap[prevTileByte], 1);

    nextPlayFieldByte = (nextPlayFieldByte + PLAYFIELD_WIDTH) % PLAYFIELD_SIZE;
    prevPlayFieldByte = (prevPlayFieldByte + PLAYFIELD_WIDTH) % PLAYFIELD_SIZE;
    nextTileByte = (nextTileByte + TILEMAP_WIDTH) % TILEMAP_SIZE;
    prevTileByte = (prevTileByte + TILEMAP_WIDTH) % TILEMAP_SIZE;
  }
}

// DEMO ROUTINES
// ////////////////////////////////////////////////////////////////////
void PrintRow(byte data[], uint16_t dataLength, byte y, byte ty) {
  byte i;

  c_textcolor(11);
  printf("\n[%i](%i)  | ", y, ty);

  for (i = 0; i < dataLength; i += MODULE ) {
    if (data[i] == 0) {
      printf("%s", BLANK);
    } else if (data[i] == 255) {
      printf("%s", FILL);
    } else {
      printf("E");
    }
  }
}

void PrintPlayFieldRow(byte row, uint16_t bScrollX, uint16_t bScrollY) {
  uint16_t i,
    iStart = row * PLAYFIELD_WIDTH,
    iStop = iStart + PLAYFIELD_WIDTH,
    currentRow = (iScrollY >> 3) % PLAYFIELD_HEIGHT,
    currentCol = (iScrollX >> 3) % PLAYFIELD_WIDTH,
    nextCol = (currentCol + VIEWPORT_WIDTH) % PLAYFIELD_WIDTH,
    prevCol = (currentCol + VIEWPORT_WIDTH + 1) % PLAYFIELD_WIDTH,
    nextRow = (currentRow + VIEWPORT_HEIGHT) % PLAYFIELD_HEIGHT,
    prevRow = (currentRow + VIEWPORT_HEIGHT + 1) % PLAYFIELD_HEIGHT,
    counter = 0;

  /*printf("iStart: %3i, nextCol: %3i, prevCol: %3i, nextRow: %3i, prevRow: %3i ",
  iStart, nextCol, prevCol, nextRow, prevRow);*/

  c_textcolor(11);
  c_textbackground(0);
  printf("[%i] -- [", row);

  //c_textbackground(8);

  for (i = iStart; i < iStop; i++ ) {
    if (
      (row == prevRow || row == nextRow ) ||
      (counter == nextCol || counter == prevCol)
    ) {
      c_textbackground(0);
      c_textcolor(11);
    } else {
      c_textbackground(4);
      c_textcolor(0);
    }

    //printf("%i ", bPlayfield[i]);
    if (bPlayfield[i] == 0) {
      printf("%s", BLANK);
    } else if (bPlayfield[i] == 1) {
      //c_textcolor(color++ & 3);
      printf("%s", FILL);
      //c_textcolor(11);
    } else {
      printf("E");
    }
    counter++;
    //printf("%s", bPlayfield[i] == 1 ? FILL : BLANK);
  }

  c_textbackground(0);
  c_textcolor(11);
  printf("]\n");
}

void PrintPlayField(void) {
  byte i;

  printf("PLAYFIELD VISUALIZATION (%i bytes):\n------------------------------------\n\n",
    PLAYFIELD_SIZE);

  for (i = 0; i < PLAYFIELD_HEIGHT; i++) {
    PrintPlayFieldRow(i, iScrollX, iScrollY);
  }

  printf("\n\n");
}

void cls(void) {
  c_clrscr();
}

void delay(int t) {
  float x = 1;

  while (t-- > 0) {
    x = cos(x);
  }
}