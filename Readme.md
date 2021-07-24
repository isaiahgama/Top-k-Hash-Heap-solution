# CS130A PA2 - Top-k / Heavy-Hitter

The heavy hitter or top-k problem is a famous problem in computer science, typically used
in settings where a stream of data (sensor data, click stream, advertisement requests, etc)
is being analyzed to detect the most popular items. An easy solution is to keep a counter
for each item in the stream, and increment the counter every time the corresponding item
is received. Unfortunately, often the domain of items is too large to maintain a counter for
each element, eg, the domain might be all IP addresses. In this case, we typically maintain a
smaller finite set of counters. So, for each new item, we create a counter which corresponds
to that item. The counter is incremented every time this item is encountered. This works
fine until the finite set of counters is full. We need to eliminate one counter and add a new
one. Usually, the element with the smallest count is deleted. Different strategies have been
proposed regarding the initialization of the new counter. One very successful strategy is to
initialize the new counter with the value of the deleted (smallest count) counter. Of course
the resulting top-k elements are an approximation of the real top-k, but it has been shown
to be quite accurate for realistic distributions. In this code, I use this strategy.
