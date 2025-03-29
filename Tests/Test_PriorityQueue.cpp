#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DataStructures/PriorityQueue.h"
#include "../doctest.h"

using namespace ds;

TEST_CASE("Test priority queue") {
    PriorityQueue pq(5);

    CHECK(pq.isEmpty());

    pq.insert(0, 10);
    pq.insert(1, 5);
    pq.insert(2, 7);

    CHECK_FALSE(pq.isEmpty());
    CHECK(pq.contains(1));
    CHECK(pq.contains(2));
    CHECK(pq.getDistance(1) == 5);
    CHECK(pq.getDistance(2) == 7);

    // Test decreaseKey
    pq.decreaseKey(2, 2);
    CHECK(pq.getDistance(2) == 2);

    // Test extractMin (should now return 2)
    int minVertex = pq.extractMin();
    CHECK(minVertex == 2);
    CHECK_FALSE(pq.contains(2));

    // Extract next minimum (should be 1)
    minVertex = pq.extractMin();
    CHECK(minVertex == 1);

    // Extract final (should be 0)
    minVertex = pq.extractMin();
    CHECK(minVertex == 0);

    // Should now be empty
    CHECK(pq.isEmpty());
}
