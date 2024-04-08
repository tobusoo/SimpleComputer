#pragma once

enum keys
{
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_PLUS,
  KEY_MINUS,
  KEY_I,
  KEY_L,
  KEY_S,
  KEY_R,
  KEY_T,
  KEY_F5,
  KEY_F6,
  KEY_ESC,
  KEY_ENTER,
  KEY_UP_ARROW,
  KEY_DOWN_ARROW,
  KEY_RIGHT_ARROW,
  KEY_LEFT_ARROW,
  KEY_UNKNOWN,
};

int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout);
