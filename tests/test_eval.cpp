#include "tests/scheme_test.h"

TEST_CASE_METHOD(SchemeTest, "Quote") {
    ExpectEq("(quote (1 2))", "(1 2)");
    ExpectEq("'(1 2)", "(1 2)");
    ExpectEq("'101", "101");
    ExpectEq("(quote (-2 . 3))", "(-2 . 3)");
}
