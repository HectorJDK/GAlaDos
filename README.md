GAlaDos
=======

Proyecto GAlaDos Compilador Orientado A Objetos

Comandos de compilacion del compilador 

lex tokens.l
bison -d gramatica.y
gcc -o GAlaDos gramatica.tab.c lex.yy.c -lfl
./GAlaDos < ejemplos/prueba.txt 

