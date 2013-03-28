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

	extern char * yytext;
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>  /* strcpy */
	#include "uthash.h"
	#define YYERROR_VERBOSE 1
	
//----------------------------------------------------------------------------------------


void yyerror( const char *str )
{
	fprintf( stderr, "error: %s\n", str );
}


//Variables globales para la semantica-------------------------------------------------------

//Banderas
int error = 0;
int ejecutar = 0;
int variablesGlobales=0;
int funcionesD=0;
int funcionesI=0;

//Globales
int id=1;
char *nombreV=NULL;
char *tipoV=NULL;
char *datoV="dato";

char *nombreP=NULL;

char *nombreO=NULL;

char tempObjetos[25];
char tempFunciones[25];
unsigned short tempTipos;
char tempVariable[25];



//Estructura Variables uthash-------------------------------------------------------
typedef struct directorio {
        char nombre[25];              /* key */
        int tipo;
        unsigned long direccion;
        UT_hash_handle hh;         /* makes this structure hashable */
} directorio;

//Estructura Procedimientos uthash-------------------------------------------------------
typedef struct directorioProcedimientos {
        char nombre[25];
        directorio *variablesLocales;
        UT_hash_handle hh;
}directorioProcedimientos;

//Estructura Objetos uthash-------------------------------------------------------
typedef struct directorioObjetos {
        char nombre[25];
        directorio *variablesGlobales;
        directorioProcedimientos *procedimientos;
        UT_hash_handle hh;
}directorioObjetos;

//Declaracion e inicializacion de la estructura objetos
directorioObjetos *objetos = NULL;


void add_variablesLocales(char *objeto, char *funcion, char *nombre, unsigned short tipo, unsigned long direccion) {
        directorioObjetos *existeO;
        directorioProcedimientos *existeP;
        directorio *temp;

        HASH_FIND_STR(objetos, objeto, existeO);  /* existe el objeto? */
        if (existeO) {
        	    HASH_FIND_STR(existeO->procedimientos, funcion, existeP);  /* existe el procedimiento? */
       			if (existeP) {
	                HASH_FIND_STR(existeP->variablesLocales, nombre, temp);
	                if (temp==NULL) {
	                        temp = (directorio*)malloc(sizeof(directorio));
	                        strcpy(temp->nombre, nombre);
	                        temp->tipo = tipo;
	                        temp->direccion = direccion;
	                        HASH_ADD_STR(existeP->variablesLocales, nombre, temp);  /* id: name of key field */
	                } else {
	                        printf("Error, la llave se repite");
	                }
	            } else {
               		printf("Error Funcion no se encuentra");
        		}
        } else {
            printf("Error Objeto no se encuentra");
        }
}

void add_variablesGlobales(char *objeto, char *nombre, unsigned short tipo, unsigned long direccion) {
        directorioObjetos *existe;
        directorio *temp;

        HASH_FIND_STR(objetos, objeto, existe);  /* id already in the hash? */
        if (existe) {
                HASH_FIND_STR(existe->variablesGlobales, nombre, temp);
                if (temp==NULL) {
                        temp = (directorio*)malloc(sizeof(directorio));
                        strcpy(temp->nombre, nombre);
                        temp->tipo = tipo;
                        temp->direccion = direccion;
                        HASH_ADD_STR(existe->variablesGlobales, nombre, temp);  /* id: name of key field */
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Objeto no se encuentra");
        }
}



void agregarFuncion(char *objeto, char *nombre) {
        directorioProcedimientos *temp;
        directorioObjetos *existe;  

        HASH_FIND_STR(objetos, objeto, existe);  /* id already in the hash? */
        if (existe) {
                HASH_FIND_STR(existe->procedimientos, nombre, temp);
                if (temp==NULL) {
                        temp = (directorioProcedimientos*)malloc(sizeof(directorioProcedimientos));
                        strcpy(temp->nombre, nombre);                      
                        temp->variablesLocales = NULL;
                        HASH_ADD_STR(existe->procedimientos, nombre, temp);  /* id: name of key field */
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Funcion no se encuentra");
        }
}

void agregarObjeto(char *nombre){
        directorioObjetos *temp;

        HASH_FIND_STR(objetos, nombre, temp);  /* id already in the hash? */
        if (temp==NULL) {
                temp = (directorioObjetos*)malloc(sizeof(directorioObjetos));
                strcpy(temp->nombre, nombre);
                temp->variablesGlobales = NULL;
                temp->procedimientos = NULL;
          HASH_ADD_STR(objetos, nombre, temp);  /* id: name of key field */
        } else {
                printf("Error, la llave se repite");
        }       

}

void imprimirObjetos() {
			
			directorioObjetos *o;
	        directorioProcedimientos *s;
	        directorio *p;

	        //Imprimir tabla de objetos
	        for(o = objetos; o != NULL; o=(directorioObjetos*)(o->hh.next)){
		        printf("Nombre del objeto: %s \n", o->nombre);
		        //Imprimir variables globales (main)
		        for(p=o->variablesGlobales; p!= NULL; p=(struct directorio*)(p->hh.next)) {
		                printf("Sus variables globales son \n");
		                printf("Nombre de la variable: %s , tipo: %i , direccion: %lu \n", p->nombre, p->tipo, p->direccion);
		        }
		        //Imprimir procedimientos del objeto y sus tablas de variables
		        printf("Sus procedimientos son: \n");
		        for(s=o->procedimientos; s!= NULL; s=(directorioProcedimientos*)(s->hh.next)) {
		                printf("Nombre del procedimiento: %s \n", s->nombre);
		                printf("Sus variables son \n");
		                for(p=s->variablesLocales; p!= NULL; p=(struct directorio*)(p->hh.next)) {
		                        printf("Nombre de la variable: %s , tipo: %i , direccion: %lu \n", p->nombre, p->tipo, p->direccion);
		                }
		        }		        
	    	}
	}
//----------------------------------------------------------------------------

int main()
{
	//Realizar escaneo de gramatica
	yyparse();
	
	//Desplegar la tabla de objetos	
	imprimirObjetos();

	return 0;
}




/* Line 268 of yacc.c  */
#line 269 "gramatica.tab.c"

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
#line 199 "gramatica.y"

	char* sval;
	unsigned short ival;



/* Line 293 of yacc.c  */
#line 370 "gramatica.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 382 "gramatica.tab.c"

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
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNRULES -- Number of states.  */
#define YYNSTATES  278

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
       0,     0,     3,     4,     5,    17,    18,    22,    26,    27,
      28,    32,    36,    40,    44,    48,    53,    58,    62,    64,
      68,    70,    74,    76,    78,    80,    84,    88,    89,    93,
      96,    99,   100,   103,   108,   109,   113,   116,   117,   120,
     122,   124,   126,   128,   130,   132,   134,   136,   139,   140,
     143,   146,   149,   150,   153,   156,   160,   163,   166,   168,
     170,   172,   174,   176,   178,   180,   182,   187,   188,   191,
     200,   201,   204,   207,   208,   214,   215,   218,   219,   229,
     231,   233,   234,   236,   237,   238,   245,   247,   249,   251,
     253,   255,   257,   258,   261,   263,   265,   266,   272,   273,
     276,   277,   287,   290,   291,   294,   297,   300,   303,   306,
     308,   310,   313,   317,   320,   326,   328,   330,   331,   333,
     338,   340,   342,   344,   346,   351,   354,   357,   359,   361,
     363,   364,   367,   370,   371,   374,   380,   382,   383,   386,
     389,   398,   399,   402,   411,   415
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      60,     0,    -1,    -1,    -1,    61,    63,    89,    94,   107,
      25,    62,    42,   112,   113,    43,    -1,    -1,     7,    64,
      65,    -1,    44,    66,    45,    -1,    -1,    -1,    68,    67,
      66,    -1,    14,    58,    69,    -1,    15,    58,    69,    -1,
      16,    58,    69,    -1,    13,    58,    69,    -1,    20,    58,
      77,    70,    -1,    19,    58,    77,    70,    -1,     6,    58,
      72,    -1,    39,    -1,    34,    79,    39,    -1,    39,    -1,
      34,    71,    39,    -1,    73,    -1,    58,    -1,    39,    -1,
       5,    58,    39,    -1,    42,    74,    43,    -1,    -1,    75,
      39,    74,    -1,    54,    76,    -1,    57,    76,    -1,    -1,
       4,    75,    -1,    44,    82,    45,    78,    -1,    -1,    44,
      82,    45,    -1,    82,    80,    -1,    -1,    81,    82,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    46,    -1,    47,    -1,    84,    83,    -1,    -1,
      35,    82,    -1,    36,    82,    -1,    86,    85,    -1,    -1,
      37,    84,    -1,    38,    84,    -1,    40,    79,    41,    -1,
      35,    87,    -1,    36,    87,    -1,    87,    -1,    88,    -1,
     126,    -1,    54,    -1,    57,    -1,    56,    -1,    55,    -1,
      58,    -1,     9,    44,    90,    45,    -1,    -1,    91,    90,
      -1,    18,    58,    92,    42,    93,    94,   107,    43,    -1,
      -1,    24,    58,    -1,    12,    65,    -1,    -1,    10,    95,
      44,    96,    45,    -1,    -1,    97,    96,    -1,    -1,    99,
      58,    98,    40,   100,    41,    23,   106,    39,    -1,    21,
      -1,    22,    -1,    -1,   101,    -1,    -1,    -1,    58,   102,
       3,   104,   103,   105,    -1,    14,    -1,    15,    -1,    13,
      -1,    16,    -1,    19,    -1,    20,    -1,    -1,     4,   101,
      -1,   104,    -1,    17,    -1,    -1,    11,   108,    44,   109,
      45,    -1,    -1,   110,   109,    -1,    -1,    58,   111,    40,
     100,    41,    42,   112,   113,    43,    -1,     8,    65,    -1,
      -1,   114,   113,    -1,   115,    39,    -1,   121,    39,    -1,
     126,    39,    -1,   128,    39,    -1,   129,    -1,   132,    -1,
      58,   116,    -1,    77,    34,    79,    -1,    34,   117,    -1,
      32,    58,   118,    34,   117,    -1,    73,    -1,    79,    -1,
      -1,    77,    -1,    26,    40,   120,    41,    -1,    14,    -1,
      15,    -1,    13,    -1,    16,    -1,    27,    40,   122,    41,
      -1,   123,   125,    -1,    58,   124,    -1,    54,    -1,    57,
      -1,    55,    -1,    -1,    33,   122,    -1,    77,   125,    -1,
      -1,    33,   122,    -1,    58,   127,    40,    79,    41,    -1,
     119,    -1,    -1,    32,    58,    -1,    23,    79,    -1,    28,
      40,    79,    41,    42,   113,    43,   130,    -1,    -1,    29,
     131,    -1,    30,    40,    79,    41,    42,   113,    43,   130,
      -1,    42,   113,    43,    -1,    31,    40,    79,    41,    42,
     113,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   264,   264,   267,   264,   278,   277,   287,   290,   293,
     292,   307,   313,   319,   325,   331,   337,   343,   350,   351,
     355,   356,   360,   361,   365,   366,   370,   373,   375,   378,
     379,   382,   384,   388,   391,   393,   397,   400,   402,   406,
     407,   408,   409,   410,   411,   412,   413,   417,   420,   422,
     423,   427,   430,   432,   433,   437,   438,   439,   440,   444,
     445,   449,   450,   451,   452,   453,   457,   459,   461,   465,
     467,   469,   473,   478,   477,   487,   489,   494,   493,   504,
     505,   508,   510,   515,   520,   514,   527,   533,   538,   542,
     546,   550,   556,   557,   561,   562,   567,   566,   575,   577,
     582,   581,   589,   592,   594,   598,   599,   600,   601,   602,
     603,   607,   611,   612,   613,   616,   617,   620,   622,   626,
     630,   630,   630,   630,   634,   638,   639,   643,   644,   645,
     648,   650,   651,   654,   656,   661,   662,   665,   667,   671,
     676,   679,   681,   685,   686,   690
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
  "IDENTIFICADOR", "$accept", "programa", "$@1", "$@2",
  "variables_globales", "$@3", "bloque_variables", "bloque_variables_rep",
  "$@4", "declara_variables", "declara_variables_atomica",
  "declara_variables_matriz", "declara_variables_matriz1",
  "declara_variables_objeto", "asignacion_matriz", "asignacion_matriz_rep",
  "asignacion_matriz_valor", "asignacion_matriz_valor1", "dimensiones",
  "dimensiones_rep", "expresion", "expresion_condicional", "op_booleanos",
  "exp", "exp_suma_resta", "termino", "termino_multi_divide", "factor",
  "factor_operando", "var_cte", "declara_objetos", "declara_objetos_rep",
  "objeto", "objeto_herencia", "atributos_globales", "declara_funciones",
  "$@5", "declara_funciones_rep", "declaracion_prototipos", "$@6",
  "permiso", "parametros", "parametros_rep", "$@7", "$@8", "tipo",
  "parametros_rep1", "declaracion_prototipos_regresa",
  "implementa_funciones", "$@9", "implementa_funciones_rep", "funciones",
  "$@10", "variables_locales", "bloque", "estatuto", "asignacion",
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
       0,    59,    61,    62,    60,    64,    63,    65,    66,    67,
      66,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    74,    74,    75,
      75,    76,    76,    77,    78,    78,    79,    80,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    82,    83,    83,
      83,    84,    85,    85,    85,    86,    86,    86,    86,    87,
      87,    88,    88,    88,    88,    88,    89,    90,    90,    91,
      92,    92,    93,    95,    94,    96,    96,    98,    97,    99,
      99,   100,   100,   102,   103,   101,   104,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   108,   107,   109,   109,
     111,   110,   112,   113,   113,   114,   114,   114,   114,   114,
     114,   115,   116,   116,   116,   117,   117,   118,   118,   119,
     120,   120,   120,   120,   121,   122,   122,   123,   123,   123,
     124,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     129,   130,   130,   131,   131,   132
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    11,     0,     3,     3,     0,     0,
       3,     3,     3,     3,     3,     4,     4,     3,     1,     3,
       1,     3,     1,     1,     1,     3,     3,     0,     3,     2,
       2,     0,     2,     4,     0,     3,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     2,
       2,     2,     0,     2,     2,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     0,     2,     8,
       0,     2,     2,     0,     5,     0,     2,     0,     9,     1,
       1,     0,     1,     0,     0,     6,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     1,     0,     5,     0,     2,
       0,     9,     2,     0,     2,     2,     2,     2,     2,     1,
       1,     2,     3,     2,     5,     1,     1,     0,     1,     4,
       1,     1,     1,     1,     4,     2,     2,     1,     1,     1,
       0,     2,     2,     0,     2,     5,     1,     0,     2,     2,
       8,     0,     2,     8,     3,     7
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     5,     0,     0,     0,     0,     8,
       6,    67,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,     0,     0,    67,     0,    96,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,    70,    66,
      68,    75,     0,     3,     0,    24,    17,     0,    18,    14,
      11,    12,    13,     0,     0,     0,    10,     0,     0,    79,
      80,     0,    75,     0,    98,     0,     0,     0,     0,     0,
       0,    61,    64,    63,    62,    65,     0,    37,    48,    52,
      58,    59,   136,    60,     0,     0,    20,    16,    15,    71,
       0,    74,    76,    77,   100,     0,    98,     0,    25,     0,
      56,    57,     0,     0,     0,    19,    45,    46,    39,    40,
      41,    42,    43,    44,    36,     0,     0,     0,    47,     0,
       0,    51,    34,    27,    23,     0,    22,     0,     0,     0,
       0,    97,    99,     0,   103,   122,   120,   121,   123,     0,
      55,   138,     0,    38,    49,    50,    53,    54,     0,    33,
      31,    31,     0,     0,    21,    72,     0,    81,    81,   102,
       0,     0,     0,     0,   137,     0,   103,     0,     0,     0,
       0,   109,   110,   119,     0,     0,     0,    29,    30,    26,
      27,     0,    83,     0,    82,     0,   139,     0,     0,     0,
       0,     0,     0,   111,     4,   104,   105,   106,   107,   108,
     135,    35,    32,    28,    69,     0,     0,     0,   127,   129,
     128,   130,     0,   133,     0,     0,   117,   115,   116,   113,
       0,     0,     0,     0,     0,   133,   126,   124,     0,   125,
       0,     0,   118,     0,   112,    88,    86,    87,    89,    90,
      91,    84,    95,    94,     0,   103,   131,   132,   134,   103,
     103,     0,    92,    78,     0,     0,     0,   114,     0,    85,
     101,   141,   145,    93,     0,   140,     0,   103,   142,     0,
       0,     0,   144,     0,   103,     0,   141,   143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    65,     5,     6,    10,    21,    37,    22,
      49,    87,   125,    46,   217,   152,   153,   177,    54,   149,
     218,   114,   115,    77,   118,    78,   121,    79,    80,    81,
       8,    24,    25,    58,   128,    13,    26,    61,    62,   129,
      63,   183,   184,   205,   252,   241,   259,   244,    28,    42,
      95,    96,   130,   134,   165,   166,   167,   193,   219,   233,
      82,   139,   168,   212,   213,   226,   229,    83,   104,   170,
     171,   265,   268,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const yytype_int16 yypact[] =
{
    -175,    14,    27,  -175,  -175,    30,    -8,    11,    38,    63,
    -175,    39,  -175,    64,    22,    26,    44,    46,    59,    66,
      77,    51,  -175,    86,    84,    39,   105,  -175,   125,     2,
     -22,   -22,   -22,   -22,   109,   109,  -175,    63,   127,  -175,
    -175,    94,   110,  -175,    97,  -175,  -175,    16,  -175,  -175,
    -175,  -175,  -175,    16,    -1,    -1,  -175,    98,   115,  -175,
    -175,   113,    94,   101,   103,   120,   121,   112,     4,     4,
      16,  -175,  -175,  -175,  -175,   -21,   124,    41,   102,   108,
    -175,  -175,  -175,  -175,   119,   -36,  -175,  -175,  -175,  -175,
     153,  -175,  -175,  -175,  -175,   122,   103,   158,  -175,   118,
    -175,  -175,   128,   114,   130,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,    16,    16,    16,  -175,    16,
      16,  -175,   131,    71,  -175,   129,  -175,    -8,    38,   134,
     136,  -175,  -175,    -8,   -18,  -175,  -175,  -175,  -175,   137,
    -175,  -175,    16,  -175,  -175,  -175,  -175,  -175,    16,  -175,
     167,   167,   138,   140,  -175,  -175,    64,   126,   126,  -175,
      16,   143,   145,   146,   -16,   144,   -18,   141,   149,   150,
     151,  -175,  -175,  -175,   152,   147,    71,  -175,  -175,  -175,
      71,   148,  -175,   154,  -175,   155,  -175,    43,    16,    16,
     139,   -11,   160,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,   195,   176,   159,  -175,  -175,
    -175,    -7,   161,   170,   163,   164,     9,  -175,  -175,  -175,
      16,   107,    92,   158,    43,   170,  -175,  -175,    43,  -175,
     165,   166,  -175,   172,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,   171,   -18,  -175,  -175,  -175,   -18,
     -18,   -11,   196,  -175,   168,   169,   173,  -175,   126,  -175,
    -175,   180,  -175,  -175,   -10,  -175,   174,   -18,  -175,    16,
     175,   178,  -175,   179,   -18,   177,   180,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,  -175,  -175,  -175,  -175,  -106,   186,  -175,  -175,
      32,   162,  -175,  -175,   142,    33,    48,    74,   -34,  -175,
     -47,  -175,  -175,   -49,  -175,    20,  -175,  -175,    79,  -175,
    -175,   190,  -175,  -175,  -175,   100,  -175,   181,  -175,  -175,
    -175,    68,   -29,  -175,  -175,     8,  -175,  -175,    75,  -175,
     156,  -175,  -175,    10,  -164,  -175,  -175,  -175,   -19,  -175,
    -175,  -175,  -175,  -174,  -175,  -175,    12,  -131,  -175,  -175,
    -175,   -42,  -175,  -175
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -139
static const yytype_int16 yytable[] =
{
      76,    55,   195,   169,    84,   160,   123,    44,    67,   161,
     162,   103,    47,   163,     3,    67,   190,    48,   191,  -137,
     266,   155,   124,   102,    68,    69,   224,   159,    53,    70,
      67,   123,   267,    85,     4,   169,     9,    53,    86,     7,
     164,    45,    67,    71,    72,    73,    74,    75,    12,  -138,
     246,    68,    69,    53,   248,    11,    70,    23,    71,    72,
      73,    74,    75,    50,    51,    52,   143,   144,   145,    14,
      71,    72,    73,    74,    75,    27,    15,    16,    17,    18,
      29,   254,    19,    20,    30,   255,   256,   106,   107,   108,
     109,   110,   111,   112,   113,   174,    36,   208,   209,   175,
     210,   211,    31,   270,    32,   235,   236,   237,   238,   242,
     275,   239,   240,   186,   169,    59,    60,    33,   169,   169,
     235,   236,   237,   238,    34,   150,   239,   240,   151,    39,
     192,   135,   136,   137,   138,    35,   169,   116,   117,   146,
     147,   214,   215,   169,    38,   119,   120,   100,   101,    41,
      43,    57,    99,    53,    64,    66,    89,    90,    91,    93,
      98,    94,    97,   105,   122,   127,   133,   131,   154,   140,
     142,   176,   141,   234,   157,   148,   158,   225,   173,   180,
     196,   179,   232,   187,   182,   188,   189,   194,   197,   198,
     199,   204,   201,   200,   220,   206,   207,   216,   221,   222,
     258,   223,   227,   228,   230,   231,   251,   249,   250,   264,
     253,   260,   261,   203,   269,    40,   262,    88,   272,   273,
     276,   274,   271,    56,   202,   178,   185,   126,   156,   263,
     243,   181,   257,   245,   277,     0,     0,   247,     0,     0,
       0,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,   132
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-175))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      47,    35,   166,   134,    53,    23,    42,     5,    26,    27,
      28,    32,    34,    31,     0,    26,    32,    39,    34,    40,
      30,   127,    58,    70,    35,    36,    33,   133,    44,    40,
      26,    42,    42,    34,     7,   166,    44,    44,    39,     9,
      58,    39,    26,    54,    55,    56,    57,    58,    10,    40,
     224,    35,    36,    44,   228,    44,    40,    18,    54,    55,
      56,    57,    58,    31,    32,    33,   115,   116,   117,     6,
      54,    55,    56,    57,    58,    11,    13,    14,    15,    16,
      58,   245,    19,    20,    58,   249,   250,    46,    47,    48,
      49,    50,    51,    52,    53,   142,    45,    54,    55,   148,
      57,    58,    58,   267,    58,    13,    14,    15,    16,    17,
     274,    19,    20,   160,   245,    21,    22,    58,   249,   250,
      13,    14,    15,    16,    58,    54,    19,    20,    57,    45,
     164,    13,    14,    15,    16,    58,   267,    35,    36,   119,
     120,   188,   189,   274,    58,    37,    38,    68,    69,    44,
      25,    24,    40,    44,    44,    58,    58,    42,    45,    58,
      39,    58,    42,    39,    45,    12,     8,    45,    39,    41,
      40,     4,    58,   220,    40,    44,    40,   211,    41,    39,
      39,    43,   216,    40,    58,    40,    40,    43,    39,    39,
      39,    43,    45,    41,    34,    41,    41,    58,     3,    23,
       4,    42,    41,    33,    41,    41,    34,    42,    42,    29,
      39,    43,    43,   180,    40,    25,    43,    55,    43,    41,
      43,    42,   269,    37,   176,   151,   158,    85,   128,   258,
     222,   156,   251,   223,   276,    -1,    -1,   225,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,    61,     0,     7,    63,    64,     9,    89,    44,
      65,    44,    10,    94,     6,    13,    14,    15,    16,    19,
      20,    66,    68,    18,    90,    91,    95,    11,   107,    58,
      58,    58,    58,    58,    58,    58,    45,    67,    58,    45,
      90,    44,   108,    25,     5,    39,    72,    34,    39,    69,
      69,    69,    69,    44,    77,    77,    66,    24,    92,    21,
      22,    96,    97,    99,    44,    62,    58,    26,    35,    36,
      40,    54,    55,    56,    57,    58,    79,    82,    84,    86,
      87,    88,   119,   126,    82,    34,    39,    70,    70,    58,
      42,    45,    96,    58,    58,   109,   110,    42,    39,    40,
      87,    87,    79,    32,   127,    39,    46,    47,    48,    49,
      50,    51,    52,    53,    80,    81,    35,    36,    83,    37,
      38,    85,    45,    42,    58,    71,    73,    12,    93,    98,
     111,    45,   109,     8,   112,    13,    14,    15,    16,   120,
      41,    58,    40,    82,    82,    82,    84,    84,    44,    78,
      54,    57,    74,    75,    39,    65,    94,    40,    40,    65,
      23,    27,    28,    31,    58,   113,   114,   115,   121,   126,
     128,   129,   132,    41,    79,    82,     4,    76,    76,    43,
      39,   107,    58,   100,   101,   100,    79,    40,    40,    40,
      32,    34,    77,   116,    43,   113,    39,    39,    39,    39,
      41,    45,    75,    74,    43,   102,    41,    41,    54,    55,
      57,    58,   122,   123,    79,    79,    58,    73,    79,   117,
      34,     3,    23,    42,    33,    77,   124,    41,    33,   125,
      41,    41,    77,   118,    79,    13,    14,    15,    16,    19,
      20,   104,    17,   104,   106,   112,   122,   125,   122,    42,
      42,    34,   103,    39,   113,   113,   113,   117,     4,   105,
      43,    43,    43,   101,    29,   130,    30,    42,   131,    40,
     113,    79,    43,    41,    42,   113,    43,   130
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
#line 264 "gramatica.y"
    {
	agregarObjeto("main");	
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 267 "gramatica.y"
    {
		ejecutar = 1;
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 270 "gramatica.y"
    {
		printf("programa correctamente escrito\n");
		
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 278 "gramatica.y"
    {
		variablesGlobales=1;			
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 282 "gramatica.y"
    {
		variablesGlobales=0;		
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 293 "gramatica.y"
    {		
			//Checar la bandera de posicion
			if(variablesGlobales == 1){					
				 add_variablesGlobales("main" ,nombreV, tempTipos, 15);
				 tempTipos=-1;
			} else 
			if(funcionesI == 1){	
					add_variablesLocales("main", tempFunciones, nombreV, tempTipos,1);	
	 				tempTipos=-1;
			}								
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 308 "gramatica.y"
    {				
		nombreV = (yyvsp[(2) - (3)].sval);
		tempTipos=(yyvsp[(1) - (3)].ival);		
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 314 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (3)].sval);
		tempTipos=(yyvsp[(1) - (3)].ival);		
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 320 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (3)].sval);
		tempTipos=(yyvsp[(1) - (3)].ival);		
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 326 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (3)].sval);
		tempTipos=(yyvsp[(1) - (3)].ival);		
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 332 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (4)].sval);
		tempTipos=(yyvsp[(1) - (4)].ival);		
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 338 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (4)].sval);
		tempTipos=(yyvsp[(1) - (4)].ival);		
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 344 "gramatica.y"
    {		
		nombreV = (yyvsp[(2) - (3)].sval);	
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 478 "gramatica.y"
    {
		funcionesD = 1;
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 482 "gramatica.y"
    {
		funcionesD=0;
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 494 "gramatica.y"
    {
		if(funcionesD == 1){				
			agregarFuncion("main" ,(yyvsp[(2) - (2)].sval));
			strncpy(tempFunciones, (yyvsp[(2) - (2)].sval), strlen((yyvsp[(2) - (2)].sval)));						
		}
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 515 "gramatica.y"
    {
		strncpy(tempVariable, (yyvsp[(1) - (1)].sval), strlen((yyvsp[(1) - (1)].sval)));		
		
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 520 "gramatica.y"
    {			
		add_variablesLocales("main", tempFunciones, tempVariable, tempTipos,1);	
	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 528 "gramatica.y"
    {

		tempTipos=(yyvsp[(1) - (1)].ival);		

	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 534 "gramatica.y"
    {
		
		tempTipos=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 539 "gramatica.y"
    {
		tempTipos=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 543 "gramatica.y"
    {
		tempTipos=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 547 "gramatica.y"
    {
		tempTipos=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 551 "gramatica.y"
    {
		tempTipos=(yyvsp[(1) - (1)].ival);
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 567 "gramatica.y"
    {
		funcionesI=1;
	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 570 "gramatica.y"
    {
		funcionesI = 0;
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 582 "gramatica.y"
    {
		strncpy(tempFunciones, (yyvsp[(1) - (1)].sval), strlen((yyvsp[(1) - (1)].sval)));
	}
    break;



/* Line 1806 of yacc.c  */
#line 2139 "gramatica.tab.c"
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



