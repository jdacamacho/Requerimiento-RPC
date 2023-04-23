/*Definicion de las operaciones que se pueden realizar*/

const MAXNOM = 20;

struct nodo_cliente{	
	char login[MAXNOM];	
	char contrasenia[MAXNOM];
	int identificacionClnt;
	char nombre[MAXNOM];
	char apellido[MAXNOM];
		
};

program gestion_cliente{
	version gestion_cliente_version_1{
		bool registrarCliente(nodo_cliente objUsuario)=1;
		bool enviarDatosSesionCliente(nodo_cliente objUsuario)=2;	
	}=1;
}=0x20000001;
