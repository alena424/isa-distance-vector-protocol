#include "response.h"

#define PORT_RIP6 521

void send_response(response_args *arguments){
  // we need to create packet
  u_char *packet;
  // allocate space for packet
  size_t length = LENGTH_RIP_HEADER + LENGTH_RIP_ENTRY + LENGTH_RIP_ENTRY ;
  packet = (u_char *) malloc( length);

  // header
  rip_h header;
  header.command = RESPONSE;
  header.version = 1;
  header.zeros = 0;

  // we need to copy info to packet
  memcpy( packet, &header, LENGTH_RIP_HEADER );

  // rip_entry
  ripng_entry rip_entr;
  ripng_entry_next rip_entr_next;

  rip_entr.route_tag = arguments->route_tag ;
  rip_entr.prefixLength = arguments->prefix_int;
  rip_entr.metric = arguments->number_of_hops;

  rip_entr.prefix = arguments->addr;

  rip_entr_next.route_tag = 0;
  rip_entr_next.prefixLength =0;
  rip_entr_next.metric = 0xFF;
  rip_entr_next.next_hop = arguments->next_hop;

  memcpy(packet, &rip_entr, LENGTH_RIP_ENTRY);
  memcpy(packet, &rip_entr_next, LENGTH_RIP_ENTRY);

  // lets create socket, bind and send
  struct sockaddr_in6 my_addr, dest_addr;

  bzero(&my_addr, sizeof(my_addr));
  bzero(&dest_addr, sizeof(dest_addr));

  int my_socket = 0;
  if ( ( my_socket = socket(AF_INET6, SOCK_DGRAM, 0) ) < 0 ){
  	perror("socket failed\n");
  }

  int ifindex;
  ifindex =if_nametoindex( arguments->interface);
  printf("ifinedx %d\n", ifindex);
  my_addr.sin6_scope_id=ifindex;
  my_addr.sin6_family = AF_INET6;
  my_addr.sin6_port = htons(PORT_RIP6);

// random address from my interface
  /*char pom[] =  "fe80::a00:27ff:fe00:99";
  inet_ntop(AF_INET6, &my_addr.sin6_addr, pom, sizeof(pom) );*/
  my_addr.sin6_addr = in6addr_any;

  // socket options
  if ( setsockopt(my_socket, IPPROTO_IPV6, IPV6_MULTICAST_IF,&ifindex,sizeof(ifindex) ) < 0){
      perror("Setsockopt interface failed\n");
      return;
  }
  int hop = 255;
  if ( setsockopt(my_socket, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,&hop,sizeof(hop) ) < 0){
      perror("Setsockopthop  failed\n");
      return;
  }

  //if ( (bind(my_socket, (struct sockaddr*) &my_addr, sizeof( my_addr )) ) < 0){
  //  perror("ERROR: socket failed");
   // return;
  //}

  // destination address
  dest_addr.sin6_family = AF_INET6;
  dest_addr.sin6_port = htons(PORT_RIP6);
  dest_addr.sin6_scope_id = ifindex;

  char multicast_addr[] = "ff02::9";
  if ( ( inet_ntop(AF_INET6, &dest_addr.sin6_addr, multicast_addr, sizeof(multicast_addr) )) == 0 ){
    fprintf(stderr,  "inet top failed\n" );
  }
  //size_t *packet_size = LENGTH_RIP_ENTRY + LENGTH_RIP_HEADER;
  sendto(my_socket, packet, length, 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
  //fprintf( stderr, "size %d was send \n",size );

  close(my_socket);

}

/********************** end of response.c ***************************/
