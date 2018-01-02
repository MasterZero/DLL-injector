#include <stdio.h>
#include "Injector.h"
#include <vector>
using namespace std;

int main()
{

	int result = DllInjector::inject("uTorrent.exe", "C:\\\\Users\\zero\\source\\repos\\DLL injector\\DLL injector\\test.dll");


	printf("result code: %i\n", result);
	system("pause");

	return 0;
}