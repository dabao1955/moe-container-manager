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
struct __attribute__((aligned(32))) ARGS
{
  unsigned int interval;
  int mode;
  int r;
  int g;
  int b;
  int depth;
  int keeptime;
};
static void parse_args(int argc, char **argv, struct ARGS *args)
{
  if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "v") == 0)
  {
    show_version_info();
    exit(0);
  }
  if (strcmp(argv[1], "typewriter") == 0 || strcmp(argv[1], "t") == 0)
  {
    args->mode = 1;
  }
  else if (strcmp(argv[1], "blink") == 0 || strcmp(argv[1], "b") == 0)
  {
    args->mode = 2;
  }
  else
  {
    error("Unknown command !");
  }
  for (int i = 2; i < argc; i++)
  {
    if (strcmp(argv[i], "--speed") == 0 || strcmp(argv[i], "-s") == 0)
    {
      i++;
      args->interval = 1000000 / (unsigned int)atoi(argv[i]);
    }
    else if (strcmp(argv[i], "--red") == 0 || strcmp(argv[i], "-r") == 0)
    {
      i++;
      args->r = atoi(argv[i]);
    }
    else if (strcmp(argv[i], "--green") == 0 || strcmp(argv[i], "-g") == 0)
    {
      i++;
      args->g = atoi(argv[i]);
    }
    else if (strcmp(argv[i], "--blue") == 0 || strcmp(argv[i], "-b") == 0)
    {
      i++;
      args->b = atoi(argv[i]);
    }
    else if (strcmp(argv[i], "--keep") == 0 || strcmp(argv[i], "-k") == 0)
    {
      i++;
      args->keeptime = atoi(argv[i]);
    }
    else if (strcmp(argv[i], "--depth") == 0 || strcmp(argv[i], "-d") == 0)
    {
      i++;
      args->depth = atoi(argv[i]);
    }
    else
    {
      error("Unknown argument !");
    }
  }
  if (args->r > 255 || args->g > 255 || args->b > 255)
  {
    error("Max RGB color value is 255 !");
  }
}
int main(int argc, char **argv)
{
  if (argc < 2)
  {
    error("Missing arguments");
  }
  struct ARGS args = {
    .interval = 100000,
    .mode = 1,
    .r = 255,
    .g = 0,
    .b = 0,
    .depth = 100,
    .keeptime = 3,
  };
  parse_args(argc, argv, &args);
  if (!is_pipe())
  {
    error("This program only gets input with a pipe!");
  }
  char buf[BUF_SIZE] = {'\000'};
  get_input(buf, BUF_SIZE);
  switch (args.mode)
  {
  case 1:
    typewriter(buf, args.interval);
    break;
  case 2:
    blink(buf, args.keeptime, args.r, args.g, args.b, args.depth, args.interval);
    break;
  default:
    break;
  }
  return 0;
}