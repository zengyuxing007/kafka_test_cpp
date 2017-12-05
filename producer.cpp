#include <cppkafka/producer.h>
#include <iostream>

using namespace std;
using namespace cppkafka;

int main(int argc,char** argv) {

		int p(0);

		if(argc > 1 && argv[1])
		{
			p= strtol(argv[1],NULL,10);
		}

		cout << "partition:"<<p<<endl;

		// Create the config

		Configuration config = {
				{ "metadata.broker.list", "c-m19448y69w.kafka.cn-east-1.internal:9092" }
		};

		// Create the producer
		Producer producer(config);

		// Produce a message!
		string message = "hey there!";
		MessageBuilder mesg("cubegun");
		mesg.partition(p).payload(message);

		while(1)
		{
				producer.produce(mesg);
				producer.flush();
				sleep(1);
		}

}
