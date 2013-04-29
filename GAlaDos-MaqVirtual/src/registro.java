/**
 * Clase registro
 * 
 * Simula un registro de memoria conteniendo la direccion en el bloque
 * @author Oziel Garza, Hector De la Garza
 *
 */
public class registro {
	
	public int direccion;
	public int valorEntero;
	public double valorDecimal;
	public String valorTexto;
	public boolean valorBooleano;
	
	public registro(){
		this.direccion = 0;
//		this.valorEntero=0;
//		this.valorDecimal=0.0;
//		this.valorTexto="";
//		this.valorBooleano=false;		
	}
	
	//setters y getters
	public int getDireccion(){
		return this.direccion;
	}
	
	public void setDireccion(int direccion){
		this.direccion = direccion;
	}

	public int getValorEntero(){
		return this.valorEntero;
	}
	
	public void setValorEntero(int valorEntero){
		this.valorEntero = valorEntero;
	}
	
	public double getValorDecimal(){
		return this.valorDecimal;
	}
	
	public void setValorDecimal(double valorDecimal){
		this.valorDecimal = valorDecimal;
	}
	
	public String getValorTexto(){
		return this.valorTexto;
	}
	
	public void setValorTexto(String valorTexto){
		this.valorTexto = valorTexto;
	}
	
	public boolean getValorBooleano(){
		return this.valorBooleano;
	}
	
	public void setValorBooleano(boolean valorBooleano){
		this.valorBooleano = valorBooleano;
	}
}


