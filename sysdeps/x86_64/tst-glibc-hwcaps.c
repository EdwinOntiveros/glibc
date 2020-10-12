/* glibc-hwcaps subdirectory test.  x86_64 version.
   Copyright (C) 2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <support/check.h>
#include <sys/param.h>

extern int marker2 (void);
extern int marker3 (void);
extern int marker4 (void);

/* Return the x86-64-vN level, 1 for the baseline.  */
static int
compute_level (void)
{
  /* These checks are not entirely accurate because they are limited
     by GCC capabilities.  But wrong results will only result from
     inconsistent CPU models involving virtualization.  */
  if (!(__builtin_cpu_supports ("sse3")
        && __builtin_cpu_supports ("sse4.1")
        && __builtin_cpu_supports ("sse4.2")
        && __builtin_cpu_supports ("ssse3")))
    return 1;
  if (!(__builtin_cpu_supports ("avx")
        && __builtin_cpu_supports ("avx2")
        && __builtin_cpu_supports ("bmi")
        && __builtin_cpu_supports ("bmi2")
        && __builtin_cpu_supports ("fma")))
    return 2;
  if (!(__builtin_cpu_supports ("avx512f")
        && __builtin_cpu_supports ("avx512bw")
        && __builtin_cpu_supports ("avx512cd")
        && __builtin_cpu_supports ("avx512dq")
        && __builtin_cpu_supports ("avx512vl")))
    return 3;
  return 4;
}

static int
do_test (void)
{
  int level = compute_level ();
  printf ("info: detected x86-64 micro-architecture level: %d\n", level);
  TEST_COMPARE (marker2 (), MIN (level, 2));
  TEST_COMPARE (marker3 (), MIN (level, 3));
  TEST_COMPARE (marker4 (), MIN (level, 4));
  return 0;
}

#include <support/test-driver.c>
