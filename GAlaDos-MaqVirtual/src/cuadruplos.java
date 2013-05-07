/**
 * Clase cuadruplos
 * 
 * Estructura especial para manipulación de los cuadruplos
 * 
 * @author Oziel Garza, Hector De la Garza
 *
 */
public class cuadruplos {
	
	//Elementos de cuadruplos
	public int operacion;							//Operacion a ejecutar
	public int operando1;							//Elemento del operando 1 en formato entero	
	public String operando1S;						//Elemento del operando 1 en formato string
	public int operando2;							//Elemento del operando 2 en formato entero
	public String operando2S;						//Elemento del operando 2 en formato string
	public int resultado;							//Elemento del resultado en formato entero
	public String resultadoS;						//Elemento del resultado en formato string
	
	//Constructor
	public cuadruplos(){
		this.operacion=-1;
		this.operando1=-1;
		this.operando2=-1;
		this.resultado=-1;
	}
	
	//Constructor especial para ERA
	public cuadruplos(String operando1S , String resultadoS){
		this.operacion=-1;
		this.operando1S=operando1S;
		this.operando2=-1;
		this.resultadoS=resultadoS;
	}
	
	//Constructor especial para ORO
	public cuadruplos(String operando1S , String operando2S, String resultadoS){
		this.operacion=-1;
		this.operando1S=operando1S;
		this.operando1S=operando2S;
		this.resultadoS=resultadoS;
	}
		
	//Getters y setters
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
	
	
	public String getOperando1S(){
		return this.operando1S;
	}
	
	public void setOperando1S(String operando1S){
		this.operando1S = operando1S;
	}
			
	
	public int getOperando2(){
		return this.operando2;
	}
	
	public void setOperando2(int operando2){
		this.operando2 = operando2;
	}
			
	public String getOperando2S(){
		return this.operando2S;
	}
	
	public void setOperando2S(String operando2S){
		this.operando2S = operando2S;
	}
	
	public int getResultado(){
		return this.resultado;
	}
	
	public void setResultado(int resultado){
		this.resultado = resultado;
	}
	
	public String getResultadoS(){
		return this.resultadoS;
	}
	
	public void setResultadoS(String resultadoS){
		this.resultadoS = resultadoS;
	}
}
