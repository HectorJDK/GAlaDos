/**
 * Clase objetos
 * 
 * Clase que almacena los objetos del programa y sus estructuras
 * de variables globales y retornos.
 * @author Oziel Garza, Hector De la Garza
 */
import java.util.*;

public class objetos {
	
	//Atributos de objetos
	String nombre;
	bloque globales;
	bloque retornos;
	
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
	
	public bloque getRetornos(){
		return this.retornos;
	}
	
	public void setRetornos(bloque retornos){
		this.retornos = retornos;
	}
}
