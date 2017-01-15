/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples: 
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2
*/


class MedianFinder {
      private:
        priority_queue<int> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;
      public:

        // Adds a number into the data structure.
        void addNum(int num) {
          if(!maxHeap.empty() && num > maxHeap.top()){
            minHeap.push(num);
            if(minHeap.size() > maxHeap.size() + 1){
              int t = minHeap.top();
              minHeap.pop();
              maxHeap.push(t);
            }
          }
          else {
            maxHeap.push(num);
            if(minHeap.size() < maxHeap.size() - 1){
              int t = maxHeap.top();
              maxHeap.pop();
              minHeap.push(t);
            }
          }
        }

        // Returns the median of current data stream
        double findMedian() {
          if(minHeap.size() == maxHeap.size())
            return (double)(minHeap.top() + maxHeap.top()) / 2;
          else if(minHeap.size() > maxHeap.size())
            return minHeap.top();
          else
            return maxHeap.top();
        }
      };
