/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "gramatica.y"

	//Hector Jesus De La Garza Ponce
	//Oziel Alonso Garza Lopez
	extern char * yytext;
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>  /* strcpy */
	#include "uthash.h"
	#include "tablasVarProc.h"
	#include "codigosOperaciones.h"
	#include "cuadruplos.h"
	#include "pilas.h"
	#include "utilerias.h"
	#define YYERROR_VERBOSE 1
	
//----------------------------------------------------------------------------------------


void yyerror( const char *str )
{
	fprintf( stderr, "error: %s\n", str );
}

//Globales miscelaneas de Control
int tamanioIdentificadores = 25;

//Banderas
int error = 0;

//Varialbes para el manejo de las secciones
int seccVariablesGlobales = 0;
int seccVariablesLocales = 0;
int seccFuncionesImplementacion = 0;
int seccObjeto = 0;
int seccMain = 0;

//Variables para la creacion de variables en la tabla
char nombreVariable[25];
unsigned short tipoVariable;
char nombreProcedimiento[25];
char nombreObjeto[25];
int direccionVariable;

//Pilas Operandos
pila *operandos;
pila *operadores;

//Pilas Avail
pila *availEntero;
pila *availDecimal;
pila *availTexto;
pila *availBoolean;

//Contador de cuadruplos
int contadorIndice = 0;

//Variables para control
nodoOperando *operando;
nodoOperador *operador;
directorio *variable;

//Variables para control de memoria
int cantidadVariablesTemp = 1000;
int cantidadVariablesLocal = 1000;
int cantidadVariablesGlobal = 1000;

//Direcciones base para memoria
int baseMemoriaTemp = 10000;
int baseMemoriaLocal = 5000;
int baseMemoriaGlobal = 1000;

//Usado para calculo de direcciones
int cursorEntero = 1;
int cursorDecimal = 2;
int cursorTexto = 3;
int cursorBooleano = 4;

//Division de la memoria
//Por el momento solo son 1000 direcciones por cada tipo
//****************************
//Temporales
//De la 10,000 hasta la 13,999
int memoriaEnteroTemp;
int memoriaDecimalTemp;
int memoriaTextoTemp;
int memoriaBooleanoTemp;

//Locales
//De la 5,000 hasta la 8,999
int memoriaEnteroLocal;
int memoriaDecimalLocal;
int memoriaTextoLocal;
int memoriaBooleanoLocal;
//****************************

//Locales
//De la 1,000 hasta la 4,999
int memoriaEnteroGlobal;
int memoriaDecimalGlobal;
int memoriaTextoGlobal;
int memoriaBooleanoGlobal;
//****************************


//cuboSemantico
static int cuboSemantico[4][4][14];

//Lista de cuadruplos
cuadruplos *listaCuadruplos = NULL;

//Declaracion e inicializacion de la estructura objetos
directorioObjetos *objetos = NULL;



//----------------------------------------------------------------------------

void  generarMultiplicacionDivision(){
	listaCuadruplos = verificacionGeneracionCuadruplo(1 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarSumaResta(){
	listaCuadruplos = verificacionGeneracionCuadruplo(2 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarRelacional(){
	listaCuadruplos = verificacionGeneracionCuadruplo(3, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarAndOr(){
	listaCuadruplos = verificacionGeneracionCuadruplo(4, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void asignarMemoriaVariable(){
	//Checamos en que seccion nos encontramos al momento de crear una variable
	if (seccVariablesGlobales == 1) {
			//Estamos en las variables Globales
			//Determinar que tipo de variable tomaremos el dato
		switch(tipoVariable){
			case 0:
				if (memoriaEnteroGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorEntero)) {
					direccionVariable = memoriaEnteroGlobal;
					memoriaEnteroGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-entero\n");
					exit(1);
				}	
			break;

			case 1:
				if (memoriaDecimalGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorDecimal)) {
					direccionVariable = memoriaDecimalGlobal;
					memoriaDecimalGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-decimal\n");
					exit(1);
				}
			break;

			case 2:
				if (memoriaTextoGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorTexto)) {
					direccionVariable = memoriaTextoGlobal;
					memoriaTextoGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-Texto\n");
					exit(1);
				}
			break;

			case 3:
				if (memoriaBooleanoGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorBooleano)) {
					direccionVariable = memoriaBooleanoGlobal;
					memoriaBooleanoGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-Booleano\n");
					exit(1);
				}
			break;
		}

	} else if (seccVariablesLocales == 1) {
		switch(tipoVariable){
			case 0:
				if (memoriaEnteroLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorEntero)) {
					direccionVariable = memoriaEnteroLocal;
					memoriaEnteroLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-entero\n");
					exit(1);
				}
			break;

			case 1:
				if (memoriaDecimalLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorDecimal)) {
					direccionVariable = memoriaDecimalLocal;
					memoriaDecimalLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-decimal\n");
					exit(1);
				}
			break;

			case 2:
				if (memoriaTextoLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorTexto)) {
					direccionVariable = memoriaTextoLocal;
					memoriaTextoLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-Texto\n");
					exit(1);
				}
			break;

			case 3:
				if (memoriaBooleanoLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorBooleano)) {
					direccionVariable = memoriaBooleanoLocal;
					memoriaBooleanoLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-Booleano\n");
					exit(1);
				}
			break;
		}
	}
}
	
void calcularMemoriaVirtual(){
	memoriaEnteroTemp = baseMemoriaTemp + (cantidadVariablesTemp * 0);
	memoriaDecimalTemp = baseMemoriaTemp + (cantidadVariablesTemp * 1);
	memoriaTextoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 2);
	memoriaBooleanoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 3);
	memoriaEnteroLocal = baseMemoriaLocal + (cantidadVariablesLocal * 0);
	memoriaDecimalLocal = baseMemoriaLocal + (cantidadVariablesLocal * 1);
	memoriaTextoLocal =	baseMemoriaLocal + (cantidadVariablesLocal * 2);
	memoriaBooleanoLocal = baseMemoriaLocal + (cantidadVariablesLocal * 3);
	memoriaEnteroGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 0);
	memoriaDecimalGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 1);
	memoriaTextoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 2);
	memoriaBooleanoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 3);
}

int main()
{


	//Realizar escaneo de gramatica
	yyparse();
	
	//Desplegar la tabla de objetos
	return 0;
}




/* Line 268 of yacc.c  */
#line 326 "gramatica.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 256 "gramatica.y"

	char* sval;
	unsigned short ival;



/* Line 293 of yacc.c  */
#line 427 "gramatica.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 439 "gramatica.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNRULES -- Number of states.  */
#define YYNSTATES  285

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    19,    20,    24,    28,
      29,    30,    34,    38,    42,    46,    50,    55,    60,    64,
      66,    70,    72,    74,    76,    80,    84,    85,    89,    92,
      95,    96,    99,   104,   105,   109,   112,   113,   116,   119,
     122,   123,   126,   128,   130,   132,   134,   136,   138,   139,
     143,   144,   145,   149,   150,   154,   155,   159,   160,   161,
     165,   166,   170,   171,   176,   179,   182,   184,   186,   188,
     190,   192,   194,   196,   198,   203,   204,   207,   216,   217,
     220,   223,   228,   229,   232,   233,   243,   245,   247,   248,
     250,   251,   252,   259,   261,   263,   265,   267,   269,   271,
     272,   275,   277,   279,   284,   285,   288,   289,   299,   300,
     304,   305,   308,   311,   314,   317,   320,   322,   324,   327,
     331,   334,   340,   342,   344,   345,   347,   352,   354,   356,
     358,   360,   365,   368,   371,   373,   375,   377,   378,   381,
     384,   385,   388,   394,   396,   397,   400,   403,   412,   413,
     416,   425,   429
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      60,     0,    -1,    -1,    -1,    -1,    61,    98,    62,    64,
     103,   115,    25,    63,    42,   119,   121,    43,    -1,    -1,
       7,    65,    66,    -1,    44,    67,    45,    -1,    -1,    -1,
      69,    68,    67,    -1,    14,    58,    39,    -1,    15,    58,
      39,    -1,    16,    58,    39,    -1,    13,    58,    39,    -1,
      20,    58,    77,    70,    -1,    19,    58,    77,    70,    -1,
       6,    58,    72,    -1,    39,    -1,    34,    71,    39,    -1,
      73,    -1,    58,    -1,    39,    -1,     5,    58,    39,    -1,
      42,    74,    43,    -1,    -1,    75,    39,    74,    -1,    54,
      76,    -1,    57,    76,    -1,    -1,     4,    75,    -1,    44,
      84,    45,    78,    -1,    -1,    44,    84,    45,    -1,    81,
      80,    -1,    -1,    46,    79,    -1,    47,    79,    -1,    84,
      82,    -1,    -1,    83,    84,    -1,    48,    -1,    49,    -1,
      50,    -1,    51,    -1,    52,    -1,    53,    -1,    -1,    89,
      85,    86,    -1,    -1,    -1,    35,    87,    84,    -1,    -1,
      36,    88,    84,    -1,    -1,    94,    90,    91,    -1,    -1,
      -1,    37,    92,    89,    -1,    -1,    38,    93,    89,    -1,
      -1,    40,    95,    79,    41,    -1,    35,    96,    -1,    36,
      96,    -1,    96,    -1,    97,    -1,   134,    -1,    54,    -1,
      57,    -1,    56,    -1,    55,    -1,    58,    -1,     9,    44,
      99,    45,    -1,    -1,   100,    99,    -1,    18,    58,   101,
      42,   102,   103,   115,    43,    -1,    -1,    24,    58,    -1,
      12,    66,    -1,    10,    44,   104,    45,    -1,    -1,   105,
     104,    -1,    -1,   107,    58,   106,    40,   108,    41,    23,
     114,    39,    -1,    21,    -1,    22,    -1,    -1,   109,    -1,
      -1,    -1,    58,   110,     3,   112,   111,   113,    -1,    14,
      -1,    15,    -1,    13,    -1,    16,    -1,    19,    -1,    20,
      -1,    -1,     4,   109,    -1,   112,    -1,    17,    -1,    11,
      44,   116,    45,    -1,    -1,   117,   116,    -1,    -1,    58,
     118,    40,   108,    41,    42,   119,   121,    43,    -1,    -1,
       8,   120,    66,    -1,    -1,   122,   121,    -1,   123,    39,
      -1,   129,    39,    -1,   134,    39,    -1,   136,    39,    -1,
     137,    -1,   140,    -1,    58,   124,    -1,    77,    34,    79,
      -1,    34,   125,    -1,    32,    58,   126,    34,   125,    -1,
      73,    -1,    79,    -1,    -1,    77,    -1,    26,    40,   128,
      41,    -1,    14,    -1,    15,    -1,    13,    -1,    16,    -1,
      27,    40,   130,    41,    -1,   131,   133,    -1,    58,   132,
      -1,    54,    -1,    57,    -1,    55,    -1,    -1,    33,   130,
      -1,    77,   133,    -1,    -1,    33,   130,    -1,    58,   135,
      40,    79,    41,    -1,   127,    -1,    -1,    32,    58,    -1,
      23,    79,    -1,    28,    40,    79,    41,    42,   121,    43,
     138,    -1,    -1,    29,   139,    -1,    30,    40,    79,    41,
      42,   121,    43,   138,    -1,    42,   121,    43,    -1,    31,
      40,    79,    41,    42,   121,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   321,   321,   361,   373,   321,   388,   387,   399,   402,
     405,   404,   438,   445,   452,   459,   466,   471,   476,   483,
     484,   488,   489,   493,   494,   498,   501,   503,   506,   507,
     510,   512,   516,   519,   521,   525,   528,   530,   531,   535,
     538,   540,   544,   545,   546,   547,   548,   549,   554,   553,
     559,   562,   561,   572,   571,   585,   584,   591,   594,   593,
     605,   604,   618,   617,   631,   632,   633,   637,   638,   642,
     643,   644,   645,   646,   674,   676,   678,   682,   684,   686,
     690,   694,   697,   699,   704,   703,   719,   720,   723,   725,
     730,   736,   729,   744,   748,   753,   757,   761,   765,   771,
     772,   776,   777,   781,   784,   786,   791,   790,   800,   799,
     811,   813,   817,   818,   819,   820,   821,   822,   826,   830,
     831,   832,   835,   836,   839,   841,   845,   849,   849,   849,
     849,   853,   857,   858,   862,   863,   864,   867,   869,   870,
     873,   875,   880,   881,   884,   886,   890,   895,   898,   900,
     904,   905,   909
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DOSPUNTOS", "COMA", "ES", "CREAROBJETO",
  "VARIABLES_GLOBALES", "VARIABLES_LOCALES", "DECLARA_OBJETOS",
  "DECLARA_FUNCIONES", "IMPLEMENTA_FUNCIONES", "ATRIBUTOS_GLOBALES",
  "BOOLEANO", "ENTERO", "DECIMAL", "TEXTO", "NADA", "CLASE",
  "MATRIZENTERA", "MATRIZDECIMAL", "PRIVADA", "PUBLICA", "REGRESA",
  "HIJODE", "EJECUTARPROGRAMA", "LEERDELTECLADO", "DESPLIEGA", "SI",
  "SINO", "ENTONCES", "MIENTRAS", "FLECHA", "CONCATENA", "IGUAL", "MAS",
  "MENOS", "POR", "ENTRE", "PUNTOYCOMA", "APARENTESIS", "CPARENTESIS",
  "ALLAVE", "CLLAVE", "ACORCHETE", "CCORCHETE", "AMPERSAND", "BARRA",
  "COMPARA", "NEGACION", "MAYORQUE", "MENORQUE", "MAYORIGUAL",
  "MENORIGUAL", "CTEENTERA", "CTETEXTO", "CTEBOOLEANO", "CTEDECIMAL",
  "IDENTIFICADOR", "$accept", "programa", "$@1", "$@2", "$@3",
  "variables_globales", "$@4", "bloque_variables", "bloque_variables_rep",
  "$@5", "declara_variables", "declara_variables_matriz",
  "declara_variables_matriz1", "declara_variables_objeto",
  "asignacion_matriz", "asignacion_matriz_rep", "asignacion_matriz_valor",
  "asignacion_matriz_valor1", "dimensiones", "dimensiones_rep",
  "serexpresion", "expresion_and_or", "expresion", "expresion_condicional",
  "op_booleanos", "exp", "$@6", "exp_suma_resta", "$@7", "$@8", "termino",
  "$@9", "termino_multi_divide", "$@10", "$@11", "factor", "$@12",
  "factor_operando", "var_cte", "declara_objetos", "declara_objetos_rep",
  "objeto", "objeto_herencia", "atributos_globales", "declara_funciones",
  "declara_funciones_rep", "declaracion_prototipos", "$@13", "permiso",
  "parametros", "parametros_rep", "$@14", "$@15", "tipo",
  "parametros_rep1", "declaracion_prototipos_regresa",
  "implementa_funciones", "implementa_funciones_rep", "funciones", "$@16",
  "variables_locales", "$@17", "bloque", "estatuto", "asignacion",
  "asignacion1", "asignacion2", "asignacion3", "lectura", "lectura1",
  "escritura", "escritura_valores", "valores", "escritura_valores1",
  "escritura_concatena", "llama_funcion", "llama_funcion_opcional",
  "regresa", "condicional", "condicional_ifelse", "condicional_else",
  "ciclo", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    61,    62,    63,    60,    65,    64,    66,    67,
      68,    67,    69,    69,    69,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    74,    74,    75,    75,
      76,    76,    77,    78,    78,    79,    80,    80,    80,    81,
      82,    82,    83,    83,    83,    83,    83,    83,    85,    84,
      86,    87,    86,    88,    86,    90,    89,    91,    92,    91,
      93,    91,    95,    94,    94,    94,    94,    96,    96,    97,
      97,    97,    97,    97,    98,    99,    99,   100,   101,   101,
     102,   103,   104,   104,   106,   105,   107,   107,   108,   108,
     110,   111,   109,   112,   112,   112,   112,   112,   112,   113,
     113,   114,   114,   115,   116,   116,   118,   117,   120,   119,
     121,   121,   122,   122,   122,   122,   122,   122,   123,   124,
     124,   124,   125,   125,   126,   126,   127,   128,   128,   128,
     128,   129,   130,   130,   131,   131,   131,   132,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   137,   138,   138,
     139,   139,   140
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    12,     0,     3,     3,     0,
       0,     3,     3,     3,     3,     3,     4,     4,     3,     1,
       3,     1,     1,     1,     3,     3,     0,     3,     2,     2,
       0,     2,     4,     0,     3,     2,     0,     2,     2,     2,
       0,     2,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     0,     3,     0,     3,     0,     3,     0,     0,     3,
       0,     3,     0,     4,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     0,     2,     8,     0,     2,
       2,     4,     0,     2,     0,     9,     1,     1,     0,     1,
       0,     0,     6,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     1,     4,     0,     2,     0,     9,     0,     3,
       0,     2,     2,     2,     2,     2,     1,     1,     2,     3,
       2,     5,     1,     1,     0,     1,     4,     1,     1,     1,
       1,     4,     2,     2,     1,     1,     1,     0,     2,     2,
       0,     2,     5,     1,     0,     2,     2,     8,     0,     2,
       8,     3,     7
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,    75,     0,     0,     0,
      75,     6,     0,    78,    74,    76,     0,     0,     0,     0,
       0,     9,     7,    82,     0,     0,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,    86,    87,     0,
      82,     0,   104,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     9,    81,    83,    84,   106,     0,
     104,     0,    80,     0,     0,    23,    18,    15,    12,    13,
      14,     0,     0,     0,    11,     0,     0,   103,   105,     0,
       0,     0,     0,     0,     0,    62,    69,    72,    71,    70,
      73,     0,    48,    55,    66,    67,   143,    68,     0,    19,
      17,    16,    88,    88,   108,   110,    77,    24,     0,    64,
      65,     0,     0,     0,    33,    50,    57,    26,    22,     0,
      21,    90,     0,    89,     0,     0,     0,     0,     0,     0,
     144,     0,   110,     0,     0,     0,     0,   116,   117,   129,
     127,   128,   130,     0,     0,    36,    40,   145,     0,     0,
      32,    51,    53,    49,    58,    60,    56,    30,    30,     0,
       0,    20,     0,     0,     0,   109,   146,     0,     0,     0,
       0,     0,     0,   118,     5,   111,   112,   113,   114,   115,
     126,    63,     0,     0,    35,    42,    43,    44,    45,    46,
      47,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    25,    26,     0,     0,     0,   134,   136,   135,
     137,     0,   140,     0,     0,   124,   122,   123,   120,     0,
      37,    38,    41,   142,    34,    52,    54,    59,    61,    31,
      27,    95,    93,    94,    96,    97,    98,    91,   102,   101,
       0,   110,     0,   140,   133,   131,     0,   132,     0,     0,
     125,     0,   119,    99,    85,     0,   138,   139,   141,   110,
     110,     0,     0,    92,   107,     0,     0,   121,   100,   148,
     152,     0,   147,     0,   110,   149,     0,     0,     0,   151,
       0,   110,     0,   148,   150
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,    61,    12,    16,    22,    35,    54,
      36,   100,   119,    66,   216,   159,   160,   200,    72,   150,
     217,   184,   145,   191,   192,   146,   115,   153,   195,   196,
      92,   116,   156,   197,   198,    93,   111,    94,    95,     5,
       9,    10,    20,    45,    18,    39,    40,    75,    41,   122,
     123,   162,   253,   237,   263,   240,    25,    59,    60,    76,
     105,   125,   131,   132,   133,   173,   218,   251,    96,   143,
     134,   211,   212,   244,   247,    97,   113,   136,   137,   272,
     275,   138
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -187
static const yytype_int16 yypact[] =
{
    -187,    17,    48,  -187,    -8,  -187,    67,    60,    25,    47,
      67,  -187,    95,    84,  -187,  -187,    83,    88,   115,    76,
      91,    55,  -187,    78,    93,   110,  -187,   126,    81,    85,
      86,    89,    90,    92,    98,    96,  -187,  -187,  -187,    97,
      78,    99,   100,  -187,    83,    95,     3,   101,   107,   112,
     114,   105,   105,  -187,    55,  -187,  -187,  -187,  -187,   116,
     100,   117,  -187,   115,   104,  -187,  -187,  -187,  -187,  -187,
    -187,    -3,     1,     1,  -187,   123,   124,  -187,  -187,   159,
     125,   131,   132,     8,     8,  -187,  -187,  -187,  -187,  -187,
     -19,   128,  -187,  -187,  -187,  -187,  -187,  -187,   -30,  -187,
    -187,  -187,   113,   113,  -187,   -17,  -187,  -187,    63,  -187,
    -187,    -3,   119,   134,   135,    13,    73,    27,  -187,   136,
    -187,  -187,   137,  -187,   139,    83,    -3,   141,   142,   143,
     -14,   144,   -17,   145,   146,   147,   149,  -187,  -187,  -187,
    -187,  -187,  -187,   148,   150,    75,    65,  -187,    -3,    -3,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,   186,   186,   151,
     153,  -187,   190,   172,   154,  -187,  -187,    49,    -3,    -3,
     140,   -11,   163,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    -3,    -3,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    -3,   158,   155,    -3,    -3,    -3,    -3,    27,
    -187,  -187,  -187,    27,    82,    74,   159,  -187,  -187,  -187,
       6,   160,   169,   162,   164,   -18,  -187,  -187,  -187,    -3,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
     165,   -17,    49,   169,  -187,  -187,    49,  -187,   166,   167,
    -187,   173,  -187,   202,  -187,   168,  -187,  -187,  -187,   -17,
     -17,   -11,   113,  -187,  -187,   170,   171,  -187,  -187,   181,
    -187,   -23,  -187,   175,   -17,  -187,    -3,   174,   177,  -187,
     178,   -17,   176,   181,  -187
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -187,  -187,  -187,  -187,  -187,  -187,  -187,   -39,   179,  -187,
    -187,   152,  -187,  -187,   118,     9,    22,    64,   -50,  -187,
    -110,  -187,  -187,  -187,  -187,   -67,  -187,  -187,  -187,  -187,
     -78,  -187,  -187,  -187,  -187,  -187,  -187,    40,  -187,  -187,
     213,  -187,  -187,  -187,   182,   184,  -187,  -187,  -187,   127,
     -36,  -187,  -187,    23,  -187,  -187,   180,   185,  -187,  -187,
      26,  -187,  -129,  -187,  -187,  -187,   -32,  -187,  -187,  -187,
    -187,  -186,  -187,  -187,   -12,  -105,  -187,  -187,  -187,   -49,
    -187,  -187
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -146
static const yytype_int16 yytable[] =
{
     135,   144,    73,   175,    91,    62,   126,   273,    64,    82,
     127,   128,   117,   112,   129,    82,   166,     3,   170,   274,
     171,  -144,  -145,    82,    83,    84,    71,   135,   118,    85,
      71,   117,    83,    84,    82,    98,     6,    85,   193,   242,
      99,   130,    65,    86,    87,    88,    89,    90,   151,   152,
      71,    86,    87,    88,    89,    90,   256,     4,   213,   214,
     258,    28,    86,    87,    88,    89,    90,    11,    29,    30,
      31,    32,   220,   221,    33,    34,   139,   140,   141,   142,
     172,   157,   194,    13,   158,     8,   165,   231,   232,   233,
     234,   238,    14,   235,   236,   231,   232,   233,   234,    37,
      38,   235,   236,   207,   208,    17,   209,   210,    19,   252,
     154,   155,   255,   185,   186,   187,   188,   189,   190,   227,
     228,   182,   183,   109,   110,   222,    24,    21,   225,   226,
     265,   266,    23,    27,    26,    43,   135,    42,    44,    46,
      67,    53,    55,    47,    48,   277,    68,    49,    50,    71,
      51,    69,   282,    70,   135,   135,    52,    57,    58,    79,
     243,    77,    81,   102,   103,   250,   278,   104,   106,   135,
     107,   121,   108,   114,   148,   161,   135,   147,   163,   149,
     164,   167,   168,   169,   176,   177,   178,   174,   179,   180,
     199,   181,   203,   204,   202,   205,   206,   219,   215,   223,
     224,   245,   246,   248,   254,   249,   262,   261,   259,   260,
     271,   264,   230,   269,   270,   276,   120,   279,   280,   283,
     281,   229,   201,    15,    56,   101,   268,    63,   239,   267,
     124,   257,   241,    74,   284,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,    78
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-187))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     105,   111,    52,   132,    71,    44,    23,    30,     5,    26,
      27,    28,    42,    32,    31,    26,   126,     0,    32,    42,
      34,    40,    40,    26,    35,    36,    44,   132,    58,    40,
      44,    42,    35,    36,    26,    34,    44,    40,   148,    33,
      39,    58,    39,    54,    55,    56,    57,    58,    35,    36,
      44,    54,    55,    56,    57,    58,   242,     9,   168,   169,
     246,     6,    54,    55,    56,    57,    58,     7,    13,    14,
      15,    16,   182,   183,    19,    20,    13,    14,    15,    16,
     130,    54,   149,    58,    57,    18,   125,    13,    14,    15,
      16,    17,    45,    19,    20,    13,    14,    15,    16,    21,
      22,    19,    20,    54,    55,    10,    57,    58,    24,   219,
      37,    38,   241,    48,    49,    50,    51,    52,    53,   197,
     198,    46,    47,    83,    84,   192,    11,    44,   195,   196,
     259,   260,    44,    42,    58,    25,   241,    44,    12,    58,
      39,    45,    45,    58,    58,   274,    39,    58,    58,    44,
      58,    39,   281,    39,   259,   260,    58,    58,    58,    42,
     210,    45,    58,    40,    40,   215,   276,     8,    43,   274,
      39,    58,    40,    45,    40,    39,   281,    58,    41,    44,
      41,    40,    40,    40,    39,    39,    39,    43,    39,    41,
       4,    41,    39,     3,    43,    23,    42,    34,    58,    41,
      45,    41,    33,    41,    39,    41,     4,    34,    42,    42,
      29,    43,   203,    43,    43,    40,    98,    43,    41,    43,
      42,   199,   158,    10,    40,    73,   262,    45,   205,   261,
     103,   243,   206,    54,   283,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,    61,     0,     9,    98,    44,    62,    18,    99,
     100,     7,    64,    58,    45,    99,    65,    10,   103,    24,
     101,    44,    66,    44,    11,   115,    58,    42,     6,    13,
      14,    15,    16,    19,    20,    67,    69,    21,    22,   104,
     105,   107,    44,    25,    12,   102,    58,    58,    58,    58,
      58,    58,    58,    45,    68,    45,   104,    58,    58,   116,
     117,    63,    66,   103,     5,    39,    72,    39,    39,    39,
      39,    44,    77,    77,    67,   106,   118,    45,   116,    42,
     115,    58,    26,    35,    36,    40,    54,    55,    56,    57,
      58,    84,    89,    94,    96,    97,   127,   134,    34,    39,
      70,    70,    40,    40,     8,   119,    43,    39,    40,    96,
      96,    95,    32,   135,    45,    85,    90,    42,    58,    71,
      73,    58,   108,   109,   108,   120,    23,    27,    28,    31,
      58,   121,   122,   123,   129,   134,   136,   137,   140,    13,
      14,    15,    16,   128,    79,    81,    84,    58,    40,    44,
      78,    35,    36,    86,    37,    38,    91,    54,    57,    74,
      75,    39,   110,    41,    41,    66,    79,    40,    40,    40,
      32,    34,    77,   124,    43,   121,    39,    39,    39,    39,
      41,    41,    46,    47,    80,    48,    49,    50,    51,    52,
      53,    82,    83,    79,    84,    87,    88,    92,    93,     4,
      76,    76,    43,    39,     3,    23,    42,    54,    55,    57,
      58,   130,   131,    79,    79,    58,    73,    79,   125,    34,
      79,    79,    84,    41,    45,    84,    84,    89,    89,    75,
      74,    13,    14,    15,    16,    19,    20,   112,    17,   112,
     114,   119,    33,    77,   132,    41,    33,   133,    41,    41,
      77,   126,    79,   111,    39,   121,   130,   133,   130,    42,
      42,    34,     4,   113,    43,   121,   121,   125,   109,    43,
      43,    29,   138,    30,    42,   139,    40,   121,    79,    43,
      41,    42,   121,    43,   138
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 321 "gramatica.y"
    {
		//Accion numero 1
		//Inicializacion de estructuras

		//Calculamos la memoria a usar
		calcularMemoriaVirtual();

		//Creacion de las pilas en memoria
		operandos = malloc(sizeof(pila));
		operandos->tamanio = 0;
		operandos->primero = NULL;

		operadores = malloc(sizeof(pila));
		operadores->tamanio = 0;
		operadores->primero = NULL;

		//Creacion de las pilas de Avail en Memoria
		availEntero = malloc(sizeof(pila));
		availEntero->tamanio = 0;
		availEntero->primero = NULL;

		availDecimal = malloc(sizeof(pila));
		availDecimal->tamanio = 0;
		availDecimal->primero = NULL;

		availTexto = malloc(sizeof(pila));
		availTexto->tamanio = 0;
		availTexto->primero = NULL;

		availBoolean = malloc(sizeof(pila));
		availBoolean->tamanio = 0;
		availBoolean->primero = NULL;

		//Inicializacion del Avial
		inicializarAvail(availEntero, availDecimal, availTexto, availBoolean, &memoriaEnteroTemp, &memoriaDecimalTemp, &memoriaTextoTemp, &memoriaBooleanoTemp);

		//Inicializacion del CuboSemantico
		inicializarSemantica(cuboSemantico);
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 361 "gramatica.y"
    {
		//Accion numero 2
		//Agregar main a tabla de objetos, siempre habra que haber un main	
		objetos = agregarObjeto(objetos, ":main:");

		//Prendemos la bandera de MAIN
		seccMain = 1;

		//Apagamos la bandera de Objeto
		seccObjeto = 0;
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 373 "gramatica.y"
    {
		strncpy(nombreProcedimiento, "ejecutarProgama", tamanioIdentificadores);
		objetos = agregarFuncion(objetos, ":main:" ,nombreProcedimiento);

	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 379 "gramatica.y"
    {	
		//Desplegar mensaje de terminacion de compilacion
		printf("programa correctamente escrito\n");
		imprimirObjetos(objetos);
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 388 "gramatica.y"
    {
		//Prendemos la bandera de variablesGLobales
		seccVariablesGlobales=1;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 393 "gramatica.y"
    {
		//Al salir del bloque apagamos la bandera de variables globales
		seccVariablesGlobales=0;
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 405 "gramatica.y"
    {	
		//Verificamos en que parte estamos
		if(seccMain == 1){
			//Estamos en el main
			//Checar la bandera de variables
			if(seccVariablesGlobales == 1){
				//Agregar a tabla de variables globales					
				objetos = agregarVariablesGlobales(objetos, ":main:" , nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;

			} else if(seccVariablesLocales == 1){	
				//Agregar a tabla de variables locales de la funcion
				objetos = agregarVariablesLocales(objetos, ":main:", nombreProcedimiento, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;
			}
		} else if (seccObjeto == 1){
			//Estamos en un objeto
			if(seccVariablesGlobales == 1){
				//Agregar a tabla de variables globales					
				objetos = agregarVariablesGlobales(objetos, nombreObjeto, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;

			} else if(seccVariablesLocales == 1){	
				//Agregar a tabla de variables locales de la funcion
				objetos = agregarVariablesLocales(objetos, nombreObjeto, nombreProcedimiento, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;
			}
		}								
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 439 "gramatica.y"
    {				
		tipoVariable = (yyvsp[(1) - (3)].ival);
		strncpy(nombreVariable, (yyvsp[(2) - (3)].sval), tamanioIdentificadores);
		asignarMemoriaVariable();
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 446 "gramatica.y"
    {		
		tipoVariable = (yyvsp[(1) - (3)].ival);
		strncpy(nombreVariable, (yyvsp[(2) - (3)].sval), tamanioIdentificadores);
		asignarMemoriaVariable();
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 453 "gramatica.y"
    {		
		tipoVariable = (yyvsp[(1) - (3)].ival);
		strncpy(nombreVariable, (yyvsp[(2) - (3)].sval), tamanioIdentificadores);
		asignarMemoriaVariable();
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 460 "gramatica.y"
    {		
		tipoVariable = (yyvsp[(1) - (3)].ival);
		strncpy(nombreVariable, (yyvsp[(2) - (3)].sval), tamanioIdentificadores);
		asignarMemoriaVariable();
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 467 "gramatica.y"
    {		
		//Pendiente
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 472 "gramatica.y"
    {		
		//Pendiente
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 477 "gramatica.y"
    {		
		//Pendiente
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 554 "gramatica.y"
    {
		generarSumaResta();	
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 562 "gramatica.y"
    {
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_SUMA;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 572 "gramatica.y"
    {
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_RESTA;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 585 "gramatica.y"
    {
		generarMultiplicacionDivision();
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 594 "gramatica.y"
    {
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_MULTIPLICACION;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 605 "gramatica.y"
    {
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_DIVISION;
		
		//Metemos la division en la pila de operadores
		push(operadores, operador);
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 618 "gramatica.y"
    {
		//Creacion del nodo para meterlo en la pila
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_APARENTESIS;

		//Si encontramos un parentesis debemos meterlo como fondo falso
		push(operadores, operador);
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 627 "gramatica.y"
    {
		//Encontramos el cirre del parentesis lo sacamos de la pila
		pop(operadores);	
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 647 "gramatica.y"
    {	
		printf("Nombre de variable: %s", (yyvsp[(1) - (1)].sval));
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, (yyvsp[(1) - (1)].sval), tamanioIdentificadores);
		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
		
			//crearemos un nodoOperando para agregarlo a la pila
			operando = (nodoOperando*)malloc(sizeof(nodoOperando));
			operando->temp = 0;
			operando->tipo = variable->tipo; 
			strcpy(operando->nombre, variable->nombre);
			operando->direccion = variable->direccion;

			push(operandos,operando);

		} else if (seccObjeto == 1) {
			//Estamos en la funcion de un objeto
			//Pendiente
		}
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 704 "gramatica.y"
    {
		//Checamos en que parte estamos
		if(seccMain == 1){
			//Estamos en MAIN
			strncpy(nombreProcedimiento, (yyvsp[(2) - (2)].sval), tamanioIdentificadores);
			objetos = agregarFuncion(objetos, ":main:" ,nombreProcedimiento);
		} else if (seccObjeto == 1) {
			//Estams en objeto

		}
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 730 "gramatica.y"
    {
		//Actualizar el temporal con el nombre del parametro
		strncpy(nombreVariable, (yyvsp[(1) - (1)].sval), tamanioIdentificadores);
		
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 736 "gramatica.y"
    {		
		//Agregar el parametro a la tabla de variables locales de la funcion	
		objetos = agregarVariablesLocales(objetos, ":main:", nombreProcedimiento, nombreVariable, tipoVariable,1);
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 745 "gramatica.y"
    {
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 749 "gramatica.y"
    {
		
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 754 "gramatica.y"
    {
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 758 "gramatica.y"
    {
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 762 "gramatica.y"
    {
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 766 "gramatica.y"
    {
		tipoVariable=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 791 "gramatica.y"
    {
		//Actualizar el temporal con el nombre de la funcion
		strncpy(nombreProcedimiento, (yyvsp[(1) - (1)].sval), tamanioIdentificadores);
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 800 "gramatica.y"
    {
		//Prendemos la bandera de variablesGLobales
		seccVariablesLocales=1;	
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 805 "gramatica.y"
    {
		//Al salir del bloque apagamos la bandera de variables globales
		seccVariablesLocales=0;
	}
    break;



/* Line 1806 of yacc.c  */
#line 2401 "gramatica.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



