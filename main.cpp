//this program is the 21 game. there are two players--player and the computer. the one who get the biggest number
//less than or equal to 21 wins.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

//this function is a mapping process. we convert the number to the cards.
string mapping(int n)
{
   int number;
   string match;
   switch(n/13)
   {case 0:match="hearts ";break;
   case 1:match="diamond ";break;
   case 2:match="spades ";break;
   case 3:match="club ";break;}
   number=n%13+1;
   if (number==1){
       match=match+"A";
   }
   if (number==10){
       match=match+"10";
   }
   if (number==11){
       match=match+"J";
   }
   if (number==12){
       match=match+"Q";
   }
   if (number==13){
       match=match+"K";
   }
   if (number<=10&&number>=2){
    match=match+(char)(number+'0');
   }
   return match;
}

//this function calculates the card's point.
double point(int n)
{
    int mod;
    mod=n%13+1;
    if (mod<=10){
        return mod;
    }
    else
    {
        return 0.5;
    }
}

//generate random number between 0 and 51.
int deal(int a[])
{
    int card;
    srand(time(NULL));
    card=rand()%52;
    while(a[card]==0)
    {
        card=rand()%52;
    }
    a[card]=0;
    return card;
}

//clean is the riffle process.
void clean(int a[],int b[])
{
    int i;
    for (i=0;i<=51;++i)
    {
        a[i]=1;
    }
    int j;
    for (j=0;j<=51;++j)
    {
        a[i]=0;
    }
}

//this is the game process.
void one_game_process()
{
    int poker[52];//the array of the pokers.
    int used_poker[52];//the array of the used pokers.
    double counter_for_pla=0,counter_for_com=0;//the points of player and computer.
    int poker_for_pla=0,poker_for_com=0;//the number of player's pokers and computer's pokers.
    int first,second;//the first two cards.
    string more;
    bool input_valid;
    clean(poker,used_poker);//clean is the riffle process.
    first=deal(poker);//deal is to give out the card.
    second=deal(poker);
    cout<<"the player's role"<<endl;
    cout<<"the cards of player"<<" "<<mapping(first)<<" , "<<mapping(second)<<endl;
    cout<<""<<endl;
    counter_for_pla=counter_for_pla+point(first)+point(second);
    poker_for_pla=poker_for_pla+2;
    used_poker[0]=first;
    used_poker[1]=second;
    more='D';//we don't know whether user want to continue.
    while ((more!="n")&&(more!="N"))
    {
    	input_valid=0;
        while(!input_valid)
        {
			cout<<"Continue?(y/n):";
			cin>>more;
			try
	        {
	        	if((more!="N")&&(more!="n")&&(more!="Y")&&(more!="y")){
	        		throw more;
			   }
				else{
					input_valid=1;
				}
			}
			catch(string &wrong)
			{
				input_valid=0;
			}
		}
        if (more=="y"||more=="Y")
        {
            int another;
            another=deal(poker);
            poker_for_pla++;
            used_poker[poker_for_pla-1]=another;
            cout<<"another poker:";
            int i;
            for (i=0;i<poker_for_pla;++i)
            {
                cout<<mapping(used_poker[i])<<" , ";
            }
            cout<<""<<endl;
            counter_for_pla=counter_for_pla+point(another);
            if (counter_for_pla>21){
                cout<<"The computer wins."<<endl;
                return;
            }
        }
    }
    first=deal(poker);
    second=deal(poker);
    cout<<"the computer's role"<<endl;
    cout<<"the cards of computer"<<" "<<mapping(first)<<" , "<<mapping(second)<<endl;
    cout<<""<<endl;
    counter_for_com=counter_for_com+point(first)+point(second);
    poker_for_com=poker_for_com+2;
    used_poker[poker_for_pla]=first;
    used_poker[poker_for_pla+1]=second;
    while ((counter_for_com<counter_for_pla)||((counter_for_com==counter_for_pla)&&(poker_for_com<=poker_for_pla)))
    {
        int another;
        another=deal(poker);
        poker_for_com++;
        used_poker[poker_for_pla+poker_for_com-1]=another;
        cout<<"another poker:";
        int i;
        for (i=poker_for_pla;i<poker_for_pla+poker_for_com;++i)
        {
            cout<<mapping(used_poker[i])<<" , ";
        }
        cout<<""<<endl;
        counter_for_com=counter_for_com+point(another);
        if (counter_for_com>21){
            cout<<"The player wins."<<endl;
            return;
        }
    }
    cout<<"The computer wins."<<endl;
    return;
}

int main()
{
    string conti="y";
    bool input_valid;
    while ((conti!="n")&&(conti!="N"))
    {
        if (conti=="y"||conti=="Y"){
            one_game_process();
            cout<<""<<endl;
        }
        input_valid=0;
        while (!input_valid)
        {
        	cout<<"Continue?(y/n):"<<endl;
			cin>>conti;
	        try
	        {
	        	if((conti!="N")&&(conti!="n")&&(conti!="Y")&&(conti!="y")){
	        		throw conti;
				}
				else{
					input_valid=1;
				}
			}
			catch(string &wrong)
			{
				input_valid=0;
			}
		}
    }
    return 0;
}
//there is no possibility of tie in my program. although the implementation is easy, in my program, the computer tries to win 
//the player with the lowest cost. if computer faces a tie, it will ask for more in order to win.
//I think this resembles our way to play the twenty-one point.
