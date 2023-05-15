#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }


// ADD

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs){
  if (VERBOSE) {
    fprintf(stderr, "add: entering function\n");
  }

  // Fill the function, the goal is to compute lhs + rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result

  const size_t lhs_len = strlen(lhs);
  const size_t rhs_len = strlen(rhs);
  const size_t result_len = (lhs_len > rhs_len ? lhs_len : rhs_len) + 2;

  // 
  char *result = (char *)calloc(result_len, sizeof(char));

  unsigned int carry = 0;
  size_t i = 0;
  while (*lhs || *rhs || carry) {
    const unsigned int lhs_digit = get_digit_value(*lhs);
    const unsigned int rhs_digit = get_digit_value(*rhs);
    const unsigned int sum = lhs_digit + rhs_digit + carry;

    carry = (sum >= base ? 1 : 0);
    result[i++] = to_digit(sum % base);

    ++lhs;
    ++rhs;
}
}

// SUB !WAY

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }

  // Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
  const size_t lhs_len = strlen(lhs);
  const size_t rhs_len = strlen(rhs);
  const size_t result_len = lhs_len + 1;
  char *result = (char *)calloc(result_len, sizeof(char));

  unsigned int borrow = 0;
  size_t i = 0;
  while (*lhs || *rhs) {
    const unsigned int lhs_digit = get_digit_value(*lhs);
    const unsigned int rhs_digit = get_digit_value(*rhs);
    const unsigned int diff = lhs_digit - rhs_digit - borrow;

    borrow = (diff >= base ? 1 : 0);
    result[i++] = to_digit((diff + base) % base);

    ++lhs;
    ++rhs;
}
}
// MUL NG
// !!!!! FILTER INPUT
//        For my beloved Seg, M. Seg Fault...
//        TEST FLOAT


char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  // Initialize the result buffer with zeros
  const size_t lhs_len = strlen(lhs);
  const size_t rhs_len = strlen(rhs);
  const size_t result_size = lhs_len + rhs_len + 1; // +1 for the potential carry
  char *result = calloc(result_size, sizeof(char));
  if (!result) {
    debug_abort("Failed to allocate memory for result in arithmatoy_mul()\n");
  }

  // Multiply each digit of rhs with the digits of lhs and add the result to the buffer
  for (size_t i = 0; i < rhs_len; ++i) {
    const unsigned int digit_rhs = get_digit_value(rhs[rhs_len - i - 1]);
    if (digit_rhs >= base) {
      debug_abort("Invalid digit in rhs in arithmatoy_mul()\n");
    }
    unsigned int carry = 0;
    for (size_t j = 0; j < lhs_len; ++j) {
      const unsigned int digit_lhs = get_digit_value(lhs[lhs_len - j - 1]);
      if (digit_lhs >= base) {
        debug_abort("Invalid digit in lhs in arithmatoy_mul()\n");
      }
      const unsigned int digit_res = get_digit_value(result[i + j]);
      if (digit_res >= base) {
        debug_abort("Invalid digit in result in arithmatoy_mul()\n");
      }
      const unsigned int prod = digit_lhs * digit_rhs + digit_res + carry;
      carry = prod / base;
      const unsigned int res_digit = prod % base;
      result[i + j] = to_digit(res_digit);
    }
    result[i + lhs_len] = to_digit(carry);
  }

  // Reverse the result and drop leading zeros
  reverse(result);
  const char *result_without_leading_zeros = drop_leading_zeros(result);

  // Free the unused memory and return the result
  char *result_to_return = strdup(result_without_leading_zeros);
  arithmatoy_free(result);
  return result_to_return;
}

"""
char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  // Fill the function, the goal is to compute lhs * rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
  const size_t lhs_len = strlen(lhs);
  const size_t rhs_len = strlen(rhs);
  const size_t result_len = lhs_len + rhs_len + 1;

  // !! calloc
  char *result = (char *)calloc(result_len, sizeof(char));

  for (size_t i = 0; i < lhs_len; ++i) {
    const unsigned int lhs_digit = get_digit_value(lhs[i]);
    unsigned int carry = 0;
    size_t j = 0;

    for (; j < rhs_len; ++j) {
      const unsigned int rhs_digit = get_digit_value(rhs[j]);
      const unsigned int product = lhs_digit * rhs_digit + carry + get_digit_value(result[i+j]);

      carry = product / base;
      result[i+j] = to_digit(product % base); // check float
    }
    result[i+j] = to_digit(carry);
  }
  // ... 
  return reverse((char *)drop_leading_zeros(result));
}
"""

// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}
