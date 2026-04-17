%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern char* yytext;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string(const char *yy_str);
void yy_delete_buffer(YY_BUFFER_STATE b);
void yyerror(const char *s);
int yylex();

typedef struct {
    char op[16];
    char arg1[64];
    char arg2[64];
    char result[64];
} Quad;

Quad quad_table[1000];
int quad_index = 0;
int temp_count = 1;
int label_count = 1;

/* LOOP STACKS FOR BREAK / CONTINUE */
char* loop_exit_stack[100];
char* loop_continue_stack[100];
char* loop_cond_stack[100];
char* loop_body_stack[100];
int loop_top = -1;

char* new_temp() {
    char *temp = (char*)malloc(16);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char* newLabel() {
    char *label = (char*)malloc(16);
    sprintf(label, "L%d", label_count++);
    return label;
}

void emit(char* op, char* arg1, char* arg2, char* result) {
    if (quad_index >= 1000) {
        fprintf(stderr, "[Error] Quadruple table overflow. Program too large.\n");
        exit(1);
    }
    snprintf(quad_table[quad_index].op, 16, "%s", op ? op : "");
    snprintf(quad_table[quad_index].arg1, 64, "%s", arg1 ? arg1 : "");
    snprintf(quad_table[quad_index].arg2, 64, "%s", arg2 ? arg2 : "");
    snprintf(quad_table[quad_index].result, 64, "%s", result ? result : "");
    quad_index++;
}

char* read_source_from_stdin() {
    size_t capacity = 1024;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    int ch;

    if (!buffer) return NULL;
    while ((ch = getchar()) != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* resized = (char*)realloc(buffer, capacity);
            if (!resized) {
                free(buffer);
                return NULL;
            }
            buffer = resized;
        }
        buffer[length++] = (char)ch;
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

void print_source_program(const char* src) {
    char* copy = strdup(src);
    char* saveptr = NULL;
    char* line = strtok_r(copy, "\n", &saveptr);
    int line_no = 1;

    printf("\nInput Source Program (Line-by-Line):\n");
    printf("------------------------------------\n");
    while (line) {
        printf("%3d | %s\n", line_no++, line);
        line = strtok_r(NULL, "\n", &saveptr);
    }

    free(copy);
}

void print_ir_line_by_line() {
    printf("\nGenerated Intermediate Code (Line-by-Line):\n");
    printf("--------------------------------------------\n");
    for (int index = 0; index < quad_index; index++) {
        Quad *quad = &quad_table[index];
        if (strcmp(quad->op, "label") == 0) {
            printf("%3d | %s:\n", index, quad->result);
        } else if (strcmp(quad->op, "goto") == 0) {
            printf("%3d | goto %s\n", index, quad->result);
        } else if (strcmp(quad->op, "ifFalse") == 0) {
            printf("%3d | ifFalse %s goto %s\n", index, quad->arg1, quad->result);
        } else if (strcmp(quad->op, "=") == 0) {
            printf("%3d | %s = %s\n", index, quad->result, quad->arg1);
        } else if (strcmp(quad->op, "minus") == 0 || strcmp(quad->op, "!") == 0) {
            printf("%3d | %s = %s %s\n", index, quad->result, quad->op, quad->arg1);
        } else if (strcmp(quad->op, "return") == 0) {
            printf("%3d | return %s\n", index, quad->arg1);
        } else if (strcmp(quad->op, "param") == 0) {
            printf("%3d | param %s\n", index, quad->arg1);
        } else if (strcmp(quad->op, "call") == 0) {
            printf("%3d | call %s\n", index, quad->arg1);
        } else {
            printf("%3d | %s = %s %s %s\n", index, quad->result, quad->arg1, quad->op, quad->arg2);
        }
    }
}
%}

%union {
    char* str;
}

%token ACCIO LUMOS BEGIN_BLK END_BLK
%token VARIABLE TYPE_INT TYPE_LONG TYPE_SHORT TYPE_FLOAT TYPE_DOUBLE TYPE_CHAR TYPE_VOID
%token IF ELSE WHILE FOR FUNC CALL RETURN BREAK CONTINUE
%token AND OR NOT BIT_NOT
%token EQ NE LT GT LE GE
%token PLUS MINUS MULT DIV MOD BIT_AND BIT_OR BIT_XOR
%token DOLLAR COLON ASSIGN COMMA LPAREN RPAREN
%token <str> ID NUMBER STRING CHAR_LIT

%type <str> expr term factor condition rel_op if_prefix

%start program_prime

%left OR
%left AND
%left PLUS MINUS
%left MULT DIV MOD
%right NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program_prime : program ;
program : ACCIO stmt_list LUMOS ;

block : BEGIN_BLK stmt_list END_BLK ;

stmt_list : stmt_list stmt | ;
stmt : var_decl DOLLAR
     | assignment DOLLAR
     | if_stmt
     | while_stmt
     | for_stmt
     | block
     | func_decl DOLLAR
     | func_call DOLLAR
     | break_stmt DOLLAR
     | continue_stmt DOLLAR
     | return_stmt DOLLAR ;

var_decl : VARIABLE ID COLON type ;

type : TYPE_INT | TYPE_LONG | TYPE_SHORT | TYPE_FLOAT | TYPE_DOUBLE | TYPE_CHAR | TYPE_VOID ;

assignment : ID ASSIGN expr { emit("=", $3, "", $1); };

if_prefix
    : IF LPAREN condition RPAREN
      {
          char* Lfalse = newLabel();
          emit("ifFalse", $3, "", Lfalse);
          $$ = Lfalse;
      }
    ;

if_stmt
    : if_prefix block %prec LOWER_THAN_ELSE
      {
          emit("label", "", "", $1);
      }
    | if_prefix block ELSE
      {
          char* Lend = newLabel();
          emit("goto", "", "", Lend);
          emit("label", "", "", $1);
          $<str>$ = Lend;
      }
      block
      {
          emit("label", "", "", $<str>4);
      }
    ;

while_stmt 
    : WHILE
      {
          char* Lstart = newLabel();
          char* Lend = newLabel();

          emit("label", "", "", Lstart);

          if (loop_top < 99) {
              loop_exit_stack[++loop_top] = Lend;
              loop_continue_stack[loop_top] = Lstart;
          } else {
              yyerror("Maximum loop nesting depth exceeded");
          }

          $<str>$ = Lstart;
      }
      LPAREN condition RPAREN
      {
          emit("ifFalse", $4, "", loop_exit_stack[loop_top]);
      }
      block
      {
          emit("goto", "", "", $<str>2);
          emit("label", "", "", loop_exit_stack[loop_top]);
          loop_top--;
      }
    ;

for_stmt
    : FOR LPAREN assignment DOLLAR
      {
          char* Lcond = newLabel();
          char* Lbody = newLabel();
          char* Lupdate = newLabel();
          char* Lend = newLabel();

          emit("label", "", "", Lcond);

          if (loop_top < 99) {
              loop_exit_stack[++loop_top] = Lend;
              loop_continue_stack[loop_top] = Lupdate;
              loop_cond_stack[loop_top] = Lcond;
              loop_body_stack[loop_top] = Lbody;
          } else {
              yyerror("Maximum loop nesting depth exceeded");
          }
      }
      condition DOLLAR
      {
          emit("ifFalse", $6, "", loop_exit_stack[loop_top]);
          emit("goto", "", "", loop_body_stack[loop_top]);
          emit("label", "", "", loop_continue_stack[loop_top]);
      }
      assignment RPAREN
      {
          emit("goto", "", "", loop_cond_stack[loop_top]);
          emit("label", "", "", loop_body_stack[loop_top]);
      }
      block
      {
          emit("goto", "", "", loop_continue_stack[loop_top]);
          emit("label", "", "", loop_exit_stack[loop_top]);
          loop_top--;
      }
    ;

func_call : CALL ID LPAREN arg_list RPAREN { emit("call", $2, "", ""); };
arg_list : args | ;
args : args COMMA expr { emit("param", $3, "", ""); }
     | expr { emit("param", $1, "", ""); };

func_decl : FUNC type ID LPAREN param_list RPAREN block ;
param_list : param_list COMMA param | param | ;
param : ID COLON type ;

return_stmt : RETURN expr { emit("return", $2, "", ""); };

break_stmt : BREAK {
    if (loop_top >= 0)
        emit("goto", "", "", loop_exit_stack[loop_top]);
    else
        yyerror("'break' statement not within loop");
};

continue_stmt : CONTINUE {
    if (loop_top >= 0)
        emit("goto", "", "", loop_continue_stack[loop_top]);
    else
        yyerror("'continue' statement not within loop");
};

condition : expr rel_op expr { char* t = new_temp(); emit($2, $1, $3, t); $$ = t; }
          | condition AND condition { char* t = new_temp(); emit("&&", $1, $3, t); $$ = t; }
          | condition OR condition { char* t = new_temp(); emit("||", $1, $3, t); $$ = t; }
          | NOT condition { char* t = new_temp(); emit("!", $2, "", t); $$ = t; }
          | LPAREN condition RPAREN { $$ = $2; };

rel_op : LT { $$ = "<"; } | GT { $$ = ">"; } | EQ { $$ = "=="; }
       | LE { $$ = "<="; } | GE { $$ = ">="; } | NE { $$ = "!="; };

expr : expr PLUS term { char* t = new_temp(); emit("+", $1, $3, t); $$ = t; }
     | expr MINUS term { char* t = new_temp(); emit("-", $1, $3, t); $$ = t; }
     | term { $$ = $1; };

term : term MULT factor { char* t = new_temp(); emit("*", $1, $3, t); $$ = t; }
     | term DIV factor { char* t = new_temp(); emit("/", $1, $3, t); $$ = t; }
     | term MOD factor { char* t = new_temp(); emit("%", $1, $3, t); $$ = t; }
     | factor { $$ = $1; };

factor : LPAREN expr RPAREN { $$ = $2; }
       | MINUS factor { char* t = new_temp(); emit("minus", $2, "", t); $$ = t; }
       | ID { $$ = $1; }
       | NUMBER { $$ = $1; };

%%

void print_quads() {
    printf("\n%-5s %-10s %-10s %-10s %-10s\n", "Idx", "Op", "Arg1", "Arg2", "Result");
    printf("-----------------------------------------------------\n");
    for(int i = 0; i < quad_index; i++) {
        printf("%-5d %-10s %-10s %-10s %-10s\n",
            i, quad_table[i].op,
            quad_table[i].arg1,
            quad_table[i].arg2,
            quad_table[i].result);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "\033[1;31m[Syntax/Semantic Error] Line %d: %s near '%s'\033[0m\n", yylineno, s, yytext);
}

int main() {
    char* source = read_source_from_stdin();
    if (!source) {
        fprintf(stderr, "[Error] No input source provided.\n");
        return 1;
    }

    print_source_program(source);

    YY_BUFFER_STATE buffer_state = yy_scan_string(source);
    yylineno = 1;
    
    if (yyparse() == 0) {
        printf("\nParsing Successful!\n");
        print_ir_line_by_line();
        print_quads();
    } else {
        printf("\nParsing failed due to errors.\n");
    }

    yy_delete_buffer(buffer_state);
    free(source);
    return 0;
}