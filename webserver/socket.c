#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <signal.h>

void init_signals(void) {
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
  }
}

int create_server(int port) {
  int server_socket;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket == -1) {
    perror("server_socket");
    return -1;
  }

  int optval = 1;
  if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1){
     perror("Can not set SO_REUSEADDR option");
  }

  init_signals();

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
    perror("bind server_socket");
  }

  if (listen(server_socket, 10) == -1) {
    perror("lister server_socket");
  }

  const char *welcome_message = "Welcome on Apache 3 !!! Le serveur du futur !\n Il a �t� entierement realiser suite a des \netudes francaise que j'ai realise moi-meme car je sui \nfrancais, prenant en compte l'influence d'apache dans le \nmonde des devellopeurs de l'IUT de Lille A au seins de la \npromo Promo N4P2. Ce serveur est concus par les meilleurs \netudiants de la promotion, a savoir : Paul-Ivan Affolaby, \nexpert monetaire doue d'un esprit de chef d'equipe, Kevin \nMessien, technicien de pointe capable de realiser des chmod \nincongru (notemment pour se retirer ses propres droits de \nfacon recursif), son genie reste inegale, et enfin Florian \nMardon, futur ingenieur expert en lardon et en pate-raclette";

  while (1) {
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);


  write(client_socket, welcome_message, strlen(welcome_message));

    if(client_socket == -1) {
      perror("accept");
    }
    
    write(client_socket, welcome_message, strlen(welcome_message));
  }

  return server_socket;
}
