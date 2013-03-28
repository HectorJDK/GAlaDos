/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DOSPUNTOS = 258,
     COMA = 259,
     ES = 260,
     CREAROBJETO = 261,
     VARIABLES_GLOBALES = 262,
     VARIABLES_LOCALES = 263,
     DECLARA_OBJETOS = 264,
     DECLARA_FUNCIONES = 265,
     IMPLEMENTA_FUNCIONES = 266,
     ATRIBUTOS_GLOBALES = 267,
     BOOLEANO = 268,
     ENTERO = 269,
     DECIMAL = 270,
     TEXTO = 271,
     NADA = 272,
     CLASE = 273,
     MATRIZENTERA = 274,
     MATRIZDECIMAL = 275,
     PRIVADA = 276,
     PUBLICA = 277,
     REGRESA = 278,
     HIJODE = 279,
     EJECUTARPROGRAMA = 280,
     LEERDELTECLADO = 281,
     DESPLIEGA = 282,
     SI = 283,
     SINO = 284,
     ENTONCES = 285,
     MIENTRAS = 286,
     FLECHA = 287,
     CONCATENA = 288,
     IGUAL = 289,
     MAS = 290,
     MENOS = 291,
     POR = 292,
     ENTRE = 293,
     PUNTOYCOMA = 294,
     APARENTESIS = 295,
     CPARENTESIS = 296,
     ALLAVE = 297,
     CLLAVE = 298,
     ACORCHETE = 299,
     CCORCHETE = 300,
     AMPERSAND = 301,
     BARRA = 302,
     COMPARA = 303,
     NEGACION = 304,
     MAYORQUE = 305,
     MENORQUE = 306,
     MAYORIGUAL = 307,
     MENORIGUAL = 308,
     CTEENTERA = 309,
     CTETEXTO = 310,
     CTEBOOLEANO = 311,
     CTEDECIMAL = 312,
     IDENTIFICADOR = 313
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 199 "gramatica.y"

	char* sval;
	unsigned short ival;



/* Line 2068 of yacc.c  */
#line 115 "gramatica.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


