#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

// Fixed benchmark sizes (per assignment plan).
static const size_t k_sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
static const size_t k_num_sizes = sizeof(k_sizes) / sizeof(k_sizes[0]);

static volatile double g_checksum_fp = 0.0;
static volatile long long g_checksum_int = 0;

static inline uint64_t xorshift64(uint64_t *state) {
  uint64_t x = *state;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  *state = x;
  return x;
}

static inline uint64_t now_ns(void) {
  struct timespec ts;
  // CLOCK_MONOTONIC is a steady clock suitable for benchmarking.
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    return 0;
  }
  return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static inline int reps_for_n(size_t n) {
  // Keep runtimes reasonable and still smooth out noise.
  // For very small n we need many reps; for large n, few reps.
  const size_t target_ops = 20000000ull;  // ~20M multiply-adds.
  size_t reps = target_ops / (n ? n : 1);
  if (reps < 3) reps = 3;
  if (reps > 2000000ull) reps = 2000000ull;
  return (int)reps;
}

static void fill_schar(signed char *a, signed char *b, size_t n, uint64_t seed) {
  uint64_t st = seed;
  for (size_t i = 0; i < n; i++) {
    // Small range to reduce overflow in accumulator while still varying.
    a[i] = (signed char)((int)(xorshift64(&st) % 31) - 15);
    b[i] = (signed char)((int)(xorshift64(&st) % 31) - 15);
  }
}

static void fill_short(short *a, short *b, size_t n, uint64_t seed) {
  uint64_t st = seed;
  for (size_t i = 0; i < n; i++) {
    a[i] = (short)((int)(xorshift64(&st) % 2001) - 1000);
    b[i] = (short)((int)(xorshift64(&st) % 2001) - 1000);
  }
}

static void fill_int(int *a, int *b, size_t n, uint64_t seed) {
  uint64_t st = seed;
  for (size_t i = 0; i < n; i++) {
    a[i] = (int)((int64_t)(xorshift64(&st) % 2000001ull) - 1000000);
    b[i] = (int)((int64_t)(xorshift64(&st) % 2000001ull) - 1000000);
  }
}

static void fill_float(float *a, float *b, size_t n, uint64_t seed) {
  uint64_t st = seed;
  for (size_t i = 0; i < n; i++) {
    // Map to roughly [-1, 1].
    uint64_t ra = xorshift64(&st);
    uint64_t rb = xorshift64(&st);
    a[i] = (float)(((double)(ra & 0xffffu) / 32768.0) - 1.0);
    b[i] = (float)(((double)(rb & 0xffffu) / 32768.0) - 1.0);
  }
}

static void fill_double(double *a, double *b, size_t n, uint64_t seed) {
  uint64_t st = seed;
  for (size_t i = 0; i < n; i++) {
    uint64_t ra = xorshift64(&st);
    uint64_t rb = xorshift64(&st);
    a[i] = ((double)(ra & 0xffffu) / 32768.0) - 1.0;
    b[i] = ((double)(rb & 0xffffu) / 32768.0) - 1.0;
  }
}

static inline long long dot_schar_once(const signed char *a, const signed char *b, size_t n) {
  long long acc = 0;
  for (size_t i = 0; i < n; i++) acc += (long long)a[i] * (long long)b[i];
  return acc;
}

static inline long long dot_short_once(const short *a, const short *b, size_t n) {
  long long acc = 0;
  for (size_t i = 0; i < n; i++) acc += (long long)a[i] * (long long)b[i];
  return acc;
}

static inline long long dot_int_once(const int *a, const int *b, size_t n) {
  long long acc = 0;
  for (size_t i = 0; i < n; i++) acc += (long long)a[i] * (long long)b[i];
  return acc;
}

static inline double dot_float_once(const float *a, const float *b, size_t n) {
  double acc = 0.0;
  for (size_t i = 0; i < n; i++) acc += (double)a[i] * (double)b[i];
  return acc;
}

static inline double dot_double_once(const double *a, const double *b, size_t n) {
  double acc = 0.0;
  for (size_t i = 0; i < n; i++) acc += a[i] * b[i];
  return acc;
}

static void print_csv_header(void) {
  printf("lang,type,N,reps,total_ns,avg_ns,checksum\n");
}

static void bench_schar(size_t n) {
  signed char *a = (signed char *)malloc(n * sizeof(*a));
  signed char *b = (signed char *)malloc(n * sizeof(*b));
  if (!a || !b) {
    fprintf(stderr, "alloc failed for schar N=%zu\n", n);
    exit(1);
  }
  fill_schar(a, b, n, 0xC0FFEEu + (uint64_t)n);

  const int reps = reps_for_n(n);
  long long sum = 0;
  const uint64_t t0 = now_ns();
  for (int r = 0; r < reps; r++) sum += dot_schar_once(a, b, n);
  const uint64_t t1 = now_ns();

  g_checksum_int += sum;
  const uint64_t total = t1 - t0;
  const double avg = (double)total / (double)reps;
  printf("C,signed_char,%zu,%d,%" PRIu64 ",%.2f,%lld\n", n, reps, total, avg, (long long)g_checksum_int);

  free(a);
  free(b);
}

static void bench_short(size_t n) {
  short *a = (short *)malloc(n * sizeof(*a));
  short *b = (short *)malloc(n * sizeof(*b));
  if (!a || !b) {
    fprintf(stderr, "alloc failed for short N=%zu\n", n);
    exit(1);
  }
  fill_short(a, b, n, 0xBADC0DEu + (uint64_t)n);

  const int reps = reps_for_n(n);
  long long sum = 0;
  const uint64_t t0 = now_ns();
  for (int r = 0; r < reps; r++) sum += dot_short_once(a, b, n);
  const uint64_t t1 = now_ns();

  g_checksum_int += sum;
  const uint64_t total = t1 - t0;
  const double avg = (double)total / (double)reps;
  printf("C,short,%zu,%d,%" PRIu64 ",%.2f,%lld\n", n, reps, total, avg, (long long)g_checksum_int);

  free(a);
  free(b);
}

static void bench_int(size_t n) {
  int *a = (int *)malloc(n * sizeof(*a));
  int *b = (int *)malloc(n * sizeof(*b));
  if (!a || !b) {
    fprintf(stderr, "alloc failed for int N=%zu\n", n);
    exit(1);
  }
  fill_int(a, b, n, 0x12345678u + (uint64_t)n);

  const int reps = reps_for_n(n);
  long long sum = 0;
  const uint64_t t0 = now_ns();
  for (int r = 0; r < reps; r++) sum += dot_int_once(a, b, n);
  const uint64_t t1 = now_ns();

  g_checksum_int += sum;
  const uint64_t total = t1 - t0;
  const double avg = (double)total / (double)reps;
  printf("C,int,%zu,%d,%" PRIu64 ",%.2f,%lld\n", n, reps, total, avg, (long long)g_checksum_int);

  free(a);
  free(b);
}

static void bench_float(size_t n) {
  float *a = (float *)malloc(n * sizeof(*a));
  float *b = (float *)malloc(n * sizeof(*b));
  if (!a || !b) {
    fprintf(stderr, "alloc failed for float N=%zu\n", n);
    exit(1);
  }
  fill_float(a, b, n, 0x31415926u + (uint64_t)n);

  const int reps = reps_for_n(n);
  double sum = 0.0;
  const uint64_t t0 = now_ns();
  for (int r = 0; r < reps; r++) sum += dot_float_once(a, b, n);
  const uint64_t t1 = now_ns();

  g_checksum_fp += sum;
  const uint64_t total = t1 - t0;
  const double avg = (double)total / (double)reps;
  printf("C,float,%zu,%d,%" PRIu64 ",%.2f,%.6f\n", n, reps, total, avg, (double)g_checksum_fp);

  free(a);
  free(b);
}

static void bench_double(size_t n) {
  double *a = (double *)malloc(n * sizeof(*a));
  double *b = (double *)malloc(n * sizeof(*b));
  if (!a || !b) {
    fprintf(stderr, "alloc failed for double N=%zu\n", n);
    exit(1);
  }
  fill_double(a, b, n, 0x27182818u + (uint64_t)n);

  const int reps = reps_for_n(n);
  double sum = 0.0;
  const uint64_t t0 = now_ns();
  for (int r = 0; r < reps; r++) sum += dot_double_once(a, b, n);
  const uint64_t t1 = now_ns();

  g_checksum_fp += sum;
  const uint64_t total = t1 - t0;
  const double avg = (double)total / (double)reps;
  printf("C,double,%zu,%d,%" PRIu64 ",%.2f,%.6f\n", n, reps, total, avg, (double)g_checksum_fp);

  free(a);
  free(b);
}

int main(void) {
  print_csv_header();
  for (size_t i = 0; i < k_num_sizes; i++) bench_schar(k_sizes[i]);
  for (size_t i = 0; i < k_num_sizes; i++) bench_short(k_sizes[i]);
  for (size_t i = 0; i < k_num_sizes; i++) bench_int(k_sizes[i]);
  for (size_t i = 0; i < k_num_sizes; i++) bench_float(k_sizes[i]);
  for (size_t i = 0; i < k_num_sizes; i++) bench_double(k_sizes[i]);

  // Ensure side-effects are visible.
  fprintf(stderr, "checksum_int=%lld checksum_fp=%.6f\n", (long long)g_checksum_int, (double)g_checksum_fp);
  return 0;
}
