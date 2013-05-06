import java.util.*;

public class funcion {
	
	String nombre;
	int regresa;
	int permiso;
	int direccionCuadruplo;
	bloque locales;
	bloque temporales;
	HashMap<Integer,Integer> parametros;
	
	//Constructor
	public funcion(){
		locales = new bloque();
		temporales = new bloque();
		parametros = new HashMap<Integer,Integer>();
	}
	
	public bloque getLocales(){
		return this.locales;
	}
	
	public void setLocales(bloque  locales){
		this.locales = locales;
	}
	
	public bloque  getTemporales(){
		return this.temporales;
	}
	
	public void setTemporales(bloque  temporales){
		this.temporales = temporales;
	}
	
	public String getNombre(){
		return this.nombre;
	}
	
	public void setNombre (String nombre){
		this.nombre = nombre;
	}
	
	public int getRegresa(){
		return this.regresa;
	}
	
	public void setRegresa (int regresa){
		this.regresa = regresa;
	}
	
	public int getPermiso(){
		return this.permiso;
	}
	
	public void setPermiso (int permiso){
		this.permiso = permiso;
	}
	
	public int getDireccionCuadruplo(){
		return this.direccionCuadruplo;
	}
	
	public void setDireccionCuadruplo (int direccionCuadruplo){
		this.direccionCuadruplo = direccionCuadruplo;
	}
}
