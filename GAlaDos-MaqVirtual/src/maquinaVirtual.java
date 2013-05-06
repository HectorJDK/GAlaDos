/**
 * Maquina Virtual GALaDos
 * 
 * Programa que carga los cuadruplos y datos (tablas de objetos y constantes)
 * a estructuras especiales. 
 * Realiza el proceso de ejecucion mediante la simulacion de un bloque de 
 * memoria con registros.
 * 
 * @author Oziel Garza, Hector De la Garza
 */

//Librerias para lectura de archivo
import java.io.*;
//Librerias para estructuras
import java.util.*;

public class maquinaVirtual {
	
	//Estructuras de memoria
	
	static objetos workspaceActual;						//El espacio de memoria actual
	static funcion funcion;								//Funcion actual	
	static bloque constantes;							//Espacio de constantes
	static HashMap<Integer,retorno> retornos;								//Espacio de retornos
	
	public static void main(String [ ] args) throws IOException{
		
		//Declaracion de variables y estructuras principales
		BufferedReader br = new BufferedReader(new FileReader("obj/codigoObjeto.txt"));		//Crear el objeto BufferedReader y cargar el documento			
		InputStreamReader stream = new InputStreamReader(System.in);							//Lectura de teclado
		BufferedReader brT = new BufferedReader(stream);		//Crear objeto para leer de teclado			
		ArrayList<cuadruplos> cuadruplos ;				//Crear la lista que contendra los cuadruplos						
		HashMap<String, objetos> workspaces;					//Espacios de ejecucion (objetos)		
		xmlParser datos;								//Manejador del xml
		bloque bloque;									//Objeto auxiliar para el manejo de los bloques de datos
		cuadruplos cuadruplo;					 		//Crear el objeto cuadruplo			
		String[] cuadruploLinea;						//String auxiliar para separacion de elementos del cuadruplo
		String line;									//String para leer la linea de archivo
		int indice;										//Auxiliares para el manejo de ejecucion de los cuadruplos	
		boolean finEjecucion;			//Bandera para terminar la ejecucion (Fin de programa)
		int operacion;									//Auxiliares para el manejo de ejecucion de los cuadruplos	  
		Stack<Integer> pilaEjecucion;					//Pila para transferir ejecucion a modulos
		Stack<funcion> pilaFuncion;						//Pila para almacenar la base del modulo
		Stack<objetos> pilaObjetos;						//Pila para almacenar el objeto
		funcion funcionNueva;							//Funcion temporal para llamada a modulos							
		boolean accederAClase;
		String nombreClaseAcceder;
		
	    try {
			
			//Inicializacion de variables y estructuras
	    	datos = new xmlParser();
			//registro = new registro();			
			cuadruplo = new cuadruplos();
			//Crear arraylist de objetos cuadruplos
	        cuadruplos = new ArrayList<cuadruplos>();
	        bloque = new bloque();
	        //Objetos
	        workspaces = new HashMap<String,objetos>();
	        
	        accederAClase = false;
	        nombreClaseAcceder = "";
	        //workspaces = datos.cargarObjetos(workspaces, "");
	        
	        /*
	         * Cargar datos en las estructuras principales
	         */
	        //Apuntador al workspace actual
	        workspaceActual = new objetos();
	        workspaces = datos.cargarObjetos(workspaces, "main", "main");
	        workspaceActual = workspaces.get("main");
	        
	        //Funciones
	        funcion = new funcion();
	        //funcionActual
	        funcion = datos.cargarFunciones(workspaceActual, "ejecutarProgama", funcion, "main");
	      	  	     
	        //Constantes
	        constantes = new bloque();
	        constantes = datos.cargarConstantes(constantes);
	        
	        //Retornos
	        retornos = new HashMap<Integer,retorno>();
	        retornos = datos.cargarRetornos(retornos);
	      
	        //Variables de Ejecucion
	        line = br.readLine();
	        indice = 0;
	        finEjecucion = false; 	
	        pilaEjecucion = new Stack<Integer>();
	        pilaFuncion = new Stack<funcion>();
	        pilaObjetos= new Stack<objetos>();
	        
	        //Variable auxiliar para llamadas a modulos
	        funcionNueva = new funcion();
	        
	        /**
	         * Seccion para cargar los cuadruplos de archivo a la estructura arraylist
	         */
	        //Iterar hasta que termine todas las lineas del documento
	        while (line != null) {	        	
	        	cuadruploLinea = line.split(", ");	        	
        		cuadruplo.setOperacion(Integer.parseInt(cuadruploLinea[0]));
        		//Si es un cuadruplo ERA construir el cuadruplo con strings
        		if(Integer.parseInt(cuadruploLinea[0])==21){
        			cuadruplo.setOperando1S(cuadruploLinea[1]);
        			cuadruplo.setOperando2(Integer.parseInt(cuadruploLinea[2]));
        			cuadruplo.setResultadoS(cuadruploLinea[3]);
        		} else  if(Integer.parseInt(cuadruploLinea[0])==30 | Integer.parseInt(cuadruploLinea[0])==29){
        			cuadruplo.setOperando1S(cuadruploLinea[1]);
        			cuadruplo.setOperando2S(cuadruploLinea[2]);
        			cuadruplo.setResultadoS(cuadruploLinea[3]);
        		} else {
        			cuadruplo.setOperando1(Integer.parseInt(cuadruploLinea[1]));
        			cuadruplo.setOperando2(Integer.parseInt(cuadruploLinea[2]));
        			cuadruplo.setResultado(Integer.parseInt(cuadruploLinea[3]));        			
        		}
        		
        		
	        	//Agregarlo a la lista	       	        	
        		cuadruplos.add( cuadruplo);
        		
        		//Reinicializar objeto cuadruplos
        		if(Integer.parseInt(cuadruploLinea[0])==21){
        			cuadruplo = new cuadruplos("","");
        		} else {
        			cuadruplo = new cuadruplos();
        		}        		
        		//Leer siguiente cuadruplo de archivo
	        	line = br.readLine();	           
	        }
	       	       	       	     
	       
	        //Enviar la ejecucion a ejecutarPrograma 
    		cuadruplo = cuadruplos.get(indice);    	
    		if(cuadruplo.getOperacion() == 19){ 
				indice = cuadruplo.getResultado();
				cuadruplo = cuadruplos.get(cuadruplo.getResultado());     				
			}
    		
            //Iniciar ejecucion    		
    		while(!finEjecucion){
    			
    			//Obtener la operacion a ejecutar
    			operacion = cuadruplo.getOperacion(); 

    			//Variables para direcciones y tipos de los elementos del cuadruplo
    			int direccionOperando1, direccionOperando2, direccionResultado,  tipoOperando1, tipoOperando2, tipoResultado;
    			
    			//Direcciones de operandos y resultado
    			direccionOperando1 = cuadruplo.getOperando1();
				direccionOperando2 = cuadruplo.getOperando2();    			
				direccionResultado= cuadruplo.getResultado();
			
				/*
				 * Ajuste de direcciones para indexamiento de matrices y arreglos
				 */
				if(direccionOperando1 >= 100000){
					//Obtener la direccion del elemento del arreglo						
					direccionOperando1 = direccionOperando1 - 100000;						
					//Entero					
					direccionOperando1 = obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando1);
				
				}
				if(direccionOperando2 >= 100000){
					//Obtener la direccion del elemento del arreglo						
					direccionOperando2 = direccionOperando2 - 100000;						
					//Entero
					direccionOperando2 = obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando2);						
				}
				if(direccionResultado >= 100000){
					direccionResultado = direccionResultado - 100000;
					direccionResultado = obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionResultado);										
				}
				
				/*
				 * Tipos de operandos y resultado
				 */
    			tipoOperando1 = obtenerTipo(direccionOperando1);
    			tipoOperando2 = obtenerTipo(direccionOperando2);
    			//Si es una direccion de retornos, obtener el tipo que contiene
    			if(direccionResultado>=0 && direccionResultado<1000){ 
    				tipoResultado = datos.tipoRetorno(workspaceActual.getNombre(), ""+direccionResultado);
    			} else {
    				tipoResultado = obtenerTipo(direccionResultado);
    			}
    			
    			/*
    			 * Variables para el manejo de los operandos de acuerdo al tipo
    			 * E - Entero, D- Decimal, T - Texto, B- Booleano
    			 */
    			int operando1E=0, operando2E=0;
    			double operando1D=0.0, operando2D=0.0;
    			String operando1T="", operando2T=""; 
    			boolean operando1B=false, operando2B=false;
    			
    			/*
    			 * Obtener de memoria los valores de los operandos del cuadruplo
    			 */
    			//Si es operacion de ERA, PARAM, VERIFICA, SUMAMAT no mapear los elementos del cuadruplo.
    			if(operacion != 23 && operacion != 22 && operacion != 26 && operacion != 27 && operacion != 28){
    			
    				//Selector de memoria en base a la direccion
    				//Operando1
    				//Memoria especial de retornos
    				if(direccionOperando1>=0 && direccionOperando1<1000){  
    					tipoOperando1 = datos.tipoRetorno(workspaceActual.getNombre(), ""+direccionOperando1);    				    					    					
    					switch(tipoOperando1){
    					case 0:      						
    						operando1E = retornos.get(direccionOperando1).entero ;     							
    					break;
    					case 1:    		
    						operando1D = retornos.get(direccionOperando1).decimal;
    					break;
    					case 2:
    						operando1T = retornos.get(direccionOperando1).texto;
    					break;
    					case 3:
    						operando1B =  retornos.get(direccionOperando1).booleano;
    					break;
    					}
    				}  else if(direccionOperando1>=1000 && direccionOperando1<5000){      					    			
    				//Espacio de globales    				
    					bloque.inicializarBase(1000);
    					direccionOperando1 = bloque.mapearDireccion(direccionOperando1);
	    				switch(tipoOperando1){
						case 0:						
							operando1E =  workspaceActual.getGlobales().entero.get(direccionOperando1);    			
						break;
						case 1:    		
							operando1D =  workspaceActual.getGlobales().decimal.get(direccionOperando1);    	
						break;
						case 2:
							operando1T =  workspaceActual.getGlobales().texto.get(direccionOperando1);    	
						break;
						case 3:
							operando1B =  workspaceActual.getGlobales().booleano.get(direccionOperando1);    	
						break;
						}
    				} else  if(direccionOperando1>=5000 && direccionOperando1<9000){      					    			
    				//Espacio de locales 				
    					bloque.inicializarBase(5000);
    					direccionOperando1 = bloque.mapearDireccion(direccionOperando1);
						switch(tipoOperando1){
						case 0:						
							operando1E =  funcion.getLocales().entero.get(direccionOperando1); 							
						break;
						case 1:    		
							operando1D =  funcion.getLocales().decimal.get(direccionOperando1);    
						break;
						case 2:
							operando1T =  funcion.getLocales().texto.get(direccionOperando1);    
						break;
						case 3:
							operando1B =  funcion.getLocales().booleano.get(direccionOperando1);    
						break;
						}
					} else  if(direccionOperando1>=9000 && direccionOperando1<13000){      					    			
    				//Espacio de temporales				
						bloque.inicializarBase(9000);
    					direccionOperando1 = bloque.mapearDireccion(direccionOperando1);
						switch(tipoOperando1){
						case 0:						
							operando1E =  funcion.getTemporales().entero.get(direccionOperando1);			
						break;
						case 1:    		
							operando1D = funcion.getTemporales().decimal.get(direccionOperando1);
						break;
						case 2:
							operando1T = funcion.getTemporales().texto.get(direccionOperando1);
						break;
						case 3:
							operando1B = funcion.getTemporales().booleano.get(direccionOperando1);
						break;
						}
					} else  if(direccionOperando1>=13000 && direccionOperando1<17000){      					    			
    				//Espacio de constantes		
						bloque.inicializarBase(13000);
    					direccionOperando1 = bloque.mapearDireccion(direccionOperando1);    				
						switch(tipoOperando1){
						case 0:						
							operando1E =  constantes.entero.get(direccionOperando1);    			
						break;
						case 1:    		
							operando1D =constantes.decimal.get(direccionOperando1); 
						break;
						case 2:
							operando1T = constantes.texto.get(direccionOperando1); 
						break;
						case 3:
							operando1B = constantes.booleano.get(direccionOperando1); 
						break;
						}
					}
					
					//Operando2
    				//Memoria especial de retornos
    				if(direccionOperando2>=0 && direccionOperando2<1000){     					    				
    					tipoOperando2 = datos.tipoRetorno(workspaceActual.getNombre(), ""+direccionOperando2);    				    					    					
    					switch(tipoOperando2){
    					case 0:      						
    						operando1E = retornos.get(direccionOperando1).entero ;     							
    					break;
    					case 1:    		
    						operando1D = retornos.get(direccionOperando1).decimal;
    					break;
    					case 2:
    						operando1T = retornos.get(direccionOperando1).texto;
    					break;
    					case 3:
    						operando1B =  retornos.get(direccionOperando1).booleano;
    					break;
    					}
    				}  else if(direccionOperando2>=1000 && direccionOperando2<5000){  
    					bloque.inicializarBase(1000);
    					direccionOperando2 = bloque.mapearDireccion(direccionOperando2);  
	    				//Espacio de globales    				    				
						switch(tipoOperando2){
						case 0:						
							operando2E =  workspaceActual.getGlobales().entero.get(direccionOperando2);    			
						break;
						case 1:    		
							operando2D =  workspaceActual.getGlobales().decimal.get(direccionOperando2);
						break;
						case 2:
							operando2T = workspaceActual.getGlobales().texto.get(direccionOperando2);
						break;
						case 3:
							operando2B =  workspaceActual.getGlobales().booleano.get(direccionOperando2);
						break;
						}
    				} else  if(direccionOperando2>=5000 && direccionOperando2<9000){      					    			
    				//Espacio de locales 				
    					bloque.inicializarBase(5000);
    					direccionOperando2 = bloque.mapearDireccion(direccionOperando2);  
						switch(tipoOperando2){
						case 0:						
							operando2E =  funcion.getLocales().entero.get(direccionOperando2);    			
						break;
						case 1:    		
							operando2D = funcion.getLocales().decimal.get(direccionOperando2);  
						break;
						case 2:
							operando2T =  funcion.getLocales().texto.get(direccionOperando2);  
						break;
						case 3:
							operando2B = funcion.getLocales().booleano.get(direccionOperando2);  
						break;
						}
					} else  if(direccionOperando2>=9000 && direccionOperando2<13000){      					    			
    				//Espacio de temporales				
						bloque.inicializarBase(9000);
    					direccionOperando2 = bloque.mapearDireccion(direccionOperando2);  
						switch(tipoOperando2){
						case 0:						
							operando2E =  funcion.getTemporales().entero.get(direccionOperando2);			
						break;
						case 1:    		
							operando2D = funcion.getTemporales().decimal.get(direccionOperando2);    
						break;
						case 2:
							operando2T = funcion.getTemporales().texto.get(direccionOperando2);    
						break;
						case 3:
							operando2B = funcion.getTemporales().booleano.get(direccionOperando2);    
						break;
						}
					} else  if(direccionOperando2>=13000 && direccionOperando2<17000){      					    			
    				//Espacio de constantes			
						bloque.inicializarBase(13000);
    					direccionOperando2 = bloque.mapearDireccion(direccionOperando2);  
						switch(tipoOperando2){
						case 0:						
							operando2E =  constantes.entero.get(direccionOperando2);    			
						break;
						case 1:    		
							operando2D =constantes.decimal.get(direccionOperando2);  
						break;
						case 2:
							operando2T = constantes.texto.get(direccionOperando2);  
						break;
						case 3:
							operando2B = constantes.booleano.get(direccionOperando2);  
						break;
						}
					}
    			}
    			
    			//Para mapeo correcto en memoria (contenido de la direccion usado en matrices y arreglos)
    			direccionOperando1 = cuadruplo.getOperando1();
    			//Ajuste de direcciones para indexamiento de matrices y arreglos
				if(direccionOperando1 >= 100000){
					//Obtener la direccion del elemento del arreglo						
					direccionOperando1 = direccionOperando1 - 100000;						
					//Entero
					direccionOperando1 = obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando1);						
				}
				direccionOperando2 = cuadruplo.getOperando2();  
				if(direccionOperando2 >= 100000){
					//Obtener la direccion del elemento del arreglo						
					direccionOperando2 = direccionOperando2 - 100000;						
					//Entero
					direccionOperando2 = obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando2);						
				}
				
				/*
				 * Realizar la operacion solicitada
				 */
    			switch (operacion){    		
    			case (0):
    			//Suma    				    		
    				if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Suma de dos enteros
    						if(tipoResultado==0){ 
    							//Asignarlo a un entero
    	    					almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E + operando2E);	    					     	    								
    						} else {
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E + operando2E);	    					     	    								        						
    						}
    					}else{
    						//Suma de entero mas decimal
    						if(tipoResultado==0){    		
    							//Asignarlo a un entero
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado,operando1E + (int)operando2D);	    					     	    								        						   				
    						} else {    
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E + operando2D);	    					     	    								        						
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Suma decimal mas entero    						
    						if(tipoResultado==0){    				
    							//Asignarlo a un entero  	    					 
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)operando1D + operando2E);	    					     	    								        						    					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D + operando2E);	    					     	    								        						 
    						}
    					}else{
    						//Suma de decimales
    						if(tipoResultado==0){        						
    							//Asignarlo a un entero   	    					   
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)(operando1D + operando2D));	    					     	    								        						   					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D + operando2D);	    					     	    								        						
    						}
    					}
    				}	 
    				//Continuar con el siguiente cuadruplo
    				indice++;
    				cuadruplo = cuadruplos.get(indice);       				
    			break;    				
    			//Resta
    			case (1): 
    				
    				if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Resta de dos enteros
    						if(tipoResultado==0){ 
    							//Asignarlo a un entero
    		    				almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E - operando2E);	    					     	    								
    						} else {
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E - operando2E);	    					     	    								        						
    						}
    					}else{
    						//Resta de entero mas decimal
    						if(tipoResultado==0){    		
    							//Asignarlo a un entero
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado,operando1E - (int)operando2D);	    					     	    								        						   				
    						} else {    
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E - operando2D);	    					     	    								        						
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Resta decimal mas entero    						
    						if(tipoResultado==0){    				
    							//Asignarlo a un entero  	    					 
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)operando1D - operando2E);	    					     	    								        						    					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D - operando2E);	    					     	    								        						 
    						}
    					}else{
    						//Resta de decimales
    						if(tipoResultado==0){        						
    							//Asignarlo a un entero   	    					   
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)(operando1D - operando2D));	    					     	    								        						   					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D - operando2D);	    					     	    								        						
    						}
    					}
    				}
    				//Continuar con el siguiente cuadruplo
    				indice++;
    				cuadruplo = cuadruplos.get(indice);     		  			
    				break;  			
    			//Division
				case (2):  
    				if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Division de dos enteros
    						if(tipoResultado==0){ 
    							//Asignarlo a un entero
    	    					almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E / operando2E);	    					     	    								
    						} else {
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E / operando2E);	    					     	    								        						
    						}
    					}else{
    						//Division de entero mas decimal
    						if(tipoResultado==0){    		
    							//Asignarlo a un entero
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado,operando1E / (int)operando2D);	    					     	    								        						   				
    						} else {    
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E / operando2D);	    					     	    								        						
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Division decimal mas entero    						
    						if(tipoResultado==0){    				
    							//Asignarlo a un entero  	    					 
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)operando1D / operando2E);	    					     	    								        						    					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D / operando2E);	    					     	    								        						 
    						}
    					}else{
    						//Division de decimales
    						if(tipoResultado==0){        						
    							//Asignarlo a un entero   	    					   
    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)(operando1D / operando2D));	    					     	    								        						   					
    						} else {    			
    							//Asignarlo a un decimal
    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D / operando2D);	    					     	    								        						
    						}
    					}
    				} 
					//Continuar con el siguiente cuadruplo
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				break;  		
	    			//Multiplicacion
					case (3):  
						if(tipoOperando1 == 0){
	    					if(tipoOperando2 == 0){
	    						//Multiplicacion de dos enteros
	    						if(tipoResultado==0){ 
	    							//Asignarlo a un entero
	    	    					almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E * operando2E);	    					     	    								
	    						} else {
	    							//Asignarlo a un decimal
	    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E * operando2E);	    					     	    								        						
	    						}
	    					}else{
	    						//Multiplicacion de entero mas decimal
	    						if(tipoResultado==0){    		
	    							//Asignarlo a un entero
	    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado,operando1E * (int)operando2D);	    					     	    								        						   				
	    						} else {    
	    							//Asignarlo a un decimal
	    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1E * operando2D);	    					     	    								        						
	    						}
	    					}    					
	    				} else {
	    					if(tipoOperando2 == 0){
	    						//Multiplicacion decimal mas entero    						
	    						if(tipoResultado==0){    				
	    							//Asignarlo a un entero  	    					 
	    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)operando1D * operando2E);	    					     	    								        						    					
	    						} else {    			
	    							//Asignarlo a un decimal
	    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D * operando2E);	    					     	    								        						 
	    						}
	    					}else{
	    						//Multiplicacion de decimales
	    						if(tipoResultado==0){        						
	    							//Asignarlo a un entero   	    					   
	    							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)(operando1D * operando2D));	    					     	    								        						   					
	    						} else {    			
	    							//Asignarlo a un decimal
	    							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, operando1D * operando2D);	    					     	    								        						
	    						}
	    					}
	    				} 
					//Continuar con el siguiente cuadruplo
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				break;
					case 4:
					//Mayor que
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E > operando2E){								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	    					     	    								        							    														
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Entero > Decimal
							if(operando1E > operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D > operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Decimal > Decimal
							if(operando1D > operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}	
					}	
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);    				
					break;
				case 5:
					//Menor que
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero < Entero
							if(operando1E < operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	    					     	    								        							    														
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Entero < Decimal
							if(operando1E < operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal < Entero
							if(operando1D < operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Decimal < Decimal
							if(operando1D < operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}	
					}
					indice++;
					cuadruplo = cuadruplos.get(indice);    						
					break;
				case 6:
					//Mayor o igual
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero >= Entero
							if(operando1E >= operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	    					     	    								        							    														
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Entero >= Decimal
							if(operando1E >= operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal >= Entero
							if(operando1D >= operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Decimal >= Decimal
							if(operando1D >= operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}	
					}
					//Continuar con el siguiente cuadruplo
					indice++;
					cuadruplo = cuadruplos.get(indice);    						
					break;										
				case 7:
					//Menor o igual
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero <= Entero
							if(operando1E <= operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	    					     	    								        							    														
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Entero <= Decimal
							if(operando1E <= operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal <= Entero
							if(operando1D <= operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						} else {
							//Decimal <= Decimal
							if(operando1D <= operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
							}
						}	
					}
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);    						
					break;
					case 8:				
					//Igual
						if(tipoOperando1 == 0){
							if(tipoOperando2 == 0){
								//Entero == Entero
								if(operando1E == operando2E){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	    					     	    								        							    														
								} else {								
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
								}
							} else {
								//Entero == Decimal
								if(operando1E == operando2D){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
								} else {
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
								}
							}
						} else if(tipoOperando1 == 1){ 
							if(tipoOperando2 == 0){
								//Decimal == Entero
								if(operando1D == operando2E){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
								} else {								
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
								}
							} else {
								//Decimal == Decimal
								if(operando1D <= operando2D){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);	
								} else {
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);	
								}
							}	
						} else if(tipoOperando1 == 2){
							if(tipoOperando2 == 2){
								//Texto == Texto
								if(operando1T.equals(operando2T)){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
								} else {								
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
								}
							}
					} else if(tipoOperando1 == 3){
						if(tipoOperando2 == 3){
							//Booleano == Booleano
							if(operando1B){								
								if(operando2B){									
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);										
								} else {									
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);											
								}
							} else {
								if(operando2B){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);										
								} else {
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);										
								}								
							}
						}
					}
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);    								
					break;
			case 9:
			//Diferente
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero != Entero
							if(operando1E != operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						} else {
							//Entero != Decimal
							if(operando1E != operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						}
					} else if(tipoOperando1 == 1){
						if(tipoOperando2 == 0){
							//Decimal != Entero
							if(operando1D != operando2E){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						} else {
							//Decimal != Decimal
							if(operando1D != operando2D){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						}	
					} else if(tipoOperando1 == 2){
						if(tipoOperando2 == 2){
							//Texto != Texto
							if(!operando1T.equals(operando2T)){
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {								
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						}
					} else if(tipoOperando1 == 3){
						if(tipoOperando2 == 3){
							//Booleano != Booleano
							if(operando1B){								
								if(operando2B){									
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);										
								} else {									
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);										
								}
							} else {
								if(operando2B){
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
								} else {
									almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);										
								}								
							}
						}
					}	
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);    								
					break;
				case 10:
					//AND
					if (tipoOperando1 == 3) {
						if (tipoOperando2 == 3) {
							// Booleano AND Booleano
							if (operando1B & operando2B) {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);									
							}
						}
					}	
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);    									
    				break;
				case 11:					
					//OR
					if (tipoOperando1 == 3) {
						if (tipoOperando2 == 3) {
							// Booleano OR Booleano
							if (operando1B | operando2B) {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, true);									
							} else {
								almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, false);								
							}
						}
					}	
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);					
					break;
				case 12:
					//Asignacion						   				
				switch(tipoOperando1){				
					case 0:					
						//Operando1 Entero
						if(tipoResultado == 0){
							//Asignarlo a un entero
							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando1));	    					     	    								        						    							    																											
						} else {
							//Asignarlo a un decimal
							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionOperando1));						
						}	
						break;
					case 1:
						//Decimal
						if(tipoResultado == 0){
							//Asignarlo a un entero
							almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int)obtieneDecimal(constantes, workspaceActual, funcion, bloque, direccionOperando1));	    					     	    								        						    							    																											
						} else {
							//Asignarlo a un decimal
							almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, obtieneDecimal(constantes, workspaceActual, funcion, bloque, direccionOperando1));
						}	
						break;
					case 2:
						//Texto
						if(tipoResultado == 2){
							//Asignarlo a un texto
							almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado, obtieneTexto(constantes, workspaceActual, funcion, bloque, direccionOperando1));	    					     	    								        						    							    																																		
						}
						break;
					case 3:
						//Booleano
						if(tipoResultado == 3){
							//Asignarlo a un booleano
							almacenaBooleano(constantes, workspaceActual, funcion, bloque, direccionResultado, obtieneBooleano(constantes, workspaceActual, funcion, bloque, direccionOperando1));	    					     	    								        						    							    																																		
						}
					}
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				//finEjecucion = true;
				break;
				case 13:
					//CONCATENA
					switch(tipoOperando1) {
					case 0:
						switch(tipoOperando2){
							case 0:
								//ENTERO concatena ENTERO 
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1E+operando2E);
							break;
							case 1: 
								//Entero concatena Decimal
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1E+operando2D);
								break;
							case 2:
								//Entero concatena Texto
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1E+operando2T);								
							break;
						} 
					break;
					case 1:
						switch(tipoOperando2){
							case 0:
								//Decimal concatena ENTERO 
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1D+operando2E);								
							break;
							case 1: 
								//Decimal concatena Decimal
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1D+operando2D);								
							break;
							case 2:
								//Decimal concatena Texto
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1D+operando2T);								
							break;
						} 
					break;
					case 2:
						switch(tipoOperando2){
							case 0:
								//Texto concatena ENTERO 
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1T+operando2T);								
							break;
							case 1: 
								//Texto concatena Decimal
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1T+operando2T);								
							break;
							case 2:
								//Texto concatena Texto
								almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	""+operando1T+operando2T);								
							break;
						} 
					break;
					}		
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);					
					break;
				case 16:
					//GOTOFALSO
					//Obtener el valor booleano y verificar su valor, si es falso se fija el siguiente
					//cuadruplo con el salto especificado en el cuadruplo
					if(direccionOperando1>=0 && direccionOperando1<1000){ 
						//Espacio de retornos  
						if(!retornos.get(direccionOperando1).booleano){
							indice = cuadruplo.getResultado();
						} else {
							indice++;
						}						
					}  else if(direccionOperando1>=1000 && direccionOperando1<5000){      					    			
					//Espacio de globales    
						bloque.inicializarBase(1000);
						if(!workspaceActual.getGlobales().booleano.get(bloque.mapearDireccion(direccionOperando1))){
							indice = cuadruplo.getResultado();
						} else {
							indice++;
						}
					} else  if(direccionOperando1>=5000 && direccionOperando1<9000){      					    			
					//Espacio de locales 
						bloque.inicializarBase(5000);
						if(!funcion.getLocales().booleano.get(bloque.mapearDireccion(direccionOperando1))){
							indice = cuadruplo.getResultado();
						} else {
							indice++;
						}
					} else  if(direccionOperando1>=9000 && direccionOperando1<13000){      					    			
					//Espacio de temporales	
						bloque.inicializarBase(9000);
						if(!funcion.getTemporales().booleano.get(bloque.mapearDireccion(direccionOperando1))){
							indice = cuadruplo.getResultado();
						} else {
							indice++;
						}
					} else  if(direccionOperando1>=13000 && direccionOperando1<17000){      					    			
					//Espacio de constantes		
						bloque.inicializarBase(13000);
						if(!constantes.booleano.get(bloque.mapearDireccion(direccionOperando1))){
							indice = cuadruplo.getResultado();
						} else {
							indice++;
						}
					}						
					cuadruplo = cuadruplos.get(indice);				
					break;
				case 17:
					//Lectura	
					//Obtener la entrada del teclado y asignarla a la variable dada en el cuadruplo
					//Texto de entrada
					String entrada = brT.readLine();
					switch(tipoResultado){
						case 0:
							//Leer y asignar a un dato entero							
							try{								
								almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, Integer.parseInt(entrada));
							} catch (NumberFormatException nfe) {
								try{
										//Si el valor es decimal, lo asignamos al entero
										almacenaEntero(constantes, workspaceActual, funcion, bloque, direccionResultado, (int) Double.parseDouble(entrada));
									} catch (NumberFormatException nfe2) {
										  //Si la entrada no corresponde a un dato numerico, imprimimos el error y termina la ejecucion
							              System.out.println("Error: Dato no numerico");
							              finEjecucion = true;
						            }  
				            }
						break;
						case 1: 
							//Leer y asignar a un dato decimal
							try{
								almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, Double.parseDouble(entrada));
							} catch (NumberFormatException nfe) {							
								try{
									//Si el valor es entero, lo asignamos al decimal
									almacenaDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado, Integer.parseInt(entrada));
								} catch (NumberFormatException nfe2) {							
									 //Si la entrada no corresponde a un dato numerico, imprimimos el error 
									 System.out.println("Error: Dato no numerico");
						             finEjecucion = true;
								}
							}
						break;
						case 2:
							//Leer entrada y asignarlo a un dato tipo texto
							almacenaTexto(constantes, workspaceActual, funcion, bloque, direccionResultado,	brT.readLine());
						break;
					} 													
					indice++;
    				cuadruplo = cuadruplos.get(indice);    							
					break;
				case 18:
					//Escritura	
					//Despliega en consola el valor de la variable o constante especificado en el cuadruplo
					switch(tipoResultado){
						case 0:
							//Imprime un dato tipo entero
							System.out.print(""+obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionResultado));
							break;
						case 1: 
							//Imprime un dato tipo decimal
							System.out.print(""+obtieneDecimal(constantes, workspaceActual, funcion, bloque, direccionResultado));
						break;
						case 2:
							//Imprime un dato tipo texto
							System.out.print(""+obtieneTexto(constantes, workspaceActual, funcion, bloque, direccionResultado));
						break;
					}
					if(cuadruplo.getResultado() == -1){
						System.out.println("");
					}
					indice++;
    				cuadruplo = cuadruplos.get(indice);    				    								
					break;
				case 19:	
					//GOTO
					//Desplaza la ejecucion al cuadruplo especificado
					indice = cuadruplo.getResultado();									
					cuadruplo = cuadruplos.get(indice);					
					break;
				case 20:
					//ENDPROC
					//Se termina la ejecucion del modulo. Se regresa a la ejecucion obtenida de la pila
					//Se reestablece la memoria local y temporal
					
					//Sacar la direccion de ejecucion
					indice = pilaEjecucion.pop()+1;					
					
					//Reestablecer el bloque de memoria
					funcion = pilaFuncion.pop();					
					
					cuadruplo = cuadruplos.get(indice);					
					break;
				case 21:					
					//ERA	
					//Cargar la nueva estructura de la funcion
					
					//Obtener el nombre de la funcion y del objeto
					String nombreFuncion = cuadruplo.getOperando1S();
					String nombreObjeto = cuadruplo.getResultadoS();
					
					//Crear la nueva funcion
					funcionNueva = new funcion();
			        
					//Cargar su informacion
			        funcionNueva = datos.cargarFunciones(workspaceActual, nombreFuncion, funcionNueva, nombreObjeto);										
    							      
			        //Continuar con el siguiente cuadruplo
					indice++;					
    				cuadruplo = cuadruplos.get(indice);    			
    				break;
				case 22: 
					//PARAM				
					//Asignar cada parametro con su valor a la estructura de la funcion
					
					//Obtenemos la direccion del valor a asignar y numero de parametro
					int direccionAsignar = direccionOperando1;
					bloque.inicializarBase(5000);
					int direccionParametro = bloque.mapearDireccion(direccionResultado);					
					//Asignamos el parametro en la funcion nueva
					switch(tipoOperando1){
					case 0:
						//Asociar un parametro tipo entero
						funcionNueva.locales.ingresaElementoEntero(direccionParametro, obtieneEntero(constantes, workspaceActual, funcion, bloque, direccionAsignar));						
						break;
					case 1:
						//Asociar un parametro tipo decimal
						funcionNueva.locales.ingresaElementoDecimal(direccionParametro, obtieneDecimal(constantes, workspaceActual, funcion, bloque, direccionAsignar));
						break;
					case 2:
						//Asociar un parametro tipo texto
						funcionNueva.locales.ingresaElementoTexto(direccionParametro, obtieneTexto(constantes, workspaceActual, funcion, bloque, direccionAsignar));
						break;
					case 3:
						//Asociar un parametro tipo booleano
						funcionNueva.locales.ingresaElementoBooleano(direccionParametro, obtieneBooleano(constantes, workspaceActual, funcion, bloque, direccionAsignar));
						break;
					}
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);					
					break;
				case 23:
					//GOSUB
					//Guardar la base actual, actualizar la nueva base y enviar la ejecucion al primer cuadruplo del modulo 
    				
					//Meter la funcion actual a la pila
					pilaFuncion.push(funcion);
					
					//Meter direccion de retorno en la pila de ejecucion
					pilaEjecucion.push(indice);
					
					//Transferir el control de ejecucion a donde inicia el procedimiento
					indice = cuadruplo.getOperando1();
					
					//Cargar la nueva estructura
					funcion = funcionNueva;															
					  if(accederAClase){
						  pilaObjetos.push(workspaceActual);
						  workspaceActual = workspaces.get(nombreClaseAcceder);
				      }
					  
					
					cuadruplo = cuadruplos.get(indice);										
					break;
				case 25:
					//FIN DE PROGRAMA
					//Termina la ejecucion
					finEjecucion = true;
					break;
				case 26:
					//VERIFICA
					//Checar si el desplazamiento esta dentro de los limites del arreglo
					
					//Obtener el indice del arreglo que se quiere acceder
					int indiceMatriz = obtieneEntero(constantes, workspaceActual, funcion, bloque, cuadruplo.getOperando1());
					
					//Checar si el indice esta fuera de los limites del arreglo
					if(indiceMatriz < cuadruplo.getOperando2() | indiceMatriz > cuadruplo.getResultado()){												
						//Fin de programa
						System.out.println("Error: El indice esta fuera de los limites del arreglo/matriz");
						finEjecucion = true;
					} else {
						//Continuar con el siguiente cuadruplo
						indice++;
	    				cuadruplo = cuadruplos.get(indice);		
					}					
					break;	
				case 27:
					//SUMAMAT
					//Suma la direccion base y el desplazamiento para el indexamiento de matrices y arreglos 
					
					//Obtener S (el desplazamiento)
					int indiceSumar = obtieneEntero(constantes, workspaceActual, funcion, bloque, cuadruplo.getOperando1());
				
					//Sumar la base y almacenarlo en memoria
					almacenaEntero(constantes, workspaceActual, funcion, bloque, cuadruplo.getResultado(), indiceSumar + cuadruplo.getOperando2());																									
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);		
    				break;
				case 28:
					//MULTIMAT
					//Multiplica el desplazamiento por el tamaño de la matriz
					
					//Obtener S (el desplazamiento)
					int indiceMultiplicar = obtieneEntero(constantes, workspaceActual, funcion, bloque, cuadruplo.getOperando1());
					
					//Multiplicar por m1 y almacenarlo en memoria
					almacenaEntero(constantes, workspaceActual, funcion, bloque, cuadruplo.getResultado(), indiceMultiplicar * cuadruplo.getOperando2());																									
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);		
    				break;
				case 29:
					//ORO
					//Carga datos del objeto para tener acceso posteriormente
					//Establece una llave unica 
					String llave = cuadruplo.getOperando1S()+cuadruplo.getOperando2S()+cuadruplo.getResultadoS();					
					
					//Cargar los datos de la clase y lo carga en la estructura
					workspaces = datos.cargarObjetos(workspaces, llave, cuadruplo.getOperando2S());
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);
					break;
				case 30:
					//ACCESS
					//Se detecta necesidad de acceso a una clase
					
					accederAClase = true;
					nombreClaseAcceder = cuadruplo.getOperando1S()+cuadruplo.getOperando2S()+cuadruplo.getResultadoS();	
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);	
					break;
				case 31:
					//ENDACCESS	
					accederAClase = false;
					nombreClaseAcceder = "";
					workspaceActual = pilaObjetos.pop();
					
					//Continuar con el siguiente cuadruplo
					indice++;
    				cuadruplo = cuadruplos.get(indice);
					break;
					
    			}
    		}
	    } finally {
	        br.close();
	    }
	}    			    		    
	
	/**
	 * Funcion para obtener el tipo en base a la direccion de memoria virtual
	 * 
	 * @param direccion
	 * @return 0-entero, 1-decimal, 2-texto, 3-booleano
	 */
	public static int obtenerTipo(int direccion) {
		
		//Variables para las direcciones base de memoria
		int baseMemoriaConstante = 13000;
		int baseMemoriaTemp = 9000;
		int baseMemoriaLocal = 5000;
		int baseMemoriaGlobal = 1000;
		int diferencia = 0;
		
		if (direccion >= baseMemoriaConstante) {
			//Si la direccion esta en el espacio de constantes, obtener la diferencia
			diferencia = direccion - baseMemoriaConstante;
		} else if (direccion < baseMemoriaConstante
				&& direccion >= baseMemoriaTemp) {
			//Si la direccion esta en el espacio de temporales, obtener la diferencia
			diferencia = direccion - baseMemoriaTemp;
		} else if (direccion < baseMemoriaTemp && direccion >= baseMemoriaLocal) {
			//Si la direccion esta en el espacio de locales, obtener la diferencia
			diferencia = direccion - baseMemoriaLocal;
		} else {
			//Si la direccion esta en el espacio de globales, obtener la diferencia
			diferencia = direccion - baseMemoriaGlobal;
		}
		//Regresar el tipo correspondiente
		return diferencia / 1000;
	}

	/**
	 * Metodo para almacenar un registro entero en las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @param valor
	 */
	public static void almacenaEntero(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado, int valor){
		//Agregar un registro nuevo  
	if(direccionResultado>=0 && direccionResultado<1000){ 
		//Espacio de Retornos  
		retornos.get(direccionResultado).entero =  valor;    		    					  					    						
	}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
	//Espacio de globales    
		bloque.inicializarBase(1000);
		workspaceActual.getGlobales().ingresaElementoEntero(bloque.mapearDireccion(direccionResultado), valor);    		    					  					    						
	} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
	//Espacio de locales 
		bloque.inicializarBase(5000);
		funcion.getLocales().ingresaElementoEntero(bloque.mapearDireccion(direccionResultado), valor);
	} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
	//Espacio de temporales	
		bloque.inicializarBase(9000);
		funcion.getTemporales().ingresaElementoEntero(bloque.mapearDireccion(direccionResultado), valor); 
	} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
	//Espacio de constantes		
		bloque.inicializarBase(13000);
		constantes.ingresaElementoEntero(bloque.mapearDireccion(direccionResultado), valor);  						
	} 

	}
	
	/**
	 * Metodo para almacenar un registro decimal en las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @param valor
	 */
	public static void almacenaDecimal(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado, double valor){
	//Agregar un registro nuevo  
	if(direccionResultado>=0 && direccionResultado<1000){ 
		//Espacio de Retornos  
		retornos.get(direccionResultado).decimal=  valor;      		    					  					    						
	}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
	//Espacio de globales    
		bloque.inicializarBase(1000);
		workspaceActual.getGlobales().ingresaElementoDecimal(bloque.mapearDireccion(direccionResultado), valor);    		    					  					    						
	} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
	//Espacio de locales 
		bloque.inicializarBase(5000);
		funcion.getLocales().ingresaElementoDecimal(bloque.mapearDireccion(direccionResultado), valor);
	} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
	//Espacio de temporales	
		bloque.inicializarBase(9000);
		funcion.getTemporales().ingresaElementoDecimal(bloque.mapearDireccion(direccionResultado), valor); 
	} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
	//Espacio de constantes		
		bloque.inicializarBase(13000);
		constantes.ingresaElementoDecimal(bloque.mapearDireccion(direccionResultado), valor);  						
	}
	}
	
	/**
	 * Metodo para almacenar un registro texto en las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @param valor
	 */
	public static void almacenaTexto(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado, String valor){
	//Agregar un registro nuevo  
	if(direccionResultado>=0 && direccionResultado<1000){ 
		//Espacio de retornos  
		retornos.get(direccionResultado).texto =  valor;       		    					  					    						
	}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
	//Espacio de globales    
		bloque.inicializarBase(1000);
		workspaceActual.getGlobales().ingresaElementoTexto(bloque.mapearDireccion(direccionResultado), valor);    		    					  					    						
	} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
	//Espacio de locales 
		bloque.inicializarBase(5000);
		funcion.getLocales().ingresaElementoTexto(bloque.mapearDireccion(direccionResultado), valor);
	} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
	//Espacio de temporales	
		bloque.inicializarBase(9000);
		funcion.getTemporales().ingresaElementoTexto(bloque.mapearDireccion(direccionResultado), valor); 
	} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
	//Espacio de constantes		
		bloque.inicializarBase(13000);
		constantes.ingresaElementoTexto(bloque.mapearDireccion(direccionResultado), valor);  						
	}  
	}
	
	/**
	 * Metodo para almacenar un registro booleano en las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @param valor
	 */
	public static void almacenaBooleano(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado, boolean valor){
	//Agregar un registro nuevo  
	if(direccionResultado>=0 && direccionResultado<1000){ 
		//Espacio de retornos  
		retornos.get(direccionResultado).booleano =  valor;     		    					  					    						
	}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
	//Espacio de globales    
		bloque.inicializarBase(1000);
		workspaceActual.getGlobales().ingresaElementoBooleano(bloque.mapearDireccion(direccionResultado), valor);    		    					  					    						
	} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
	//Espacio de locales 
		bloque.inicializarBase(5000);
		funcion.getLocales().ingresaElementoBooleano(bloque.mapearDireccion(direccionResultado), valor);
	} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
	//Espacio de temporales	
		bloque.inicializarBase(9000);
		funcion.getTemporales().ingresaElementoBooleano(bloque.mapearDireccion(direccionResultado), valor); 
	} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
	//Espacio de constantes		
		bloque.inicializarBase(13000);
		constantes.ingresaElementoBooleano(bloque.mapearDireccion(direccionResultado), valor);  						
	}  
	}
	
	/**
	 * Metodo para recuperar el valor de un registro en las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @param valor
	 */
	public static int obtieneEntero(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado){
		
		int valor = -1;
		
		if(direccionResultado>=0 && direccionResultado<1000){ 
			//Espacio de retornos 
			retornos.get(direccionResultado).entero =  valor;       					  					    						
		}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
		//Espacio de globales    
			bloque.inicializarBase(1000);
			valor = workspaceActual.getGlobales().entero.get(bloque.mapearDireccion(direccionResultado));		    					  					    						
		} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
		//Espacio de locales 
			bloque.inicializarBase(5000);
			valor = funcion.getLocales().entero.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
		//Espacio de temporales	
			bloque.inicializarBase(9000);
			valor = funcion.getTemporales().entero.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
		//Espacio de constantes		
			bloque.inicializarBase(13000);
			valor = constantes.entero.get(bloque.mapearDireccion(direccionResultado));  						
		}
		return valor;
	}
	
	/**
	 * Metodo para obtener un registro decimal de las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @return
	 */
	public static double obtieneDecimal(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado){
		
		double valor = -1;
		
		if(direccionResultado>=0 && direccionResultado<1000){ 
			//Espacio de retornos 
			retornos.get(direccionResultado).decimal =  valor;       					  					    						
		}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
		//Espacio de globales    
			bloque.inicializarBase(1000);
			valor = workspaceActual.getGlobales().decimal.get(bloque.mapearDireccion(direccionResultado));		    					  					    						
		} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
		//Espacio de locales 
			bloque.inicializarBase(5000);
			valor = funcion.getLocales().decimal.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
		//Espacio de temporales	
			bloque.inicializarBase(9000);
			valor = funcion.getTemporales().decimal.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
		//Espacio de constantes		
			bloque.inicializarBase(13000);
			valor = constantes.decimal.get(bloque.mapearDireccion(direccionResultado));  						
		}
		return valor;
	}
	
	/**
	 * Metodo para obtener un registro texto de las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @return
	 */
	public static String obtieneTexto(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado){
		
		String valor = "";
		
		if(direccionResultado>=0 && direccionResultado<1000){ 
			//Espacio de retornos 
			retornos.get(direccionResultado).texto =  valor;      					  					    						
		}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
		//Espacio de globales    
			bloque.inicializarBase(1000);
			valor = workspaceActual.getGlobales().texto.get(bloque.mapearDireccion(direccionResultado));		    					  					    						
		} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
		//Espacio de locales 
			bloque.inicializarBase(5000);
			valor = funcion.getLocales().texto.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
		//Espacio de temporales	
			bloque.inicializarBase(9000);
			valor = funcion.getTemporales().texto.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
		//Espacio de constantes		
			bloque.inicializarBase(13000);
			valor = constantes.texto.get(bloque.mapearDireccion(direccionResultado));  						
		}
		return valor;
	}
	/**
	 * Metodo para obtener un registro booleano de las estructuras de memoria
	 * @param constantes
	 * @param workspaceActual
	 * @param funcion
	 * @param bloque
	 * @param direccionResultado
	 * @return
	 */
	public static boolean obtieneBooleano(bloque constantes, objetos workspaceActual, funcion funcion, bloque bloque, int  direccionResultado){
		
		boolean valor = false;
		
		if(direccionResultado>=0 && direccionResultado<1000){ 
			//Espacio de retornos 
			retornos.get(direccionResultado).booleano =  valor;       					  					    						
		}  else if(direccionResultado>=1000 && direccionResultado<5000){      					    			
		//Espacio de globales    
			bloque.inicializarBase(1000);
			valor = workspaceActual.getGlobales().booleano.get(bloque.mapearDireccion(direccionResultado));		    					  					    						
		} else  if(direccionResultado>=5000 && direccionResultado<9000){      					    			
		//Espacio de locales 
			bloque.inicializarBase(5000);
			valor = funcion.getLocales().booleano.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=9000 && direccionResultado<13000){      					    			
		//Espacio de temporales	
			bloque.inicializarBase(9000);
			valor = funcion.getTemporales().booleano.get(bloque.mapearDireccion(direccionResultado));
		} else  if(direccionResultado>=13000 && direccionResultado<17000){      					    			
		//Espacio de constantes		
			bloque.inicializarBase(13000);
			valor = constantes.booleano.get(bloque.mapearDireccion(direccionResultado));  						
		}
		return valor;
	}
}
