/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface2.h"
#include "interface3.h"
#include <string.h>

void menuLogin(){
	printf("\n === bienvenido ===");
	printf("\n 1. Registrarse");
	printf("\n 2. Iniciar sesion");
	printf("\n 3. salir");
}

void menu(){
	printf("\n === bienvenido ===");
	printf("\n 1. Registrar producto");
	printf("\n 2. Listar productos");
	printf("\n 3. Abrir subasta");
	printf("\n 4. Cerrar subasta");
	printf("\n 5. salir");
}

void mostrarVector(listaProductos *produc){
	for(int i=0 ; i<5 ;i++){
		if(produc->productos[i].codigoProducto == 0){
			break;
		}
		else{
			printf("\n Producto:");
			printf("\n codigo: %d",produc->productos[i].codigoProducto);
			printf("\n nombre: %s",produc->productos[i].nombre);
			printf("\n valor: %f",produc->productos[i].valorProducto);
		}
	}
}
void
gestion_administrador_2(char *host)
{
	CLIENT *clnt1;
	bool_t  *result_1;
	nodo_administrador  objAdministrador;
	CLIENT *clnt2;
	bool_t  *result_2;
	bool_t  *result_3;
	bool_t  *result_4;
	nodo_producto objProducto;
	listaProductos *misProductos ;
	oferta *ofertaGanadora;
	nodo_cliente_oferta clienteGanador;
	nodo_producto productoVendido;

#ifndef	DEBUG
	clnt1 = clnt_create (host, gestion_administrador, gestion_administrador_version_2, "udp");
	if (clnt1 == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	clnt2 = clnt_create (host, gestion_productos, gestion_productos_version_3, "tcp");
	if (clnt2 == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	
	
	int ingresar=0;
	do{
		menuLogin();
		printf("\n Digite una opcion:");
		scanf("%d",&ingresar);
		switch (ingresar)
		{
			case 1:

				printf("\n Ingrese su identificacion:");
				scanf("%d",&objAdministrador.identificacionAdm);
				printf("\n Ingrese el nombre:");
				scanf("%s",objAdministrador.nombre);
				printf("\n Ingrese el apellido:");
				scanf("%s",objAdministrador.apellido);
				printf("\n Ingrese el login:");
				scanf("%s",objAdministrador.login);
				printf("\n Ingrese la contrasenia:");
				scanf("%s",objAdministrador.contrasenia);

				result_1 = registraradministrador_2(&objAdministrador, clnt1);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt1, "call failed");
				}
				if(*result_1==TRUE){
					printf("\n Registro exitoso!");
				}
				else{
					printf("\n ERROR, el administrador ya existe...");
				}
			break;
			case 2:

				printf("\n Ingrese el login:");
				scanf("%s",objAdministrador.login);
				printf("\n Ingrese la contrasenia:");
				scanf("%s",objAdministrador.contrasenia);

				result_2 = enviardatossesionadministrador_2(&objAdministrador, clnt1);
				if (result_2 == (bool_t *) NULL) {
					clnt_perror (clnt1, "call failed");
				}

				if(*result_2==TRUE){
					printf("\n Bienvenido al sistema!");
					int opcion;
					int codigoProducto;
					do{
						menu();
						printf("\n Digite una opcion:");
						scanf("%d",&opcion);

						switch (opcion)
						{
							case 1:
								printf("\n Ingrese el codigo:");
								scanf("%d",&objProducto.codigoProducto);
								printf("\n Ingrese el nombre:");
								scanf("%s",objProducto.nombre);
								printf("\n Ingrese el valor:");
								scanf("%f",&objProducto.valorProducto);
								
								printf("\n %d",objProducto.codigoProducto);
								printf("\n %s",objProducto.nombre);
								printf("\n %f",objProducto.valorProducto);
								result_3 = admregistrarproductoofertar_3(&objProducto,clnt2);
						
								if (result_3 == (bool_t *) NULL) {
									clnt_perror (clnt1, "call failed");
								}
								
								if(*result_3 == TRUE){
									printf("\n Se registro el producto con exito!");
								}
								else{
									printf("\n ERROR, el producto ingresado ya se encuentra registrado...");
								}
							break;
							case 2:
								misProductos =  admlistarproductosofertar_3(NULL,clnt2);
								if(misProductos->productos[0].codigoProducto == 0){
									printf("\n ERROR, NO existen productos");
								}
								else{
									printf("\n Productos:");
									mostrarVector(misProductos);
								}
							break;
							case 3:
								printf("\n Ingrese el codigo del producto:");
								scanf("%d",&codigoProducto);
								result_4 = abrirsubasta_3(&codigoProducto,clnt2);
								if(*result_4 == TRUE){
									printf("\n Producto subastado con exito!");
								}
								else{
									printf("\n ERROR, no existe el producto o ya hay un producto en subasta...");
								}
							break;
							case 4:
								ofertaGanadora = cerrarsubasta_3(NULL,clnt2);
								if(ofertaGanadora->valorPuja != 0.0){
									clienteGanador = ofertaGanadora->objCliente;
									productoVendido = ofertaGanadora->objProducto;
									printf("\n EL ganador:");
									printf("\n Datos del cliente:");
									printf("\n codigo: %d",clienteGanador.identificacionClnt);
									printf("\n nombre: %s",clienteGanador.nombre);
									printf("\n apellido: %s",clienteGanador.apellido);
									printf("\n Datos del producto:");
									printf("\n codigo: %d",productoVendido.codigoProducto);
									printf("\n nombre: %s",productoVendido.nombre);
									printf("\n valor: %f",productoVendido.valorProducto);
									
								}
								else{
									printf("\n Nadie realizo una puja por el producto...");
								}
							break;
							case 5:
								printf("\n Saliendo...");
							break;
							default:
								printf("\n ERROR, digite una opcion valida...");
							break;
						}

					}while(opcion !=5);
					
				}
				else{
					printf("\n ERROR, login o contrasenia incorrecta.");
				}
			break;
			case 3:
				printf("\n Saliendo...");
			break;
			default:
				printf("\n Error, digite una opcion valida!");
			break;
		}
		if(ingresar<1 && ingresar>3){
			printf("\n ERROR, digite una opcion valida!!");
		}
		
	}while(ingresar !=3);
#ifndef	DEBUG
	clnt_destroy (clnt1);
	clnt_destroy (clnt2);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	gestion_administrador_2 (host);
exit (0);
}