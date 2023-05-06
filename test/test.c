#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "lib.h"

START_TEST(test_calculator)
{
    char expression1[] = "3+5*2-67*3";
    int result1 = calculator(expression1);
    ck_assert_int_eq(result1, -388);

    char expression2[] = "10+20/5";
    int result2 = calculator(expression2);
    ck_assert_int_eq(result2, 14);

    char expression3[] = "2^3+4";
    int result3 = calculator(expression3);
    ck_assert_int_eq(result3, 12);

}
END_TEST

START_TEST(test_exponent)
{
    int numStack[100];
    char opStack[100];
    int numTop = -1;
    int opTop = -1;

    numStack[++numTop] = 5;
    numStack[++numTop] = 3;
    opStack[++opTop] = '+';

    exponent(numStack, opStack, &numTop, &opTop);

    ck_assert_int_eq(numStack[numTop], 8);
}
END_TEST

START_TEST(test_priority)
{
    char operator1 = '+';
    int result1 = priority(operator1);
    ck_assert_int_eq(result1, 1);

    char operator2 = '*';
    int result2 = priority(operator2);
    ck_assert_int_eq(result2, 2);

    char operator3 = '^';
    int result3 = priority(operator3);
    ck_assert_int_eq(result3, 3);

}
END_TEST

int main(void)
	{
		Suite *s = suite_create("calculator");
		TCase *tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_calculator);
		suite_add_tcase(s, tc_core);

        tcase_add_test(tc_core, test_exponent);
		suite_add_tcase(s, tc_core);

		SRunner *sr = srunner_create(s);
		srunner_run_all(sr, CK_VERBOSE);
		int number_failed = srunner_ntests_failed(sr);
		srunner_free(sr);

		return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
	}
