/*
 * wifi.h
 *
 *  Created on: Jan 28, 2025
 *      Author: paul
 */

#ifndef _WIFI_H_
#define _WIFI_H_


#ifdef __cplusplus
extern "C" {
#endif

/** Includes **/
#include "netdev_api.h"

/** Exported macros **/
#define ARPING_DEMO	1
#define LWIP_DEMO	2
#define MAIN_APP_CODE ARPING_DEMO

/** Exported variables **/

/** Inline functions **/

/** Exported Functions **/
void startWifi(void);
extern stm_ret_t send_arp_req(struct network_handle *net_handle, uint8_t *src_mac,
		uint32_t *src_ip, uint8_t *dst_mac, uint32_t *dst_ip);

#ifdef __cplusplus
}
#endif



#endif /* INC_WIFI_H_ */
