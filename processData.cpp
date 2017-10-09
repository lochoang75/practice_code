/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"

L1List<char*>IDList;
struct Temp{
    char  id[10];
    time_t time;
};
//------------------------------------------------------------------
//------------------------------------------------------------------
//Event 0: Print all envent code in event list
//Void function
void print_event(ninjaEvent_t&data){
    cout<<data.code<<" ";
}
void Event0(){
    L1List<ninjaEvent_t> Event;
    char*name="events.txt";
    loadEvents(name,Event);
    Event.traverse(&print_event);   
    cout<<"\n";
}
//-----------------------------------------------------------------
//------------------------------------------------------------------
//Event 1:Print out first ninja in list
//void function
void Event1(L1List<NinjaInfo_t>&nList){
    cout<<nList.at(0).id;
    cout<<"\n";
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void Event2(L1List<NinjaInfo_t>&nList){
    cout<<nList.at(nList.getSize()-1).id;
    cout<<"\n";
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void traverse_id(char *&ID,void*ptr,bool &flag){
	char*idnList = new char();
	strcpy(idnList, ((Temp*)ptr)->id);
    if(!strcmp(ID,idnList)){
        flag=1;
    }
}
void create_id_list(NinjaInfo_t&data){
    Temp* p=new Temp;
    strcpy(p->id,data.id);
    bool flag=0;
    IDList.traverse(&traverse_id,p,flag);
    char*ptr=new char();
    strcpy(ptr,p->id);
    if(flag==0){
        IDList.push_back(ptr);
    }
}

void Event3(L1List<NinjaInfo_t> &nList){
        nList.traverse(&create_id_list);
        cout<< IDList.getSize();
        cout<<endl;
    }
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//Event 4: find ninja who have biggest ninja tags
//void function
void find_max(char*&ID,void*ptr,bool&flag){
	char*max_id=new char();
	strcpy(max_id,((Temp*)ptr)->id);
	if(strcmp(ID,max_id)>0){
		strcpy(((Temp*)ptr)->id,ID);
	}
}
void Event4(L1List<NinjaInfo_t>&nList){
	if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
	else{
		Temp*ptr=new Temp();
		strcpy(ptr->id,IDList.at(0));
		bool flag=0;
		IDList.traverse(&find_max,ptr,flag);
		cout<<ptr->id<<endl;
	}
}

//--------------------------------------------------------------------
//---------------------------------------------------------------------
//Event 5ABCD: first time save the ninja ABCD 
//void function
void find_first_move(NinjaInfo_t&data,void*ptr,bool &flag){
	if(!strcmp(data.id,((Temp*)ptr)->id)){
		((Temp*)ptr)->time=data.timestamp;
		flag=1;
	}
}
void Event5(L1List<NinjaInfo_t>&nList,ninjaEvent_t&event){
	bool flag=0;
	Temp*ptr=new Temp;
	strcpy(ptr->id,event.code+1);
	nList.traverse(&find_first_move,ptr,flag);
	if(flag==0){
		cout<<"-1"<<endl;
	}
	else{
		char*time=new char();
		strPrintTime(time,ptr->time);
		cout<<time<<endl;
	}
}
   bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
   	cout<<event.code<<":";
   	if(event.code[0]=='0'){
      	Event0();
   }
   	else if(event.code[0]=='1'){
       	Event1(nList);
   }
  	else if(event.code[0]=='2'){
       	Event2(nList);
   }
  	else if(event.code[0]=='3'){
    	Event3(nList);
	}
	else if(event.code[0]=='4'){
		Event4(nList);
	}
	else if(event.code[0]=='5'){
		Event5(nList,event);
	}
    //IDList.clean();
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}

