//
// Created by Michael Nixon on 20/1/26.
//

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "../include/problem_parser.h"
#include "../src/types.h"

SATProblem parse_dimacs_cnf(std::istream& in) {
    SATProblem problem;
    problem.num_variables = 0;
    
    std::string line;
    ProblemLine pl;
    bool problem_line_found = false;
    
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        
        if (line.front() == 'c') {
            continue;
        }
        
        if (line.front() == 'p') {
            pl = parse_problem_line(line);
            problem.num_variables = pl.num_variables;
            problem_line_found = true;
            continue;
        }
        
        if (!problem_line_found) {
            throw std::runtime_error("parse_dimacs_cnf: clauses found before problem line");
        }
        
        std::istringstream iss(line);
        Clause clause;
        int lit;
        
        while (iss >> lit) {
            if (lit == 0) break;
            clause.push_back(lit);
        }
        
        if (!clause.empty()) {
            problem.clauses.push_back(clause);
        }
    }
    
    if (!problem_line_found) {
        throw std::runtime_error("parse_dimacs_cnf: no problem line found");
    }
    
    return problem;
}

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
