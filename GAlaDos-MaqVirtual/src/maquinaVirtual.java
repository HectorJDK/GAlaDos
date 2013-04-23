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
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
//Librerias para estructuras
import java.util.*;


public class maquinaVirtual {
	
	public static void main(String [ ] args) throws IOException{
		
		//Declaracion de variables y estructuras principales
		BufferedReader br = new BufferedReader(new FileReader("obj/codigoObjeto.txt"));		//Crear el objeto BufferedReader y cargar el documento			
		ArrayList<cuadruplos> cuadruplos ;				//Crear la lista que contendra los cuadruplos				
		HashMap<Integer, registro> bloque;				//Crear la estructura que contendrá el bloque de memoria con los registros				
		cuadruplos cuadruplo;					 		//Crear el objeto cuadruplo				
		registro registro;								//Crear el objeto registro de memoria
		boolean finEjecucion;							//Bandera para terminar la ejecucion (Fin de programa)
	    String line;									//String para leer la linea de archivo
	    String[] cuadruploLinea;						//String auxiliar para separacion de elementos del cuadruplo
	    int operacion, operando1, operando2;			//Auxiliares para almacenar elementos de los cuadruplos	    
		xmlParser datos;
	    try {
			
			//Inicializacion de variables y estructuras
			registro = new registro();	
			cuadruplo = new cuadruplos();
			finEjecucion = false; 				        
			line = br.readLine();			
	        
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
    		
	        //Iniciar ejecucion    		
    		while(!finEjecucion){
    		
    			//Primer cuadruplo
    			cuadruplo = cuadruplos.get(0);    			
    			if(cuadruplo.getOperacion() == 19){    				
    				cuadruplo = cuadruplos.get(cuadruplo.getResultado()-1);     				
    			}
    			//Obtener la operacion a ejecutar
    			operacion = cuadruplo.getOperacion();    			
    			//Obtener los operandos 
    			operando1 = bloque.get(cuadruplo.getOperando1()).getValor();
    			operando2 = bloque.get(cuadruplo.getOperando2()).getValor();
    			
    			switch (operacion){
    			//Suma
    			case (0):  
    				//Caso entero
    				    				
    				//Agregar un registro nuevo
    				registro.setDireccion(cuadruplo.getResultado());    			
    				registro.setValor(operando1 + operando2);
    				
    				//Agregar el registro al bloque de memoria
    				bloque.put(cuadruplo.getResultado(), registro);
    				
    				//Imprimir resultado de suma de 1 + 2 
    				System.out.println(registro.getValor());
    				break;
    				//Resta
    			case (1):  
    				//Caso entero
    				
    				//Agregar un registro nuevo
    				registro.setDireccion(cuadruplo.getResultado());    			
    				registro.setValor(operando1 - operando2);
    				
    				//Agregar el registro al bloque de memoria
    				bloque.put(cuadruplo.getResultado(), registro);
    				
    				//Imprimir resultado de suma de 1 + 2 
    				System.out.println(registro.getValor());
    				break;    			
    			//Division
				case (2):  
					//Caso entero
					
					//Agregar un registro nuevo
					registro.setDireccion(cuadruplo.getResultado());    			
					registro.setValor(operando1 / operando2);
					
					//Agregar el registro al bloque de memoria
					bloque.put(cuadruplo.getResultado(), registro);
					
					//Imprimir resultado de suma de 1 + 2 
					System.out.println(registro.getValor());
					break;    		
	    			//Multiplicacion
				case (3):  
					//Caso entero
					
					//Agregar un registro nuevo
					registro.setDireccion(cuadruplo.getResultado());    			
					registro.setValor(operando1 * operando2);
					
					//Agregar el registro al bloque de memoria
					bloque.put(cuadruplo.getResultado(), registro);
					
					//Imprimir resultado de suma de 1 + 2 
					System.out.println(registro.getValor());
					break;
	    			
    			}    			
    			finEjecucion = true;
    	}
	        
	    } finally {
	        br.close();
	    }
	}  
}
