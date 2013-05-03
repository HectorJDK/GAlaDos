import java.util.*;

public class bloque {

	public ArrayList<Integer> entero;
	public ArrayList<Double> decimal;
	public ArrayList<String> texto;
	public ArrayList<Boolean> booleano;
	int baseEntero;
	int baseDecimal;
	int baseTexto;
	int baseBooleano;
	
	public bloque(){
		entero = new ArrayList<Integer>();
		decimal = new ArrayList<Double>();
		texto = new ArrayList<String>();
		booleano = new ArrayList<Boolean>();
	}
	
	public void inicializarBase(int baseEntero){
		this.baseEntero = baseEntero;
		this.baseDecimal =  baseEntero + 1000;
		this.baseTexto =  baseEntero +2000;
		this.baseBooleano =  baseEntero+3000;
	}
	
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
	
	public void ingresaElementoEntero(int direccion, int valor){	
			if(entero.size() < direccion){
				entero.set(direccion,valor);
			} else {
				entero.add(direccion, valor); 
			}		
	}
	public void ingresaElementoDecimal(int direccion, double valor){	
		if(decimal.size()<direccion){
			decimal.set(direccion,valor);
		} else {
			decimal.add(direccion, valor); 
		}		
}
	public void ingresaElementoTexto(int direccion, String valor){	
		if(texto.size()<direccion){
			texto.set(direccion,valor);
		} else {
			texto.add(direccion, valor); 
		}		
}
	public void ingresaElementoBooleano(int direccion, boolean valor){	
		if(booleano.size()<direccion){
			booleano.set(direccion,valor);
		} else {
			booleano.add(direccion, valor); 
		}		
}	
}
