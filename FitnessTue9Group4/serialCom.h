/*
 * serialCom.h
 * Debug module for printing to serial coms using a simple interface
 *
 *  Created on: 14/03/2020
 *      Author: csm119
 */

#ifndef SERIALCOM_H_
#define SERIALCOM_H_

void initSerialCom(void);
void printCom(char *pucBuffer);
void printfCom(const char * restrict format, ...);

#endif /* SERIALCOM_H_ */
