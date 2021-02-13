#include "AMQPcpp.h"

using namespace std;

int main (int argc, char** argv) {

    string mq_server_user = "test";
    string mq_server_pwd = "test123456";
    string mq_server_host = "39.105.106.62:5672";
    string test_exchange = "smm_spec_amqpcpp_10000";
    string test_queue = "smm_spec_amqpcpp_10000_0_00000017";
    string test_message_key = "ccm_intspec_10000_ccm_0";

	try {
//		AMQP amqp;
//		AMQP amqp(AMQPDEBUG);
	
		//AMQP amqp("test:test123456@39.105.106.62:5672/");		// all connect string
		string connect_str = mq_server_user + ":" + mq_server_pwd + "@" + mq_server_host;
		AMQP amqp(connect_str);	

		AMQPExchange * ex = amqp.createExchange("smm_spec_amqpcpp_10000");
		ex->Declare(test_exchange, "direct");

		AMQPQueue * qu = amqp.createQueue(test_queue);
		qu->Declare();
		qu->Bind(test_exchange, test_queue);
        
		string ss = "amqpccp publist test";
        string message_exchange = "ccm_intgbal_10000";
        ex->setMessageExchange(message_exchange);
        ex->Publish(ss , test_message_key);
                
#if 0
		string ss = "message 1 ";

		ex->setHeader("Delivery-mode", 2);
		ex->setHeader("Content-type", "text/text");
		ex->setHeader("Content-encoding", "UTF-8");

		ex->Publish(  ss , ""); // publish very long message
		
		ex->Publish(  "message 2 " , "");
		ex->Publish(  "message 3 " , "");
#endif
		
		if (argc==2) {
			AMQPQueue * qu = amqp.createQueue();			
			qu->Cancel(   amqp_cstring_bytes(argv[1]) );
		}												
						
	} catch (AMQPException e) {
		std::cout << e.getMessage() << std::endl;
	}

	return 0;

}
