#include <stdio.h>
#include <stdlib.h>

#include "arithmatoy.h"
#include "utils.h"

int main(int argc, const char *argv[]) {
  if (argc < 5) {
    fprintf(
        stderr,
        "Usage: %s add|sub|mul <base> <arg1> <arg2> [--verbose]\n",
        argv[0]
    );
    return 1;
  }

  if (argc == 6 && 0 == strcmp(argv[5], "--verbose")) {
    VERBOSE = 1;
  }

  int base = atoi(argv[2]);
  if (base < 2 || base > 36) {
    fprintf(stderr, "Invalid base %d, should be between 2 and 36.\n", base);
  }

  if (0 == strcmp(argv[1], "add")) {
    printf(
        "%s + %s = %s\n",
        argv[3],
        argv[4],
        arithmatoy_add(base, argv[3], argv[4])
    );
    return 0;
  }

  if (0 == strcmp(argv[1], "sub")) {
    printf(
        "%s - %s = %s\n",
        argv[3],
        argv[4],
        arithmatoy_sub(base, argv[3], argv[4])
    );
    return 0;
  }

  if (0 == strcmp(argv[1], "mul")) {
    printf(
        "%s * %s = %s\n",
        argv[3],
        argv[4],
        arithmatoy_mul(base, argv[3], argv[4])
    );
    return 0;
  }

  fprintf(stderr, "Invalid operator %s\n", argv[1]);
  return 1;
}
