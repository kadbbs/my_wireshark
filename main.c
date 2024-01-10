#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>

#define MAX_PACKET_SIZE 65535

void print_mac_frame_hex(const unsigned char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}


void print_ascii(char *buf,int size){
	printf("*********ASCII***********");
	for(int i=0;i<size;i++){
		
		printf("%c ",buf[i]);
		if((i%15)==0){
			printf("\n");	
		}
	}
	printf("\n**********************");
}


void parse_packet(const unsigned char* buffer, int size) {
	// 解析MAC帧
	struct ethhdr* eth = (struct ethhdr*)buffer;
	printf("MAC Frame:\n");
	print_mac_frame_hex(buffer, size);

	// 解析IP报文
	struct iphdr* ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	char source_ip[INET_ADDRSTRLEN];
	char dest_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(ip->saddr), source_ip, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(ip->daddr), dest_ip, INET_ADDRSTRLEN);
	printf("IP Header:\n");
	printf(" - Version: %d\n", ip->version);
	printf(" - Header Length: %d bytes\n", ip->ihl * 4);
	printf(" - Protocol: %d\n", ip->protocol);
	printf(" - Source IP: %s\n", source_ip);
	printf(" - Destination IP: %s\n", dest_ip);

	// 解析协议
	switch (ip->protocol) {
		case IPPROTO_UDP:{
					 // 解析UDP报文
					 struct udphdr* udp = (struct udphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
					 printf("UDP Header:\n");
					 printf(" - Source Port: %d\n", ntohs(udp->source));
					 printf(" - Destination Port: %d\n", ntohs(udp->dest));
					 printf(" - Length: %d bytes\n", ntohs(udp->len));
					 printf(" - Checksum: 0x%04X\n", ntohs(udp->check));
					 break;
				 }
		case IPPROTO_TCP:{
					 // 解析TCP报文
					 struct tcphdr* tcp = (struct tcphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
					 printf("TCP Header:\n");
					 printf(" - Source Port: %d\n", ntohs(tcp->source));
					 printf(" - Destination Port: %d\n", ntohs(tcp->dest));
					 printf(" - Sequence Number: %u\n", ntohl(tcp->seq));
					 printf(" - Acknowledgment Number: %u\n", ntohl(tcp->ack_seq));
					 printf(" - Data Offset: %d bytes\n", tcp->doff * 4);
					 printf(" - Flags: 0x%02X\n", tcp->syn);
					 printf(" - Window Size: %d\n", ntohs(tcp->window));
					 printf(" - Checksum: 0x%04X\n", ntohs(tcp->check));
					 break;
				 }
		case IPPROTO_ICMP:{
					  // 解析ICMP报文
					  struct icmphdr* icmp = (struct icmphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
					  printf("ICMP Header:\n");
					  printf(" - Type: %d\n", icmp->type);
					  printf(" - Code: %d\n", icmp->code);
					  printf(" - Checksum: 0x%04X\n", ntohs(icmp->checksum));


					  // 根据不同的ICMP类型打印额外的字段
					  switch (icmp->type) {
						  case ICMP_ECHO:
							  printf("ICMP Echo Header:\n");
							  printf("  Identifier: %u\n", ntohs(icmp->un.echo.id));
							  printf("  Sequence Number: %u\n", ntohs(icmp->un.echo.sequence));
							  printf("  Data: %s\n", icmp + 1); // 假设数据紧跟在ICMP头部后面
						  case ICMP_ECHOREPLY:
							  printf("  Identifier: %u\n", ntohs(icmp->un.echo.id));
							  printf("  Sequence Number: %u\n", ntohs(icmp->un.echo.sequence));
							  break;
						  case ICMP_REDIRECT:
							  printf("  Gateway: 0x%08x\n", ntohl(icmp->un.gateway));
							  break;
						  case ICMP_FRAG_NEEDED:
							  printf("  MTU: %u\n", ntohs(icmp->un.frag.mtu));
							  break;
						  default:
							  // 对于其他类型的ICMP报文，可以添加相应的打印逻辑
							  break;
					  }

					  //	if(icmp->type==ICMP_ECHO){
					  //		printf("sequence : ",icmp->echo.sequence);	

					  //	}

					  break;
				  }
		default:
				  printf("Unknown Protocol\n");
				  break;
	}
}

#if 0
void print_mac_frame_hex(const unsigned char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
#endif
int main(int argc,char **argv) {
	int sockfd;
	unsigned char buffer[MAX_PACKET_SIZE];

	char interface_name[16]="lo";
	//struct sockaddr_ll sll;
	struct ifreq if_lo;
	if(argc==1){}else if(argc==2){
		memset(interface_name,0,sizeof(interface_name));
		strncpy(interface_name,argv[1],strlen(argv[1]));	

	}else{
		printf("argement number is failed!!\n");
		exit(0);
	}
#if 1
	memset(&if_lo,0,sizeof(if_lo));
	strncpy((char *)if_lo.ifr_name,interface_name,IFNAMSIZ);
#endif
	//sll.sll_ifindex=73;			
	//socklen_t len=sizeof(sll);
	// 创建原始套接字
	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd < 0) {
		perror("Error creating socket");
		return 1;
	}

	// 绑定到lo接口
 	struct sockaddr_ll sa;
	memset(&sa, 0, sizeof(struct sockaddr_ll));
	sa.sll_family = AF_PACKET;
	sa.sll_protocol = htons(ETH_P_ALL);
	sa.sll_ifindex = if_nametoindex("lo");
	if (bind(sockfd, (struct sockaddr*)&sa, sizeof(struct sockaddr_ll)) == -1) {
		perror("Failed to bind raw socket to lo interface");
		close(sockfd);
		return -1;
	}
	#if 0
	if(setsockopt(sockfd,SOL_SOCKET,SO_BINDTODEVICE,(char*)&if_lo,sizeof(if_lo))<0){
		perror("setsockopt");
		exit(0);

	}
	int opt = 6; /*优先级 0 ~ 6 ：6 最高，优先处理*/
	int err = setsockopt(sockfd , SOL_SOCKET , SO_PRIORITY , &opt , sizeof(opt));/*设置s的优先级*/
	if(err){//失败
		printf("setsockopt SO_PRIORITY failure \n");
		exit(0);
	}
	#endif
	while (1) {
		memset(buffer,0,sizeof(buffer));
		// 接收数据包
		int packet_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
		if (packet_size < 0) {
			perror("Error receiving packet");
			return 1;
		}

		// 解析MAC帧
	//	struct ethhdr* eth = (struct ethhdr*)buffer;
	//	printf("MAC Frame:\n");
	//	print_mac_frame_hex(buffer, packet_size);
		print_ascii(buffer, packet_size);
		parse_packet(buffer, packet_size);
		// 解析其他协议，如IP、ICMP、UDP、TCP等
		// ...

		printf("\n");
		memset(buffer,0,sizeof(buffer));
	}

	close(sockfd);
	return 0;
}

#if 0

void printf_ip_frame_hex(){

// 解析IP报文
struct iphdr* ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
printf("IP Header:\n");
printf(" - Version: %d\n", ip->version);
printf(" - Header Length: %d bytes\n", ip->ihl * 4);
printf(" - Protocol: %d\n", ip->protocol);
printf(" - Source IP: %s\n", inet_ntoa(*(struct in_addr*)&ip->saddr));
printf(" - Destination IP: %s\n", inet_ntoa(*(struct in_addr*)&ip->daddr));

// 解析协议
switch (ip->protocol) {
    case IPPROTO_UDP:
        // 解析UDP报文
        struct udphdr* udp = (struct udphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
        printf("UDP Header:\n");
        printf(" - Source Port: %d\n", ntohs(udp->source));
        printf(" - Destination Port: %d\n", ntohs(udp->dest));
        printf(" - Length: %d bytes\n", ntohs(udp->len));
        printf(" - Checksum: 0x%04X\n", ntohs(udp->check));
        break;
    case IPPROTO_TCP:
        // 解析TCP报文
        struct tcphdr* tcp = (struct tcphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
        printf("TCP Header:\n");
        printf(" - Source Port: %d\n", ntohs(tcp->source));
        printf(" - Destination Port: %d\n", ntohs(tcp->dest));
        printf(" - Sequence Number: %u\n", ntohl(tcp->seq));
        printf(" - Acknowledgment Number: %u\n", ntohl(tcp->ack_seq));
        printf(" - Data Offset: %d bytes\n", tcp->doff * 4);
        printf(" - Flags: 0x%02X\n", tcp->syn);
        printf(" - Window Size: %d\n", ntohs(tcp->window));
        printf(" - Checksum: 0x%04X\n", ntohs(tcp->check));
        break;
    case IPPROTO_ICMP:
        // 解析ICMP报文
        struct icmphdr* icmp = (struct icmphdr*)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);
        printf("ICMP Header:\n");
        printf(" - Type: %d\n", icmp->type);
        printf(" - Code: %d\n", icmp->code);
        printf(" - Checksum: 0x%04X\n", ntohs(icmp->checksum));
        break;
    default:
        printf("Unknown Protocol\n");
        break;
}


}

#endif

