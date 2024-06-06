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

#ifndef YY_YY_HOME_KAILL_DESKTOP_LAB3_COMPILE_PRINCIPLE_LAB3_BUILD_SYSY_TAB_HH_INCLUDED
# define YY_YY_HOME_KAILL_DESKTOP_LAB3_COMPILE_PRINCIPLE_LAB3_BUILD_SYSY_TAB_HH_INCLUDED
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
    ID = 258,                      /* ID  */
    INT_CONST = 259,               /* INT_CONST  */
    ADD = 260,                     /* ADD  */
    SUB = 261,                     /* SUB  */
    MUL = 262,                     /* MUL  */
    DIV = 263,                     /* DIV  */
    MOD = 264,                     /* MOD  */
    LT = 265,                      /* LT  */
    LE = 266,                      /* LE  */
    GT = 267,                      /* GT  */
    GE = 268,                      /* GE  */
    L_AND = 269,                   /* L_AND  */
    L_OR = 270,                    /* L_OR  */
    L_EQUAL = 271,                 /* L_EQUAL  */
    L_NOT = 272,                   /* L_NOT  */
    ASSIGN = 273,                  /* ASSIGN  */
    NE = 274,                      /* NE  */
    INT = 275,                     /* INT  */
    VOID = 276,                    /* VOID  */
    RETURN = 277,                  /* RETURN  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    WHILE = 280,                   /* WHILE  */
    BREAK = 281,                   /* BREAK  */
    CONTINUE = 282,                /* CONTINUE  */
    LP = 283,                      /* LP  */
    RP = 284,                      /* RP  */
    LB = 285,                      /* LB  */
    RB = 286,                      /* RB  */
    LC = 287,                      /* LC  */
    RC = 288,                      /* RC  */
    COMMA = 289,                   /* COMMA  */
    SEMICOLON = 290                /* SEMICOLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"

      int int_Val;
      char* str_Val;
      Root_ptr root_ptr;
      CompUnit_ptr compunit_ptr;
      ValDec_ptr valdec_ptr;
      PrimExpr_ptr primexpr_ptr;
      Block_ptr block_ptr;
      BlockItem_ptr blockitem_ptr;
      FunRParam_ptr funrparam_ptr;
      FunDef_ptr fundef_ptr;
      FunFParam_ptr funfparam_ptr;
      LVal_ptr lval_ptr;
      ExpArr_ptr exparr_ptr;
      Stmt_ptr stmt_ptr;
      AddExpr_ptr addexp_ptr;
      MulExpr_ptr mulexp_ptr;
      UnaExpr_ptr unaexpr_ptr;
      
      LOr_ptr lor_ptr;
      LAnd_ptr land_ptr;
      Eq_ptr eq_ptr;
      Rel_ptr rel_ptr; 

#line 124 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_KAILL_DESKTOP_LAB3_COMPILE_PRINCIPLE_LAB3_BUILD_SYSY_TAB_HH_INCLUDED  */
