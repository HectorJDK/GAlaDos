//Programa ejemplo del lenguaje GAlaDOs

//Hector Jesus De La Garza Ponce
//Oziel Alonso Garza Lopez

Declara_Objetos [	
	
]
Variables_Globales [			
			] 
Declara_Funciones [
	privada fibonacci (param1:entero) regresa entero;
	privada fibonacci2 (param1:entero) regresa entero;
	]
Implementa_Funciones [
	
	fibonacci () { 
		Variables_Locales[					
		]		
		
	    si(param1 == 0 | param1 ==1){
			regresa param1;			
		} sino {
			regresa fibonacci(param1-1) + fibonacci(param1-2);
		}

	}

	fibonacci2 () { 
		Variables_Locales[					
			entero llamada1;
			entero llamada2;
			entero suma;
		]		
		
	    si(param1 == 0 | param1 ==1){
			regresa param1;			
		} sino {
			llamada1=fibonacci2(param1-1);
			llamada2=fibonacci2(param1-2);
			suma = llamada1 + llamada2;
			regresa suma;
		}

	}
	
]
ejecutarPrograma {
	Variables_Locales [
		entero uno;
		decimal dos;
		decimal tres;	
		booleano cuatro;
		texto cinco;	
	]
	uno = fibonacci(5);
}

