/**
 * Clase xmlParser
 * 
 * Modulo para leer el archivo xml con los datos de objetos, funciones, retornos y constantes
 * generado por el compilador.
 * Carga la informacion al bloque de memoria
 * 
 * @author Oziel Garza, Hector De la Garza
 */
//Librerias para manejo de xml
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;

//Librerias para manejo de nodos
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

//Librerias para control de archivos
import java.io.File;
import java.util.*;
 
public class xmlParser {
 
	/**
	 * Metodo para cargar los datos de los objetos del archivo xml
	 * Lee las variables globales y las almacena en la estructura correspondiente
	 * 
	 * @param objetos: La lista de objetos, llave: El indice para accesarlo, objeto: El nombre del objeto
	 * @return La lista de objetos con el nuevo objeto cargado
	 */
	public HashMap<String, objetos> cargarObjetos(HashMap<String,objetos> objetos, String llave, String objeto) {

		try {
			// Declaracion e inicializacion de estructuras para el manejo de xml
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			//Estrucuturas de nodo auxiliares
			Node auxiliar;
			
			// Temporales para objeto
			objetos objetoTemporal = new objetos();
			bloque bloque = new bloque();

			doc.getDocumentElement().normalize();
			
			// Obtener el nodo principal del objeto
			NodeList principal = doc.getElementsByTagName(objeto);
			auxiliar = principal.item(0);			

			// Verificar si el nodo es de tipo elemento		
				if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) auxiliar;
					//Si el nodo no pertenece a la seccion de constantes o variables de retorno
					if (!eElement.getNodeName().equals("constantes") && !eElement.getNodeName().equals("variablesRetornos")) {

						// Guardar el nombre
						objetoTemporal.setNombre(eElement.getNodeName());

						// Guardar globales
						NodeList auxiliarLista2 = eElement
								.getElementsByTagName("variablesGlobales");
						auxiliar = auxiliarLista2.item(0);
						// Verificar si el nodo es de tipo elemento	
						if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
							// Objeto elemento con los subnodos
							Element eElement2 = (Element) auxiliar;
							//Obtener la lista de nodos de tipo variable global
							NodeList auxiliarLista3 = eElement2
									.getElementsByTagName("variableGlobal");
							bloque.inicializarBase(1000);
							// Iterar la lista para agregar cada variable global
							for (int temp2 = 0; temp2 < auxiliarLista3
									.getLength(); temp2++) {
								auxiliar = auxiliarLista3.item(temp2);
								// Verificar si el nodo es de tipo elemento	
								if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
									// Obtener los datos de variables globales
									Element eElement3 = (Element) auxiliar;

									int tipo = Integer.parseInt(eElement3
											.getElementsByTagName("tipo")
											.item(0).getTextContent());
									int direccion = Integer.parseInt(eElement3
											.getElementsByTagName("direccion")
											.item(0).getTextContent());
									
									//Si es un arreglo o matriz generar su espacio correspondiente
									if(eElement3.getElementsByTagName("dimensionada").item(0) != null){
																													
									int tamanio = Integer
											.parseInt(eElement3
													.getElementsByTagName(
															"tamanio")
													.item(0)
													.getTextContent());
									//Ingresar el elemento de acuerdo a su tipo
									switch (tipo) {
									case 0:
										for(int i = 0; i<tamanio; i++){
										bloque.ingresaElementoEntero(
												bloque.mapearDireccion(direccion+i),
												-1);
										}
										break;
									case 1:
										for(int i = 0; i<tamanio; i++){
										bloque.ingresaElementoDecimal(
												bloque.mapearDireccion(direccion+i),
												-1);
										}
										break;
									case 2:
										for(int i = 0; i<tamanio; i++){
										bloque.ingresaElementoTexto(
												bloque.mapearDireccion(direccion+i),
												"");
										}
										break;
									case 3:
										for(int i = 0; i<tamanio; i++){
										bloque.ingresaElementoBooleano(
												bloque.mapearDireccion(direccion+i),
												false);
										}
										break;
									}
									}
									
									//Guardar la direccion en memoria
									//Ingresar el elemento de acuerdo a su tipo
									switch (tipo) {
									case 0:
										bloque.ingresaElementoEntero(bloque
												.mapearDireccion(direccion), -1);
										break;
									case 1:
										bloque.ingresaElementoDecimal(bloque
												.mapearDireccion(direccion), -1);
										break;
									case 2:
										bloque.ingresaElementoTexto(bloque
												.mapearDireccion(direccion), "");
										break;
									case 3:
										bloque.ingresaElementoBooleano(bloque
												.mapearDireccion(direccion),
												false);
										break;
									}
								}
							}
							//Agregar la estructura de globales al objeto
							objetoTemporal.setGlobales(bloque);
							//Resetear el objeto bloque
							bloque = new bloque();								
						}
						// Agregar a la lista de objetos el objeto recien cargado						
						objetos.put(llave,objetoTemporal);
						//Resetear el objeto
						objetoTemporal = new objetos();
					}				
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return objetos;
	}
	
	/**
	 * Metodo para cargar los datos de la funcion del xml
	 * Carga los datos de variables locales y temporales
	 * 
	 * @param objeto El objeto actual
	 * @param nombre El nombre de la funcion
	 * @param funcion La estructura de funcion
	 * @return La funcion con los datos
	 */
	public funcion cargarFunciones(objetos objeto, String nombre,
			funcion funcion, String nombreObjeto) {

		try {
						
			// Declaracion e inicializacion de estructuras para el manejo del xml
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			//Estructuras de nodo auxiliares
			Node auxiliar;
			NodeList auxiliarLista;
			
			//Estructura de bloque auxiliar
			bloque bloque = new bloque();

			doc.getDocumentElement().normalize();
			
			// Obtener el nodo principal
			auxiliarLista = doc.getElementsByTagName(nombreObjeto);
						
			// Iterar la lista para buscar la funcion y cargar sus datos
			for (int temp = 0; temp < auxiliarLista.getLength(); temp++) {
				// Nodo actual
				auxiliar = auxiliarLista.item(temp);
				// Verificar si el nodo es de tipo elemento	
				if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) auxiliar;
					//Si el nodo no pertenece a la seccion de constantes o variables de retorno
					if (!eElement.getNodeName().equals("constantes") && !eElement.getNodeName().equals("variablesRetornos")) {
						// Guardar funciones
						//Obtener la lista de nodos de tipo procedimientos
						NodeList auxiliarLista3 = eElement
								.getElementsByTagName("procedimientos");
						auxiliar = auxiliarLista3.item(0);
						// Verificar si el nodo es de tipo elemento	
						if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
							// Objeto elemento con los subnodos
							Element eElement2 = (Element) auxiliar;
							
							NodeList auxiliarLista4 = eElement2.getChildNodes();
							// Iterar la lista para agregar cada funcion
							for (int temp2 = 0; temp2 < auxiliarLista4
									.getLength(); temp2++) {
								auxiliar = auxiliarLista4.item(temp2);
								// Verificar si el nodo es de tipo elemento	
								if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
									// Obtener los datos de procedimientos
									Element eElement3 = (Element) auxiliar;
									//Si el nombre del procedimiento es igual al nombre de la funcion a cargar									
									if (eElement3.getNodeName().equals(nombre)) {

										//Guardar el nombre de la funcion
										funcion.setNombre(eElement3
												.getNodeName());
										
										//Guardar el tipo de dato que regresa la funcion
										funcion.setRegresa(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"regresa")
														.item(0)
														.getTextContent()));
										
										//Guardar la visiblidad de la funcion
										funcion.setPermiso(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"permiso")
														.item(0)
														.getTextContent()));
										
										//Guardar la direccion del cuadruplo donde inicia la funcion
										funcion.setDireccionCuadruplo(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"direccionCuadruplo")
														.item(0)
														.getTextContent()));

										// Guardar locales
										bloque.inicializarBase(5000);
										//Obtener la lista de nodos de tipo variable locales
										NodeList auxiliarLista5 = eElement3
												.getElementsByTagName("variablesLocales");
										auxiliar = auxiliarLista5.item(0);
										// Verificar si el nodo es de tipo elemento	
										if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
											// Objeto elemento con los subnodos
											Element eElement4 = (Element) auxiliar;

											NodeList auxiliarLista6 = eElement4
													.getChildNodes();
											// Iterar la lista para agregar cada variable
											for (int temp3 = 0; temp3 < auxiliarLista6
													.getLength(); temp3++) {
												auxiliar = auxiliarLista6
														.item(temp3);
												if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
													// Obtener los datos de variables locales
													Element eElement5 = (Element) auxiliar;

													//Obtener el tipo
													int tipo = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"tipo")
																	.item(0)
																	.getTextContent());
													//Si el tipo es valido
													if(tipo != 4){
													int direccion = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"direccion")
																	.item(0)
																	.getTextContent());
													
													//Si es un arreglo o matriz generar su espacio correspondiente
													if(eElement5.getElementsByTagName("dimensionada").item(0) != null){
													
													//Obtener el tamaño
													int tamanio = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"tamanio")
																	.item(0)
																	.getTextContent());
													
													//Ingresar el elemento de acuerdo a su tipo
													switch (tipo) {
													case 0:
														for(int i = 0; i<tamanio; i++){
														bloque.ingresaElementoEntero(
																bloque.mapearDireccion(direccion+i),
																-1);
														}
														break;
													case 1:
														for(int i = 0; i<tamanio; i++){
														bloque.ingresaElementoDecimal(
																bloque.mapearDireccion(direccion+i),
																-1);
														}
														break;
													case 2:
														for(int i = 0; i<tamanio; i++){
														bloque.ingresaElementoTexto(
																bloque.mapearDireccion(direccion+i),
																"");
														}
														break;
													case 3:
														for(int i = 0; i<tamanio; i++){
														bloque.ingresaElementoBooleano(
																bloque.mapearDireccion(direccion+i),
																false);
														}
														break;
													}
													
													}
													//Guardar variables locales en memoria
													//Ingresar el elemento de acuerdo a su tipo
													switch (tipo) {
													case 0:
														bloque.ingresaElementoEntero(
																bloque.mapearDireccion(direccion),
																-1);
														break;
													case 1:
														bloque.ingresaElementoDecimal(
																bloque.mapearDireccion(direccion),
																-1);
														break;
													case 2:
														bloque.ingresaElementoTexto(
																bloque.mapearDireccion(direccion),
																"");
														break;
													case 3:
														bloque.ingresaElementoBooleano(
																bloque.mapearDireccion(direccion),
																false);
														break;
													}
													}
												}
											}
											//Asignar la estructura de locales a la funcion
											funcion.setLocales(bloque);
											//Resetear la estructura bloque
											bloque = new bloque();
										}																																																						
										
									}
								}

							}
						}

					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return funcion;
	}


	/**
	 * Metodo que carga las constantes del archivo xml
	 * 
	 * @param bloque Estructura bloque
	 * @return bloque El bloque con las constantes cargadas
	 */
	public bloque cargarConstantes(bloque bloque) {

		try {

			// Declaracion e inicializacion de variables para el manejo del xml
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			//Variables de constantes
			String valor;
			int direccion;
			int tipo;
			doc.getDocumentElement().normalize();			

			/**
			 * Seccion para cargar tabla de constantes a memoria
			 */
			// Obtener la lista de nodos tipo constante
			NodeList nList = doc.getElementsByTagName("constante");

			// Iterar la lista para agregar cada nodo al bloque
			for (int temp = 0; temp < nList.getLength(); temp++) {
				// Nodo actual
				Node nNode = nList.item(temp);
				// Verificar si el nodo es de tipo elemento	
				if (nNode.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) nNode;
					
					if(eElement.getElementsByTagName("direccion").item(0) != null){
						
						// Obtener la direccion
						direccion = Integer.parseInt(eElement
								.getElementsByTagName("direccion").item(0)
								.getTextContent());
						
						// Obtener el tipo
						tipo = Integer.parseInt(eElement
								.getElementsByTagName("tipo").item(0)
								.getTextContent());					
						
						// Obtener el valor
						valor = eElement.getElementsByTagName("valor").item(0)
								.getTextContent();
						bloque.inicializarBase(13000);
						
						//Ingresar el elemento de acuerdo a su tipo
						switch (tipo) {
						case 0:
							bloque.ingresaElementoEntero(
									bloque.mapearDireccion(direccion),
									Integer.parseInt(valor));
							break;
						case 1:
							bloque.ingresaElementoDecimal(
									bloque.mapearDireccion(direccion),
									Double.parseDouble(valor));
							break;
						case 2:
							bloque.ingresaElementoTexto(
									bloque.mapearDireccion(direccion), valor);
							break;
						case 3:
							if (valor.equals("falso")) {
								bloque.ingresaElementoBooleano(
										bloque.mapearDireccion(direccion), false);
							} else {
								bloque.ingresaElementoBooleano(
										bloque.mapearDireccion(direccion), true);
							}
							break;
						}
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return bloque;
	}
  
	/**
	 * Metodo que carga las variables de retornos a su estructura
	 * 
	 * @param retornos La lista de retornos
	 * @return La lista de retornos con los retornos añadidos
	 */
	public HashMap<Integer,retorno> cargarRetornos(HashMap<Integer,retorno> retornos) {

		try {

			// Declaracion e inicializacion de variables para el manejo del xml
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			//Variables de retornos
			int direccion = 0;
			int tipo;
			retorno retornoAuxiliar = new retorno();
			
			doc.getDocumentElement().normalize();			

			/**
			 * Seccion para cargar retornos a memoria
			 */

			// Obtener la lista de nodos tipo retorno
			NodeList nList = doc.getElementsByTagName("variableRetorno");

			// Iterar la lista para agregar cada nodo al bloque
			for (int temp = 0; temp < nList.getLength(); temp++) {
				// Nodo actual
				Node nNode = nList.item(temp);
				// Verificar si el nodo es de tipo elemento	
				if (nNode.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) nNode;
					
					if(eElement.getElementsByTagName("direccion").item(0) != null){
						
						// Obtener la direccion
						direccion = Integer.parseInt(eElement
								.getElementsByTagName("direccion").item(0)
								.getTextContent());
						
						// Obtener el tipo
						tipo = Integer.parseInt(eElement
								.getElementsByTagName("tipo").item(0)
								.getTextContent());	
						
						//Ingresar el elemento de acuerdo a su tipo
						switch (tipo) {
						case 0:
							retornoAuxiliar.entero = 0;
							break;
						case 1:
							retornoAuxiliar.decimal = 0.0;
							break;
						case 2:
							retornoAuxiliar.texto = "";
							break;
						case 3:
							retornoAuxiliar.booleano = false;						
							break;
						}
					}
				}
				//Agregar el retorno a la lista
				retornos.put(direccion, retornoAuxiliar);
				//Resetear el retorno
				retornoAuxiliar = new retorno();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return retornos;
	}
  
  /**
   * Metodo para obtener el tipo de un registro retorno obtenido por el xml
   * 
   * @param objeto El nombre del objeto
   * @param direccion La direccion del retorno
   * @return int tipo El tipo de dato del retorno
   */
	public int tipoRetorno(String objeto, String direccion) {
		int tipo = 0;
		try {
			// Declaracion e inicializacion de variables para el manejo del xml
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			// Obtener la lista de nodos tipo retorno
			NodeList nList = doc.getElementsByTagName("variablesRetornos");
			// Iterar la lista para agregar cada nodo al bloque
			for (int temp = 0; temp < nList.getLength(); temp++) {
				// Nodo actual
				Node nNode = nList.item(temp);
				// Verificar si el nodo es de tipo elemento	
				if (nNode.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) nNode;				
					
					//Obtener el nodo retorno que tenga la direccion proporcionada
					if(eElement.getElementsByTagName("direccion").item(0)!=null){
					if (eElement.getElementsByTagName("direccion").item(0)
							.getTextContent() == direccion) {
						//Obtener el tipo de dato
						tipo = Integer.parseInt(eElement
								.getElementsByTagName("tipo").item(0)
								.getTextContent());
					}
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return tipo;
	}
}		