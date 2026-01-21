//
// Created by Michael Nixon on 20/1/26.
//

#include <doctest/doctest.h>
#include <math.hpp>

TEST_CASE("add works") {
    CHECK(add(1, 2) == 3);
    CHECK(add(-1, 1) == 0);
}
