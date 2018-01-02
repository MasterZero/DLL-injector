#include <vector>

class DllInjector {
public:

	typedef std::vector<int> ProcessList;

	/*
	Inject dll to process by process name or process id.

	return values:
	0 - All OK
	1 - I can not find process by name
	2 - I can not open process
	3 - I can not alloc memory
	4 - I can not write to memory
	5 - I can not start thread
	*/
	static int inject(const char * szProcessName,const char * szPathToDll);
	static int inject(int processID, const char * szPathToDll);

	/* get all proccess IDs by name.
	
	return values:
	all founded IDs into std::vector<int>
	*/
	static ProcessList getProcessIDsByName(const char * process_name);
};
