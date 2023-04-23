/*Definicion de las operaciones que se pueden realizar*/

const MAXNOM = 20;

struct nodo_administrador{	
	char login[MAXNOM];	
	char contrasenia[MAXNOM];
	int identificacionAdm;
	char nombre[MAXNOM];	
	char apellido[MAXNOM];	
};

program gestion_administrador{
	version gestion_administrador_version_2{
		bool registrarAdministrador(nodo_administrador objUsuario)=1;
		bool enviarDatosSesionAdministrador(nodo_administrador objUsuario)=2;	
	}=2;
}=0x20000002;
