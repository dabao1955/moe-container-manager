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
void typewriter(char *buf, unsigned int interval)
{
  /*
   * A simple animation that prints *buf
   * to the screen, and usleep() per-character
   * to make it a typewriter effect.
   * Control characters will not trigger usleep()
   * to make sure that the output speed is correct.
   * It can only recognize control characters
   * starts with `\033` and ends with `m`.
   */
  bool control_char = false;
  for (unsigned long i = 0; i < strlen(buf); i++)
  {
    printf("%c", buf[i]);
    fflush(stdout);
    if (!control_char)
    {
      usleep(interval);
    }
    if (buf[i] == '\033')
    {
      control_char = true;
    }
    else if (buf[i] == 'm')
    {
      control_char = false;
    }
  }
  printf("\n");
}