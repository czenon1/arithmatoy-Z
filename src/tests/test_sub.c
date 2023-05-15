#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmocka.h>

#include "arithmatoy.h"

static void test_sub_random_numbers(void **state) {
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
    sprintf(result_buffer, "%lld", lhs - rhs);

    const char *result = arithmatoy_sub(10, lhs_buffer, rhs_buffer);
    if (rhs <= lhs) {
      assert_string_equal(result, result_buffer);
    } else {
      assert_ptr_equal(result, NULL);
    }
  }
}

static void test_sub_zero(void **state) {
  const char *result = arithmatoy_sub(7, "0", "0");
  assert_string_equal(result, "0");
}

static void test_sub_with_carry(void **state) {
  const char *result = arithmatoy_sub(10, "1", "9");
  assert_ptr_equal(result, NULL);
}

static void test_sub_one(void **state) {
  const char *result1 = arithmatoy_sub(14, "0", "1");
  const char *result2 = arithmatoy_sub(32, "1", "0");
  assert_ptr_equal(result1, NULL);
  assert_string_equal(result2, "1");
}

static void test_sub_base2(void **state) {
  const char *result = arithmatoy_sub(2, "100111", "100");
  assert_string_equal(result, "100011");
}

static void test_sub_with_leading_zeros(void **state) {
  const char *result = arithmatoy_sub(2, "100111", "00000100");
  assert_string_equal(result, "100011");
}

static void test_sub_base10(void **state) {
  const char *result = arithmatoy_sub(10, "184", "15");
  assert_string_equal(result, "169");
}

static void test_sub_base16(void **state) {
  const char *result = arithmatoy_sub(16, "5abff901", "7cb4");
  assert_string_equal(result, "5abf7c4d");
}

int main() {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(test_sub_random_numbers),
      cmocka_unit_test(test_sub_with_carry),
      cmocka_unit_test(test_sub_zero),
      cmocka_unit_test(test_sub_one),
      cmocka_unit_test(test_sub_base2),
      cmocka_unit_test(test_sub_with_leading_zeros),
      cmocka_unit_test(test_sub_base10),
      cmocka_unit_test(test_sub_base16),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
