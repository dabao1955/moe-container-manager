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
bool is_pipe(void)
{
  /*
   * Simply check the file type of /proc/self/fd/0
   * and return true if it is a pipe.
   */
  struct stat statbuf;
  stat("/proc/self/fd/0", &statbuf);
  if (S_ISFIFO(statbuf.st_mode))
  {
    return true;
  }
  return false;
}
void get_input(char *buf, int len)
{
  /*
   * Simply use getchar() to get input
   * and write it to *buf.
   * We do not use read() because it causes bugs.
   */
  int input = 0;
  for (int i = 0; i < len; i++)
  {
    input = getchar();
    if (input == EOF)
    {
      buf[i] = '\000';
      break;
    }
    buf[i] = (char)input;
  }
}