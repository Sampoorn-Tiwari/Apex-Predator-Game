#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;
//Using color codes to make game interactive
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string RESET = "\033[0m";
const string ORANGE = "\033[38;5;208m";
const string BROWN  = "\033[38;5;94m";
const string PURPLE = "\033[38;5;129m";

void validint(int &x);//Created this function for valid inputs only in integer data types
void validstring(string &s);//Created this function for valid inputs only in string data types

class BaseApex{           //Abstract class
    protected:
    string name;
    int attack;
    int hp;
    int maxhp;
    int lastmove=0;
    vector<string> abilities; 

    public:
    BaseApex(string name,int attack,int hp,int maxhp,vector<string> abilities){
        this->name=name;
        this->attack=attack;
        this->hp=hp;
        this->maxhp=maxhp;
        this->abilities=abilities;
    }
    
    friend ostream& operator<<(ostream& ,const BaseApex& apex);//Operator Overloading

    virtual int gettertypeid() const=0;//Assigning numbers for different type of elemetns to be able to differentiate them by their element type
    
    virtual void printer(ostream& out) const{  
        string elementname;
        int id=gettertypeid();
        
        if(id==1) elementname=ORANGE+"Fire"+RESET;
        else if(id==2) elementname=BLUE +"Water"+RESET;
        else if(id==3) elementname=YELLOW+"Electric"+RESET;
        else if(id==4) elementname=GREEN+"Grass"+RESET;
        else if(id==5) elementname=PURPLE+"Flying"+RESET;
        else if(id==6) elementname=BROWN+"Ground"+RESET;

        out<<"Apex type: "<<elementname<<endl;
        out<<"apex Name: "<<name<<endl;
        out<<"Attack : "<<attack<<endl;
        out<<"Hitpoints : "<<maxhp<<endl<<endl;

         for(int i=0;i<abilities.size();i++){
            out<<"Ability "<<i+1<<" :"<<abilities[i]<<endl<<endl;

            
        }
        cout<<"----------------------------"<<endl<<endl;
    };
    
    

    //Getters
    string getrawname() const { return name; } //to give names to file as if i gave colored names to file, file would have corrupted
    string getname() const {
        string c = RESET;
        int id = gettertypeid();
        
        if(id==1) c = ORANGE; //assigning colors based in their element
        else if(id==2) c = BLUE;
        else if(id==3) c = YELLOW;
        else if(id==4) c = GREEN;
        else if(id==5) c = PURPLE;
        else if(id==6) c = BROWN;
        
        return c + name + RESET;
    }
    int getattack() const { return attack; }
    int getmaxhp() const { return maxhp; } //stores max hitpoints of a apex predator and is not altered in game
    int gethp() const { return hp; } //this hp variable is used for fights
    const vector<string>& getabilities() const { return abilities; }
    
    bool isfainted(){ //used for deciding who wins
        if(gethp()==0)
        return true;
        else
        return false;
    }
    int randomdamage(int attack){ //used to introduce rng in attack damage 
        int lowervalue=(int)(0.70*attack);
        int highervalue=(int)(1.2*attack);
        if(highervalue<lowervalue) highervalue=lowervalue;
        int newattack=lowervalue+(rand()%(highervalue-lowervalue+1));
        return newattack;
    }
    int doingdamage(BaseApex* attacker){ //player vs player damaging function
        cout<<"1."<<attacker->abilities[0]<<"   "<<"2."<<attacker->abilities[1]<<endl;
        cout<<"3."<<attacker->abilities[2]<<"   "<<"4."<<attacker->abilities[3]<<endl;
        cout<<"Simply type the nummber before attack to select it"<<endl;
        int attackchoose;
        while(true){
        validint(attackchoose);
        if(attackchoose>4||attackchoose<1)
        {
            cout<<"Invalid move selection renter";
            continue;
        }
        if(attackchoose==lastmove)
        {
            cout<<"You used this move last time, a move cannot be used twice renter "<<endl;
            continue;
        }
        break;
        }
        lastmove=attackchoose;
        int rngdmg=randomdamage(attack);
        int damage=rngdmg;
        if(attackchoose==1){ return 0.25*damage; }
        if(attackchoose==2){ return 0.40*damage; }
        if(attackchoose==3){ return 0.60*damage; }
        if(attackchoose==4){ return 0.80*damage; }
    }
    int computerdoingdamage(){ //player vs computer damaging function
        cout<<"Computer is thinking......"<<endl;
        int movechoice;
        while(true){
        movechoice=(rand()%4)+1; //we assign computer random move by using rand() function
        if(movechoice==lastmove)
        continue;
        break;
        
        }
        lastmove=movechoice;
        cout<<"Computer chose to play :";
        
        if(movechoice==1) cout<<abilities[0]<<endl;
        if(movechoice==2) cout<<abilities[1]<<endl;
        if(movechoice==3) cout<<abilities[2]<<endl;
        if(movechoice==4) cout<<abilities[3]<<endl;

        int computerrngdmg=randomdamage(attack);

        if(movechoice==1){ return 0.25*computerrngdmg; }
        if(movechoice==2){ return 0.40*computerrngdmg; }
        if(movechoice==3){ return 0.60*computerrngdmg; }
        if(movechoice==4){ return 0.80*computerrngdmg; }

        }
    void takingdamage(int damage){ //used to give damage to defenders
        hp=hp-damage;
        if(hp<0)
        hp=0;
    }
    void heal(){ //called after each battle to reset hitpoints to max
        hp=maxhp;
        lastmove=0;
    }
    virtual ~BaseApex() {} //virtual destructor
};
//Operator Overloading
ostream& operator<<(ostream& out,const BaseApex& apex){
    apex.printer(out);
    return out;
}
//Elemental Classes

//Fire Type
class FireApex : public BaseApex{
    public:
    FireApex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 1; }
};
//Water Type
class WaterApex : public BaseApex{
    public:
    WaterApex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 2; }
};
//Electric Type
class ElectricApex : public BaseApex{
    public:
    ElectricApex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 3; }
};
//Grass Type
class GrassApex : public BaseApex{
    public:
    GrassApex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 4; }
};
//Flying Type
class FlyingApex : public BaseApex{
    public:
    FlyingApex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 5; }
};
//Ground Type
class Groundapex : public BaseApex{
    public:
    Groundapex(string name,int attack,int hp,int maxhp,vector<string> abilities):BaseApex(name,attack,hp,maxhp,abilities){}
    int gettertypeid()const override{ return 6; }
};
void validint(int &x){
    while(true){
        cin>>x;
        if(!cin.fail())
        {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
        }

        cout<<"Invalid input enter again";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void validstring(string &s){
    while(true){
        int flag=0;
        getline(cin,s);

        if(s.empty()){
            cout<<"Input cannot be empty renter";
            continue;
        }

        for(auto& x:s){
            if(!isalpha(x)&&!isspace(x))
            flag=1;
            
        }
        if(flag==0)
        break;
        else{
            cout<<"Invalid Input Enter Again :";
        }
    }
}
void inputingdata(vector<BaseApex*>& apex,int &c){ //used for registering apex predators
    string name;int attack;int maxhp;vector<string> ability(4);
     cout<<"Enter name of your apex :";validstring(name);cout<<endl;
     cout<<"Enter attack : ";validint(attack);cout<<endl;
     cout<<"Enter hitpoints : ";validint(maxhp);cout<<endl;
     for(int i=0;i<4;i++){
        cout<<"Enter ability number "<<i+1<<" : ";
        validstring(ability[i]);
     }
    if(c==1) apex.push_back(new FireApex(name,attack,maxhp,maxhp,ability));
    if(c==2) apex.push_back(new WaterApex(name,attack,maxhp,maxhp,ability));
    if(c==3) apex.push_back(new ElectricApex(name,attack,maxhp,maxhp,ability));
    if(c==4) apex.push_back(new GrassApex(name,attack,maxhp,maxhp,ability));
    if(c==5) apex.push_back(new FlyingApex(name,attack,maxhp,maxhp,ability));
    if(c==6) apex.push_back(new Groundapex(name,attack,maxhp,maxhp,ability));
}
void registerapex(vector<BaseApex*>& apex ){ //we choose element type before registering
    int elementchoosing;
    while(true){
        cout<<"Press 1 to register fire type"<<endl;
        cout<<"Press 2 to register water type"<<endl;
        cout<<"Press 3 to register electric type"<<endl;
        cout<<"Press 4 to register grass type"<<endl;
        cout<<"Press 5 to register flying type"<<endl;
        cout<<"Press 6 to register ground type"<<endl;
        cout<<"press 0 to quit registering"<<endl;
        validint(elementchoosing);
        if(elementchoosing==0)
        break;
        inputingdata(apex,elementchoosing);
    }
}
void printapexdex(vector<BaseApex*>& printapex){ //to view apexdex
    if(printapex.empty())
    {
        cout<<"ApexDex is empty"<<endl;
    }
    for(auto p:printapex)
    {
        cout<<*p;
    }
}
//file handling usage to save data using CSV method
void saveApexDex(const vector<BaseApex*>& apexList) {  //saving file
    if (apexList.empty()) {
        cout << "Nothing to save!" << endl;
        return;
    }

    ofstream file("ApexData.txt"); 
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (const auto* apex : apexList) {
        file << apex->gettertypeid() << ",";
    
        file << apex->getrawname() << ","
             << apex->getattack() << ","
             << apex->getmaxhp() << "," 
             << apex->getmaxhp() << ","; 

        
        const vector<string>& abs = apex->getabilities();
        for (int i=0;i<4;i++) {
            file<< abs[i];
            if (i<3) file << ","; 
        }
        
        file << endl; 
    }
    
    file.close();
    cout << "Data saved successfully to ApexData.txt!" << endl;
}
void loadApexDex(vector<BaseApex*>& apexList) {
    ifstream file("ApexData.txt"); // Open in Read Mode
    
    if (!file) {
        return; 
    }

    string line,name,ab1,ab2,ab3,ab4;
    int id,atk,hp,maxhp;
    char comma;

    while (file>>id) {
        file>>comma;
        
        getline(file,name,','); 
        
        file>>atk>>comma;
        file>>hp>>comma;
        file>>maxhp>>comma; 

        // Read abilities
        getline(file, ab1, ',');
        getline(file, ab2, ',');
        getline(file, ab3, ',');
        getline(file, ab4); 
        
        vector<string> abilities = {ab1, ab2, ab3, ab4};

        //Create the correct object based on ID
        if (id==1) apexList.push_back(new FireApex(name, atk, hp, maxhp, abilities));
        else if (id==2) apexList.push_back(new WaterApex(name, atk, hp, maxhp, abilities));
        else if (id==3) apexList.push_back(new ElectricApex(name, atk, hp, maxhp, abilities));
        else if (id==4) apexList.push_back(new GrassApex(name, atk, hp, maxhp, abilities));
        else if (id==5) apexList.push_back(new FlyingApex(name, atk, hp, maxhp, abilities));
        else if (id==6) apexList.push_back(new Groundapex(name, atk, hp, maxhp, abilities));
    }
    
    file.close();
    if(apexList.size()>0) {
        cout << "Loaded " << apexList.size() << " Apex Predators from save file!" << endl;
    }
} //file handling ends

pair<BaseApex*,BaseApex*> selectingapex(vector<BaseApex*>& choosingapex,string &ID1,string &ID2){ //for user selection 
    cout<<"Player 1 enter your name : ";validstring(ID1);
    cout<<"Player 2 enter your name : ";validstring(ID2);
    ID1=BLUE+ID1+RESET;
    ID2=RED+ID2+RESET;
    cout<<"To start the battle first pick apex predators for yourself"<<endl;
    while(true){
    cout<<ID1<<" choose your battle partner :"<<endl;
    cout<<"Apex data is in this format -> ( Name, Hitpoints, Attack ), you need to enter position of the apex predator to choose it."<<endl;
    cout<<"------------------------"<<endl;
    for(int i=0;i<choosingapex.size();i++){
        cout<<"Apex predator "<<i<<" data : "<<choosingapex[i]->getname()<<" "<<choosingapex[i]->getmaxhp()<<" "<<choosingapex[i]->getattack()<<endl;
    }
    cout<<"------------------------"<<endl;
    int choice1;
    validint(choice1);
    if(choice1<0||choice1>=choosingapex.size()){ cout<<"Invalid input enter again ";continue;}

    cout<<ID2<<" choose your battle partner :"<<endl;
    cout<<"Apex data is in this format -> ( Name, Hitpoints, Attack ), you need to enter position of the apex predator to choose it."<<endl;
    for(int i=0;i<choosingapex.size();i++){
        cout<<"Apex predator "<<i<<" data : "<<choosingapex[i]->getname()<<" "<<choosingapex[i]->getmaxhp()<<" "<<choosingapex[i]->getattack()<<endl;
    }
    int choice2;
    validint(choice2);
    if(choice2<0||choice2>=choosingapex.size()){ cout<<"Invalid input enter again "<<endl;continue;}
    if(choosingapex[choice1]==choosingapex[choice2]){ cout<<"Same apex predators not allowed renter"<<endl;continue;}
    return {choosingapex[choice1],choosingapex[choice2]};
    
}
}
float effectivenesschecker(int atkid,int defid){ //assigning damage multipliers to predators during battle based on elemental advantage 
    float multiplier=1.0;
    if(atkid==1){
        if(defid==4||defid==3) multiplier=1.5;
        if(defid==2) multiplier=0.5;
    }
    else if(atkid==2){
        if(defid==1) multiplier=1.5;
        if(defid==4) multiplier=0.5;
    }
    else if(atkid==3){
        if(defid==5||defid==2) multiplier=1.5;
        if(defid==6) multiplier=0.5;
    }
    else if(atkid==4){
        if(defid==2||defid==3) multiplier=1.5;
        if(defid==1) multiplier=0.5;
    }
    else if(atkid==5){
        if(defid==6) multiplier=1.5;
        if(defid==3) multiplier=0.5;
    }
    else if(atkid==6){
        if(defid==3) multiplier=1.5;
        if(defid==5) multiplier=0.5; 
    }
    return multiplier;
}
int battlemode(BaseApex* fighter1,BaseApex* fighter2,string player1,string player2){ //this function performs battle for PvP
    cout<<endl<<"-----------------------------"<<endl;
    cout<<"Left side we have "<<player1<<" apex "<<fighter1->getname()<<endl;
    cout<<"Right side we have "<<player2<<" apex "<<fighter2->getname()<<endl;
    cout<<fighter1->getname()<<"  VS  "<<fighter2->getname()<<endl;
    cout<<"***START!!!!***"<<endl;
    cout<<player1<<" "<<"STARTS!!!"<<endl;
    int turn=1;
    while(!fighter1->isfainted() && !fighter2->isfainted()){
        BaseApex* attacker;
        BaseApex* defender;
        if(turn%2!=0){
            attacker=fighter1;
            defender=fighter2;
        }
        else{
            attacker=fighter2;
            defender=fighter1;
        }
        float effectiveness=effectivenesschecker(attacker->gettertypeid(),defender->gettertypeid());
        cout<<attacker->getname()<<" choose your move : "<<endl;
        int damage=(int)(effectiveness*attacker->doingdamage(attacker));
        defender->takingdamage(damage);
        if(effectiveness==0.5){ cout<<"The attack was not effective you have elemental disadvantage !!!"<<endl;}
        if(effectiveness==1.5){ cout<<RED+"The attack was super effective you have elemental advantage !!!"+RESET<<endl;}
        cout<<attacker->getname()<<" dealt "<<damage<<" damage"<<endl;
        cout<<defender->getname()<<" hp decreased to "<<defender->gethp()<<endl;

        turn++;
        cout<<BLUE+"----------------------"+RESET<<endl;
    }
    
    if(fighter2->gethp()==0){
    fighter1->heal();
    fighter2->heal();
    return 1;
    }
    else if(fighter1->gethp()==0){
    fighter1->heal();
    fighter2->heal();
    return 2;
    }
}
pair<BaseApex*,BaseApex*> selectingapexcomputermode(vector<BaseApex*>& apex,string playername){ //Player VS Computer selection function
    cout<<"Player enter your name : ";validstring(playername);
    playername=BLUE+playername+RESET;
    cout<<"To start the battle first pick apex predators for yourself"<<endl;
    while(true){
    cout<<playername<<" choose your battle partner :"<<endl;
    cout<<"Apex data is in this format -> ( Name, Hitpoints, Attack ), you need to enter position of the apex predator to choose it."<<endl;
    for(int i=0;i<apex.size();i++){
        cout<<"Apex predator "<<i<<" data : "<<apex[i]->getname()<<" "<<apex[i]->getmaxhp()<<" "<<apex[i]->getattack()<<endl;
    }
    int choice1;
    validint(choice1);
    if(choice1<0||choice1>=apex.size()){ cout<<"Invalid input enter again ";continue;}
    int choice2=-1;
    
    for(int i=0;i<apex.size();i++){  //with this we always try to give computer elemental advantage to make battle harder for player
        bool iscounter=false;
        if(apex[choice1]->gettertypeid()==2 && apex[i]->gettertypeid()==4) iscounter=true;;
        if(apex[choice1]->gettertypeid()==1 && apex[i]->gettertypeid()==2) iscounter=true;;
        if(apex[choice1]->gettertypeid()==3 && apex[i]->gettertypeid()==6) iscounter=true;;
        if(apex[choice1]->gettertypeid()==4 && apex[i]->gettertypeid()==1) iscounter=true;;
        if(apex[choice1]->gettertypeid()==5 && apex[i]->gettertypeid()==3) iscounter=true;;
        if(apex[choice1]->gettertypeid()==6 && apex[i]->gettertypeid()==5) iscounter=true;;

        if(iscounter) {choice2=i;break;}
        else if(choice2==-1){
            choice2=(choice1+1)%apex.size();
        }
    }
    cout<<"Computer chose "<<apex[choice2]->getname()<<endl;
    return {apex[choice1],apex[choice2]};
    }

}
int computerbattlemode(BaseApex* fighter1,BaseApex* fighter2,string playername){ //battle function for Player VS computer
     cout<<endl<<"-----------------------------"<<endl;
    cout<<"Left side we have "<<playername<<" apex "<<fighter1->getname()<<endl;
    cout<<"Right side we have computer apex "<<fighter2->getname()<<endl;
    cout<<fighter1->getname()<<"  VS  "<<fighter2->getname()<<endl;
    cout<<"***START!!!!***"<<endl;
    cout<<playername<<" "<<"start the battle"<<endl;
    int turn=1;
    while(!fighter1->isfainted() && !fighter2->isfainted()){
        BaseApex* attacker;
        BaseApex* defender;
        if(turn%2!=0){
            attacker=fighter1;
            defender=fighter2;

        float effectiveness=effectivenesschecker(attacker->gettertypeid(),defender->gettertypeid());
        cout<<attacker->getname()<<" choose your move : "<<endl;
        int damage=(int)(effectiveness*attacker->doingdamage(attacker));
        defender->takingdamage(damage);
        if(effectiveness==0.5){ cout<<"The attack was not effective you have elemental disadvantage !!!"<<endl;}
        if(effectiveness==1.5){ cout<<RED+"The attack was super effective you have elemental advantage !!!"+RESET<<endl;}
        cout<<attacker->getname()<<" dealt "<<damage<<" damage"<<endl;
        cout<<defender->getname()<<" hp decreased to "<<defender->gethp()<<endl;
        }
        else{
            attacker=fighter2;
            defender=fighter1;

            cout<<"Computer's turn"<<endl;
            float effectiveness=effectivenesschecker(attacker->gettertypeid(),defender->gettertypeid());
            int damage=(int)(effectiveness*attacker->computerdoingdamage());
            defender->takingdamage(damage);
            if(effectiveness==0.5){ cout<<"The attack was not effective "<<endl;}
            if(effectiveness==1.5){ cout<<"The attack was super effective "<<endl;}
            cout<<attacker->getname()<<" dealt "<<damage<<" damage"<<endl;
            cout<<defender->getname()<<" hp decreased to "<<defender->gethp()<<endl;  
        }
        turn++;
        cout<<BLUE+"----------------------"+RESET<<endl;
    }
    if(fighter2->gethp()==0){
    fighter1->heal();
    fighter2->heal();
    return 1;
    }
    else if(fighter1->gethp()==0){
    fighter1->heal();
    fighter2->heal();
    return 2;
    }
}
int main(){
    srand(time(0)); //everytime code runs different time --> different seed --> rand() starts at different position each time
    vector<BaseApex*> ApexDex;
    loadApexDex(ApexDex);// loading from file before program runs
    int choice;
    cout<<ORANGE+"---Welcome to the Apex Arena---"+RESET<<endl;
    while(true){
        cout<<BLUE+"Enter 1 to register Predators [ONLY ADMIN CAN ACCESS THIS]"<<endl; //main menu
        cout<<"Enter 2 to view the Apexdex"<<endl;
        cout<<"Enter 3 to play Player versus Player mode"<<endl;
        cout<<"Enter 4 to play with computer"<<endl;
        cout<<"Enter 5 to know about battles"<<endl;
        cout<<"Enter 0 to exit the Apex Arena"<<endl;
        cout<<"---------------------------"+RESET<<endl;
        validint(choice);
        if(choice<0||choice>5){
            cout<<RED+"Invalid input enter again "+RESET<<endl;
            continue;
        }
        if(choice==0)
        {
        saveApexDex(ApexDex);// saving to file once program ends
        for(auto& cl:ApexDex)
        delete cl;
        break;
        }

        if(choice==1){
            string password;
            while(true){
                cout<<"Enter password to confirm you are admin"; //registering is password protected well not really as anyone can edit if statement lol
                validstring(password);
                if(password=="apexarenaadminopen")
                {
                    registerapex(ApexDex);
                    break;
                }
                
                else{
                    cout<<"Invalid Password renter"<<endl;
                    break;
                }

            }
        }
        if(choice==2){
            printapexdex(ApexDex);
        }
        if(choice==3){
            string playerid1,playerid2;
            if(ApexDex.size()<2){ cout<<"Not enough apex predators registered, register first to battle";continue;}
            pair<BaseApex*,BaseApex*> fighters=selectingapex(ApexDex,playerid1,playerid2);
            BaseApex* figther1;
            BaseApex* figther2;
            figther1=fighters.first;
            figther2=fighters.second;
            int winner= battlemode(figther1,figther2,playerid1,playerid2); 

            if(winner==1){
                cout<<"Congratulations "<<playerid1<<" you win"<<endl;
                cout<<playerid2<<" Better luck next time"<<endl;
            }
            else if(winner==2){
                cout<<"Congratulations "<<playerid2<<" you win"<<endl;
                cout<<playerid1<<" Better luck next time"<<endl;
            }
        }
        if(choice==4){
            string playerid;
            if(ApexDex.size()<2){ cout<<"Not enough apex predators registered, register first to battle";continue;}
            pair<BaseApex*,BaseApex*> playerandcomputer=selectingapexcomputermode(ApexDex,playerid);
            BaseApex* predator1=playerandcomputer.first;
            BaseApex* predator2=playerandcomputer.second;
            int winner= computerbattlemode(predator1,predator2,playerid);
            if(winner==1){
                cout<<BLUE+"---------------------"+RESET<<endl;
                cout<<"Congratulations "<<playerid<<" you win"<<endl;
                cout<<"Computer lost"<<endl;
                cout<<BLUE+"---------------------"+RESET<<endl;
            }
            else if(winner==2){
                cout<<BLUE+"---------------------"+RESET<<endl;
                cout<<"Computer won"<<endl;
                cout<<playerid<<" Better luck next time"<<endl;
                cout<<BLUE+"---------------------"+RESET<<endl;
            }
        }
        if(choice==5){
            cout<<RED+"---Game Manual---"+RESET<<endl;
            cout<<RED+"------------------"+RESET<<endl;
            cout<<"1.All Apex Predators belong to some element type"<<endl;
            cout<<"2.Elemental advantage increaes your damage dealt by 1.5 times of your apex predator attack"<<endl;
            cout<<"3.Elemental disadvantage decreases your damage dealt to 0.5 times of your apex predator attack"<<endl;
            cout<<"4.Each apex predator have 4 abilities."<<endl;
            cout<<"5.Ability 1st and 2nd are normal attacks of apex predator"<<endl;
            cout<<"6.Ability 3rd and 4th are heavy attacks of apex predator"<<endl;
            cout<<RED+"------------------"+RESET<<endl;
            cout<<"Elemental effectiveness :"<<endl;
            cout<<ORANGE+"FIRE"+RESET<<" TYPE Strong Against (1.5x Damage): Grass, Electric Weak Against (0.5x Damage): Water"<<endl;
            cout<<BLUE+"WATER"+RESET<<" TYPE Strong Against (1.5x Damage): Fire Weak Against (0.5x Damage): Grass"<<endl;
            cout<<YELLOW+"ELECTRIC"+RESET<<" TYPE Strong Against (1.5x Damage): Flying, Water Weak Against (0.5x Damage): Ground"<<endl;
            cout<<GREEN+"GRASS"+RESET<<" TYPE Strong Against (1.5x Damage): Water, Electric Weak Against (0.5x Damage): Fire"<<endl;
            cout<<PURPLE+"FLYING"+RESET<<" TYPE Strong Against (1.5x Damage): Ground Weak Against (0.5x Damage): Electric"<<endl;
            cout<<BROWN+"GROUND"+RESET<<" TYPE Strong Against (1.5x Damage): Electric Weak Against (0.5x Damage): Flying"<<endl;
        }
    }
    cout<<ORANGE+"Thanks for playing see you later"<<endl;
    cout<<"-----------------------------"+RESET<<endl;
    return 0;
    
}