/*
描述
计算机系统中使用的UTC时间基于原子钟，这种计时方式同“地球自转一周是24小时”的计时方式有微小的偏差。为了弥补这种偏差，我们偶尔需要增加一个“闰秒”。  

最近的一次闰秒增加发生在UTC时间2016年的最后一天。我们在2016年12月31日23时59分59秒和2017年1月1日0时0分0秒之间增加了这样一秒：2016年12月31日23时59分60秒，记作2016-12-31 23:59:60。  

目前一共增加了27次闰秒，具体添加的时间见下表：

给出两个时间，请你判断在考虑闰秒的情况下，这两个时间间隔多少秒。  

输入
两个时间各占一行，格式是yyyy-MM-dd HH:mm:ss，范围在1970-01-01 00:00:00至2017-03-12 23:59:59之间。保证第一个时间不晚于第二个时间。

输出
两个时间间隔多少秒。

样例输入
2016-12-31 23:59:59 
2017-01-01 00:00:00
样例输出
2
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> split(const string& data,const string& delim){
    vector<int> res;
    unsigned long idx = 0, tidx = 0;
    while((tidx = data.find(delim, idx)) != string::npos){
        res.push_back(stoi(data.substr(idx, tidx - idx)));
        idx = tidx + delim.size();
    }
    if(idx != data.size())
        res.push_back(stoi(data.substr(idx, data.size() - idx)));
    return res;
}

vector<string> myplus({"1972-06-30 23:59:60", "1972-12-31 23:59:60", "1973-12-31 23:59:60", "1974-12-31 23:59:60", "1975-12-31 23:59:60", "1976-12-31 23:59:60", "1977-12-31 23:59:60", "1978-12-31 23:59:60", "1979-12-31 23:59:60", "1981-06-30 23:59:60", "1982-06-30 23:59:60", "1983-06-30 23:59:60", "1985-06-30 23:59:60", "1987-12-31 23:59:60", "1989-12-31 23:59:60", "1990-12-31 23:59:60", "1992-06-30 23:59:60", "1993-06-30 23:59:60", "1994-06-30 23:59:60", "1995-12-31 23:59:60", "1997-06-30 23:59:60", "1998-12-31 23:59:60", "2005-12-31 23:59:60", "2008-12-31 23:59:60", "2012-06-30 23:59:60", "2015-06-30 23:59:60", "2016-12-31 23:59:60", "2017-03-13 23:59:59"});

int main(){
    string dstr[2], tstr[2], time[2];
    cin >> dstr[0] >> tstr[0] >> dstr[1] >> tstr[1];
    
    vector<int> dint[2], tint[2];
    dint[0] = split(dstr[0], "-");
    dint[1] = split(dstr[1], "-");
    tint[0] = split(tstr[0], ":");
    tint[1] = split(tstr[1], ":");
    
    time[0] = dstr[0] + " " + tstr[0];
    time[1] = dstr[1] + " " + tstr[1];
    
    auto iter1 = lower_bound(myplus.begin(), myplus.end(), time[0]), iter2 = lower_bound(myplus.begin(), myplus.end(), time[1]);
    
    int interval = (int)(iter2 - iter1);
    
    struct tm timeinfo[2];
    strptime(time[0].c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo[0]);
    strptime(time[1].c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo[1]);
    time_t seconds[2];
    seconds[0] = mktime(&timeinfo[0]);
    seconds[1] = mktime(&timeinfo[1]);
    cout << seconds[1] - seconds[0] + interval << endl;
    
    return 0;
}

