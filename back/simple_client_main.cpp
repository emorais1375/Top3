#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char *argv[] )
{
  try
  {

    ClientSocket client_socket ( "localhost", 30000 );

    std::string reply;

    try
	  {
	    client_socket << "Aqui será devolvido a combinação dos caminhos possíveis";
	    client_socket >> reply;
	  }
    catch ( SocketException& ) {}

    std::cout << "Recebemos essa resposta do servidor:\n\"" << reply << "\"\n";;

  }
  catch ( SocketException& e )
  {
    std::cout << "Exception was caught:" << e.description() << "\n";
  }

  return 0;
}