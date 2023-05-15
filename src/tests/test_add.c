#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmocka.h>

#include "arithmatoy.h"

static void test_add_random_numbers(void **state) {
  srand(0);
  for (size_t i = 0; i < 4096; ++i) {
    const long long lhs = rand();
    char lhs_buffer[16];
    sprintf(lhs_buffer, "%lld", lhs);

    const long long rhs = rand();
    char rhs_buffer[16];
    sprintf(rhs_buffer, "%lld", rhs);

    char result_buffer[16];
    sprintf(result_buffer, "%lld", lhs + rhs);

    const char *result = arithmatoy_add(10, lhs_buffer, rhs_buffer);
    assert_string_equal(result, result_buffer);
  }
}

static void test_add_zero(void **state) {
  const char *result = arithmatoy_add(7, "0", "0");
  assert_string_equal(result, "0");
}

static void test_add_with_carry(void **state) {
  const char *result = arithmatoy_add(10, "1", "9");
  assert_string_equal(result, "10");
}

static void test_add_one(void **state) {
  const char *result1 = arithmatoy_add(14, "0", "1");
  const char *result2 = arithmatoy_add(32, "1", "0");
  assert_string_equal(result1, "1");
  assert_string_equal(result2, "1");
}

static void test_add_base2(void **state) {
  const char *result = arithmatoy_add(2, "100", "100111");
  assert_string_equal(result, "101011");
}

static void test_add_with_leading_zeros(void **state) {
  const char *result = arithmatoy_add(2, "00000100", "100111");
  assert_string_equal(result, "101011");
}

static void test_add_base10(void **state) {
  const char *result = arithmatoy_add(10, "12", "184");
  assert_string_equal(result, "196");
}

static void test_add_base16(void **state) {
  const char *result = arithmatoy_add(16, "7cb4", "5abff901");
  assert_string_equal(result, "5ac075b5");
}

int main() {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(test_add_random_numbers),
      cmocka_unit_test(test_add_with_carry),
      cmocka_unit_test(test_add_zero),
      cmocka_unit_test(test_add_one),
      cmocka_unit_test(test_add_base2),
      cmocka_unit_test(test_add_with_leading_zeros),
      cmocka_unit_test(test_add_base10),
      cmocka_unit_test(test_add_base16),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
