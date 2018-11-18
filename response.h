/**
* response.h
* @brief contains response structures
* @author Alena Tesarova, xtesar36@stud.fit.vutbr.cz
* @date 20.11.2018
* project ISA 2018
*/

#include "headers.h"
#include <net/if.h> // if_nametoindex

//-- RIP RESPONSE ---//

#define SIZE 20 // interface size

typedef struct response_args{
  char interface[SIZE]; //-i
  struct in6_addr addr; //-r
  struct in6_addr next_hop; //-n
  int prefix_int;
  int route_tag; //-t
  int number_of_hops;

} response_args;


void send_response(response_args *arguments);
