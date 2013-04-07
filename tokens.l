%{
#include <stdio.h>
#include "gramatica.tab.h"
//Hector Jesus De La Garza Ponce
//Oziel Alonso Garza Lopez
%}

atributosGlobales		(?i:Atributos_Globales)
booleano				(?i:booleano)
clase					(?i:Clase)
crearObjeto				(?i:crearObjeto)
cteDecimal				([0-9]+["."][0-9]+)
cteEntera				([0-9]+)
decimal					(?i:decimal)
declaraFunciones		(?i:Declara_Funciones)
declaraObjetos			(?i:Declara_Objetos)
despliega				(?i:despliega)
ejecutarPrograma		(?i:ejecutarPrograma)
entero					(?i:entero)
entonces				(?i:entonces)
es						(?i:es)
falso					(?i:falso)
hijoDe					(?i:hijoDe)
identificador 			([a-zA-Z][_a-zA-Z0-9]*)
implementaFunciones		(?i:Implementa_Funciones)
leerDelTeclado			(?i:leerDelTeclado)
matrizDecimal			(?i:matrizDecimal)
matrizEntera			(?i:matrizEntera)
mientras				(?i:mientras)
nada					(?i:nada)
privada					(?i:privada)
publica					(?i:publica)
regresa					(?i:regresa)
si						(?i:si)
sino					(?i:sino)
texto					(?i:texto)
vacio					(?i:vacio)
variablesGlobales		(?i:Variables_Globales)
variablesLocales		(?i:Variables_Locales)
verdadero				(?i:verdadero)
comentario				("//".*[^\n])
blanks					([ \t\n\r]+)

%x IN_COMMENT
%%

<INITIAL>{
	"/*"						BEGIN(IN_COMMENT);
	["][^"]*["]					{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return CTETEXTO;}
	"->" 						{return FLECHA;}
	"<<"						{return CONCATENA;}
	"="							{return IGUAL;}
	"+"							{return MAS;}
	"-"							{return MENOS;}
	"*"							{return POR;}
	"/"							{return ENTRE;}
	";"							{return PUNTOYCOMA;}
	"," 						{return COMA;}
	":"							{return DOSPUNTOS;}
	"("							{return APARENTESIS ;}
	")"							{return CPARENTESIS ;}
	"{"							{return ALLAVE ;}
	"}"							{return CLLAVE ;}
	"["							{return ACORCHETE;}
	"]"							{return CCORCHETE;}
	"&"							{return AMPERSAND;}
	"|"							{return BARRA;}
	"=="						{return COMPARA;}
	"¬¬"						{return NEGACION;}
	">"							{return MAYORQUE;}
	"<"							{return MENORQUE;}
	">="						{return MAYORIGUAL;}
	"<="						{return MENORIGUAL;}

	{atributosGlobales}			{return ATRIBUTOS_GLOBALES;}
	{booleano}					{
								yylval.ival = 3;
								return BOOLEANO;
								}
	{clase} 					{return CLASE;}
	{crearObjeto}				{return CREAROBJETO;}	
	{cteEntera}					{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return CTEENTERA;}
	{cteDecimal}				{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return CTEDECIMAL;}
	{falso}						{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return CTEBOOLEANO;}
	{verdadero}					{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return CTEBOOLEANO;}
	{decimal} 					{
								yylval.ival = 1;
								return DECIMAL;}
	{declaraFunciones}			{return DECLARA_FUNCIONES;}
	{declaraObjetos}			{return DECLARA_OBJETOS;}
	{despliega}					{return DESPLIEGA;}
	{ejecutarPrograma} 			{return EJECUTARPROGRAMA; }
	{entero}					{
								yylval.ival = 0;																								
								return ENTERO;}
	{entonces} 					{return ENTONCES;}
	{es} 						{return ES;}
	{hijoDe} 					{return HIJODE;}
	{implementaFunciones}		{return IMPLEMENTA_FUNCIONES;}
	{leerDelTeclado}			{return LEERDELTECLADO;}
	{matrizDecimal} 			{
								yylval.ival = 5;
								return MATRIZDECIMAL;
								}
	{matrizEntera} 				{
								yylval.ival = 4;
								return MATRIZENTERA;
								}
	{mientras} 					{return MIENTRAS;}
	{nada}						{return NADA;}
	{privada} 					{return PRIVADA;}
	{publica}   				{return PUBLICA;}
	{regresa}	 				{return REGRESA;}
	{sino}						{return SINO;}
	{si} 						{return SI;}
	{texto}						{
								yylval.ival = 2;
								return TEXTO;
								}
	{variablesGlobales}			{return VARIABLES_GLOBALES;}
	{variablesLocales}			{return VARIABLES_LOCALES;}

	{identificador}				{
								yylval.sval = yytext;
								strncpy(yylval.sval, yytext, strlen(yytext));
								return IDENTIFICADOR;
							}
	{blanks} 					{/* Ignore whitespace */}
	{comentario}     			{/* eat up one-line comments */}

	}

<IN_COMMENT>{
	"*/"						BEGIN(INITIAL);
	[^*\n]+						// eat comment in chunks
	"*"							// eat the lone star
	\n							yylineno++;
}


%%