cmake_minimum_required(VERSION 3.2)
project(HLANG_TESTS)

add_subdirectory(lib/googletest)

#include_directories(${HLANG_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES
        ../include/hlang/parser/expr_parser.h
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
        ../include/hlang/ast/expr/literal.h
        ../include/hlang/ast/ast_headers.h
        ../include/hlang/ast/expr/identifier.h
        ../include/hlang/ast/expr/unary_operator.h
        ../include/hlang/ast/expr/ternary_operator.h
        ../include/hlang/ast/expr/binary_operator.h
        ../src/lexer/lexer.cpp
        ../src/ast/expression.cpp
        ../src/ast/statement.cpp
        ../src/parser/expr/infix/assignment.cpp
        ../src/parser/expr/infix/binary_operator.cpp
        ../src/parser/expr/infix/ternary_operator.cpp
        ../src/parser/expr/prefix/identifier.cpp
        ../src/parser/expr/prefix/literal.cpp
        ../src/parser/expr/prefix/unary_operator.cpp
        ../src/parser/expr/prefix/parentheses.cpp
        ../src/parser/expr_parser.cpp
        src/demo_tests.cpp
        src/run_all_tests.cpp
        main.cpp ../include/hlang/visitor/analyzer/analyzer.h ../src/visitor/analyzer/analyzer.cpp ../include/hlang/error/type_error.h ../include/hlang/visitor/generator/cpp_gen.h ../src/visitor/generator/cpp_gen.cpp ../include/hlang/parser/stmt_parser.h ../src/parser/stmt_parser.cpp ../include/hlang/visitor/generator/cpp_emitter.h ../src/visitor/generator/cpp_emitter.cpp ../include/hlang/parser/expr/infix/call.h ../src/parser/expr/infix/call.cpp ../include/hlang/ast/expr/call.h ../include/hlang/ast/stmt/program.h ../include/hlang/ast/stmt/proc_decl.h ../include/hlang/ast/stmt/stmts.h ../include/hlang/ast/stmt/block.h ../include/hlang/ast/stmt/assignment.h ../include/hlang/ast/stmt/var_decl.h ../include/hlang/ast/stmt/params_decl.h ../include/hlang/ast/stmt/call.h ../include/hlang/ast/stmt/if.h ../include/hlang/ast/stmt/for.h ../include/hlang/ast/expr/range.h ../include/hlang/builtin/range.h)

add_executable(hlang_tests ${SOURCE_FILES} ../src/ast/expression.cpp)
#target_link_libraries(hlang_tests ${llvm_libs})
target_link_libraries(hlang_tests gtest)
install(TARGETS hlang_tests DESTINATION bin)

