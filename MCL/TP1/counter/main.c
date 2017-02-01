#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

#include "counter.h"

static int setup_CounterZero(void ** state) {
	counter * c = alloc_counter();

	if (c == NULL)
		return -1;

	init_counter(c);
	*state = c;

	return 0;
}

static int setup_CounterOne(void ** state) {
	counter * c = alloc_counter();

	if (c == NULL)
		return -1;

	init_counter(c);
	inc_counter(c);
	*state = c;

	return 0;
}

static int teardown(void ** state) {
	free(*state);
	return 0;
}

static void test_incCounter(void ** state) {
  counter * c = (counter *) (*state);
  inc_counter(c);
  assert_int_equal(1, c->ms);
}

static void test_decCounter(void ** state) {
  counter * c = (counter *) (*state);
  dec_counter(c);
  assert_int_equal(0, c->ms);
}

static void test_decCounter0(void ** state) {
  counter * c = (counter *) (*state);
  dec_counter(c);
  assert_int_equal(0, c->ms);
}

int main() {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(test_incCounter, setup_CounterZero, teardown),
    cmocka_unit_test_setup_teardown(test_decCounter, setup_CounterOne, teardown),
    cmocka_unit_test_setup_teardown(test_decCounter0, setup_CounterZero, teardown)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
