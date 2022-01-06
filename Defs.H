#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD,		
	DSN,
	EXIT
};

enum  MODE	//Modes of operation
{
	DESIGN,
	
};

//Maximum number of connections that can be connected to any output components
#define MAX_CONNS 20




#endif