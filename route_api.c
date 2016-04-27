/*Note:
Just a model. So put all codes into one file. 
*/

/****************************************h of router driver*****************************************************************/
#define ROUTER_ARP_INVALID -1
#define ROUTER_MAX_PORT_NUM 24
#define ROUTER_MAX_ARP_INDEX 16*1024

#define IS_NULL_CHECK(var) (var == NULL) 
#define ROUTER_CPU_PORT 0

typedef enum router_error_e {
    ROUTER_E_NONE,        
    ROUTER_E_INTERNAL,
    ROUTER_E_MEMORY,    
    ROUTER_E_UNIT,      
    ROUTER_E_PARAM,
    ROUTER_E_EMPTY,
    ROUTER_E_FULL,
    ROUTER_E_NOT_FOUND,
    ROUTER_E_EXISTS, 
    ROUTER_E_TIMEOUT,
    ROUTER_E_BUSY,
    ROUTER_E_FAIL,
    ROUTER_E_DISABLED,
    ROUTER_E_BADID,
    ROUTER_E_RESOURCE,
    ROUTER_E_CONFIG, 
    ROUTER_E_UNAVAIL,
    ROUTER_E_INIT              
} router_error_t;

typedef struct router_dest_info_s 
{
    int vrf;
	int vlan; 	/*reserve*/
    int route_dip_addr; /*destination IP*/
	int route_dip_mask;
}router_dest_info_t;
	
typedef struct router_next_hop_info_s 
{
    int route_next_hop_ip;
	int vrf;
    int vlan;
}router_next_hop_info_t;

typedef uint8 router_mac_t[6];

typedef struct router_port_s
{
	int vlan;
	int ingress_interface;
	int ip;
	int vrf;
	router_mac_t my_mac;
}router_port_t;

/****************************************Global var of router driver*****************************************************************/
int g_default_arp_index;
router_port_t g_router_port[ROUTER_MAX_PORT_NUM];
int g_router_arp_counter[ROUTER_MAX_ARP_INDEX] = 0;


/****************************************API of router driver*****************************************************************/

/*add router, 
router_dest_info:  dest note ip info
router_next_hop_info: next hop info from which dest note can be reached.
*/
int router_route_add(router_dest_info_t router_dest_info, router_dest_info_t router_next_hop_info)
{
	int rv;
	int arp_index;

	/*Get the APR index by next hop IP. According to ARP, get DMAC, then dest port(according to DMAC), then srcmac&vlan(in router, a vlan and ing_l3_intf per port) */
	rv = router_bcm_arp_get(router_next_hop_info, &arp_index);
	if(arp_index == ROUTER_E_NONE)
	{
		/*ARP is not found, a default ARP(drop or tocpu) is used*/
		arp_index = g_default_arp_index;
	}
	
	/*If the ARP index is found, add the route entry*/
	rv = router_bcm_route_add(router_dest_info,arp_index);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_route_add failed! rv=%d\n", rv);
		return rv;
	}
	
	return ROUTER_E_NONE;
}

/*delete route entry*/
int router_route_delete(router_dest_info_t router_dest_info, router_dest_info_t router_next_hop_info)
{
	int rv;

	rv = router_bcm_route_delete(router_dest_info_t router_dest_info);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_route_delete failed! rv = %d\n",rv);
		return rv;
	}

	return ROUTER_E_NONE;
}


/*add ARP
router_next_hop_info: next hop info
arp_mac: next hop dest mac.
*/
int router_arp_add(router_dest_info_t router_next_hop_info, router_mac_t arp_mac)
{
	int rv;
	int arp_index;

	rv = router_bcm_arp_get(router_next_hop_info, &arp_index);
	if(arp_index == ROUTER_ARP_INVALID)
	{
		/*ARP is not found, add a new arp index*/
		rv = router_bcm_arp_create(arp_mac, &arp_index);

		/*add l3 host entry*/
		rv = router_bcm_host_add(router_next_hop_info, arp_index);
		if(rv != ROUTER_E_NONE)
		{
			printf("router_bcm_host_add failed, rv = %d\n", rv);
			return rv;
		}
		g_router_arp_counter[arp_index]++;
	}
	else
	{
		/*override the old arp*/
		rv = router_arp_update();
	}
	
	
}

/*delete arp*/
int router_arp_delete(router_dest_info_t router_next_hop_info, router_mac_t arp_mac)
{
	int rv;
	int arp_index;

	/*get arp index*/
	rv = router_bcm_arp_get(router_next_hop_info, &arp_index);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_host_get failed! rv = %d\n", rv);
		return rv;
	}

	/*delete l3 host entry(arp table)*/
	rv = router_bcm_host_delete(router_next_hop_info);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_host_delete failed! rv = %d\n", rv);
		return rv;
	}

	/*decrease the arp index used counter */
	g_router_arp_counter[arp_index]--;

	/*when the arp is not used, destroy it!*/
	if(g_router_arp_counter[arp_index] == 0)
	{
		rv = router_bcm_arp_destroy(arp_index);
		
	}

	return ROUTER_E_NONE;
}

int router_arp_update(router_dest_info_t router_next_hop_info, router_mac_t arp_mac)
{
	int rv;
	int new_arp_index, old_arp_index;

	/*get the old arp*/
	rv = router_bcm_arp_get(router_next_hop_info, &old_arp_index);

	/*if the old arp is not used, delete it*/	
	if(!(g_router_arp_counter[old_arp_index]--))
	{
		rv = router_bcm_arp_destroy(old_arp_index);
		if(rv != ROUTER_E_NONE)
		{
			printf("router_bcm_arp_destroy failed! rv = %d\n", rv);
			return rv;
		}
	}

	/*create a new arp*/
	rv = router_bcm_arp_create(arp_mac, &new_arp_index);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_arp_create failed! rv = %d\n", rv);
		return rv;
	}

	g_router_arp_counter[new_arp_index]++;

	return ROUTER_E_NONE;
}

/*add router port*/
int router_port_add(int ip, router_mac_t my_mac, int port)
{
	int rv;
	router_port_t router_port;

	memset(&router_port, 0, sizeof(router_port));
	router_port[port].vlan = port;
	router_port[port].ip = ip;
	memcpy(router_port[port].my_mac, my_mac, 6);

	rv = router_bcm_port_add(&router_port);
	if (rv != ROUTER_E_NONE) {
	  printf ("router_bcm_port_add failed: %x \n", rc);
	}

	memcpy(&g_router_port[port], &router_port, sizeof(router_port)); 

	return ROUTER_E_NONE;
}

/*delete router port*/
int router_port_delete(int port)
{
	int rv;
	router_port_t router_port;

	memset(&router_port, 0, sizeof(router_port));
	router_port.vlan = g_router_port[port].vlan;
	router_port.ip = g_router_port[[port].ip;
	router_port.ingress_interface = g_router_port[port].ingress_interface;
	memcpy(router_port.my_mac, g_router_port[port].my_mac, 6);
	
	rv = router_bcm_port_delete(router_port);
	if(rv != ROUTER_E_NONE)
	{
		printf("router_bcm_port_delete failed! rv = %d\n", rv);
		return rv;
	}

	return ROUTER_E_NONE;
}

/****************************************internal function of router driver*****************************************************************/

int router_bcm_route_add(router_dest_info_t router_dest_info, int arp_index)
{
	int rv;
	int unit = 0;
	bcm_l3_route_t bcm_route_info;
	bcm_if_t l3a_intf; 

	bcm_l3_route_t_init(&bcm_route_info);
	bcm_route_info.l3a_subnet = router_dest_info.route_dip_addr;
	bcm_route_info.l3a_ip_mask = router_dest_info.route_dip_mask;
	bcm_route_info.l3a_vrf = router_dest_info.vrf;
	bcm_route_info.l3a_intf = arp_index;
	
	rv = bcm_l3_route_add(unit, bcm_route_info);
	if (rv != BCM_E_NONE) {
	  printf ("bcm_l3_route_add failed: %x \n", rc);
	}

	return rv;
}

int router_bcm_route_delete(router_dest_info_t router_dest_info)
{
	int rv;
	int unit = 0;
	bcm_l3_route_t bcm_route_info;
	bcm_if_t l3a_intf; 

	bcm_l3_route_t_init(&bcm_route_info);
	bcm_route_info.l3a_subnet = router_dest_info.route_dip_addr;
	bcm_route_info.l3a_ip_mask = router_dest_info.route_dip_mask;
	bcm_route_info.l3a_vrf = router_dest_info.vrf;
	
	rv = bcm_l3_route_delete(unit, bcm_route_info);
	if (rv != BCM_E_NONE) {
	  printf ("bcm_l3_route_add failed: %x \n", rc);
	}

	return rv;
	
}


int router_bcm_arp_create(router_mac_t router_mac, int *arp_index)
{
	int rv;
	int unit = 0;
	int port;
	uint32 flags;
	bcm_vlan_t vid;
	bcm_if_t l3egr;
	bcm_l2_addr_t l2addr;
	bcm_l3_egress_t egr;

	if(IS_NULL_CHECK(arp_index))
	{	
		return ROUTER_E_PARAM;
	}

	/*traverse all vlan*/
	for(port=1; port<=ROUTER_MAX_PORT_NUM; port++)
	{
		vid = g_router_port[port].vlan;
		rv = bcm_l2_addr_get(unit, router_mac, vid, &l2addr);
		if(rv == BCM_E_NONE)
		{
			if(port != l2addr.port)
			{
				/*should never happen*/
			}
			break;
		}
	}

	port = l2addr.port;

	/*create egress interface(ARP)*/
	bcm_l3_egress_t_init(&egr);
	memcpy(egr.mac_addr, router_mac, 6);  
    egr.vlan   = g_router_port[port].vlan;
    egr.module = 0;
    egr.port   = port;
	egr.intf   = g_router_port[port].ingress_interface;
	rv = bcm_l3_egress_create(unit, flags, &egr, &l3egr);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_egress_create failed, rv = %d\n",rv);
		return rv;
	}
	
	*arp_index = l3egr;

	return ROUTER_E_NONE;
}

/*destroy l3 egress object(l3 egress intf)*/
int router_bcm_arp_destroy(int arp_index)
{
	int rv;
	int unit = 0;

	/*destroy egress interface(ARP)*/
	rv = bcm_l3_egress_destroy(unit, arp_index);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_egress_create failed, rv = %d\n",rv);
		return rv;
	}

	return ROUTER_E_NONE;
}

/*Get ARP according to next hop*/
int router_bcm_arp_get(router_dest_info_t next_hop, int *arp_index)
{
	int rv;
	router_dest_info_t dest_ip;

	
	memset(&dest_ip, 0, sizeof(dest_ip));
	dest_ip.route_dip_addr = next_hop.route_next_hop_ip;
	dest_ip.vrf = next_hop.vrf;
	/*Get related l3 host entry to get the ARP*/
	rv = router_bcm_host_get(dest_ip, arp_index);
	if(rv == ROUTER_E_NOT_FOUND)
	{
		*arp_index = ROUTER_ARP_INVALID;
	}
	
	return rv;
}


int router_bcm_host_add(router_dest_info_t router_next_hop, int arp_index)
{
	int rv;
	int unit;
	bcm_l3_host_t host;

	bcm_l3_host_t_init(&host);
	host.l3a_ip_addr = router_next_hop.route_next_hop_ip;
	host.vrf = router_next_hop.vrf;
	host.l3a_intf = arp_index;

	rv = bcm_l3_host_add(unit, &host);
	if()
	{
		
	}

	return rv;
}

int router_bcm_host_delete(router_dest_info_t router_next_hop)
{
	int rv;
	int unit;
	bcm_l3_host_t host;

	bcm_l3_host_t_init(&host);
	host.l3a_ip_addr = router_next_hop.route_next_hop_ip;
	host.vrf = router_next_hop.vrf;
	
	rv = bcm_l3_host_delete(unit, &host);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_host_delete failed! rv = %d\n", rv);
		return rv;
	}

	return ROUTER_E_NONE;
}


int router_bcm_host_get(router_dest_info_t router_next_hop, int *arp_index)
{
	int rv;
	int unit;
	bcm_l3_host_t host;

	bcm_l3_host_t_init(&host);
	host.l3a_ip_addr = router_next_hop.route_next_hop_ip;
	host.vrf = router_next_hop.vrf;
	rv = bcm_l3_host_find(unit, &host);
	if(rv != ROUTER_E_NONE)
	{
		return rv;
	}

	*arp_index = host.l3a_intf;
}


/*add l3 ingress interface*/
int router_bcm_port_add(router_port_t *router_port)
{
	int rv;
	int unit = 0;
	bcm_l3_intf_t l3_intf;
	bcm_l2_addr_t l2addr;
	bcm_l3_host_t l3_host;

	/*create vlan*/
	rv = bcm_vlan_create(unit, router_port->vlan);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_vlan_create failed! rv = %d\n", rv);
		return rv;
	}

	/*add l2 mac entry for l3*/
	bcm_l2_addr_t_init(&l2addr, router_port->my_mac, router_port->vlan);
	l2addr.flags |= BCM_L2_L3LOOKUP | BCM_L2_STATIC;
	rv = bcm_l2_addr_add(unit,l2addr);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l2_addr_add failed! rv = %d\n", rv);
		return rv;
	}

	/*create l3 ingress intf*/
	bcm_l3_intf_t_init(&l3_intf);
	l3_intf.l3a_vid = router_port->vlan;
	memcpy(l3_intf.l3a_mac_addr, router_port->my_mac, 6);
	rv = bcm_l3_intf_create(unit,&l3_intf);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_intf_create failed! rv = %d\n", rv);
		return rv;
	}

	router_port->ingress_interface = l3_intf.l3a_intf_id;

	/*add l3 entry to cpu*/
	bcm_l3_host_t_init(&l3_host);
	l3_host.l3a_vrf = router_port.vrf;
	l3_host.l3a_ip_addr = router_port.ip;
	//l3_host.l3a_port_tgid = ROUTER_CPU_PORT; /*cpu port*/
	l3_host.l3a_intf = g_default_arp_index;
	rv = bcm_l3_host_add(unit,l3_host);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_host_add failed, rv = %d\n", rv);
		return rv;
	}

	return ROUTER_E_NONE;
}

int router_bcm_port_delete(router_port_t router_port)
{
	int rv;
	int unit;
	bcm_l3_host_t l3_host;
	bcm_l3_intf_t l3_intf;	

	/*delete l3 entry to cpu*/
	bcm_l3_host_t_init(&l3_host);
	l3_host.l3a_vrf = router_port.vrf;
	l3_host.l3a_ip_addr = router_port.ip;
	rv = bcm_l3_host_delete(unit,l3_host);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_host_delete failed, rv = %d\n", rv);
		return rv;
	}

	
	/*delete l3 ingress intf*/
	bcm_l3_intf_t_init(&l3_intf);
	l3_intf.l3a_vid = router_port.vlan;
	memcpy(l3_intf.l3a_mac_addr, router_port.my_mac, 6);
	l3_intf.l3a_intf_id = router_port.ingress_interface;
	rv = bcm_l3_intf_delete(unit,&l3_intf);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l3_intf_delete failed! rv = %d\n", rv);
		return rv;
	}

	/*delete l2 mac entry for l3*/
	rv = bcm_l2_addr_delete(unit,router_port.my_mac, router_port.vlan);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_l2_addr_delete failed! rv = %d\n", rv);
		return rv;
	}

			
	/*delete port vlan*/
	rv = bcm_vlan_destroy(unit, router_port.vlan);
	if(rv != BCM_E_NONE)
	{
		printf("bcm_vlan_destroy failed! rv = %d\n", rv);
		return rv;
	}

	return ROUTER_E_NONE;
}
