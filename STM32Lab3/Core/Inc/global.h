/*
 * global.h
 *
 *  Created on: Nov 13, 2023
 *      Author: hieun
 */


#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "softwareTimer.h"
#include "button.h"

//define các trạng thái của máy trạng thái
#define INIT		 1
#define AUTO_RED	 2
#define AUTO_GREEN	 3
#define AUTO_YELLOW	 4

extern int status;

#endif /* INC_GLOBAL_H_ */
