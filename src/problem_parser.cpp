//
// Created by Michael Nixon on 20/1/26.
//

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "../include/problem_parser.h"

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        parts.push_back(item);
    }
    return parts;
}

int process_stream(std::istream& in) {
    std::string line;
    int count = 0;

    while (std::getline(in, line)) {
        if (!line.empty()) ++count;
    }
    return count;
}

int count_non_comment_lines(std::istream& in) {
    std::string line;
    int count = 0;

    while (std::getline(in, line)) {
        if (!line.empty() && line.front() != 'c') {
            ++count;
        }
    }
    return count;
}

ProblemLine parse_problem_line(const std::string& line) {
    std::vector<std::string> args = split(line, ' ');
    if (args.size() != 4) {
        throw std::runtime_error("parse_problem_line: requires 4 arguments");
    }
    if (args[0] != "p") {
        throw std::runtime_error("parse_problem_line: input must begin with 'p'");
    }
    if (args[1] != "cnf") {
        throw std::runtime_error("parse_problem_line: input must be in cnf form");
    }

    return {
        .num_variables = std::stoi(args[2]),
        .num_clauses = std::stoi(args[3]),
    };
}
