/*
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
*/


class Twitter {
  private:
    unordered_map<int, vector<int>> id2tweets;
    unordered_map<int, unordered_set<int>> id2followees;
    unordered_map<int, int> time2tweets;
    unordered_map<int, int> tweets2time;
    int time;
  public:
    /** Initialize your data structure here. */
    Twitter() {
      id2tweets.clear();
      id2followees.clear();
      time2tweets.clear();
      tweets2time.clear();
      time = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
      time2tweets[time] = tweetId;
      tweets2time[tweetId] = time;
      id2tweets[userId].push_back(time);
      ++ time;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
      priority_queue<int> pq;
      unordered_set<int> us = id2followees[userId];
      for(auto j = us.begin(); j != us.end(); ++ j){
        vector<int> v = id2tweets[*j];
        for(int k : v)
        pq.push(k);
      }
      for(int k : id2tweets[userId])
        pq.push(k);
      vector<int> res;
      for(int i = 0;i < 10 && !pq.empty(); ++ i){
        res.push_back(time2tweets[pq.top()]);
        pq.pop();
      }
      return res;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
      if(followerId != followeeId)
        id2followees[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
      auto iter = id2followees.find(followerId);
      if(iter != id2followees.end())
        iter->second.erase(followeeId);
    }
  };

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */
