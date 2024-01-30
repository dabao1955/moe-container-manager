// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of nekoasc, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2023 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */
#include "include/nekoasc.h"
void blink(char *buf, int keep_time, int r, int g, int b, int depth, unsigned int interval)
{
  printf("\033[?25l");
  time_t time_old = 0;
  time(&time_old);
  time_t time_now = 0;
  int r_tmp = 0, g_tmp = 0, b_tmp = 0;
  while (true)
  {
    for (int i = 0; i < depth; i++)
    {
      r_tmp = r - i > 0 ? r - i : 0;
      g_tmp = g - i > 0 ? g - i : 0;
      b_tmp = b - i > 0 ? b - i : 0;
      printf("\033c");
      printf("\033[38;2;%d;%d;%dm%s\n", r_tmp, g_tmp, b_tmp, buf);
      printf("\n");
      fflush(stdout);
      usleep(interval);
    }
    for (int i = 0; i < depth; i++)
    {
      r_tmp = r - depth + i > 0 ? r - depth + i : 0;
      g_tmp = g - depth + i > 0 ? g - depth + i : 0;
      b_tmp = b - depth + i > 0 ? b - depth + i : 0;
      printf("\033c");
      printf("\033[38;2;%d;%d;%dm%s\n", r_tmp, g_tmp, b_tmp, buf);
      printf("\n");
      fflush(stdout);
      usleep(interval);
    }
    time(&time_now);
    if (time_now - time_old >= keep_time)
    {
      break;
    }
  }
  printf("\033[?25h");
}