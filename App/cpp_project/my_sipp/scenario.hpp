#ifndef __SCENARIO__
#define __SCENARIO__

class scenario
{
public:
	scenario(char * filename, int deflt);
    ~scenario();

    void runInit();
	
    void computeSippMode();
};

#endif

