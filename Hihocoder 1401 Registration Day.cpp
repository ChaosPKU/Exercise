/*

描述
It's H University's Registration Day for new students. There are M offices in H University, numbered from 1 to M. Students need to visit some of them in a certain order to finish their registration procedures. The offices are in different places. So it takes K units of time to move from one office to another.

There is only one teacher in each office. It takes him/her some time to finish one student's procedure. For different students this time may vary. At the same time the teacher can only serve one student so some students may need to wait outside until the teacher is available. Students who arrived at the office earlier will be served earlier. If multiple students arrived at the same time they will be served in ascending order by student number.

N new students need to finish his/her registration. They are numbered from 1 to N. The ith student's student number is Si. He will be arrived at H University's gate at time Ti. He needs to visit Pi offices in sequence which are Oi,1, Oi,2, ... Oi,Pi. It takes him Wi,1, Wi,2, ... Wi,Pi units of time to finish the procedure in respective offices. It also takes him K units of time to move from the gate to the first office.

For each student can you tell when his registration will be finished?

输入
The first line contains 3 integers, N, M and K.  (1 <= N <= 10000, 1 <= M <= 100, 1 <= K <= 1000)

The following N lines each describe a student.

For each line the first three integers are Si, Ti and Pi. Then following Pi pairs of integers: Oi,1, Wi,1, Oi,2, Wi,2, ... Oi,Pi, Wi,Pi. (1 <= Si <= 2000000000, 1 <= Ti <= 10000, 1 <= Pi <= M, 1 <= Oi,j <= M, 1 <= Wi,j <= 1000)

输出
For each student output the time when he finished the registration.

样例提示
Student 1600012345 will be arrived at the gate at time 500. He needs to first visit Office #1 and then Office #2. He will be arrived at office #1 at time 600. He will leave office #1 at time 1100. Then He will arrive at office #2 at 1200. At the same time another student arrives at the same office too. His student number is smaller so he will be served first. He leaves Office #2 at 1700. End of registration.

Student 1600054321 will be arrived at the gate at time 1100. He will be arrived at Office #2 at 1200. Another student with smaller student number will be served first so he waits for his turn until 1700. He leaves Office #2 at 2000. End of registration.

样例输入
2 2 100  
1600012345 500 2 1 500 2 500  
1600054321 1100 1 2 300
样例输出
1700  
2000

*/

#include <iostream>
#include <queue>

using namespace std;
int N, M, K;

class student{
public:
    int id, atime, num, idx;
    vector<int> offices, wtimes;
};

vector<student> stus;
vector<int> ofctime;

class Event{
public:
    int stuIdx, ofcIdx, stime, ktime;
    Event(int _sd, int _od, int _st, int _kt): stuIdx(_sd), ofcIdx(_od), stime(_st), ktime(_kt){}
    bool hasnext(){
        return ofcIdx + 1 < stus[stuIdx].num;
    }
    Event next(){
        if(ofcIdx >= 0){
            stime = max(ofctime[stus[stuIdx].offices[ofcIdx]], stime);
            ofctime[stus[stuIdx].offices[ofcIdx]] = stime += ktime;
        }
        stime += K;
        ktime = stus[stuIdx].wtimes[++ ofcIdx];
        return *this;
    }
};

bool operator<(const Event & a, const Event &b){
    if(a.stime != b.stime) return a.stime > b.stime;
    return stus[a.stuIdx].id > stus[b.stuIdx].id;
}

vector<int> res;
priority_queue<Event, vector<Event> > PQ;

int main(){
    cin >> N >> M >> K;
    stus.resize(N + 1);
    res.resize(N);
    ofctime.resize(M + 1, 0);
    for(int i = 0;i < N; ++ i){
        stus[i].idx = i;
        cin >> stus[i].id >> stus[i].atime >> stus[i].num;
        stus[i].offices.resize(stus[i].num);
        stus[i].wtimes.resize(stus[i].num);
        for(int j = 0;j < stus[i].num; ++ j)
            cin >> stus[i].offices[j] >> stus[i].wtimes[j];
        PQ.push(Event(i, -1, stus[i].atime, 0));
    }
    while(!PQ.empty()){
        Event e = PQ.top();
        PQ.pop();
        if(e.hasnext())
            PQ.push(e.next());
        else{
            e.stime = max(e.stime, ofctime[stus[e.stuIdx].offices[e.ofcIdx]]);
            ofctime[stus[e.stuIdx].offices[e.ofcIdx]] = res[e.stuIdx] = e.stime + e.ktime;
        }
    }
    
    for(int i = 0; i < res.size(); ++ i)
        cout << res[i] << endl;
    
    return 0;
}
