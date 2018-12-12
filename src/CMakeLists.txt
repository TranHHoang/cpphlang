cmake_minimum_required(VERSION 3.2)
project(HLang)

#file(GLOB_RECURSE PROJ_SRC "../include/hlang/*.h" ".cpp")
#set(SOURCE_FILES main.cpp ${PROJ_SRC})

#set(SOURCE_FILES main.cpp lexer/lexer.cpp ../include/hlang/ast/ast_node.h ../include/hlang/visitor/ast_visitor.h ../include/hlang/ast/expression_node.h ../include/hlang/ast/statement_node.h ast/expression_node.cpp ast/statement_node.cpp ../include/hlang/parser/expr/iinfix.h ../include/hlang/parser/parser.h ../include/hlang/parser/expr/iprefix.h)

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
        ../include/hlang/ast/expr/assignment.h
        ../include/hlang/ast/expr/array_decl.h

        lexer/lexer.cpp
        ast/expression.cpp
        ast/statement.cpp
        parser/expr/infix/assignment.cpp
        parser/expr/infix/binary_operator.cpp
        parser/expr/infix/ternary_operator.cpp
        parser/expr/prefix/identifier.cpp
        parser/expr/prefix/literal.cpp
        parser/expr/prefix/unary_operator.cpp
        parser/expr/prefix/parentheses.cpp

        parser/expr_parser.cpp
        main.cpp
        ../include/hlang/visitor/analyzer/analyzer.h visitor/analyzer/analyzer.cpp ../include/hlang/error/type_error.h ../include/hlang/visitor/generator/cpp_gen.h visitor/generator/cpp_gen.cpp ../include/hlang/parser/stmt_parser.h parser/stmt_parser.cpp ../include/hlang/visitor/generator/cpp_emitter.h visitor/generator/cpp_emitter.cpp ../include/hlang/parser/expr/infix/call.h parser/expr/infix/call.cpp ../include/hlang/ast/expr/call.h ../include/hlang/ast/stmt/program.h ../include/hlang/ast/stmt/proc_decl.h ../include/hlang/ast/stmt/stmts.h ../include/hlang/ast/stmt/block.h ../include/hlang/ast/stmt/assignment.h ../include/hlang/ast/stmt/var_decl.h ../include/hlang/ast/stmt/params_decl.h ../include/hlang/ast/stmt/call.h ../include/hlang/ast/stmt/if.h ../include/hlang/ast/stmt/for.h ../include/hlang/ast/expr/range.h ../include/hlang/builtin/range.h)


add_executable(HLang ${SOURCE_FILES})
#target_link_libraries(divider division)

# link llvm
#target_link_libraries(HLang ${llvm_libs})
# install
install(TARGETS HLang
        RUNTIME DESTINATION bin
        DESTINATION ${HLANG_INSTALL_BIN_DIR})
