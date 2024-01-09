#ifndef NYT_LED_MATRIX_hpp
#define NYT_LED_MATRIX_hpp

#include "led_settings.h"

static uint8_t ledAngles[8][8] = {
  {31, 38, 46, 57, 70, 80, 89, 96},
  {24, 31, 41, 55, 72, 86, 96, 102},
  {15, 21, 31, 50, 77, 96, 106, 111},
  {5, 7, 12, 31, 96, 114, 119, 122},
  {249, 247, 242, 223, 159, 141, 136, 133},
  {239, 233, 223, 204, 178, 159, 149, 144},
  {230, 223, 213, 199, 183, 169, 159, 153},
  {223, 216, 208, 197, 185, 175, 166, 159}
};

inline uint16_t *getMatrixLeds(uint8_t x, uint8_t y, uint8_t z) {
  if (x == 0) {
    if (y == 2) {
      if (z == 3) {
        static uint16_t a[] = {1, 87}; return a;
      }
    }
    if (y == 3) {
      if (z == 2) {
        static uint16_t a[] = {1, 21}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 88}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 140}; return a;
      }
    }
    if (y == 4) {
      if (z == 8) {
        static uint16_t a[] = {1, 270}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 357}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 444}; return a;
      }
    }
    if (y == 5) {
      if (z == 6) {
        static uint16_t a[] = {1, 200}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 274}; return a;
      }
    }
    if (y == 6) {
      if (z == 2) {
        static uint16_t a[] = {3, 24, 25, 27}; return a;
      }
    }
  }
  if (x == 1) {
    if (y == 0) {
      if (z == 9) {
        static uint16_t a[] = {1, 360}; return a;
      }
    }
    if (y == 1) {
      if (z == 7) {
        static uint16_t a[] = {1, 267}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 446}; return a;
      }
    }
    if (y == 2) {
      if (z == 3) {
        static uint16_t a[] = {1, 95}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 213}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 222}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 268}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {3, 358, 361, 397}; return a;
      }
    }
    if (y == 3) {
      if (z == 3) {
        static uint16_t a[] = {1, 89}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 91, 93}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {3, 211, 215, 224}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 275}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {3, 340, 349, 350}; return a;
      }
    }
    if (y == 4) {
      if (z == 1) {
        static uint16_t a[] = {1, 20}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 86}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 81, 84}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 141}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {4, 207, 208, 209, 214}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 276}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 269}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {2, 339, 398}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 445}; return a;
      }
    }
    if (y == 5) {
      if (z == 3) {
        static uint16_t a[] = {1, 80}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 77}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 142}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 202}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 279}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {1, 439}; return a;
      }
    }
    if (y == 6) {
      if (z == 2) {
        static uint16_t a[] = {2, 28, 29}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 75}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 72, 73}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {2, 147, 148}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 201}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 423}; return a;
      }
    }
    if (y == 8) {
      if (z == 3) {
        static uint16_t a[] = {1, 68}; return a;
      }
    }
    if (y == 9) {
      if (z == 6) {
        static uint16_t a[] = {1, 193}; return a;
      }
    }
  }
  if (x == 2) {
    if (y == 0) {
      if (z == 1) {
        static uint16_t a[] = {1, 11}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 262}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {2, 256, 257}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {1, 454}; return a;
      }
    }
    if (y == 1) {
      if (z == 10) {
        static uint16_t a[] = {1, 393}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {2, 456, 457}; return a;
      }
    }
    if (y == 2) {
      if (z == 3) {
        static uint16_t a[] = {1, 90}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 133}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {3, 221, 226, 230}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {3, 359, 392, 394}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {1, 494}; return a;
      }
    }
    if (y == 3) {
      if (z == 1) {
        static uint16_t a[] = {1, 19}; return a;
      }
      if (z == 2) {
        static uint16_t a[] = {1, 18}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {3, 219, 220, 223}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {2, 265, 266}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 352}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 448}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {1, 447}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {2, 491, 492}; return a;
      }
    }
    if (y == 4) {
      if (z == 6) {
        static uint16_t a[] = {3, 204, 205, 206}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 278}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 253}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {5, 341, 348, 372, 395, 399}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {1, 440}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 425}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {2, 488, 489}; return a;
      }
      if (z == 15) {
        static uint16_t a[] = {1, 490}; return a;
      }
    }
    if (y == 5) {
      if (z == 1) {
        static uint16_t a[] = {1, 22}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 79}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 78}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {4, 197, 198, 199, 203}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {3, 272, 277, 283}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 342}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {3, 430, 437, 438}; return a;
      }
    }
    if (y == 6) {
      if (z == 3) {
        static uint16_t a[] = {1, 76}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 70, 71}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {2, 190, 196}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 284}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 334}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {2, 428, 429}; return a;
      }
    }
    if (y == 7) {
      if (z == 1) {
        static uint16_t a[] = {2, 31, 32}; return a;
      }
      if (z == 2) {
        static uint16_t a[] = {1, 33}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 67}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 152, 153}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {3, 192, 194, 195}; return a;
      }
    }
  }
  if (x == 3) {
    if (y == 0) {
      if (z == 3) {
        static uint16_t a[] = {1, 126}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 125}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 242}; return a;
      }
    }
    if (y == 1) {
      if (z == 3) {
        static uint16_t a[] = {2, 97, 104}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 235}; return a;
      }
    }
    if (y == 2) {
      if (z == 3) {
        static uint16_t a[] = {5, 94, 96, 98, 99, 103}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 130}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 225}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 229}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 263}; return a;
      }
    }
    if (y == 3) {
      if (z == 1) {
        static uint16_t a[] = {1, 17}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {2, 212, 218}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 227}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 254}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 367}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {1, 450}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {2, 470, 471}; return a;
      }
    }
    if (y == 4) {
      if (z == 3) {
        static uint16_t a[] = {1, 85}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 344}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 400}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {2, 441, 451}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {4, 424, 434, 435, 443}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {2, 472, 496}; return a;
      }
      if (z == 15) {
        static uint16_t a[] = {3, 485, 486, 487}; return a;
      }
    }
    if (y == 5) {
      if (z == 12) {
        static uint16_t a[] = {2, 415, 436}; return a;
      }
    }
    if (y == 6) {
      if (z == 2) {
        static uint16_t a[] = {2, 34, 35}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 74}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 155}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 187}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {2, 290, 291}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 286}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {3, 321, 326, 333}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {2, 426, 427}; return a;
      }
    }
    if (y == 7) {
      if (z == 1) {
        static uint16_t a[] = {1, 36}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {2, 62, 63}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 64}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 185}; return a;
      }
    }
    if (y == 8) {
      if (z == 1) {
        static uint16_t a[] = {1, 41}; return a;
      }
      if (z == 2) {
        static uint16_t a[] = {2, 38, 39}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {2, 60, 61}; return a;
      }
    }
  }
  if (x == 4) {
    if (y == 0) {
      if (z == 2) {
        static uint16_t a[] = {1, 110}; return a;
      }
      if (z == 3) {
        static uint16_t a[] = {1, 116}; return a;
      }
    }
    if (y == 1) {
      if (z == 1) {
        static uint16_t a[] = {1, 8}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 129}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 231}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {2, 236, 243}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {3, 237, 250, 251}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 462}; return a;
      }
    }
    if (y == 2) {
      if (z == 5) {
        static uint16_t a[] = {1, 233}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {2, 234, 239}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {1, 255}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 387}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 366}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 449}; return a;
      }
    }
    if (y == 3) {
      if (z == 1) {
        static uint16_t a[] = {1, 13}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 228}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 365}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {2, 373, 379}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {2, 452, 499}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {3, 461, 468, 495}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {1, 481}; return a;
      }
    }
    if (y == 4) {
      if (z == 4) {
        static uint16_t a[] = {1, 92}; return a;
      }
      if (z == 5) {
        static uint16_t a[] = {1, 232}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 258}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {4, 319, 332, 386, 390}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {1, 463}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {2, 466, 497}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {1, 480}; return a;
      }
      if (z == 15) {
        static uint16_t a[] = {2, 479, 484}; return a;
      }
    }
    if (y == 5) {
      if (z == 9) {
        static uint16_t a[] = {2, 302, 303}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {4, 401, 403, 413, 414}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {1, 469}; return a;
      }
    }
    if (y == 6) {
      if (z == 4) {
        static uint16_t a[] = {1, 156}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {2, 181, 182}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {2, 288, 293}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {2, 402, 422}; return a;
      }
    }
    if (y == 7) {
      if (z == 3) {
        static uint16_t a[] = {1, 58}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {2, 59, 158}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {2, 179, 186}; return a;
      }
      if (z == 7) {
        static uint16_t a[] = {2, 183, 184}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 292}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 325}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 324}; return a;
      }
    }
    if (y == 8) {
      if (z == 1) {
        static uint16_t a[] = {1, 40}; return a;
      }
      if (z == 4) {
        static uint16_t a[] = {1, 159}; return a;
      }
    }
  }
  if (x == 5) {
    if (y == 0) {
      if (z == 11) {
        static uint16_t a[] = {1, 383}; return a;
      }
    }
    if (y == 1) {
      if (z == 11) {
        static uint16_t a[] = {2, 382, 391}; return a;
      }
    }
    if (y == 2) {
      if (z == 10) {
        static uint16_t a[] = {1, 375}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {1, 467}; return a;
      }
    }
    if (y == 3) {
      if (z == 4) {
        static uint16_t a[] = {1, 100}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {2, 368, 374}; return a;
      }
    }
    if (y == 4) {
      if (z == 10) {
        static uint16_t a[] = {1, 318}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {1, 482}; return a;
      }
      if (z == 15) {
        static uint16_t a[] = {2, 476, 483}; return a;
      }
    }
    if (y == 5) {
      if (z == 4) {
        static uint16_t a[] = {1, 157}; return a;
      }
      if (z == 8) {
        static uint16_t a[] = {1, 301}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 317}; return a;
      }
      if (z == 11) {
        static uint16_t a[] = {1, 405}; return a;
      }
      if (z == 13) {
        static uint16_t a[] = {1, 473}; return a;
      }
      if (z == 14) {
        static uint16_t a[] = {1, 474}; return a;
      }
    }
    if (y == 6) {
      if (z == 2) {
        static uint16_t a[] = {1, 44}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 323}; return a;
      }
      if (z == 12) {
        static uint16_t a[] = {3, 417, 418, 419}; return a;
      }
    }
    if (y == 7) {
      if (z == 3) {
        static uint16_t a[] = {1, 55}; return a;
      }
      if (z == 6) {
        static uint16_t a[] = {1, 178}; return a;
      }
    }
  }
  if (x == 6) {
    if (y == 1) {
      if (z == 3) {
        static uint16_t a[] = {1, 105}; return a;
      }
    }
    if (y == 3) {
      if (z == 4) {
        static uint16_t a[] = {1, 101}; return a;
      }
      if (z == 9) {
        static uint16_t a[] = {1, 369}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 378}; return a;
      }
    }
    if (y == 4) {
      if (z == 9) {
        static uint16_t a[] = {1, 380}; return a;
      }
      if (z == 10) {
        static uint16_t a[] = {1, 381}; return a;
      }
    }
    if (y == 6) {
      if (z == 12) {
        static uint16_t a[] = {2, 409, 410}; return a;
      }
    }
  }
  if (x == 7) {
    if (y == 2) {
      if (z == 4) {
        static uint16_t a[] = {1, 111}; return a;
      }
    }
  }
  if (x == 8) {
    if (y == 2) {
      if (z == 4) {
        static uint16_t a[] = {1, 112}; return a;
      }
    }
  }

  static uint16_t a[] = {0};
  return a;
}

#endif
