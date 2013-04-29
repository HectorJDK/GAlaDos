/**
 * xmlParser
 * Modulo para leer el archivo xml con los datos de variables y constantes
 * generado por el compilador.
 * Carga la informacion al bloque de memoria
 * @author Oziel Garza, Hector De la Garza
 */
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;
import java.util.HashMap;
 
public class xmlParser {
 
	/**
	 * Metodo cargarDatos
	 * Lee la informacion del archivo xml. Los nodos para constantes se cargan 
	 * en registros y se agregan al bloque de memoria.
	 * @param registro. Estructura para ingresar en el bloque.
	 * @param bloque. El bloque inicial.
	 * @return bloque. El bloque con los registros agregados.
	 */
  public  HashMap<Integer, registro> cargarDatos(registro registro, HashMap<Integer, registro> bloque) {
 
    try {
    	
    //Declaracion e inicializacion de estructuras y objetos	
	File fXmlFile = new File("obj/datos.txt");			
	DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
	DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
	Document doc = dBuilder.parse(fXmlFile);	
	String direccion, valor, nombre;
	int tipo;
	doc.getDocumentElement().normalize(); 

	/**
	 * Seccion para cargar tabla de constantes a memoria
	 */
	//Obtener la lista de nodos tipo constante
	NodeList nList = doc.getElementsByTagName("constante"); 
	
	//Iterar la lista para agregar cada nodo al bloque
	for (int temp = 0; temp < nList.getLength(); temp++) { 
		//Nodo actual
		Node nNode = nList.item(temp); 
		//Si el nodo tiene elementos internos
		if (nNode.getNodeType() == Node.ELEMENT_NODE) { 
			//Objeto elemento con los subnodos
			Element eElement = (Element) nNode; 					
			
			//Obtener la direccion
			direccion = eElement.getElementsByTagName("direccion").item(0).getTextContent();
			registro.setDireccion(Integer.parseInt(direccion));
			//Obtener el tipo
			tipo = Integer.parseInt(eElement.getElementsByTagName("tipo").item(0).getTextContent());	
			//Obtener el valor
			valor = eElement.getElementsByTagName("valor").item(0).getTextContent();
			switch (tipo) {
			case 0:
				registro.setValorEntero(Integer.parseInt(valor));
				break;
			case 1:
				registro.setValorDecimal(Double.parseDouble(valor));
				break;
			case 2:
				registro.setValorTexto(valor);
				break;
			case 3:
				if(valor.equals("falso")){					
					registro.setValorBooleano(false);
				} else {
					registro.setValorBooleano(true);
				}
				break;			
			}
			
			

			//Ingresarlo al bloque de memoria
			bloque.put(Integer.parseInt(direccion), registro);
			//Reinicializar la estructura
			registro = new registro();
		}
	}	
    } catch (Exception e) {
    	e.printStackTrace();
    }
	return bloque;
  }
}