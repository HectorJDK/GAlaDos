/**
 * Clase bloque
 * 
 * Mantiene las estructuras para datos tipo entero, decimal, texto y booleano
 * Incluye metodos para agregar o modificar los elementos
 * @author Oziel Garza, Hector De la Garza
 */
import java.util.*;

public class bloque {

	//Estructuras para tipos de datos
	public ArrayList<Integer> entero;
	public ArrayList<Double> decimal;
	public ArrayList<String> texto;
	public ArrayList<Boolean> booleano;
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
	 * @param baseEntero
	 */
	public void inicializarBase(int baseEntero){
		this.baseEntero = baseEntero;
		this.baseDecimal =  baseEntero + 1000;
		this.baseTexto =  baseEntero +2000;
		this.baseBooleano =  baseEntero+3000;
	}
	
	/**
	 * Metodo para mapear una direccion en su tipo y obtener el indice
	 * correspondiente en memoria
	 * @param direccion
	 * @return La direccion de memoria virtual
	 */
	public int mapearDireccion(int direccion){
		int dir = 0;
		if(direccion - baseEntero < 1000){
			dir = direccion - baseEntero;
		}else if(direccion - baseDecimal < 1000){
			dir = direccion - baseDecimal;
		}else if(direccion - baseTexto < 1000){
			dir = direccion - baseTexto;
		}else if(direccion - baseBooleano < 1000){
			dir = direccion - baseBooleano;
		}
		return dir;
	}
	
	/**
	 * Metodo para agregar un registro entero
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoEntero(int direccion, int valor){	
			if(entero.size() < direccion){
				entero.set(direccion,valor);
			} else {
				entero.add(direccion, valor); 
			}		
	}
	
	/**
	 * Metodo para agregar un registro decimal
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoDecimal(int direccion, double valor){	
		if(decimal.size()<direccion){
			decimal.set(direccion,valor);
		} else {
			decimal.add(direccion, valor); 
		}		
	}
	
	/**
	 * Metodo para agregar un registro texto
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoTexto(int direccion, String valor){	
		if(texto.size()<direccion){
			texto.set(direccion,valor);
		} else {
			texto.add(direccion, valor); 
		}		
	}
	
	/**
	 * Metodo para agregar un registro booleano
	 * @param direccion
	 * @param valor
	 */
	public void ingresaElementoBooleano(int direccion, boolean valor){	
		if(booleano.size()<direccion){
			booleano.set(direccion,valor);
		} else {
			booleano.add(direccion, valor); 
		}		
	}	
}
