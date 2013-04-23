import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;
import java.util.HashMap;
 
public class xmlParser {
 
  public  HashMap<Integer, registro> cargarDatos(registro registro, HashMap<Integer, registro> bloque) {
 
    try {
 
	File fXmlFile = new File("obj/datos.txt");
	DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
	DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
	Document doc = dBuilder.parse(fXmlFile);	
	String direccion, valor, tipo, nombre;
	doc.getDocumentElement().normalize(); 

	//Cargar tabla de constantes a memoria
	NodeList nList = doc.getElementsByTagName("constante"); 
	
	for (int temp = 0; temp < nList.getLength(); temp++) { 
		Node nNode = nList.item(temp); 
		
		if (nNode.getNodeType() == Node.ELEMENT_NODE) { 
			Element eElement = (Element) nNode; 					
			
			direccion = eElement.getElementsByTagName("direccion").item(0).getTextContent();
			registro.setDireccion(Integer.parseInt(direccion));
			
			valor = eElement.getElementsByTagName("valor").item(0).getTextContent();
			registro.setValor(Integer.parseInt(valor));
			
			tipo = eElement.getElementsByTagName("tipo").item(0).getTextContent();		
			
			bloque.put(Integer.parseInt(direccion), registro);
			registro = new registro();
		}
	}	
    } catch (Exception e) {
	e.printStackTrace();
    }
	return bloque;
  }
}