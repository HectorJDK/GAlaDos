/**
 * Clase bloque
 * 
 * Mantiene las estructuras para datos tipo entero, decimal, texto y booleano
 * Incluye metodos para agregar o modificar los elementos
 * @author Oziel Garza, Hector De la Garza
 */
import java.util.*;

public class retorno {

	//Estructuras para tipos de datos
	public int entero;					//Espacio para datos tipo entero
	public double decimal;					//Espacio para datos tipo decimal
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
