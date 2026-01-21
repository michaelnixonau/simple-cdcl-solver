//
// Created by Michael Nixon on 20/1/26.
//

#include <doctest/doctest.h>
#include <problem_parser.h>
#include <sstream>
#include <string>

// ----------------------------------------
// PROCESS_STREAM
// ----------------------------------------

TEST_CASE("process_stream: counts single line") {
    std::istringstream fake_file("abc");
    CHECK(process_stream(fake_file) == 1);
}

TEST_CASE("process_stream: counts multiple lines") {
    std::istringstream fake_file(
        "first line\n"
        "second line\n"
        "third line\n"
    );
    CHECK(process_stream(fake_file) == 3);
}

TEST_CASE("process_stream: doesn't count empty lines") {
    std::istringstream fake_file(
        "first\n"
        "\n"
        "third\n"
    );
    CHECK(process_stream(fake_file) == 2);
}

// ----------------------------------------
// COUNT_NON_COMMENT_LINES
// ----------------------------------------

TEST_CASE("count_non_comment_lines: count single line") {
    std::istringstream fake_file("regular line");
    CHECK(count_non_comment_lines(fake_file) == 1);
}


TEST_CASE("count_non_comment_lines: ignore single comment line") {
    std::istringstream fake_file("c This is a comment");
    CHECK(count_non_comment_lines(fake_file) == 0);
}

TEST_CASE("count_non_comment_lines: counts multiple lines") {
    std::istringstream fake_file(
        "first line\n"
        "second line\n"
        "third line\n"
    );
    CHECK(count_non_comment_lines(fake_file) == 3);
}

TEST_CASE("count_non_comment_lines: counts multiple lines, excluding comments") {
    std::istringstream fake_file(
        "first line\n"
        "c second line\n"
        "third line\n"
        "c fourth line\n"
    );
    CHECK(count_non_comment_lines(fake_file) == 2);
}

// ----------------------------------------
// PARSE_PROBLEM_LINE
// ----------------------------------------

TEST_CASE("parse_problem_line: parses simple problem") {
    constexpr std::string problem = "p cnf 1 2";
    const auto [num_variables, num_clauses] = parse_problem_line(problem);
    CHECK(num_variables == 1);
    CHECK(num_clauses == 2);
}

TEST_CASE("parse_problem_line: rejects non-cnf problem") {
    CHECK_THROWS(parse_problem_line("p nnf 1 2"));
}

TEST_CASE("parse_problem_line: rejects empty problem line") {
    CHECK_THROWS(parse_problem_line(""));
}

TEST_CASE("parse_problem_line: rejects incorrect number of inputs") {
    CHECK_THROWS(parse_problem_line("p cnf 1"));
}

