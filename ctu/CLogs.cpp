/*
 * CLogs.cpp
 *
 *  Created on: 2018年6月25日
 *      Author: 15645
 */

#include "CLogs.h"
using namespace std;
CLogs::CLogs() {
	// TODO Auto-generated constructor stub

}

CLogs::~CLogs() {
	// TODO Auto-generated destructor stub
}
int CLogs::GetTime()
{
	time_t timer;//time_t就是long int 类型
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	Strnowtime = asctime(tblock);
	return 0;
}

std::string CLogs::AssembleMessage(LOGLEVEL AlarmClass)
{
	std::string StrFinalMsg;
	switch(AlarmClass)
	{
		case ERROR:
			StrFinalMsg = "ERROR： " + Strmessage + Strnowtime;
			break;
		case NOTICE:
			StrFinalMsg = "NOTICE： " + Strmessage + Strnowtime;
			break;
		case WARN:
			StrFinalMsg = "WARNING： " + Strmessage + Strnowtime;
			break;
		case INFO:
			StrFinalMsg = "INFORMATION： " + Strmessage + Strnowtime;
			break;
		default:
			break;

	}
	return StrFinalMsg;
}

int CLogs::SaveMessage(std::string StrMsgToBeSave)
{
	ofstream outfile;
	outfile.open("Log.dat",ios::app);
	outfile << StrMsgToBeSave << endl;
	outfile.close();
	return 0;
}

int CLogs::LogMessage(std::string StrMsgToBeSave,LOGLEVEL AlarmClass)
{
	GetTime();
	Strmessage = StrMsgToBeSave;
	SaveMessage(AssembleMessage(AlarmClass));
	return -1;
}
