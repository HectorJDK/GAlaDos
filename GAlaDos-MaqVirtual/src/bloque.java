/**
 * Clase bloque
 * 
 * Mantiene las estructuras para datos tipo entero, decimal, texto y booleano
 * Incluye metodos para agregar o modificar elementos de cada tipo 
 * @author Oziel Garza, Hector De la Garza
 */

//Librerias para estructuras
import java.util.*;

public class bloque {

	//Estructuras para tipos de datos
	public ArrayList<Integer> entero;					//Espacio para datos tipo entero
	public ArrayList<Double> decimal;					//Espacio para datos tipo decimal
	public ArrayList<String> texto;						//Espacio para datos tipo texto
	public ArrayList<Boolean> booleano;					//Espacio para datos tipo booleano
	
	//Base para mapear memoria
	int baseEntero;
	int baseDecimal;
	int baseTexto;
	int baseBooleano;
	
	//Constructor
	public bloque(){
		entero = new ArrayList<Integer>();
		decimal = new ArrayList<Double>();
		texto = new ArrayList<String>();
		booleano = new ArrayList<Boolean>();
	}
	
	/**
	 * Metodo para establecer la base de la memoria
	 * Cada tipo tiene asignado 1000 espacios de memoria
	 * 
	 * @param baseEntero
	 */
	public void inicializarBase(int baseEntero){
		this.baseEntero = baseEntero;
		this.baseDecimal =  baseEntero + 1000;
		this.baseTexto =  baseEntero +2000;
		this.baseBooleano =  baseEntero+3000;
	}
	
	/**
	 * Método para mapear una dirección en su tipo y obtener el índice
	 * correspondiente en memoria
	 * 
	 * @param dirección
	 * @return La dirección de memoria virtual
	 */
	public int mapearDireccion(int direccion){
		//La direccion a retornar
		int dir = 0;
		
		if(direccion - baseEntero < 1000){
			//Si es de tipo entero, restar la direccion base
			dir = direccion - baseEntero;
		}else if(direccion - baseDecimal < 1000){
			//Si es de tipo decimal, restar la direccion base
			dir = direccion - baseDecimal;
		}else if(direccion - baseTexto < 1000){
			//Si es de tipo texto, restar la direccion base
			dir = direccion - baseTexto;
		}else if(direccion - baseBooleano < 1000){
			//Si es de tipo booleano, restar la direccion base
			dir = direccion - baseBooleano;
		}
		
		return dir;
	}
	
	/**
	 * Metodo para agregar un registro entero
	 * 
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoEntero(int direccion, int valor){	
			//Si la direccion es menor que el tamaño, reemplazar el valor existente
			if(entero.size() > direccion){
				entero.set(direccion,valor);
			} else {
				//Agregar una nueva direccion
				entero.add(direccion, valor); 
			}		
	}
	
	/**
	 * Metodo para agregar un registro decimal
	 * 
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoDecimal(int direccion, double valor){			
		//Si la direccion es menor que el tamaño, reemplazar el valor existente
		if(decimal.size()>direccion){
			decimal.set(direccion,valor);
		} else {
			//Agregar una nueva direccion
			decimal.add(direccion, valor); 
		}		
	}
	
	/**
	 * Metodo para agregar un registro texto
	 * 
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoTexto(int direccion, String valor){	
		//Si la direccion es menor que el tamaño, reemplazar el valor existente
		if(texto.size()>direccion){
			texto.set(direccion,valor);
		} else {
			//Agregar una nueva direccion
			texto.add(direccion, valor); 
		}		
	}
	
	/**
	 * Metodo para agregar un registro booleano
	 * 
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoBooleano(int direccion, boolean valor){	
		//Si la direccion es menor que el tamaño, reemplazar el valor existente
		if(booleano.size()>direccion){
			booleano.set(direccion,valor);
		} else {
			//Agregar una nueva direccion
			booleano.add(direccion, valor); 
		}		
	}	
}
