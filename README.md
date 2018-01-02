# DLL-injector


Class DllInjector to attach dll to process by processId or processName

### DllInjector ::inject()
#### Params:
	const char * szProcessName - process name,
	const char * szPathToDll - path to dll library

#### returns value: int
	0 - all OK
	1 - I can not find process by name
	2 - I can not open process
	3 - I can not alloc memory
	4 - I can not write to memory
	5 - I can not start thread

### DllInjector ::inject()
#### Params:
	int ProcessID - process id,
	const char * szPathToDll - path to dll library

#### returns value: same

### GetProcessIDsByName()
#### params:
	const char * process_name - process name
#### return value
std::vector<int> with all founded process ids

## Example usage
	 DllInjector::inject("uTorrent.exe", "C:\\\\Users\\zero\\source\\repos\\DLL injector\\DLL injector\\test.dll");