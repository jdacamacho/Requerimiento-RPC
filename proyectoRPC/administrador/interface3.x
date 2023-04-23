/*Declaracion de datos a transferir entre el cliente y el servidor*/

/*Declaracion de constantes*/
const MAXNOM = 20;

/*Declaracion de la estructura que permite almacenar los datos de un producto*/
struct nodo_producto{
	int codigoProducto;
	char nombre[MAXNOM];	
	float valorProducto;			
};

struct nodo_cliente_oferta{	
	int identificacionClnt;
	char nombre[MAXNOM];	
	char apellido[MAXNOM];
};

struct oferta{
	nodo_producto objProducto;
	nodo_cliente_oferta objCliente;
	float valorPuja;
};

struct listaProductos{
	nodo_producto productos[5];
};

/*Definicion de las operaciones que se pueden realizar*/
program gestion_productos{
	version gestion_productos_version_3{
		bool admRegistrarProductoOfertar(nodo_producto objProducto)=1;
		listaProductos admListarProductosOfertar()=2;
		bool abrirSubasta(int codigoProducto)=3;
		oferta cerrarSubasta()=4;
		listaProductos clntListarProductos()=5;
		nodo_producto consultarProducto(string nombre)=6;
		nodo_producto consultarDatosProductoActualSubastando()=7;
		bool clntOfrecerOferta(oferta clntOferta)=8;
	}=3;
}=0x20000003;
