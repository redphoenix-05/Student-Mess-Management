#include<iostream>
#include<vector>
#include<string>
using namespace std;
class student;
class studentrecord;
class house;
class houserecord;
class student{
    string name;
    int ID;
public:
    student(){}
    student(string n, int i){
        name=n;
        ID=i;
    }
    int getid(){
        return ID;
    }
    friend class studentrecord;
};
class studentrecord{
    vector<pair<student, int>>record;
public:
    studentrecord(){}
    bool exists(int id, int houseid){
        bool exist=false;
        auto it=record.begin();
        for(auto elem:record)
        {
            if(elem.first.getid()==id &&  elem.second==houseid){
                exist=true;
                record.erase(it);
                break;
            }
            it++;
        }
        return exist;
    }
    void addstudent(student stu, int houseId){
        record.push_back({stu, houseId});
    }
    void rent(studentrecord &s, houserecord &h);
    void leave(studentrecord &s, houserecord &h);
};
class house{
    int id,water,floor,cost,distance;
    string hname;
    bool vacant;
public:
    friend class houserecord;
    house(){}
    house(int i, int l, int f, int p, int d, string n,  bool e){
        id=i;
        water=l;
        floor=f;
        cost=p;
        distance=d;
        hname=n;
        vacant=e;
    }
    int getid(){
        return id;
    }
    bool getvacant(){
        return vacant;
    }
    void setvacant(bool what){
        vacant=what;
    }
    void show(){
        cout << id << "\t\t" << ((water==1)?"Good":"Salty") << "\t" << floor << "\t" << cost << "\t";
        cout << ((vacant)?"Yes":"NO") <<"\t" << distance << "\t " << hname << endl; 
    }
    friend void query(houserecord);
};
class houserecord{
    vector<house>record;
    public:
        houserecord(){}
        void defaultadd(int i, int w, int f, int c, int d, string n){
            house temp( i , w , f , c , d, n,true);
            record.push_back(temp);
        }
        void showall(){
            cout<<"House Id\tWater\tFloor\tCost\tVacancy\tDistance House Name" << endl;
            for(auto elem:record)
            {
                elem.show();
            }
            cout << endl;
        }
        void addhouse(){
            int i,w,f,c,d;
            string n;
            cout << " -----------------------------" << endl;
            cout << "|>-       Add New House     -<|" << endl;
            cout << " -----------------------------" << endl;
            cout << "Enter House ID: ";
            cin >> i;
            cout << "Enter water condition[1(Good), 2(Salty)]: ";
            cin >> w;
            cout << "Enter floor: ";
            cin >> f;
            cout << "Enter cost: ";
            cin >> c;
            cout << "Enter distance: ";
            cin >> d;
            cout << "Enter House Name: ";
            cin >> n; 
            if(i<=0 || (w!=1 && w!=2) || f<0 || c<0 || d<=0)
            {
                cout << "Wrong input for adding house" << endl;
            }
            else
            {
                house h(i,w,f,c,d,n, true);
                record.push_back(h);
                cout << endl <<"House Registered Successfully!" << endl << endl;
            }
        }
        void removehouse(){
            int i,w,f,c;
            cout << " -----------------------------" << endl;
            cout << "|>-       Remove a House    -<|" << endl;
            cout << " -----------------------------" << endl;
            cout << "Enter house id: " ;
            cin >> i;
            cout << "Enter water condition[1(Good), 2(Salty)]: ";
            cin >> w;
            cout << "Enter floor: ";
            cin >> f;
            cout << "Enter cost: ";
            cin >> c;
            auto it=record.begin();
            for(auto elem:record)
            {
                if(elem.id==i && elem.water==w && elem.floor==f && elem.cost==c)
                {
                    record.erase(it);
                    cout<< endl << "House successfully removed!" << endl << endl;
                    return;
                }
                it++;
            }
            cout<< endl << "This house don't exist in the record" << endl << endl;
        }
        void setvacant(int i, bool what){
            for(auto &elem: record)
            {
                if(elem.getid()==i){
                    elem.setvacant(what);
                }
            }
        }
        bool isvacant(int i){
            for(auto elem: record)
            {
                if(elem.getid()==i && elem.getvacant())
                {
                    return true;
                }
            }
            return false;
        }
        friend void query(houserecord);
        void rent(studentrecord &s,houserecord &h);
        void leave(studentrecord &s,houserecord &h);
};
void rent(studentrecord &s, houserecord &h){
    int i, houseid; string n;
    cout << " -----------------------------" << endl;
    cout << "|>-       Rent a House      -<|" << endl;
    cout << " -----------------------------" << endl;
    cout<< "Enter Student Name: ";
    cin.ignore();
    cin >> n;
    cout << "Enter Student ID: ";
    cin >> i;
    cout << "Enter House ID: ";
    cin >> houseid;
    if(h.isvacant(houseid))
    {
        h.setvacant(houseid, false);
        student x(n,i);
        s.addstudent(x,houseid);
        cout << endl << "House rented successfully!" << endl << endl;
    }
    else
    {
        cout << endl << "This house is not available." << endl << endl;
    }
}
void leave(studentrecord &s, houserecord &h){
    int i, houseid;
    cout << " -----------------------------" << endl;
    cout << "|>-        Leave house      -<|" << endl;
    cout << " -----------------------------" << endl;
    cout << "Enter student id: ";
    cin >> i;
    cout << "Enter house id: ";
    cin >> houseid;
    if(s.exists(i, houseid))
    {
        h.setvacant(houseid,true);
        cout << endl << "Thank you for using our system." << endl << endl;
    }
    else
    {
        cout << "The house is not rented." << endl << endl;
    }
    cout << endl;
}
void query(houserecord h){
    int w,f,maxCost;
    cout << " -----------------------------" << endl;
    cout << "|>-       Search House      -<|" << endl;
    cout << " -----------------------------" << endl;
    cout << "Water condition: [1(Good), 2(Salty)] : ";
    cin >> w;
    cout << "Floor: ";
    cin >> f;
    cout << "Maximum cost: ";
    cin >> maxCost;
    bool found=false;
    cout << endl << "-------------------------------------------------" << endl;
    cout << "House Id\tWater\tFloor\tCost\tVacancy\tDistance\tHouse Name" << endl;
    for(auto elem: h.record)
    {
        if(elem.water==w && elem.floor==f && elem.cost<=maxCost)
        {
            if(elem.vacant)
            {
                found=true;
                elem.show();
            }
        }
    }
    if(!found)
    {
        cout << endl << "No house found!" << endl;
    }
    cout << "-------------------------------------------------\n";
    cout << endl;
}
int main(){
    houserecord hr;
    studentrecord sr;
    hr.defaultadd(101,1,3,4500,105,"JAHARAT MAHAL");
    hr.defaultadd(102,2,5,1500,100,"LIGHT HOUSE");
    hr.defaultadd(103,2,2,2500,200,"WHITE HOUSE");
    hr.defaultadd(104,1,3,3500,300,"KHAN LODGE");
    hr.defaultadd(105,1,1,3000,200,"SOPNO DIP");
    hr.defaultadd(201,2,5,1500,150,"SAKIB PALACE");
    while(true)
    {
        cout << "********************************" << endl;
        cout << "* KUET Student Mess Management *" << endl;
        cout << "********************************" << endl << endl;
        cout << "| 1.Register new house\n| 2.Show All house" << endl;
        cout << "| 3.Remove House\n| 4.Search House" << endl;
        cout << "| 5.Rent house\n| 6.Leave house\n| 0.Exit" << endl << endl;
        cout << "Your Choice: ";
        int i;
        cin >> i;
        if(i==1){
            hr.addhouse();
        }
        else if(i==2){
            hr.showall();
        }
        else if(i==3){
            hr.removehouse();
        }
        else if(i==4){
            query(hr);
        }
        else if(i==5){
            rent(sr,hr);
        }
        else if(i==6){
            leave(sr,hr);
        }
        else if(i==0){
            cout<<"Thanks for using our service" << endl;
            break;
        }
        else{
            cout<<"Error! Invalid Input." << endl;
        }
    }
    return 0;
}