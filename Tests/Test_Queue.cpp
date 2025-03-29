// davidkitinberg@gmail.com

//#include "Test_Queue.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // Makes doctest run this test without main
#include "../DataStructures/Queue.h"
#include "../Graph/Graph.h"
#include "../doctest.h"

using namespace ds;

TEST_CASE("Test Queue") {
  Queue q(3);

  CHECK(q.isEmpty());
  CHECK_FALSE(q.isFull());

  // Enqueue elements
  CHECK(q.enqueue(10) == 0);
  CHECK(q.enqueue(20) == 0);
  // Check new size
  CHECK(q.size() == 2);

  CHECK_FALSE(q.isEmpty());

  // Check peek function functinality
  CHECK(q.peek() == 10);
  // Dequeue elements
  CHECK(q.dequeue() == 10);
  // Check peek function functinality #2
  CHECK(q.peek() == 20);

  // Dequeue elements and check if empty
  CHECK(q.dequeue() == 20);
  CHECK(q.isEmpty());
}