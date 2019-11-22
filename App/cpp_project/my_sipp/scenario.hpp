#ifndef __SCENARIO__
#define __SCENARIO__

#define MODE_CLIENT        0
#define MODE_SERVER        1

class message
{
public:
	message(int index, const char *desc);
    ~message();
};

typedef std::vector<message *> msgvec;

class scenario
{
public:
	scenario(char * filename, int deflt);
    ~scenario();

    void runInit();

	msgvec messages;
    msgvec initmessages;
	
    void computeSippMode();

private:
   int msg_index;
	
};

/* There are external variable containing the current scenario */
extern int           sendMode;

extern const char * default_scenario[12];

#endif

