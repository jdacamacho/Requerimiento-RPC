/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface1.h"
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
	printf("\n 1. Listar productos");
	printf("\n 2. Consultar producto");
	printf("\n 3. Consultar subasta actual");
	printf("\n 4. Realizar puja");
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
			printf("\n nombre: %f",produc->productos[i].valorProducto);
		}
	}
}
void
gestion_cliente_1(char *host)
{
	CLIENT *clnt1;
	bool_t  *result_1;
	nodo_cliente  objCliente;
	CLIENT *clnt2;
	bool_t  *result_2;
	bool_t  *result_3;
	listaProductos *misProductos ;
	nodo_producto *productoConsultado;
	nodo_producto *actualSubasta;
	char *nombreProductoConsultar;
	oferta *miOferta;
	nodo_cliente_oferta infoCliente;
	float puja;

#ifndef	DEBUG
	clnt1 = clnt_create (host, gestion_cliente, gestion_cliente_version_1, "udp");
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
				scanf("%d",&objCliente.identificacionClnt);
				printf("\n Ingrese el nombre:");
				scanf("%s",objCliente.nombre);
				printf("\n Ingrese el apellido:");
				scanf("%s",objCliente.apellido);
				printf("\n Ingrese el login:");
				scanf("%s",objCliente.login);
				printf("\n Ingrese la contrasenia:");
				scanf("%s",objCliente.contrasenia);

				result_1 =  registrarcliente_1(&objCliente, clnt1);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt1, "call failed");
				}
				if(*result_1==TRUE){
					printf("\n Registro exitoso!");
				}
				else{
					printf("\n ERROR, el cliente ya se encuentra registrado...");
				}
			break;
			case 2:
				printf("\n Ingrese el login:");
				scanf("%s",objCliente.login);
				printf("\n Ingrese la contrasenia:");
				scanf("%s",objCliente.contrasenia);

				result_2 =  enviardatossesioncliente_1(&objCliente, clnt1);
				if (result_1 == (bool_t *) NULL) {
					clnt_perror (clnt1, "call failed");
				}

				if(*result_2==TRUE){
					printf("\n Bienvenido al sistema!");
					int opcion;
					do{
						menu();
						printf("\n Digite una opcion:");
						scanf("%d",&opcion);
						switch (opcion)
						{
							case 1:
								misProductos =  admlistarproductosofertar_3(NULL,clnt2);
								if(misProductos->productos[0].codigoProducto == 0){
									printf("\n ERROR, NO existen productos");
								}
								else{
									printf("\n Productos:");
									mostrarVector(misProductos);
								}
							break;
							case 2:
								nombreProductoConsultar = (char*) malloc(20*sizeof(char));
								printf("\n Ingrese el nombre del producto:");
								scanf("%s",nombreProductoConsultar);
								productoConsultado=consultarproducto_3(&nombreProductoConsultar,clnt2);
								if(productoConsultado->codigoProducto!=0){
									printf("\n Producto:");
									printf("\n codigo: %d",productoConsultado->codigoProducto);
									printf("\n nombre: %s",productoConsultado->nombre);
									printf("\n nombre: %f",productoConsultado->valorProducto);
								}
								else{
									printf("\n NO existe el producto buscado...");
								}
							break;
							case 3:
								actualSubasta= consultardatosproductoactualsubastando_3(NULL,clnt2);
								if(actualSubasta->codigoProducto == -1){
									printf("\n NO hay productos en subasta");
								}
								else{
									printf("\n Producto en subasta:");
									printf("\n codigo: %d",actualSubasta->codigoProducto);
									printf("\n nombre:%s",actualSubasta->nombre);
									printf("\n valor: %f",actualSubasta->valorProducto);
								}
							break;
							case 4:
								printf("\n Digite el valor de su puja:");
								scanf("%f",&puja);
								infoCliente.identificacionClnt = objCliente.identificacionClnt;
								strcpy(infoCliente.nombre,objCliente.nombre);
								strcpy(infoCliente.apellido,objCliente.apellido);
								miOferta->objCliente = infoCliente;
								miOferta->valorPuja=puja;
								result_3=clntofreceroferta_3(miOferta,clnt2);
								if(*result_3 == TRUE){
									printf("\n Se realizo la puja con exito!");
								}
								else{
									printf("\n No se pudo realizar la puja...");
								}
							break;
							default:
								printf("\n Error,digite una opcion valida...");
							break;
						}
					}while(opcion!=5);
				}
				else{
					printf("\n ERROR, login o contrasenia incorrecta.");
				}
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
	gestion_cliente_1 (host);
exit (0);
}