/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "new_parser.y"

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

#line 200 "new_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "new_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ACCIO = 3,                      /* ACCIO  */
  YYSYMBOL_LUMOS = 4,                      /* LUMOS  */
  YYSYMBOL_BEGIN_BLK = 5,                  /* BEGIN_BLK  */
  YYSYMBOL_END_BLK = 6,                    /* END_BLK  */
  YYSYMBOL_VARIABLE = 7,                   /* VARIABLE  */
  YYSYMBOL_TYPE_INT = 8,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_LONG = 9,                  /* TYPE_LONG  */
  YYSYMBOL_TYPE_SHORT = 10,                /* TYPE_SHORT  */
  YYSYMBOL_TYPE_FLOAT = 11,                /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_DOUBLE = 12,               /* TYPE_DOUBLE  */
  YYSYMBOL_TYPE_CHAR = 13,                 /* TYPE_CHAR  */
  YYSYMBOL_TYPE_VOID = 14,                 /* TYPE_VOID  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_FUNC = 19,                      /* FUNC  */
  YYSYMBOL_CALL = 20,                      /* CALL  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_BREAK = 22,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 23,                  /* CONTINUE  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_BIT_NOT = 27,                   /* BIT_NOT  */
  YYSYMBOL_EQ = 28,                        /* EQ  */
  YYSYMBOL_NE = 29,                        /* NE  */
  YYSYMBOL_LT = 30,                        /* LT  */
  YYSYMBOL_GT = 31,                        /* GT  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GE = 33,                        /* GE  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_MULT = 36,                      /* MULT  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_MOD = 38,                       /* MOD  */
  YYSYMBOL_BIT_AND = 39,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 40,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 41,                   /* BIT_XOR  */
  YYSYMBOL_DOLLAR = 42,                    /* DOLLAR  */
  YYSYMBOL_COLON = 43,                     /* COLON  */
  YYSYMBOL_ASSIGN = 44,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_LPAREN = 46,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 47,                    /* RPAREN  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_NUMBER = 49,                    /* NUMBER  */
  YYSYMBOL_STRING = 50,                    /* STRING  */
  YYSYMBOL_CHAR_LIT = 51,                  /* CHAR_LIT  */
  YYSYMBOL_LOWER_THAN_ELSE = 52,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program_prime = 54,             /* program_prime  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_block = 56,                     /* block  */
  YYSYMBOL_stmt_list = 57,                 /* stmt_list  */
  YYSYMBOL_stmt = 58,                      /* stmt  */
  YYSYMBOL_var_decl = 59,                  /* var_decl  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_assignment = 61,                /* assignment  */
  YYSYMBOL_if_prefix = 62,                 /* if_prefix  */
  YYSYMBOL_if_stmt = 63,                   /* if_stmt  */
  YYSYMBOL_64_1 = 64,                      /* @1  */
  YYSYMBOL_while_stmt = 65,                /* while_stmt  */
  YYSYMBOL_66_2 = 66,                      /* @2  */
  YYSYMBOL_67_3 = 67,                      /* $@3  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_69_4 = 69,                      /* $@4  */
  YYSYMBOL_70_5 = 70,                      /* $@5  */
  YYSYMBOL_71_6 = 71,                      /* $@6  */
  YYSYMBOL_func_call = 72,                 /* func_call  */
  YYSYMBOL_arg_list = 73,                  /* arg_list  */
  YYSYMBOL_args = 74,                      /* args  */
  YYSYMBOL_func_decl = 75,                 /* func_decl  */
  YYSYMBOL_param_list = 76,                /* param_list  */
  YYSYMBOL_param = 77,                     /* param  */
  YYSYMBOL_return_stmt = 78,               /* return_stmt  */
  YYSYMBOL_break_stmt = 79,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 80,             /* continue_stmt  */
  YYSYMBOL_condition = 81,                 /* condition  */
  YYSYMBOL_rel_op = 82,                    /* rel_op  */
  YYSYMBOL_expr = 83,                      /* expr  */
  YYSYMBOL_term = 84,                      /* term  */
  YYSYMBOL_factor = 85                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   157,   157,   159,   161,   163,   163,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   177,   179,
     179,   179,   179,   179,   179,   179,   181,   184,   193,   198,
     197,   212,   224,   211,   237,   251,   257,   236,   270,   272,
     272,   273,   274,   276,   277,   277,   277,   278,   280,   282,
     287,   292,   293,   294,   295,   296,   298,   298,   298,   299,
     299,   299,   301,   302,   303,   305,   306,   307,   308,   310,
     311,   312,   313
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ACCIO", "LUMOS",
  "BEGIN_BLK", "END_BLK", "VARIABLE", "TYPE_INT", "TYPE_LONG",
  "TYPE_SHORT", "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_CHAR", "TYPE_VOID",
  "IF", "ELSE", "WHILE", "FOR", "FUNC", "CALL", "RETURN", "BREAK",
  "CONTINUE", "AND", "OR", "NOT", "BIT_NOT", "EQ", "NE", "LT", "GT", "LE",
  "GE", "PLUS", "MINUS", "MULT", "DIV", "MOD", "BIT_AND", "BIT_OR",
  "BIT_XOR", "DOLLAR", "COLON", "ASSIGN", "COMMA", "LPAREN", "RPAREN",
  "ID", "NUMBER", "STRING", "CHAR_LIT", "LOWER_THAN_ELSE", "$accept",
  "program_prime", "program", "block", "stmt_list", "stmt", "var_decl",
  "type", "assignment", "if_prefix", "if_stmt", "@1", "while_stmt", "@2",
  "$@3", "for_stmt", "$@4", "$@5", "$@6", "func_call", "arg_list", "args",
  "func_decl", "param_list", "param", "return_stmt", "break_stmt",
  "continue_stmt", "condition", "rel_op", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      13,   -61,    19,   -61,    23,   -61,   -61,   -61,     2,     6,
     -61,    10,   117,    12,    47,   -61,   -61,    26,   -61,   -61,
      50,    52,    67,   -61,   -61,   -61,    57,    58,    60,    61,
      63,    68,    33,   -17,    62,    59,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,    64,    69,    47,    47,   -61,   -61,    24,
     -16,   -61,    47,   -61,   -61,    90,   -61,   -61,   -61,   -61,
     -61,   -61,   117,   -17,   -17,   -12,    89,   -17,    71,    86,
      47,   -61,   -24,    47,    47,    47,    47,    47,    24,   -61,
     -61,   -61,   -10,    34,   -17,   -17,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,    47,    30,   -61,    66,    87,    65,    24,
     -61,   -16,   -16,   -61,   -61,   -61,    67,   -61,   -61,    85,
      24,   -61,   -17,    92,   -11,   -61,   -61,    47,   -61,    67,
     -18,   117,    66,    67,    24,   -61,   -61,   -61,   -61,   -61,
      59,    91,   -61,    67,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     0,     2,     0,     1,     3,     6,     0,     0,
      31,     0,     0,     0,     0,    49,    50,     0,    12,     5,
       0,     0,     0,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,    71,    72,    48,
      64,    68,     0,     7,     8,    28,    14,    13,    17,    15,
      16,     4,     0,     0,     0,     0,     0,     0,     0,     0,
      40,    70,     0,     0,     0,     0,     0,     0,    26,    29,
      18,    54,     0,     0,     0,     0,    27,    58,    61,    56,
      57,    59,    60,     0,     0,    34,    46,     0,    39,    42,
      69,    62,    63,    65,    66,    67,     0,    55,    52,    53,
      51,    32,     0,     0,     0,    45,    38,     0,    30,     0,
       0,     0,     0,     0,    41,    33,    35,    47,    44,    43,
       0,     0,    36,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   -22,   126,   -61,   -61,   -60,   -32,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,    14,   -61,   -61,   -61,   -59,   -61,
     -13,     5,   -28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,    18,     4,    19,    20,    43,    21,    22,
      23,   106,    24,    34,   119,    25,   112,   130,   133,    26,
      97,    98,    27,   114,   115,    28,    29,    30,    65,    93,
      66,    50,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    49,    80,    68,    81,    82,    84,    85,    94,    63,
      73,    74,    84,    85,    84,    85,     1,    71,    45,     5,
      75,    76,    77,   100,   126,   108,   109,     6,     7,    64,
       8,    47,    48,    72,   122,    86,   123,   107,     9,    78,
      10,    11,    12,    13,    14,    15,    16,   103,   104,   105,
      32,    83,    33,   120,    84,    85,    35,    99,    73,    74,
      44,   127,    87,    88,    89,    90,    91,    92,    73,    74,
      52,    17,     7,     7,    61,     8,    62,   111,   101,   102,
     110,   100,    45,     9,   118,    10,    11,    12,    13,    14,
      15,    16,    53,    46,    54,    47,    48,   125,   131,    56,
      57,   129,    58,    59,   124,    60,    79,    17,    67,    84,
     117,   134,    69,    95,   113,    70,    17,    87,    88,    89,
      90,    91,    92,    73,    74,    36,    37,    38,    39,    40,
      41,    42,    96,    31,   116,   121,   128,     0,   132
};

static const yytype_int16 yycheck[] =
{
      22,    14,    62,    35,    63,    64,    24,    25,    67,    26,
      34,    35,    24,    25,    24,    25,     3,    45,    35,     0,
      36,    37,    38,    47,    42,    84,    85,     4,     5,    46,
       7,    48,    49,    46,    45,    47,    47,    47,    15,    52,
      17,    18,    19,    20,    21,    22,    23,    75,    76,    77,
      48,    64,    46,   112,    24,    25,    46,    70,    34,    35,
      48,   121,    28,    29,    30,    31,    32,    33,    34,    35,
      44,    48,     5,     5,     6,     7,    43,    47,    73,    74,
      93,    47,    35,    15,   106,    17,    18,    19,    20,    21,
      22,    23,    42,    46,    42,    48,    49,   119,   130,    42,
      42,   123,    42,    42,   117,    42,    16,    48,    46,    24,
      45,   133,    48,    42,    48,    46,    48,    28,    29,    30,
      31,    32,    33,    34,    35,     8,     9,    10,    11,    12,
      13,    14,    46,     7,    47,    43,   122,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    54,    55,    57,     0,     4,     5,     7,    15,
      17,    18,    19,    20,    21,    22,    23,    48,    56,    58,
      59,    61,    62,    63,    65,    68,    72,    75,    78,    79,
      80,    57,    48,    46,    66,    46,     8,     9,    10,    11,
      12,    13,    14,    60,    48,    35,    46,    48,    49,    83,
      84,    85,    44,    42,    42,    56,    42,    42,    42,    42,
      42,     6,    43,    26,    46,    81,    83,    46,    61,    48,
      46,    85,    83,    34,    35,    36,    37,    38,    83,    16,
      60,    81,    81,    83,    24,    25,    47,    28,    29,    30,
      31,    32,    33,    82,    81,    42,    46,    73,    74,    83,
      47,    84,    84,    85,    85,    85,    64,    47,    81,    81,
      83,    47,    69,    48,    76,    77,    47,    45,    56,    67,
      81,    43,    45,    47,    83,    56,    42,    60,    77,    56,
      70,    61,    47,    71,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    60,
      60,    60,    60,    60,    60,    60,    61,    62,    63,    64,
      63,    66,    67,    65,    69,    70,    71,    68,    72,    73,
      73,    74,    74,    75,    76,    76,    76,    77,    78,    79,
      80,    81,    81,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    85,
      85,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     3,     2,     0,     2,     2,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     2,     0,
       5,     0,     0,     7,     0,     0,     0,    12,     5,     1,
       0,     3,     1,     7,     3,     1,     0,     3,     2,     1,
       1,     3,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       2,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 26: /* assignment: ID ASSIGN expr  */
#line 181 "new_parser.y"
                            { emit("=", (yyvsp[0].str), "", (yyvsp[-2].str)); }
#line 1366 "new_parser.tab.c"
    break;

  case 27: /* if_prefix: IF LPAREN condition RPAREN  */
#line 185 "new_parser.y"
      {
          char* Lfalse = newLabel();
          emit("ifFalse", (yyvsp[-1].str), "", Lfalse);
          (yyval.str) = Lfalse;
      }
#line 1376 "new_parser.tab.c"
    break;

  case 28: /* if_stmt: if_prefix block  */
#line 194 "new_parser.y"
      {
          emit("label", "", "", (yyvsp[-1].str));
      }
#line 1384 "new_parser.tab.c"
    break;

  case 29: /* @1: %empty  */
#line 198 "new_parser.y"
      {
          char* Lend = newLabel();
          emit("goto", "", "", Lend);
          emit("label", "", "", (yyvsp[-2].str));
          (yyval.str) = Lend;
      }
#line 1395 "new_parser.tab.c"
    break;

  case 30: /* if_stmt: if_prefix block ELSE @1 block  */
#line 205 "new_parser.y"
      {
          emit("label", "", "", (yyvsp[-1].str));
      }
#line 1403 "new_parser.tab.c"
    break;

  case 31: /* @2: %empty  */
#line 212 "new_parser.y"
      {
          char* Lstart = newLabel();
          char* Lend = newLabel();

          emit("label", "", "", Lstart);

          loop_exit_stack[++loop_top] = Lend;
          loop_continue_stack[loop_top] = Lstart;

          (yyval.str) = Lstart;
      }
#line 1419 "new_parser.tab.c"
    break;

  case 32: /* $@3: %empty  */
#line 224 "new_parser.y"
      {
          emit("ifFalse", (yyvsp[-1].str), "", loop_exit_stack[loop_top]);
      }
#line 1427 "new_parser.tab.c"
    break;

  case 33: /* while_stmt: WHILE @2 LPAREN condition RPAREN $@3 block  */
#line 228 "new_parser.y"
      {
          emit("goto", "", "", (yyvsp[-5].str));
          emit("label", "", "", loop_exit_stack[loop_top]);
          loop_top--;
      }
#line 1437 "new_parser.tab.c"
    break;

  case 34: /* $@4: %empty  */
#line 237 "new_parser.y"
      {
          char* Lcond = newLabel();
          char* Lbody = newLabel();
          char* Lupdate = newLabel();
          char* Lend = newLabel();

          emit("label", "", "", Lcond);

          loop_exit_stack[++loop_top] = Lend;
          loop_continue_stack[loop_top] = Lupdate;
          loop_cond_stack[loop_top] = Lcond;
          loop_body_stack[loop_top] = Lbody;
      }
#line 1455 "new_parser.tab.c"
    break;

  case 35: /* $@5: %empty  */
#line 251 "new_parser.y"
      {
          emit("ifFalse", (yyvsp[-1].str), "", loop_exit_stack[loop_top]);
          emit("goto", "", "", loop_body_stack[loop_top]);
          emit("label", "", "", loop_continue_stack[loop_top]);
      }
#line 1465 "new_parser.tab.c"
    break;

  case 36: /* $@6: %empty  */
#line 257 "new_parser.y"
      {
          emit("goto", "", "", loop_cond_stack[loop_top]);
          emit("label", "", "", loop_body_stack[loop_top]);
      }
#line 1474 "new_parser.tab.c"
    break;

  case 37: /* for_stmt: FOR LPAREN assignment DOLLAR $@4 condition DOLLAR $@5 assignment RPAREN $@6 block  */
#line 262 "new_parser.y"
      {
          emit("goto", "", "", loop_continue_stack[loop_top]);
          emit("label", "", "", loop_exit_stack[loop_top]);
          loop_top--;
      }
#line 1484 "new_parser.tab.c"
    break;

  case 38: /* func_call: CALL ID LPAREN arg_list RPAREN  */
#line 270 "new_parser.y"
                                           { emit("call", (yyvsp[-3].str), "", ""); }
#line 1490 "new_parser.tab.c"
    break;

  case 41: /* args: args COMMA expr  */
#line 273 "new_parser.y"
                       { emit("param", (yyvsp[0].str), "", ""); }
#line 1496 "new_parser.tab.c"
    break;

  case 42: /* args: expr  */
#line 274 "new_parser.y"
            { emit("param", (yyvsp[0].str), "", ""); }
#line 1502 "new_parser.tab.c"
    break;

  case 48: /* return_stmt: RETURN expr  */
#line 280 "new_parser.y"
                          { emit("return", (yyvsp[0].str), "", ""); }
#line 1508 "new_parser.tab.c"
    break;

  case 49: /* break_stmt: BREAK  */
#line 282 "new_parser.y"
                   {
    if (loop_top >= 0)
        emit("goto", "", "", loop_exit_stack[loop_top]);
}
#line 1517 "new_parser.tab.c"
    break;

  case 50: /* continue_stmt: CONTINUE  */
#line 287 "new_parser.y"
                         {
    if (loop_top >= 0)
        emit("goto", "", "", loop_continue_stack[loop_top]);
}
#line 1526 "new_parser.tab.c"
    break;

  case 51: /* condition: expr rel_op expr  */
#line 292 "new_parser.y"
                             { char* t = new_temp(); emit((yyvsp[-1].str), (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1532 "new_parser.tab.c"
    break;

  case 52: /* condition: condition AND condition  */
#line 293 "new_parser.y"
                                    { char* t = new_temp(); emit("&&", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1538 "new_parser.tab.c"
    break;

  case 53: /* condition: condition OR condition  */
#line 294 "new_parser.y"
                                   { char* t = new_temp(); emit("||", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1544 "new_parser.tab.c"
    break;

  case 54: /* condition: NOT condition  */
#line 295 "new_parser.y"
                          { char* t = new_temp(); emit("!", (yyvsp[0].str), "", t); (yyval.str) = t; }
#line 1550 "new_parser.tab.c"
    break;

  case 55: /* condition: LPAREN condition RPAREN  */
#line 296 "new_parser.y"
                                    { (yyval.str) = (yyvsp[-1].str); }
#line 1556 "new_parser.tab.c"
    break;

  case 56: /* rel_op: LT  */
#line 298 "new_parser.y"
            { (yyval.str) = "<"; }
#line 1562 "new_parser.tab.c"
    break;

  case 57: /* rel_op: GT  */
#line 298 "new_parser.y"
                               { (yyval.str) = ">"; }
#line 1568 "new_parser.tab.c"
    break;

  case 58: /* rel_op: EQ  */
#line 298 "new_parser.y"
                                                  { (yyval.str) = "=="; }
#line 1574 "new_parser.tab.c"
    break;

  case 59: /* rel_op: LE  */
#line 299 "new_parser.y"
            { (yyval.str) = "<="; }
#line 1580 "new_parser.tab.c"
    break;

  case 60: /* rel_op: GE  */
#line 299 "new_parser.y"
                                { (yyval.str) = ">="; }
#line 1586 "new_parser.tab.c"
    break;

  case 61: /* rel_op: NE  */
#line 299 "new_parser.y"
                                                    { (yyval.str) = "!="; }
#line 1592 "new_parser.tab.c"
    break;

  case 62: /* expr: expr PLUS term  */
#line 301 "new_parser.y"
                      { char* t = new_temp(); emit("+", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1598 "new_parser.tab.c"
    break;

  case 63: /* expr: expr MINUS term  */
#line 302 "new_parser.y"
                       { char* t = new_temp(); emit("-", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1604 "new_parser.tab.c"
    break;

  case 64: /* expr: term  */
#line 303 "new_parser.y"
            { (yyval.str) = (yyvsp[0].str); }
#line 1610 "new_parser.tab.c"
    break;

  case 65: /* term: term MULT factor  */
#line 305 "new_parser.y"
                        { char* t = new_temp(); emit("*", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1616 "new_parser.tab.c"
    break;

  case 66: /* term: term DIV factor  */
#line 306 "new_parser.y"
                       { char* t = new_temp(); emit("/", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1622 "new_parser.tab.c"
    break;

  case 67: /* term: term MOD factor  */
#line 307 "new_parser.y"
                      { char* t = new_temp(); emit("%", (yyvsp[-2].str), (yyvsp[0].str), t); (yyval.str) = t; }
#line 1628 "new_parser.tab.c"
    break;

  case 68: /* term: factor  */
#line 308 "new_parser.y"
              { (yyval.str) = (yyvsp[0].str); }
#line 1634 "new_parser.tab.c"
    break;

  case 69: /* factor: LPAREN expr RPAREN  */
#line 310 "new_parser.y"
                            { (yyval.str) = (yyvsp[-1].str); }
#line 1640 "new_parser.tab.c"
    break;

  case 70: /* factor: MINUS factor  */
#line 311 "new_parser.y"
                     { char* t = new_temp(); emit("minus", (yyvsp[0].str), "", t); (yyval.str) = t; }
#line 1646 "new_parser.tab.c"
    break;

  case 71: /* factor: ID  */
#line 312 "new_parser.y"
            { (yyval.str) = (yyvsp[0].str); }
#line 1652 "new_parser.tab.c"
    break;

  case 72: /* factor: NUMBER  */
#line 313 "new_parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1658 "new_parser.tab.c"
    break;


#line 1662 "new_parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 315 "new_parser.y"


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
    fprintf(stderr, "[Error] Line %d: %s near '%s'\n", yylineno, s, yytext);
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
    }

    yy_delete_buffer(buffer_state);
    free(source);
    return 0;
}
