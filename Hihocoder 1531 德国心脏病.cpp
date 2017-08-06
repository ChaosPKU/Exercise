/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Jack在和朋友们玩德国心脏病。

德国心脏病的游戏牌分为水果牌和动物牌。水果只有4种：香蕉、草莓、樱桃、柠檬，每张水果牌上会有种类不定、总数目1-5的水果；动物只有3种：猴子、大象、猪，每张动物牌上有且仅有一只动物。

n名玩家绕圈就座，第一轮游戏从0号至n-1号轮流出牌。每个玩家面前最多只有一张牌，如果玩家出牌时，他的面前已经摆放了一张牌，他新出的牌将会严丝合缝地盖住旧牌。

任何时候玩家可以选择按铃操作。如果按铃成功，玩家可以获得当前场上所有牌（包括被盖住的牌）并进入下一轮游戏，下一轮游戏由他先出牌，然后依序轮流出牌；否则，他需要支付给每位玩家一张手牌，然后他成为下一位出牌者，继续这一局游戏。

按铃成功的条件：

1、当前场上（被盖住的牌不算，以下同）某种水果的数量正好为5。

2、当前场上出现猴子，至少有一个水果，且没有出现柠檬。

3、当前场上出现大象，至少有一个水果，且没有出现草莓。

4、当前场上出现猪，且至少有一个水果。

Bob对这个游戏很感兴趣，他给了Jack一个操作序列，希望Jack输出最终每个人拥有的牌的数量。每名玩家初始拥有10,000,000张牌。操作分为两种：出牌或按铃。操作结束时游戏立即终止。

1、出牌的格式是：Fruit+水果数s+水果种类*s，0、1、2、3分别表示香蕉、草莓、樱桃、柠檬。如Fruit 4 0 2 2 2代表1个香蕉和3个樱桃的牌。或Animal+动物种类，0、1、2分别代表猴子、大象、猪。如Animal 0代表一张猴子牌。注意，选手需要自己计算出牌者是几号玩家。

2、按铃的格式是：Ring+选手编号。如Ring 2。

输入
第一行两个正整数n(≤10), k(≤100,000)。

接下来k行，每行对应一个操作。

输出
n行，每行一个整数，代表每个玩家游戏结束后拥有的牌的数目。

样例解释
3 13 			        # 井号后为样例输入说明：3名玩家，13次操作
Fruit 5 0 0 0 0 0	# 0号玩家出牌：5个香蕉
Ring 0 			      # 0号玩家按铃：按铃成功，获得场上的1张牌，开始下一轮游戏
Ring 1 			      # 1号玩家按铃：按铃失败，给0, 2号玩家各一张牌
Fruit 3 3 0 0	 	  # 1号玩家出牌：1个柠檬+2个香蕉
Animal 0 		      # 2号玩家出牌：猴子
Fruit 4 2 2 2 2 	# 0号玩家出牌：4个樱桃
Ring 2 			      # 2号玩家按铃：按铃失败，给0, 1号玩家各一张牌
Fruit 3 0 0 0		  # 2号玩家出牌：3个香蕉，盖住上一张牌【猴子】
Fruit 2 0 0 		  # 0号玩家出牌：2个香蕉，盖住上一张牌【4个樱桃】
Ring 2 			      # 2号玩家按铃：按铃失败，给0, 1号玩家各一张牌
Animal 2 		      # 2号玩家出牌：猪，盖住上一张牌【3个香蕉】
Ring 0			      # 0号玩家按铃：按铃成功，获得场上的6张牌，开始下一轮游戏
Animal 2		      # 0号玩家出牌：猪，游戏终止
样例输入
3 13
Fruit 5 0 0 0 0 0
Ring 0
Ring 1
Fruit 3 3 0 0
Animal 0
Fruit 4 2 2 2 2
Ring 2
Fruit 3 0 0 0
Fruit 2 0 0
Ring 2
Animal 2
Ring 0
Animal 2
样例输出
10000006
9999999
9999994
*/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int N, K;

class Card{
public:
    vector<int> nums;
    Card(){nums.resize(7, 0);}
    // 0香蕉 1草莓 2樱桃 3柠檬 4猴子 5大象 6猪
};
vector<Card*> board;
int allCards = 0;

class Player{
public:
    int id, hold; // 玩家ID, 拥有几张牌
    Card show;
    Player(int _id, int _hold): id(_id), hold(_hold){}
    int check(int player){
        int fruit = 0, cards = 0;
        bool flag = false;
        vector<int> vtr(7, 0);
        for(Card* c : board)
            if(c){
                ++ cards;
                for(int i = 0;i < 7; ++ i)
                    vtr[i] += c->nums[i];
            }
        for(int i = 0;i < 4; ++ i){
            fruit += vtr[i];
            if(vtr[i] == 5){
                flag = true;
                break;
            }
        }
        flag |= (vtr[4] && fruit && !vtr[3]);
        flag |= (vtr[5] && fruit && !vtr[1]);
        flag |= (vtr[6] && fruit);
        if(flag) return cards;
        else return -1;
    }
};
vector<Player*> players;

int curPlayerID = 0, tag = 0, tmp = 0;
string action;

void init(){
    for(int i = 0;i < board.size(); ++ i)
        board[i] = NULL;
}

int main(){
    cin >> N >> K;
    board.resize(N);
    for(int i = 0; i < N; ++ i)
        players.push_back(new Player(i, 10000000));
    init();
    for(int i = 0; i < K; ++ i){
        cin >> action >> tag;
        if(action == "Fruit"){
            Card *card = new Card;
            for(int j = 0;j < tag; ++ j){
                cin >> tmp;
                card->nums[tmp] ++;
            }
            board[curPlayerID] = card;
            players[curPlayerID]->hold --;
            curPlayerID = (curPlayerID + 1) % N;
            ++ allCards;
        }
        else if(action == "Animal"){
            Card *card = new Card;
            card->nums[tag + 4] ++;
            board[curPlayerID] = card;
            players[curPlayerID]->hold --;
            curPlayerID = (curPlayerID + 1) % N;
            ++ allCards;
        }
        else if(action == "Ring"){
            if(players[tag]->check(tag) != -1){
                players[tag]->hold += allCards;
                allCards = 0;
                init();
            }
            else{
                for(int j = 0;j < N; ++ j){
                    if(j != tag){
                        players[j]->hold ++;
                    }
                }
                players[tag]->hold -= (N - 1);
            }
            curPlayerID = tag;
        }
    }
    for(int i = 0;i < N; ++ i)
        cout << players[i]->hold << endl;
    return 0;
}
