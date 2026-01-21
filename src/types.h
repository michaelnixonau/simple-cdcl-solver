//
// Created by Michael Nixon on 20/1/26.
//

#ifndef MYCLI_TYPES_H
#define MYCLI_TYPES_H

#include <cstdint>
#include <vector>

using Lit = std::int32_t;
using Clause = std::vector<Lit>;
using CNF = std::vector<Clause>;

struct SATProblem {
    int num_variables;
    CNF clauses;
};

#endif //MYCLI_TYPES_H