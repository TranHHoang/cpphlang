cmake_minimum_required(VERSION 3.2)
project(HLANG_TESTS)

add_subdirectory(lib/googletest)

#include_directories(${HLANG_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES
        ../include/hlang/parser/parser.h
        ../include/hlang/parser/expr/infix/infix.h
        ../include/hlang/parser/expr/infix/assignment.h
        ../include/hlang/parser/expr/infix/binary_operator.h
        ../include/hlang/parser/expr/infix/ternary_operator.h
        ../include/hlang/parser/expr/precedence.h
        ../include/hlang/parser/expr/prefix/prefix.h
        ../include/hlang/parser/expr/prefix/identifier.h
        ../include/hlang/parser/expr/prefix/literal.h
        ../include/hlang/parser/expr/prefix/unary_operator.h
        ../include/hlang/parser/expr/prefix/parentheses.h
        ../include/hlang/parser/expr/expr_headers.h
        ../include/hlang/error/parse_error.h
        main.cpp
        ../src/lexer/lexer.cpp
        ../src/ast/expression.cpp
        ../src/ast/statement.cpp
        ../src/parser/expr/infix/assignment.cpp
        ../src/parser/expr/infix/binary_operator.cpp
        ../src/parser/expr/infix/ternary_operator.cpp
        ../src/parser/expr/prefix/identifier_node.cpp
        ../src/parser/expr/prefix/literal.cpp
        ../src/parser/expr/prefix/unary_operator.cpp
        ../src/parser/expr/prefix/parentheses.cpp

        ../src/parser/parser.cpp
        ../include/hlang/ast/expr/literal_node.h ../include/hlang/ast/ast_headers.h ../include/hlang/ast/expr/identifier_node.h ../include/hlang/ast/expr/unary_node.h ../include/hlang/ast/expr/ternary_node.h ../include/hlang/ast/expr/binary_node.h)

add_executable(hlang_tests ${SOURCE_FILES} ../src/ast/expression.cpp)
target_link_libraries(hlang_tests gtest)
install(TARGETS hlang_tests DESTINATION bin)

