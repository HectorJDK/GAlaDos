/**
 * Clase funcion
 * 
 * Estructura principal para contener los datos de las funciones del programa
 * Incluye su propia estructura para variables locales y temporales
 * 
 * @author ozielgl
 *
 */
public class funcion {
	
	//Atributos de las funciones
	String nombre;									//Nombre de la funcion
	int regresa;									//Tipo de dato que regresa
	int permiso;									//Permiso de visibilidad (publica o privada)
	int direccionCuadruplo;							//La direccion del cuadruplo donde inicia la funcion
	//Estructuras para locales y temporales
	bloque locales;									//Estructura de variables locales
	bloque temporales;								//Estructura de variables temporales
	
	//Constructor
	public funcion(){
		locales = new bloque();
		temporales = new bloque();
	}
	
	//Getters y setters
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
	
}
