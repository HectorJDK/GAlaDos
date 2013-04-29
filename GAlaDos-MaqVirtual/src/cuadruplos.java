/**
 * Clase cuadruplos
 * 
 * Estructura especial para manipulacion de los cuadruplos
 * @author Oziel Garza, Hector De la Garza
 *
 */
public class cuadruplos {
	
	public int operacion;
	public int operando1;
	public int operando2;
	public int resultado;
	
	public cuadruplos(){
		this.operacion=-1;
		this.operando1=-1;
		this.operando2=-1;
		this.resultado=-1;
	}
	
	//Getters y setter
	public int getOperacion(){
		return this.operacion;
	}
	
	public void setOperacion(int operacion){
		this.operacion = operacion;
	}
	
	public int getOperando1(){
		return this.operando1;
	}
	public void setOperando1(int operando1){
		this.operando1 = operando1;
	}
	
	public int getOperando2(){
		return this.operando2;
	}
	public void setOperando2(int operando2){
		this.operando2 = operando2;
	}
	
	public int getResultado(){
		return this.resultado;
	}
	public void setResultado(int resultado){
		this.resultado = resultado;
	}
}
