#include <ctime>
#include <iostream>

#include "libbroker.hpp"

bool isBrokerDead (const struct BrokerData& brokerData) {
	struct timespec now;
	long elapsed;

	// Get current time
	clock_gettime(CLOCK_MONOTONIC, &now);

	// Compute difference (support rollover)
	elapsed = now.tv_nsec - brokerData.lastUpdated.tv_nsec;
	if (elapsed <= 0)
		elapsed += 1000000000L;

	// Compare with timeout
	return elapsed > BROKER_TIMEOUT;
}

// TODO: see if we can use reference instead
void updateBrokerData (struct BrokerData * brokerData, const float * newData, size_t n) {
	if (n > MAX_NB_ELEM) {
		std::cerr << "Error: tried to update " << n << " broker elements, " << MAX_NB_ELEM << " being the max" << std::endl;
		exit(1);
	}

	// Write the new data in the BrokerData structure
	for (unsigned int i = 0; i < n; i += 1) {
		brokerData->data[i] = newData[i];
	}

	// Update the time to indicate this is fresh data and the broker is not dead
	clock_gettime(CLOCK_MONOTONIC, &(brokerData->lastUpdated));
}
