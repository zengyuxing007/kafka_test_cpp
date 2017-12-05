all:producer consumer

consumer: consumer.cpp
	g++ -g -std=c++11 -o consumer consumer.cpp -lcppkafka -lrdkafka -lpthread -lrt
producer: producer.cpp
	g++ -g -std=c++11 -o producer producer.cpp -lcppkafka -lrdkafka
