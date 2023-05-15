#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmocka.h>

#include "arithmatoy.h"

static void test_mul_random_numbers(void **state) {
  srand(0);
  for (size_t i = 0; i < 4096; ++i) {
    long long lhs = rand();
    long long rhs = rand();
    if (lhs < rhs) {
      const long long tmp = lhs;
      lhs = rhs;
      rhs = tmp;
    }

    char lhs_buffer[16];
    sprintf(lhs_buffer, "%lld", lhs);

    char rhs_buffer[16];
    sprintf(rhs_buffer, "%lld", rhs);

    char result_buffer[16];
    sprintf(result_buffer, "%lld", lhs * rhs);

    const char *result = arithmatoy_mul(10, lhs_buffer, rhs_buffer);
  }
}

static void test_mul_zero(void **state) {
  const char *result = arithmatoy_mul(7, "0", "0");
  assert_string_equal(result, "0");
}

static void test_mul_with_carry(void **state) {
  const char *result = arithmatoy_mul(10, "8", "3");
  assert_string_equal(result, "24");
}

static void test_mul_zero_one(void **state) {
  const char *result1 = arithmatoy_mul(14, "0", "1");
  const char *result2 = arithmatoy_mul(32, "1", "0");
  assert_string_equal(result1, "0");
  assert_string_equal(result2, "0");
}

static void test_mul_base2(void **state) {
  const char *result = arithmatoy_mul(2, "100111", "100");
  assert_string_equal(result, "10011100");
}

static void test_mul_with_leading_zeros(void **state) {
  const char *result = arithmatoy_mul(2, "100111", "00000100");
  assert_string_equal(result, "10011100");
}

static void test_mul_base10(void **state) {
  const char *result = arithmatoy_mul(10, "184", "15");
  assert_string_equal(result, "2760");
}

static void test_mul_base16_single_digit(void **state) {
  const char *result = arithmatoy_mul(16, "5abff901", "4");
  assert_string_equal(result, "16affe404");
}

static void test_mul_base16_two_digits(void **state) {
  const char *result = arithmatoy_mul(16, "5abff901", "b4");
  assert_string_equal(result, "3fcefb14b4");
}

static void test_mul_base16(void **state) {
  const char *result = arithmatoy_mul(16, "5abff901", "7cb4");
  assert_string_equal(result, "2c34cb9790b4");
}

int main() {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(test_mul_random_numbers),
      cmocka_unit_test(test_mul_with_carry),
      cmocka_unit_test(test_mul_zero),
      cmocka_unit_test(test_mul_zero_one),
      cmocka_unit_test(test_mul_base2),
      cmocka_unit_test(test_mul_with_leading_zeros),
      cmocka_unit_test(test_mul_base10),
      cmocka_unit_test(test_mul_base16_single_digit),
      cmocka_unit_test(test_mul_base16_two_digits),
      cmocka_unit_test(test_mul_base16),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
