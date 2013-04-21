/**
 * Clase registro
 * 
 * Simula un registro de memoria conteniendo la direccion y el valor
 * Pendiente otros tipos de valores (String, booleano,...)
 * @author Oziel Garza, Hector De la Garza
 *
 */
public class registro {
	
	public int direccion;
	public int valor;
	
	public registro(){
		this.direccion = 0;
		this.valor = 0;
	}
	
	public int getDireccion(){
		return this.direccion;
	}
	
	public void setDireccion(int direccion){
		this.direccion = direccion;
	}
	
	public int getValor(){
		return this.valor;
	}
	public void setValor(int valor){
		this.valor = valor;
	}

}


