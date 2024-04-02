#pragma once

enum keys
{
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
