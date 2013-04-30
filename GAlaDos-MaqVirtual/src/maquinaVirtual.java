/**
 * Maquina Virtual GALaDos
 * 
 * Programa que carga los cuadruplos y datos (tablas de objetos y constantes)
 * a estructuras especiales. 
 * Realiza el proceso de ejecucion mediante la simulacion de un bloque de 
 * memoria con registros (clase registro.java)
 * 
 * @author Oziel Garza, Hector De la Garza
 */

//Librerias para lectura de archivo
import java.io.*;
//Librerias para estructuras
import java.util.*;


public class maquinaVirtual {
	
	public static void main(String [ ] args) throws IOException{
		
		//Declaracion de variables y estructuras principales
		BufferedReader br = new BufferedReader(new FileReader("obj/codigoObjeto.txt"));		//Crear el objeto BufferedReader y cargar el documento			
		InputStreamReader stream = new InputStreamReader(System.in);							//Lectura de teclado
		BufferedReader brT = new BufferedReader(stream);		//Crear objeto para leer de teclado			
		ArrayList<cuadruplos> cuadruplos ;				//Crear la lista que contendra los cuadruplos				
		HashMap<Integer, registro> bloque;				//Crear la estructura que contendrá el bloque de memoria con los registros				
		cuadruplos cuadruplo;					 		//Crear el objeto cuadruplo				
		registro registro;								//Crear el objeto registro de memoria
		boolean finEjecucion;							//Bandera para terminar la ejecucion (Fin de programa)
	    String line;									//String para leer la linea de archivo
	    String[] cuadruploLinea;						//String auxiliar para separacion de elementos del cuadruplo
	    int operacion, tipo, indice;					//Auxiliares para el manejo de ejecucion de los cuadruplos	    
		xmlParser datos;	
		Stack<Integer> pilaEjecucion;
		Stack<HashMap<Integer, registro>> pilaBase;		
	    try {
			
			//Inicializacion de variables y estructuras
			registro = new registro();			
			cuadruplo = new cuadruplos();
			indice = 0;
			finEjecucion = false; 				        
			line = br.readLine();			
	        pilaEjecucion = new Stack<Integer>();
	        //Crear arraylist de objetos cuadruplos
	        cuadruplos = new ArrayList<cuadruplos>();
	       
	        //Crear arrayList del bloque de memoria
	        bloque = new HashMap<Integer,registro>();	  
	        
	        datos = new xmlParser();
	        /**
	         * Seccion para cargar los cuadruplos de archivo a la estructura arraylist
	         */
	        //Iterar hasta que termine todas las lineas del documento
	        while (line != null) {	        	
	        	cuadruploLinea = line.split(", ");	        	
        		cuadruplo.setOperacion(Integer.parseInt(cuadruploLinea[0]));
        		cuadruplo.setOperando1(Integer.parseInt(cuadruploLinea[1]));
        		cuadruplo.setOperando2(Integer.parseInt(cuadruploLinea[2]));
        		cuadruplo.setResultado(Integer.parseInt(cuadruploLinea[3]));
	        	//Agregarlo a la lista	       	        	
        		cuadruplos.add( cuadruplo);
        		//Reinicializar
        		cuadruplo = new cuadruplos();
        		
        		//Leer siguiente linea
	        	line = br.readLine();	           
	        }
	       
	        /**
	         * Seccion para cargar los datos de archivo 
	         */
	        //Ingresar la tabla de constantes a la memoria	        
	        bloque = datos.cargarDatos(registro, bloque);
    		
	        //Primer cuadruplo
    		cuadruplo = cuadruplos.get(indice);
    		if(cuadruplo.getOperacion() == 19){ 
				indice = cuadruplo.getResultado()-1;
				cuadruplo = cuadruplos.get(cuadruplo.getResultado()-1);     				
			}
	        //Iniciar ejecucion    		
    		while(!finEjecucion){
    			registro = new registro();
    			 			
    			
    			//Obtener la operacion a ejecutar
    			operacion = cuadruplo.getOperacion();    			
    			int direccionOperando1, direccionOperando2, direccionResultado,  tipoOperando1, tipoOperando2, tipoResultado;
    			//Direcciones
    			direccionOperando1 = cuadruplo.getOperando1();
				direccionOperando2 = cuadruplo.getOperando2();    			
				direccionResultado= cuadruplo.getResultado();
    				
				//Tipos
    			tipoOperando1 = obtenerTipo(direccionOperando1);
    			tipoOperando2 = obtenerTipo(direccionOperando2);
    			tipoResultado = obtenerTipo(direccionResultado);
    			
    			int operando1E=0, operando2E=0;
    			double operando1D=0.0, operando2D=0.0;
    			String operando1T="", operando2T=""; 
    			boolean operando1B=false, operando2B=false;
    			
    			switch(tipoOperando1){
    			case 0:
    				operando1E = bloque.get(direccionOperando1).getValorEntero();    			
    			break;
    			case 1:
    				operando1D = bloque.get(direccionOperando1).getValorDecimal();
    			break;
    			case 2:
    				operando1T = bloque.get(direccionOperando1).getValorTexto();
    			break;
    			case 3:
    				operando1B = bloque.get(direccionOperando1).getValorBooleano();
    			break;
    			}
    			
    			switch(tipoOperando2){
    			case 0:
    				operando2E = bloque.get(direccionOperando2).getValorEntero();    				
    			break;
    			case 1:
    				operando2D = bloque.get(direccionOperando2).getValorDecimal();
    			break;
    			case 2:
    				operando2T = bloque.get(direccionOperando2).getValorTexto();
    			break;
    			case 3:
    				operando2B = bloque.get(direccionOperando2).getValorBooleano();    			
    			break;
    			}
    			
    			switch (operacion){
    			//Suma
    			case (0):    				
    				if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Suma de dos enteros
    						if(tipoResultado==0){    	    							
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero(operando1E + operando2E);    					
    						} else {    							   						
    							registro.setValorDecimal(operando1E + operando2E); 
    						}
    					}else{
    						//Suma de entero mas decimal
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1E + operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1E + operando2D); 
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Suma decimal mas entero    						
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero((int)(operando1D + operando2E));    					
    						} else {    							   						
    							registro.setValorDecimal(operando1D + operando2E); 
    						}
    					}else{
    						//Suma de decimales
    						if(tipoResultado==0){        						
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1D + operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1D + operando2D); 
    						}
    					}
    				}
	    			//Obtener los operandos 
    				registro.setDireccion(direccionResultado);    			    				    						    				    								   
    				//Agregar el registro al bloque de memoria
    				bloque.put(direccionResultado, registro);
    				
    				//System.out.println("Resultado"+bloque.get(cuadruplo.getResultado()).getValorDecimal());    				
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				break;
    				
    				//Resta
    			case (1):  
    				if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Resta de dos enteros
    						if(tipoResultado==0){    	    							
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero(operando1E - operando2E);    					
    						} else {    							   						
    							registro.setValorDecimal(operando1E - operando2E); 
    						}
    					}else{
    						//Resta de entero mas decimal
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1E - operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1E - operando2D); 
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Resta decimal mas entero    						
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero((int)(operando1D - operando2E));    					
    						} else {    							   						
    							registro.setValorDecimal(operando1D - operando2E); 
    						}
    					}else{
    						//Resta de decimales
    						if(tipoResultado==0){        						
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1D - operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1D - operando2D); 
    						}
    					}
    				}
	    			//Obtener los operandos 
    				registro.setDireccion(direccionResultado);    			    				    						    				    								   
    				//Agregar el registro al bloque de memoria
    				bloque.put(direccionResultado, registro);
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				//System.out.println("Resultado"+bloque.get(cuadruplo.getResultado()).getValorEntero());    				
    				break;  			
    			//Division
				case (2):  
					if(tipoOperando1 == 0){
						if (tipoOperando2 == 0) {
							// Division de dos enteros
							if (tipoResultado == 0) {
								// Agregar un registro nuevo
								registro.setValorEntero(operando1E / operando2E);
							} else {
								registro.setValorDecimal(operando1E
										+ operando2E);
							}
						} else {
							// Division de entero mas decimal
							if (tipoResultado == 0) {
								// Agregar un registro nuevo
								registro.setValorEntero((int) (operando1E / operando2D));
							} else {
								registro.setValorDecimal(operando1E
										+ operando2D);
							}
						}
					} else {
						if (tipoOperando2 == 0) {
							// Division decimal mas entero
							if (tipoResultado == 0) {
								// Agregar un registro nuevo
								registro.setValorEntero((int) (operando1D / operando2E));
							} else {
								registro.setValorDecimal(operando1D
										+ operando2E);
							}
						} else {
							// Division de decimales
							if (tipoResultado == 0) {
								// Agregar un registro nuevo
								registro.setValorEntero((int) (operando1D / operando2D));
							} else {
								registro.setValorDecimal(operando1D
										+ operando2D);
							}
						}
					}
	    			//Obtener los operandos 
    				registro.setDireccion(direccionResultado);    			    				    						    				    								   
    				//Agregar el registro al bloque de memoria
    				bloque.put(direccionResultado, registro);
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				//System.out.println("Resultado"+bloque.get(cuadruplo.getResultado()).getValorEntero());    				
    				break;  		
	    			//Multiplicacion
				case (3):  
					if(tipoOperando1 == 0){
    					if(tipoOperando2 == 0){
    						//Multiplicacion de dos enteros
    						if(tipoResultado==0){    	    							
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero(operando1E * operando2E);    					
    						} else {    							   						
    							registro.setValorDecimal(operando1E * operando2E); 
    						}
    					}else{
    						//Multiplicacion de entero mas decimal
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1E * operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1E * operando2D); 
    						}
    					}    					
    				} else {
    					if(tipoOperando2 == 0){
    						//Multiplicacion decimal mas entero    						
    						if(tipoResultado==0){    				
    	    					//Agregar un registro nuevo    	    					 
    	    					registro.setValorEntero((int)(operando1D * operando2E));    					
    						} else {    							   						
    							registro.setValorDecimal(operando1D * operando2E); 
    						}
    					}else{
    						//Multiplicacion de decimales
    						if(tipoResultado==0){        						
    	    					//Agregar un registro nuevo    	    					   
    	    					registro.setValorEntero((int)(operando1D * operando2D));    					
    						} else {    							        						
    							registro.setValorDecimal(operando1D * operando2D); 
    						}
    					}
    				}
	    			//Obtener los operandos 
    				registro.setDireccion(cuadruplo.getResultado());    			    				    						    				    								   
    				//Agregar el registro al bloque de memoria
    				bloque.put(cuadruplo.getResultado(), registro);
    				indice++;
    				cuadruplo = cuadruplos.get(indice);   
    				//System.out.println("Resultado"+bloque.get(cuadruplo.getResultado()).getValorDecimal());    				
    				break;
				case 4:
					//Mayor que
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E > operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero > Decimal
							if(operando1E > operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D > operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal > Decimal
							if(operando1D > operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//					System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);    				
					break;
				case 5:
					//Menor que
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E < operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero > Decimal
							if(operando1E < operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D < operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal > Decimal
							if(operando1D < operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//					System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);    						
					break;
				case 6:
					//Mayor o igual
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E >= operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero > Decimal
							if(operando1E >= operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D >= operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal > Decimal
							if(operando1D >= operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//					System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);    					
					break;						
				case 7:
					//Menor o igual
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E <= operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero > Decimal
							if(operando1E <= operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else {
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D <= operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal > Decimal
							if(operando1D <= operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//					System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);    						
					break;
				case 8:
					//Igual
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero > Entero
							if(operando1E == operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero > Decimal
							if(operando1E == operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else if(tipoOperando1 == 1){
						if(tipoOperando2 == 0){
							//Decimal > Entero
							if(operando1D == operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal > Decimal
							if(operando1D == operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					} else if(tipoOperando1 == 2){
						if(tipoOperando2 == 2){
							//Texto == Texto
							if(operando1T.equals(operando2T)){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						}
					} else if(tipoOperando1 == 3){
						if(tipoOperando2 == 3){
							//Booleano == Booleano
							if(operando1B){								
								if(operando2B){									
									registro.setValorBooleano(true);
								} else {									
									registro.setValorBooleano(false);	
								}
							} else {
								if(operando2B){
									registro.setValorBooleano(false);
								} else {
									registro.setValorBooleano(true);	
								}								
							}
						}
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//						System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				finEjecucion = true;					
					break;
				case 9:
					//Diferente
					if(tipoOperando1 == 0){
						if(tipoOperando2 == 0){
							//Entero != Entero
							if(operando1E != operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Entero != Decimal
							if(operando1E != operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					} else if(tipoOperando1 == 1){
						if(tipoOperando2 == 0){
							//Decimal != Entero
							if(operando1D != operando2E){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						} else {
							//Decimal != Decimal
							if(operando1D != operando2D){
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}	
					} else if(tipoOperando1 == 2){
						if(tipoOperando2 == 2){
							//Texto != Texto
							if(!operando1T.equals(operando2T)){
								registro.setValorBooleano(true);
							} else {								
								registro.setValorBooleano(false);
							}
						}
					} else if(tipoOperando1 == 3){
						if(tipoOperando2 == 3){
							//Booleano != Booleano
							if(operando1B){								
								if(operando2B){									
									registro.setValorBooleano(false);
								} else {									
									registro.setValorBooleano(true);	
								}
							} else {
								if(operando2B){
									registro.setValorBooleano(true);
								} else {
									registro.setValorBooleano(false);	
								}								
							}
						}
					}
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//						System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				finEjecucion = true;					
					break;
				case 10:
					//AND
					if (tipoOperando1 == 3) {
						if (tipoOperando2 == 3) {
							// Booleano AND Booleano
							if (operando1B & operando2B) {
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					}					
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//						System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				finEjecucion = true;					
					break;
				case 11:
					//OR
					if (tipoOperando1 == 3) {
						if (tipoOperando2 == 3) {
							// Booleano OR Booleano
							if (operando1B | operando2B) {
								registro.setValorBooleano(true);
							} else {
								registro.setValorBooleano(false);
							}
						}
					}					
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
//					if(bloque.get(direccionResultado).getValorBooleano()){
//						System.out.println("ladoder");    						
//					}					
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				finEjecucion = true;					
					break;
				case 12:
					//Asignacion
					//System.out.println("ladoder"+bloque.get(cuadruplo.getOperando1()).getValorEntero());    												
					registro.setDireccion(cuadruplo.getResultado());
					switch(tipoOperando1){
					case 0:
						//Entero
						if(tipoResultado == 0){
							registro.setValorEntero(bloque.get(cuadruplo.getOperando1()).getValorEntero());							
						} else {
							registro.setValorDecimal(bloque.get(cuadruplo.getOperando1()).getValorEntero());						
						}
						break;
					case 1:
						//Decimal
						if(tipoResultado == 0){
							registro.setValorEntero((int)bloque.get(cuadruplo.getOperando1()).getValorDecimal());							
						} else {
							registro.setValorDecimal(bloque.get(cuadruplo.getOperando1()).getValorDecimal());						
						}
						break;
					case 2:
						//Texto
						if(tipoResultado == 2){
							registro.setValorTexto(bloque.get(cuadruplo.getOperando1()).getValorTexto());
						}
						break;
					case 3:
						//Booleano
						if(tipoResultado == 3){
							registro.setValorBooleano(bloque.get(cuadruplo.getOperando1()).getValorBooleano());
						}
					}
										
					bloque.put(cuadruplo.getResultado(),registro);				
					
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
								registro.setValorTexto(""+operando1E+operando2E);
							break;
							case 1: 
								//Entero concatena Decimal
								registro.setValorTexto(""+operando1E+operando2D);
							break;
							case 2:
								//Entero concatena Texto
								registro.setValorTexto(""+operando1E+operando2T);
							break;
						} 
					break;
					case 1:
						switch(tipoOperando2){
							case 0:
								//Decimal concatena ENTERO 
								registro.setValorTexto(""+operando1D+operando2E);
							break;
							case 1: 
								//Decimal concatena Decimal
								registro.setValorTexto(""+operando1D+operando2D);
							break;
							case 2:
								//Decimal concatena Texto
								registro.setValorTexto(""+operando1D+operando2T);
							break;
						} 
					break;
					case 2:
						switch(tipoOperando2){
							case 0:
								//Texto concatena ENTERO 
								registro.setValorTexto(""+operando1T+operando2E);
							break;
							case 1: 
								//Texto concatena Decimal
								registro.setValorTexto(""+operando1T+operando2D);
							break;
							case 2:
								//Texto concatena Texto
								registro.setValorTexto(""+operando1T+operando2T);
							break;
						} 
					break;
					}					
					registro.setDireccion(direccionResultado);
					bloque.put(direccionResultado,registro);
					
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				//finEjecucion = true;					
					break;
				case 16:
					//GOTOFALSO
					if(!bloque.get(direccionOperando1).getValorBooleano()){						
						indice = cuadruplo.getResultado();
					} else {
						indice++;
					}
					
					cuadruplo = cuadruplos.get(indice);
						//finEjecucion = true;
					break;
				case 17:
					//Lectura					
					switch(tipoResultado){
						case 0:
							//Lee Entero
							registro.setValorEntero(Integer.parseInt(brT.readLine()));
						break;
						case 1: 
							//Lee Decimal
							registro.setValorDecimal(Double.parseDouble(brT.readLine()));
						break;
						case 2:
							//Lee Texto
							registro.setValorTexto(brT.readLine());
						break;
					} 
									
					registro.setDireccion(direccionResultado);
					if(bloque.containsKey(direccionResultado)){
						bloque.remove(direccionResultado);
					}
					bloque.put(direccionResultado,registro);
									
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				//finEjecucion = true;					
					break;
				case 18:
					//Escritura					
					switch(tipoResultado){
						case 0:
							//Imprime Entero
							System.out.println(""+bloque.get(direccionResultado).getValorEntero());
						break;
						case 1: 
							//Imprime Decimal
							System.out.println(""+bloque.get(direccionResultado).getValorDecimal());
						break;
						case 2:
							//Imprime Texto
							System.out.println(""+bloque.get(direccionResultado).getValorTexto());
						break;
					} 
																		
					indice++;
    				cuadruplo = cuadruplos.get(indice);
    				funcion funcion = new funcion(3,2);
    				funcion.setNombre("funcion1");
    				datos.cargarDatosFuncion( registro, ":main:", funcion);
    				System.out.println("func"+funcion.getPermiso());
    				//finEjecucion = true;					
					break;
				case 19:	
					//GOTO
					indice = cuadruplo.getResultado();
									
					cuadruplo = cuadruplos.get(indice);
					//finEjecucion = true;
					break;
				case 20:
					//ERA
					//llamar a funcion en xmlParser y obtener tamaño de la funcion
					//crear el objeto funcion 
					
					//Guardar el bloque de memoria
				case 21: 
					//PARAM
					//asignar cada parametro con su valor a la estructura de la funcion
					
					//Meter direccion de retorno en la pila de ejecucion
					//pilaEjecucion.push(123);
				case 22:
					//GOSUB
					//Meter el objeto funcion en la pila
					
				case 23:
					//RET
					//Sacar la direccion de ejecucion
					//pilaEjecucion.pop();
					//Reestablecer el bloque de memoria
    			}    		     			    		
    	}
	        
	    } finally {
	        br.close();
	    }
	}
	
	/**
	 * Funcion para obtener el tipo en base a la direccion de memoria 
	 * virtual 
	 * @param direccion
	 * @return 0-entero, 1-decimal, 2-texto, 3-booleano 
	 */
	public static int obtenerTipo(int direccion){
		
		int baseMemoriaConstante = 13000;
		int baseMemoriaTemp = 9000;
		int baseMemoriaLocal = 5000;
		int baseMemoriaGlobal = 1000;
		int diferencia=0;
		
		if(direccion >= baseMemoriaConstante ){					
			diferencia = direccion - baseMemoriaConstante;
		} else if(direccion < baseMemoriaConstante && direccion >= baseMemoriaTemp){
			diferencia = direccion - baseMemoriaTemp;
		} else if(direccion < baseMemoriaTemp && direccion >= baseMemoriaLocal){
			diferencia = direccion - baseMemoriaLocal;
		} else {
			diferencia = direccion - baseMemoriaGlobal;
		}
		return diferencia / 1000;						
	}
}
