/**
 * Clase xmlParser
 * 
 * Modulo para leer el archivo xml con los datos de objetos, variables y constantes
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
import java.util.ArrayList;
import java.util.*;
 
public class xmlParser {
 
	/**
	 * Metodo para cargar los datos de los objetos del archivo xml
	 * @param objetos
	 * @return La lista de objetos con sus datos
	 */
	public HashMap<String, objetos> cargarObjetos(HashMap<String,objetos> objetos, String llave, String objeto) {

		try {
			// Declaracion e inicializacion de estructuras y objetos
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			Node auxiliar;
			NodeList auxiliarLista;
			// Temporales para objeto
			objetos objetoTemporal = new objetos();
			bloque bloque = new bloque();

			doc.getDocumentElement().normalize();
			// Obtener el nodo principal
			NodeList principal = doc.getElementsByTagName(objeto);
			auxiliar = principal.item(0);
			//auxiliarLista = auxiliar.getChildNodes();

			// Iterar la lista para agregar cada objeto
			//for (int temp = 0; temp < auxiliarLista.getLength(); temp++) {
				// Nodo actual
				//auxiliar = auxiliarLista.item(temp);
				if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) auxiliar;
					if (!eElement.getNodeName().equals("constantes") && !eElement.getNodeName().equals("variablesRetornos")) {

						// Guardar el nombre
						objetoTemporal.setNombre(eElement.getNodeName());

						// Guardar globales
						NodeList auxiliarLista2 = eElement
								.getElementsByTagName("variablesGlobales");
						// System.out.println("auxLs"+auxiliarLista.getLength());
						auxiliar = auxiliarLista2.item(0);
						if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
							// Objeto elemento con los subnodos
							Element eElement2 = (Element) auxiliar;
							NodeList auxiliarLista3 = eElement2
									.getElementsByTagName("variableGlobal");
							// System.out.println("auxLs"+auxiliarLista.getLength());
							bloque.inicializarBase(1000);
							// Iterar la lista para agregar cada objeto
							for (int temp2 = 0; temp2 < auxiliarLista3
									.getLength(); temp2++) {
								auxiliar = auxiliarLista3.item(temp2);
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
									
									//Guardar datos en memoria
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
							objetoTemporal.setGlobales(bloque);
							bloque = new bloque();								
						}
						// Agregar a workspace
						objetos.put(llave,objetoTemporal);
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
	 * 
	 * @param objeto
	 * @param nombre
	 * @param funcion
	 * @return La funcion con los datos
	 */
	public funcion cargarFunciones(objetos objeto, String nombre,
			funcion funcion, String nombreObjeto) {

		try {
			// Declaracion e inicializacion de estructuras y objetos
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			Node auxiliar;
			NodeList auxiliarLista;
			bloque bloque = new bloque();

			doc.getDocumentElement().normalize();
			// Obtener el nodo principal
			//NodeList principal = doc.getElementsByTagName("GALaDos");
			auxiliarLista = doc.getElementsByTagName("main");
						
			//auxiliar = principal.item(0);
			//auxiliarLista = auxiliar.getChildNodes();			
			// Iterar la lista para agregar cada procedimiento
			for (int temp = 0; temp < auxiliarLista.getLength(); temp++) {
				// Nodo actual
				auxiliar = auxiliarLista.item(temp);
				if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) auxiliar;
					if (!eElement.getNodeName().equals("constantes") && !eElement.getNodeName().equals("variablesRetornos")) {
						// Guardar funciones

						NodeList auxiliarLista3 = eElement
								.getElementsByTagName("procedimientos");
						// System.out.println("auxLs"+auxiliarLista.getLength());
						auxiliar = auxiliarLista3.item(0);

						if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
							// Objeto elemento con los subnodos
							Element eElement2 = (Element) auxiliar;

							NodeList auxiliarLista4 = eElement2.getChildNodes();
							// Iterar la lista para agregar cada funcion
							for (int temp2 = 0; temp2 < auxiliarLista4
									.getLength(); temp2++) {
								auxiliar = auxiliarLista4.item(temp2);
								if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
									// Obtener los datos de procedimientos
									Element eElement3 = (Element) auxiliar;
									if (eElement3.getNodeName().equals(nombre)) {
										funcion.setNombre(eElement3
												.getNodeName());

										funcion.setRegresa(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"regresa")
														.item(0)
														.getTextContent()));
										funcion.setPermiso(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"permiso")
														.item(0)
														.getTextContent()));

										funcion.setDireccionCuadruplo(Integer
												.parseInt(eElement3
														.getElementsByTagName(
																"direccionCuadruplo")
														.item(0)
														.getTextContent()));

										// Guardar locales
										bloque.inicializarBase(5000);
										NodeList auxiliarLista5 = eElement3
												.getElementsByTagName("variablesLocales");
										auxiliar = auxiliarLista5.item(0);
										if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
											// Objeto elemento con los subnodos
											Element eElement4 = (Element) auxiliar;

											NodeList auxiliarLista6 = eElement4
													.getChildNodes();
											// System.out.println("auxLs"+auxiliarLista.getLength());
											// Iterar la lista para agregar cada
											// variable
											for (int temp3 = 0; temp3 < auxiliarLista6
													.getLength(); temp3++) {
												auxiliar = auxiliarLista6
														.item(temp3);
												if (auxiliar.getNodeType() == Node.ELEMENT_NODE) {
													// Obtener los datos de
													// variables locales
													Element eElement5 = (Element) auxiliar;

													int tipo = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"tipo")
																	.item(0)
																	.getTextContent());
													if(tipo != 4){
													int direccion = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"direccion")
																	.item(0)
																	.getTextContent());
													
													//Si es un arreglo o matriz generar su espacio correspondiente
													if(eElement5.getElementsByTagName("dimensionada").item(0) != null){
																																						
													int tamanio = Integer
															.parseInt(eElement5
																	.getElementsByTagName(
																			"tamanio")
																	.item(0)
																	.getTextContent());
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
													//Guardar en memoria
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
											funcion.setLocales(bloque);
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
	 * @param bloque
	 * @return bloque El bloque con las constantes cargadas
	 */
	public bloque cargarConstantes(bloque bloque) {

		try {

			// Declaracion e inicializacion de estructuras y objetos
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
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
				// Si el nodo tiene elementos internos
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
	 * Metodo que carga los retornos del archivo xml
	 * 
	 * @param bloque
	 * @return bloque El bloque con los retornos cargados
	 */
	public bloque cargarRetornos(bloque bloque) {

		try {

			// Declaracion e inicializacion de estructuras y objetos
			File fXmlFile = new File("obj/datos.txt");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);	
			int direccion;
			int tipo;
			doc.getDocumentElement().normalize();			

			/**
			 * Seccion para cargar tabla de retornos a memoria
			 */

			// Obtener la lista de nodos tipo retorno
			NodeList nList = doc.getElementsByTagName("variablesRetornos");

			// Iterar la lista para agregar cada nodo al bloque
			for (int temp = 0; temp < nList.getLength(); temp++) {
				// Nodo actual
				Node nNode = nList.item(temp);
				// Si el nodo tiene elementos internos
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
						switch (tipo) {
						case 0:
							bloque.ingresaElementoEntero(direccion, -1);
							break;
						case 1:
							bloque.ingresaElementoDecimal(direccion, -1);
							break;
						case 2:
							bloque.ingresaElementoTexto(direccion, "");
							break;
						case 3:
							bloque.ingresaElementoBooleano(direccion, false);
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
   * Metodo para obtener el tipo de un registro retorno obtenido por el xml
   * 
   * @param objeto
   * @param direccion
   * @return int tipo
   */
	public int tipoRetorno(String objeto, String direccion) {
		int tipo = 0;
		try {
			// Declaracion e inicializacion de estructuras y objetos
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
				// Si el nodo tiene elementos internos
				if (nNode.getNodeType() == Node.ELEMENT_NODE) {
					// Objeto elemento con los subnodos
					Element eElement = (Element) nNode;				
					// Cargar variables locales
					if (eElement.getElementsByTagName("direccion").item(0)
							.getTextContent() == direccion) {
						return Integer.parseInt(eElement
								.getElementsByTagName("tipo").item(0)
								.getTextContent());
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return tipo;
	}
}		