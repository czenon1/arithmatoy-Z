#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "utils.h"

static void test_get_digit_value(void **state) {
  const char *all_digits = get_all_digits();
  const size_t all_digits_count = strlen(all_digits);
  assert_int_equal(all_digits_count, ALL_DIGIT_COUNT);
  for (int i = 0; i < all_digits_count; ++i) {
    assert_int_equal(i, get_digit_value(all_digits[i]));
  }
}

static void test_to_digit(void **state) {
  const char *all_digits = get_all_digits();
  for (int i = 0; i < 10; ++i) {
    assert_int_equal('0' + i, all_digits[i]);
  }
  for (int i = 10; i < ALL_DIGIT_COUNT; ++i) {
    assert_int_equal('a' + (i - 10), all_digits[i]);
  }
}

static void test_reverse(void **state) {
  {
    char tmp[] = "";
    assert_string_equal("", reverse(tmp));
  }
  {
    char tmp[] = "a";
    assert_string_equal("a", reverse(tmp));
  }
  {
    char tmp[] = "dcba";
    assert_string_equal("abcd", reverse(tmp));
  }
  {
    char tmp[] = "edcba";
    assert_string_equal("abcde", reverse(tmp));
  }
}

static void test_drop_leading_zeros(void **state) {
  assert_string_equal("a", drop_leading_zeros("a"));
  assert_string_equal("", drop_leading_zeros(""));
  assert_string_equal("a", drop_leading_zeros("0a"));
  assert_string_equal("a0", drop_leading_zeros("a0"));
  assert_string_equal("a", drop_leading_zeros("000a"));
  assert_string_equal("0", drop_leading_zeros("0"));
  assert_string_equal("0", drop_leading_zeros("000"));
}

int main() {
  struct CMUnitTest const tests[] = {
      cmocka_unit_test(test_get_digit_value),
      cmocka_unit_test(test_to_digit),
      cmocka_unit_test(test_reverse),
      cmocka_unit_test(test_drop_leading_zeros),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
