/*
 * CLogs.h
 *
 *  Created on: 2018��6��25��
 *      Author: 15645
 */

#ifndef CLOGS_H_
#define CLOGS_H_
#include "includs.h"

enum LOGLEVEL
{
      ERROR,
      NOTICE,
      WARN,
      INFO
};
class CLogs {

public:
	CLogs();
	virtual ~CLogs();
	int LogMessage(std::string StrMsgToBeSave,LOGLEVEL AlarmClass);
private:
	std::string Strnowtime;
	std::string Strmessage;
	LOGLEVEL loglevel;
	int GetTime();
	std::string AssembleMessage(LOGLEVEL AlarmClass);
	int SaveMessage(std::string StrMsgToBeSave);

};

#endif /* CLOGS_H_ */
