/*
 * application_flow.h
 *
 *  Created on: 11 gru 2024
 *      Author: User
 */

#ifndef XPROGRAM_FLOW_APPLICATION_FLOW_H_
#define XPROGRAM_FLOW_APPLICATION_FLOW_H_

#include "data_convert.h"
#include "application_oled.h"

void ApplicationFlow_Initialization(void);

void ApplicationFlow_RedControl(void);
void ApplicationFlow_BlueControl(void);
void ApplicationFlow_BothStop(void);

void ApplicationFlow_mainscreen(void);

#endif /* XPROGRAM_FLOW_APPLICATION_FLOW_H_ */
