//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
//#include "../CIpcs.h"
#include "../includs.h"
int main() {
	class CIpcs ipcs;
	class CLogs log;
	ipcs.CreatShareMemory(UP_TYPE,1);
	ipcs.CreatShareMemory(DOWN_TYPE,1);
	cout << "���ǲ�����Ϣ111" << endl;
	return 0;
}
