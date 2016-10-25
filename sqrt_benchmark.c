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

int main(int argc, char* argv[])
{
  struct timeval timstr;                                /* structure to hold elapsed time */
  struct rusage ru;                                     /* structure to hold CPU time--system and user */
  double wallclockBefore, wallclockAfter;               /* floating point numbers to calculate elapsed wallclock time */
  double userTime;                                      /* floating point number to record elapsed user CPU time */
  double systemTime;                                    /* floating point number to record elapsed system CPU time */

  if (argc < 2) {
    printf("Please choose a sqrt method: default, rsqrt");
  } else {
    if (0 == strncmp("default", argv[1], 8)) {

    } else if (0 == strncmp("rsqrt", argv[1], 6)) {

    } else {
      printf("Invalid sqrt method.");
    }
  }

  /* iterate for maxIters timesteps */
  gettimeofday(&timstr, NULL);
  wallclockBefore = timstr.tv_sec + (timstr.tv_usec / 1000000.0);

  // CODE GOES HERE

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

void default_sqrt() {
#pragma optimize("-no-dead-code-removal")
  for (volatile int i = 1; i < 100000; i++) {
    sqrt(i);
  }
#pragma optimize("-dead-code-removal")
}


inline float sse_rsqrt_i(float fIn) {
  if (fIn == 0) { return 0.0f; }
  float fOut;
  _mm_store_ss(&fOut, _mm_mul_ss(_mm_load_ss(&fIn), _mm_rsqrt_ss(_mm_load_ss( &fIn ))));
  return fOut;
}

void sse_rsqrt() {
#pragma optimize("-no-dead-code-removal")
  for (volatile int i = 1; i < 100000; i++) {
    sse_rsqrt_i(i);
  }
#pragma optimize("-dead-code-removal")
}