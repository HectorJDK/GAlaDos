import java.util.*;

public class objetos {

	String nombre;
	bloque globales;
	bloque retornos;
	
	public objetos(){
		this.nombre="";
	}
	
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
