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
    //IDList.clean();
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}

