/**
 * Clase objetos
 * 
 * Clase que almacena los datos de objetos del programa y su estructura
 * de variables globales.
 * 
 * @author Oziel Garza, Hector De la Garza
 */

public class objetos {
	
	//Atributos de objetos
	String nombre;					//Nombre del objeto	
	bloque globales;				//Estructura de variables globales
	
	//Constructor
	public objetos(){
		this.nombre="";
	}
	
	//Getters y Setters
	public String getNombre(){
		return this.nombre;		
	}
	public void setNombre(String nombre){
		this.nombre = nombre;
	}
	
	public bloque getGlobales(){
		return this.globales;
	}
	
	public void setGlobales(bloque globales){
		this.globales = globales;
	}
	
	
}
