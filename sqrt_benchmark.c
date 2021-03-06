/*
** Benchmark different sqrt methods.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
#include <xmmintrin.h>
#include <memory.h>

#define ITERATIONS 10000000

void default_sqrt() {
#pragma optimize("-dead-code-removal", off)
  for (volatile int i = 0; i < ITERATIONS; i++) {
    sqrt(i);
  }
#pragma optimize("-dead-code-removal", on)
}


float sse_rsqrt_i(float fIn) {
  if (fIn == 0) { return 0.0f; }
  float fOut;
  _mm_store_ss(&fOut, _mm_mul_ss(_mm_load_ss(&fIn), _mm_rsqrt_ss(_mm_load_ss( &fIn ))));
  return fOut;
}

void sse_rsqrt() {
#pragma optimize("-dead-code-removal", off)
  for (volatile int i = 0; i < ITERATIONS; i++) {
    sse_rsqrt_i(i);
  }
#pragma optimize("-dead-code-removal", on)
}

int main(int argc, char* argv[])
{
  struct timeval timstr;                                /* structure to hold elapsed time */
  struct rusage ru;                                     /* structure to hold CPU time--system and user */
  double wallclockBefore, wallclockAfter;               /* floating point numbers to calculate elapsed wallclock time */
  double userTime;                                      /* floating point number to record elapsed user CPU time */
  double systemTime;                                    /* floating point number to record elapsed system CPU time */

  if (argc < 2) {
    printf("Please choose a sqrt method: default, rsqrt");
    return 1;
  }

  /* iterate for maxIters timesteps */
  gettimeofday(&timstr, NULL);
  wallclockBefore = timstr.tv_sec + (timstr.tv_usec / 1000000.0);

  if (0 == strncmp("default", argv[1], 8)) {
    default_sqrt();
  } else if (0 == strncmp("rsqrt", argv[1], 6)) {
    sse_rsqrt();
  } else {
    printf("Invalid sqrt method.");
  }

  gettimeofday(&timstr, NULL);
  wallclockAfter = timstr.tv_sec + (timstr.tv_usec / 1000000.0);
  getrusage(RUSAGE_SELF, &ru);
  timstr = ru.ru_utime;
  userTime = timstr.tv_sec + (timstr.tv_usec / 1000000.0);
  timstr = ru.ru_stime;
  systemTime = timstr.tv_sec + (timstr.tv_usec / 1000000.0);

  /* write final values and free memory */
  printf("==done==\n");
  printf("Elapsed time:\t\t\t%.6lf (s)\n", wallclockAfter - wallclockBefore);
  printf("Elapsed user CPU time:\t\t%.6lf (s)\n", userTime);
  printf("Elapsed system CPU time:\t%.6lf (s)\n", systemTime);

  return EXIT_SUCCESS;
}