/**
 * Clase retorno
 * 
 * Almacena el dato en su tipo correspondiente para cada retorno de funcion
 * 
 * @author Oziel Garza, Hector De la Garza
 */


public class retorno {

	//Estructuras para tipos de datos
	public int entero;							//Espacio para datos tipo entero
	public double decimal;						//Espacio para datos tipo decimal
	public String texto;						//Espacio para datos tipo texto
	public boolean booleano;					//Espacio para datos tipo booleano
		
	
	//Constructor
	public retorno(){
		entero = 0;
		decimal = 0.0;
		texto = "";
		booleano = false;
	}
	
}
