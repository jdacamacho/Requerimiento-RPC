/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface3.h"
#include <string.h>
listaProductos misProductos;
int posVacia=0;
int bandera=0;
nodo_producto productoSubastado;
oferta ofertaMayor;

int existeProducto(nodo_producto producto){
	for(int i=0 ; i<posVacia; i++){
		if(misProductos.productos[i].codigoProducto == producto.codigoProducto){
			return 1;
		}
	}
	return 0;
}
nodo_producto buscar(int id){
	nodo_producto result;
	for(int i=0 ; i<5 ;i++){
		if(misProductos.productos[i].codigoProducto == id){
			return misProductos.productos[i];
		}
	}
	result.codigoProducto=-1;
	strcpy(result.nombre, "vacio");
	result.valorProducto=-1.0;
	return result;
}

bool_t *
admregistrarproductoofertar_3_svc(nodo_producto *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	printf("\n Invocando registrar producto");
	printf("\n Codigo del producto %d" ,argp->codigoProducto);
	if(posVacia<5){
		if(existeProducto(*argp)==0){
			misProductos.productos[posVacia]=*argp;
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n Producto agregado!");
			printf("\n **************************");
			result=TRUE;
			posVacia++;
		}
		else{
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n ERROR, el producto ya se encuentra registrado...");
			printf("\n **************************");
			result=FALSE;
		}
		
	}
	else{
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n No se pudo registrar el producto.");
		printf("\n ************************************");
		return FALSE;
	}
	return &result;
}

listaProductos *
admlistarproductosofertar_3_svc(void *argp, struct svc_req *rqstp)
{
	static listaProductos  result;
	printf("\n RESPUESTA DEL SERVIDOR:");
	printf("\n Llamando a listar productos...");
	printf("\n ************************************");
	result=misProductos;
	return &result;
}

bool_t *
abrirsubasta_3_svc(int *argp, struct svc_req *rqstp)
{
	static bool_t  result;
	nodo_producto productoEncontrador = buscar(*argp);
	if(bandera == 0){
		if(productoEncontrador.codigoProducto != -1){
			bandera=1;
			productoSubastado=productoEncontrador;
			ofertaMayor.objProducto = productoSubastado;
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n Producto subastado con exito");
			printf("\n codigo: %d",productoSubastado.codigoProducto);
			printf("\n nombre: %s",productoSubastado.nombre);
			printf("\n valor: %f",productoSubastado.valorProducto);
			printf("\n ************************************");
			result=TRUE;
		}
		else{
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n NO existe el producto a subastar...");
			printf("\n ************************************");
			result=FALSE;
		}
	}
	else{
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n ERROR , ya existe un producto en subasta...");
		printf("\n ************************************");	
		result=FALSE;
	}
	
	return &result;
}

oferta *
cerrarsubasta_3_svc(void *argp, struct svc_req *rqstp)
{
	static oferta  result;

	if(bandera == 0){
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n ERROR , no existe una subasta...");
		printf("\n ************************************");	
	}
	else{
		bandera=0;
		if(ofertaMayor.valorPuja == 0.0){
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n No hubo ganador, nadie realizo una puja...");
			printf("\n ************************************");	
		}
		else{
			result = ofertaMayor;
		}
	}
	return &result;
}

listaProductos *
clntlistarproductos_3_svc(void *argp, struct svc_req *rqstp)
{
	static listaProductos  result;
	printf("\n RESPUESTA DEL SERVIDOR:");
	printf("\n Llamando a listar productos...");
	printf("\n ************************************");
	result=misProductos;
	return &result;
}


nodo_producto *
consultarproducto_3_svc(char **argp, struct svc_req *rqstp)
{
	static nodo_producto  result;
	
	printf("\n Invocando a consultarProducto producto");
	for(int i = 0 ; i<posVacia ; i++){
		if(strcmp(misProductos.productos[i].nombre,*argp) == 0){
			result=misProductos.productos[i];
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n Producto encontrado!");
			printf("\n **********************");
			return &result;
		}
	}
	printf("\n RESPUESTA DEL SERVIDOR:");
	printf("\n Producto no encontrado.");
	printf("\n ***********************");
	return &result;
}

nodo_producto *
consultardatosproductoactualsubastando_3_svc(void *argp, struct svc_req *rqstp)
{
	static nodo_producto  result;

	if(bandera == 1){
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n Mostrando en pantalla producto en subasta...");
		printf("\n ***********************");
		return &productoSubastado;
	}
	else{
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n NO se esta subastando actualmente un producto...");
		printf("\n ***********************");
	}
	result.codigoProducto=-1;
	strcpy(result.nombre, "vacio");
	result.valorProducto=-1.0;

	return &result;
}

bool_t *
clntofreceroferta_3_svc(oferta *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	if(bandera==1){
		if(ofertaMayor.valorPuja == 0.0){
			if(argp->valorPuja > ofertaMayor.objProducto.valorProducto){
				ofertaMayor = *argp;
				ofertaMayor.objProducto=productoSubastado;
				printf("\n RESPUESTA DEL SERVIDOR:");
				printf("\n Subasta actual:");
				printf("\n codigo: %d",ofertaMayor.objProducto.codigoProducto);
				printf("\n nombre: %s",ofertaMayor.objProducto.nombre);
				printf("\n valor: %f",ofertaMayor.objProducto.valorProducto);
				printf("\n Cliente que oferto:");
				printf("\n codigo: %d",ofertaMayor.objCliente.identificacionClnt);
				printf("\n nombre: %s",ofertaMayor.objCliente.nombre);
				printf("\n apellido: %s",ofertaMayor.objCliente.apellido);
				printf("\n valor: %f",ofertaMayor.valorPuja);
				printf("\n ***********************");
				result=TRUE;
			}
			else{
				printf("\n RESPUESTA DEL SERVIDOR:");
				printf("\n Subasta actual:");
				printf("\n codigo: %d",ofertaMayor.objProducto.codigoProducto);
				printf("\n nombre: %s",ofertaMayor.objProducto.nombre);
				printf("\n valor: %f",ofertaMayor.objProducto.valorProducto);
				printf("\n Cliente que oferto:");
				printf("\n codigo: %d",ofertaMayor.objCliente.identificacionClnt);
				printf("\n nombre: %s",ofertaMayor.objCliente.nombre);
				printf("\n apellido: %s",ofertaMayor.objCliente.apellido);
				printf("\n valor: %f",ofertaMayor.valorPuja);
				printf("\n ***********************");
				result=FALSE;
			}
		}
		else if(argp->valorPuja > ofertaMayor.valorPuja ){
			ofertaMayor = *argp;
			ofertaMayor.objProducto=productoSubastado;
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n Subasta actual:");
			printf("\n codigo: %d",ofertaMayor.objProducto.codigoProducto);
			printf("\n nombre: %s",ofertaMayor.objProducto.nombre);
			printf("\n valor: %f",ofertaMayor.objProducto.valorProducto);
			printf("\n Cliente que oferto:");
			printf("\n codigo: %d",ofertaMayor.objCliente.identificacionClnt);
			printf("\n nombre: %s",ofertaMayor.objCliente.nombre);
			printf("\n apellido: %s",ofertaMayor.objCliente.apellido);
			printf("\n valor: %f",ofertaMayor.valorPuja);
			printf("\n ***********************");
			result=TRUE;
		}
		else{
			printf("\n RESPUESTA DEL SERVIDOR:");
			printf("\n Subasta actual:");
			printf("\n codigo: %d",ofertaMayor.objProducto.codigoProducto);
			printf("\n nombre: %s",ofertaMayor.objProducto.nombre);
			printf("\n valor: %f",ofertaMayor.objProducto.valorProducto);
			printf("\n Cliente que oferto:");
			printf("\n codigo: %d",ofertaMayor.objCliente.identificacionClnt);
			printf("\n nombre: %s",ofertaMayor.objCliente.nombre);
			printf("\n apellido: %s",ofertaMayor.objCliente.apellido);
			printf("\n valor: %f",ofertaMayor.valorPuja);
			printf("\n ***********************");
			result=FALSE;
		}
	}
	else{
		printf("\n RESPUESTA DEL SERVIDOR:");
		printf("\n NO se esta subastando actualmente un producto...");
		printf("\n ***********************");
		result = FALSE;
	}
	return &result;
}