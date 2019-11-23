#include <stdio.h>

#include <time.h>

// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
    return diffInNanos;
}

int fibonacci(int n)
{
  int a = 0;
  int b = 1;
  int c = 0;

  if (n == 0) {
      return 0;
  }

  for (int i = 0;i <= n+1;i++) {
      c = a + b;
      a = b;
      b = c;
  }

  return b;
}

int main(void)
{
  struct timespec vartime = timer_start();  // begin a timer called 'vartime'
  for(int i = 0;i < 10000000;i++) {
    fibonacci(100);
    asm("");
  }
  long time_elapsed_nanos = timer_end(vartime);

  printf("Time taken (nanoseconds): %ld\n", time_elapsed_nanos);

  return 0;
}
