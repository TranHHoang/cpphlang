cmake_minimum_required(VERSION 3.2)
project(HLang)

#file(GLOB_RECURSE PROJ_SRC "../include/hlang/*.h" ".cpp")
#set(SOURCE_FILES main.cpp ${PROJ_SRC})

#set(SOURCE_FILES main.cpp lexer/lexer.cpp ../include/hlang/ast/ast_node.h ../include/hlang/visitor/ast_visitor.h ../include/hlang/ast/expression_node.h ../include/hlang/ast/statement_node.h ast/expression_node.cpp ast/statement_node.cpp ../include/hlang/parser/expr/iinfix.h ../include/hlang/parser/parser.h ../include/hlang/parser/expr/iprefix.h)

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
        lexer/lexer.cpp
        ast/expression.cpp
        ast/statement.cpp
        parser/expr/infix/assignment.cpp
        parser/expr/infix/binary_operator.cpp
        parser/expr/infix/ternary_operator.cpp
        parser/expr/prefix/identifier_node.cpp
        parser/expr/prefix/literal.cpp
        parser/expr/prefix/unary_operator.cpp
        parser/expr/prefix/parentheses.cpp

        parser/parser.cpp
        ../include/hlang/ast/expr/literal_node.h ../include/hlang/ast/ast_headers.h ../include/hlang/ast/expr/identifier_node.h ../include/hlang/ast/expr/unary_node.h ../include/hlang/ast/expr/ternary_node.h ../include/hlang/ast/expr/binary_node.h ../include/hlang/ast/expr/assignment_node.h ../include/hlang/ast/expr/array_decl_node.h)


add_executable(HLang ${SOURCE_FILES})
#target_link_libraries(divider division)
install(TARGETS HLang
        RUNTIME DESTINATION bin
        DESTINATION ${HLANG_INSTALL_BIN_DIR})
