/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_NEW_PARSER_TAB_H_INCLUDED
# define YY_YY_NEW_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ACCIO = 258,                   /* ACCIO  */
    LUMOS = 259,                   /* LUMOS  */
    BEGIN_BLK = 260,               /* BEGIN_BLK  */
    END_BLK = 261,                 /* END_BLK  */
    VARIABLE = 262,                /* VARIABLE  */
    TYPE_INT = 263,                /* TYPE_INT  */
    TYPE_LONG = 264,               /* TYPE_LONG  */
    TYPE_SHORT = 265,              /* TYPE_SHORT  */
    TYPE_FLOAT = 266,              /* TYPE_FLOAT  */
    TYPE_DOUBLE = 267,             /* TYPE_DOUBLE  */
    TYPE_CHAR = 268,               /* TYPE_CHAR  */
    TYPE_VOID = 269,               /* TYPE_VOID  */
    IF = 270,                      /* IF  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    FOR = 273,                     /* FOR  */
    FUNC = 274,                    /* FUNC  */
    CALL = 275,                    /* CALL  */
    RETURN = 276,                  /* RETURN  */
    BREAK = 277,                   /* BREAK  */
    CONTINUE = 278,                /* CONTINUE  */
    AND = 279,                     /* AND  */
    OR = 280,                      /* OR  */
    NOT = 281,                     /* NOT  */
    BIT_NOT = 282,                 /* BIT_NOT  */
    EQ = 283,                      /* EQ  */
    NE = 284,                      /* NE  */
    LT = 285,                      /* LT  */
    GT = 286,                      /* GT  */
    LE = 287,                      /* LE  */
    GE = 288,                      /* GE  */
    PLUS = 289,                    /* PLUS  */
    MINUS = 290,                   /* MINUS  */
    MULT = 291,                    /* MULT  */
    DIV = 292,                     /* DIV  */
    MOD = 293,                     /* MOD  */
    BIT_AND = 294,                 /* BIT_AND  */
    BIT_OR = 295,                  /* BIT_OR  */
    BIT_XOR = 296,                 /* BIT_XOR  */
    DOLLAR = 297,                  /* DOLLAR  */
    COLON = 298,                   /* COLON  */
    ASSIGN = 299,                  /* ASSIGN  */
    COMMA = 300,                   /* COMMA  */
    LPAREN = 301,                  /* LPAREN  */
    RPAREN = 302,                  /* RPAREN  */
    ID = 303,                      /* ID  */
    NUMBER = 304,                  /* NUMBER  */
    STRING = 305,                  /* STRING  */
    CHAR_LIT = 306,                /* CHAR_LIT  */
    LOWER_THAN_ELSE = 307          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "new_parser.y"

    char* str;

#line 120 "new_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_NEW_PARSER_TAB_H_INCLUDED  */
