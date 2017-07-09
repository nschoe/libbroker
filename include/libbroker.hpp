#ifndef _LIBBROKER_HPP_
#define _LIBBROKER_HPP_

#include <ctime>

// Define the max size of the 'data' field
#define MAX_NB_ELEM 10

// Define the SHM size to use for brokers
#define BROKER_SHM_SIZE 512

// Define the maximum time between two broker data before the broker is considered dead
#define BROKER_TIMEOUT 200000000 // in ns (0.2 s)

struct BrokerData {
	float data[MAX_NB_ELEM];     // Data the broker is tasked to fetch
	struct timespec lastUpdated; // Last time the broker updated the data (used to detect dead broker)
};

bool isBrokerDead (const struct BrokerData& brokerData);

void updateBrokerData (struct BrokerData * brokerData, const float * newData, size_t n);

#endif
