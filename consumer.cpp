#include <iostream>
#include <string>
#include <cppkafka/consumer.h>

using namespace std;
using namespace cppkafka;

int main(int argc,char** argv)
{

	string groupId("foo");

	if(argc >1 && argv[1])
	{
		groupId = argv[1];
	}

	Configuration config = {
		{ "metadata.broker.list", "c-m19448y69w.kafka.cn-east-1.internal:9092" },
		{"group.id",groupId}
	};

	// Construct from some config we've defined somewhere
	Consumer consumer(config);

	// Set the assignment callback
	consumer.set_assignment_callback([&](vector<TopicPartition>& topic_partitions) {
					// Here you could fetch offsets and do something, altering the offsets on the
					// topic_partitions vector if needed
					cout << "Got assigned " << topic_partitions.size() << " partitions!" << endl;
					});

	// Set the revocation callback
	consumer.set_revocation_callback([&](const vector<TopicPartition>& topic_partitions) {
					cout << topic_partitions.size() << " partitions revoked!" << endl;
					});


	// Subscribe to 1 topics
	consumer.subscribe({ "cubegun" });

	// Now loop forever polling for messages
	while (true) {
		Message msg = consumer.poll();

		// Make sure we have a message before processing it
		if (!msg) {
			continue;
		}

		// Messages can contain error notifications rather than actual data
		if (msg.get_error()) {
			// librdkafka provides an error indicating we've reached the
			// end of a partition every time we do so. Make sure it's not one
			// of those cases, as it's not really an error
			if (!msg.is_eof()) {
				// Handle this somehow...
			}
			continue;
		}

		// We actually have a message. At this point you can check for the
		// message's key and payload via `Message::get_key` and
		// `Message::get_payload`

		cout << "Received message on partition " << msg.get_topic() << "/"
			<< msg.get_partition() << ", offset " << msg.get_offset() << ", content :" << msg.get_payload()<< endl;
	}

}
