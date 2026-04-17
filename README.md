flex new_lexer.l
bison -d new_parser.y
gcc lex.yy.x new_parser.tab.c -o wizard_compiler
,/wizard_compiler < test_case1.txt
