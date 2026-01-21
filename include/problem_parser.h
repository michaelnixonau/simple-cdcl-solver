//
// Created by Michael Nixon on 20/1/26.
//

#ifndef MYCLI_PROBLEM_PARSER_H
#define MYCLI_PROBLEM_PARSER_H

#include <istream>
#include <vector>
#include <string>
#include "../src/types.h"

struct ProblemLine {
    int num_variables = 0;
    int num_clauses = 0;
};

// Splits a string with a delimiter char.
std::vector<std::string> split(const std::string& s, char delim);

// Counts the number of lines in a stream
int process_stream(std::istream& in);

// Counts the number of non-comment lines in a stream.
// A "comment" is any line that begins with 'c'.
int count_non_comment_lines(std::istream& in);

// Parse a single problem line string.
ProblemLine parse_problem_line(const std::string& line);

// Parse a complete DIMACS CNF format file and return the SAT problem.
SATProblem parse_dimacs_cnf(std::istream& in);

#endif //MYCLI_PROBLEM_PARSER_H