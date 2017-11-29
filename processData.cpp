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
    char  save_id[10];
    time_t time;
    time_t sumTime;
 	double lat;
 	double lon;
 	double lat_2;
 	double lon_2;
 	double distance;
 	int count;
 	int count_2;
	bool check;
	string *sString;
 	L1List<NinjaInfo_t> list;
    Temp(char*id){
    	strcpy(this->id,id);
    	time=0;
    	lat=0;
    	lon=0;
    	count=0;
    	distance=0;
    	sumTime=0;
    	lat_2=0;
    	lon_2=0;
    	count_2=0;
		check = 0;
		sString=NULL;
    }
    Temp(){
    	time=0;
    	lat=0;
    	lon=0;
    	count=0;
    	distance=0;
    	sumTime=0;
    	lat_2=0;
    	lon_2=0;
    	count_2=0;
		check = 0;
		sString = NULL;
    }
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
    loadEvents("events.txt",Event);
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
    Temp* p=new Temp(data.id);
    bool flag=0;
    IDList.traverse(&traverse_id,p,flag);
    char*ptr=new char();
    strcpy(ptr,p->id);
    if(flag==0){
        IDList.push_back(ptr);
    }
}

void Event3(L1List<NinjaInfo_t> &nList){
		if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
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
	Temp*ptr=new Temp(IDList.at(0));
	bool flag=0;
	IDList.traverse(&find_max,ptr,flag);
	cout<<ptr->id<<endl;
}

//--------------------------------------------------------------------
//---------------------------------------------------------------------
//Event 5ABCD: first time the ninja ABCD move
//void function
void find_first_move(NinjaInfo_t&data,void*ptr,bool &flag){
	Temp*p = (Temp*)ptr;
	if(!strcmp(data.id,p->id)){
		if(!p->check){//first time receive location
			p->lat=data.latitude;
			p->lon=data.longitude;
			p->check=1;
		}
		else{// all other times
			p->distance=distanceEarth(p->lat,p->lon,data.latitude,data.longitude)*1000;
			if(p->distance>5){//if move
				//p->time=data.timestamp;
				p->time = data.timestamp;
				flag=1;
			}
			else{ //if not move
				p->lat=data.latitude;
				p->lon=data.longitude;
			}
		}
	}
}
void Event5(L1List<NinjaInfo_t>&nList,ninjaEvent_t&event){
	bool flag=0;
	Temp*ptr=new Temp(event.code+1);
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
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Event 6ABCD: last time ninja ABCD stop
//void function
void find_last_stop(NinjaInfo_t&data, void*ptr, bool&flag) {
	Temp*p = (Temp*)ptr;
	if (!strcmp(data.id, p->id)) {
		if (!p->check) {//first time receive location
			p->lat = data.latitude;
			p->lon = data.longitude;
      p->time = data.timestamp;
			p->check = 1;
		}
		else {// all other times
			if (distanceEarth(p->lat, p->lon, data.latitude, data.longitude) * 1000 <= 5) {
				//p->lat = data.latitude;
				//p->lon = data.longitude;
        if(p->count==0){
				p->sumTime = p->time;//Just to optimize all variable
        p->count=1;
      }
			}
			else {
        p->count=0;
				p->lat = data.latitude;
				p->lon = data.longitude;
        p->time=data.timestamp;
			}
		}
	}
}
void Event6(L1List<NinjaInfo_t> &nList,ninjaEvent_t&event){
	Temp*ptr= new Temp(event.code+1);
	ptr->count = 0;
	bool flag=0;
	nList.traverse(&find_last_stop,ptr,flag);
	if(ptr->sumTime==0){
		cout<<"-1"<<endl;
	}
	else{
		char *time=new char();
		strPrintTime(time,ptr->sumTime);
		cout<<time<<endl;
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//Event 7ABCD: sum of times ninja stop
//void function
void count_stop(NinjaInfo_t &data, void *ptr,bool &flag){
	Temp*p=(Temp*)ptr;
	if(!strcmp(p->id,data.id)){
		if (!p->check) {//first time receive location
			p->lat = data.latitude;
			p->lon = data.longitude;
			p->check = 1;
		}
		else {
		if(distanceEarth(p->lat,p->lon,data.latitude,data.longitude)*1000<=5){
			//p->lat=data.latitude;//need to check between 2 times
			//p->lon=data.longitude;
      if(p->count_2==0){
        (p->count)++;
        p->count_2=1;
      }
		}
		else{
      p->count_2=0;
			p->lat=data.latitude;
			p->lon=data.longitude;
		}
	}
}

}
void Event7(L1List<NinjaInfo_t> &nList,ninjaEvent_t &event){
	Temp*ptr =new Temp(event.code+1);
	bool flag=0;
  ptr->count_2=0;
	nList.traverse(&count_stop,ptr,flag);
	if(ptr->count==0){
		cout<<"-1"<<endl;
	}
	else{
		cout<<ptr->count<<endl;
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//Event 8ABCD: distance ninja ABCD move
//void function
void distance(NinjaInfo_t&data,void *ptr,bool&flag){
	Temp*p=(Temp*)ptr;
	if(!strcmp(data.id,p->id)&&p->check==0){
		p->lon=data.longitude;
		p->lat=data.latitude;
		p->check = 1;
	}
	else if(!strcmp(data.id,p->id)){
		(p->distance)+=distanceEarth(data.latitude,data.longitude,p->lat,p->lon);
		p->lat=data.latitude;
		p->lon=data.longitude;
	}
}
void Event8(L1List<NinjaInfo_t>&nList,ninjaEvent_t&event){
	Temp*ptr= new Temp(event.code+1);
	bool flag=0;
	nList.traverse(&distance,ptr,flag);
	if(ptr->distance==0){
		cout<<"-1"<<endl;
	}
	else{
		cout<<ptr->distance<<endl;
	}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Event 9:ninja have longest move
//void function
//traverse id list to create id array;
void add2array(char*&data,void*ptr,bool&flag){
	Temp*p=(Temp*)ptr;
	p->sString[p->count]=data;
	p->count++;
}
//traverse ninja list to find max distance
void find_max_dist(NinjaInfo_t &data,void*ptr,bool&flag){
	Temp*temp=(Temp*)ptr;
	if(!strcmp(temp->id,data.id)&&temp->check==0){
		temp->lon=data.longitude;
		temp->lat=data.latitude;
		temp->check = 1;
	}
	else if(!strcmp(temp->id,data.id)){
		double distance=distanceEarth(temp->lat,temp->lon,data.latitude,data.longitude);
		if(distance*1000>5){
		temp->distance+=distance;
		temp->lon=data.longitude;
		temp->lat=data.latitude;
		}
	}
}
void Event9(L1List<NinjaInfo_t>&nList){
	if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
	Temp*ptr = new Temp();
	ptr->sString=new string[IDList.getSize()];
	bool flag=0;
	IDList.traverse(&add2array,ptr,flag);
	double max_dist=0;
	char*max_id=new char();
	for(int i=0;i<IDList.getSize();i++){
		char*arr=new char();
		for (int j = 0; j < 10; ++j)
				{
					arr[j]=ptr->sString[i][j];
				}
		strcpy(ptr->id, arr);
		nList.traverse(&find_max_dist,ptr,flag);
		if(ptr->distance>max_dist){
			max_dist=ptr->distance;
			strcpy(max_id,ptr->id);
		}
		ptr->distance = 0;
		
	}
	cout<<max_id<<endl;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//Event 10: Ninja have longest time to move
//void function
//traverse ninja list to find max time to go
void find_max_time(NinjaInfo_t &data,void*ptr,bool&flag){
	Temp*temp=(Temp*)ptr;
	if(!strcmp(temp->id,data.id)&&temp->check==0){
		temp->time=data.timestamp;
		temp->lat=data.latitude;
		temp->lon=data.longitude;
		temp->check++;
	}
	else if(!strcmp(temp->id,data.id)){
		double distance=distanceEarth(temp->lat,temp->lon,data.latitude,data.longitude);
		if(distance*1000>5){
			temp->sumTime+=(data.timestamp-temp->time);
			temp->time=data.timestamp;
			temp->lat=data.latitude;
			temp->lon=data.longitude;
		}
		else{
			temp->time=data.timestamp;
		}
	}
}
void Event10(L1List<NinjaInfo_t>&nList){
	if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
	Temp*ptr=new Temp();
	ptr->sString=new string[IDList.getSize()];
	bool flag=0;

	IDList.traverse(&add2array,ptr,flag);//create array
	time_t max_time=0;
	char*max_id=new char();//getid from array
	for(int i=0;i<IDList.getSize();i++){
		char*arr=new char();
		for (int j = 0; j < 10; ++j)
				{
					arr[j]=ptr->sString[i][j];
				}
		strcpy(ptr->id,arr);//create void pointer to traverse
		nList.traverse(&find_max_time,ptr,flag);
		if(ptr->sumTime>max_time){
			max_time=ptr->sumTime;
			strcpy(max_id,ptr->id);
		}
		ptr->sumTime=0;
		ptr->check=0;
	}
	cout<<max_id<<endl;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Event 11: find XYZT
//Void function
void find_XYZT(char*&id,void *ptr,bool&flag){
	Temp*p=(Temp*)ptr;
	if(strcmp(p->id,id)>0){
		if(strcmp(p->save_id,id)<0){
			p->count=1;
			strcpy(p->save_id,id);
		}
	}
}
void kick_XYZT(char*&id,void *ptr,bool&flag){
  Temp*p=(Temp*)ptr;
  if(!strcmp(p->save_id,id)){
    flag=1;
  }
}
void delete_XYZT(NinjaInfo_t&data,void*ptr,bool&flag){
  Temp*p=(Temp*)ptr;
  if(!strcmp(p->save_id,data.id)){
    flag=1;
  }
}
void Event11(L1List<NinjaInfo_t>&nList,ninjaEvent_t&event){
	if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
	char*id=new char();
	strcpy(id, event.code+2);
	Temp*ptr=new Temp(id);
	bool flag=0;
	IDList.traverse(&find_XYZT,ptr,flag);
  IDList.replaceAll(&kick_XYZT,ptr,flag);
  nList.replaceAll(&delete_XYZT,ptr,flag);
	if((ptr->count)==0){
		cout<<"-1"<<endl;
	}
	else{
		cout<<ptr->save_id<<endl;
	}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Event 12: found boruto's father
//void function
void find_naruto(NinjaInfo_t &data,void*ptr,bool&flag){
	Temp*temp=(Temp*)ptr;
	if(!strcmp(temp->id,data.id)&&temp->check==0){
		temp->time=data.timestamp;
		temp->lat=data.latitude;
		temp->lon=data.longitude;
		temp->check=1;
	}
	else if(!strcmp(temp->id,data.id)){
		double distance=distanceEarth(temp->lat,temp->lon,data.latitude,data.longitude);
		if(distance*1000>5){
			temp->time=data.timestamp;
			temp->lat=data.latitude;
			temp->lon=data.longitude;
		}
		else{
			temp->sumTime+=(data.timestamp-temp->time);
			temp->time=data.timestamp;
		}
	}
}
void Event12(L1List<NinjaInfo_t>&nList){
	if(IDList.getSize()==0){
		nList.traverse(&create_id_list);
	}
	Temp*ptr=new Temp();
	ptr->sString=new string[IDList.getSize()];
	bool flag=0;

	IDList.traverse(&add2array,ptr,flag);//create array
	time_t max_time=0;
	char*max_id=new char();//getid from array
	for(int i=0;i<IDList.getSize();i++){
		char*arr=new char();
		for (int j = 0; j < 10; ++j)
				{
					arr[j]=ptr->sString[i][j];
				}
		strcpy(ptr->id,arr);//create void pointer to traverse
		nList.traverse(&find_naruto,ptr,flag);
		if(ptr->sumTime>max_time){
			max_time=ptr->sumTime;
			strcpy(max_id,ptr->id);
		}
		ptr->distance=0;
		ptr->check=0;
		ptr->sumTime=0;
	}
	cout<<max_id<<endl;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//Event 14:ninja who be astray
//void function
void print_ninja_astray(char*&ninja){
	cout<<ninja<<" ";
}

void be_astray(NinjaInfo_t&ninja,void*ptr,bool&flag){
	Temp*p_local=(Temp*)ptr;
	if(p_local->count_2<(p_local->list).getSize()){
		double distance=distanceEarth(ninja.latitude,ninja.longitude,p_local->lat,p_local->lon);
		if(distance*1000<=5){
			flag=1;
		}
		else{
			p_local->count_2++;
		}
	}
}

void find_astray_ninja(NinjaInfo_t&data,void*ptr, bool&flag){
	Temp*p=(Temp*)ptr;
	if(!strcmp(p->id,data.id)&&p->check==0){
		(p->list).insertHead(data);
		(p->check)=1;
	}

	else if(!strcmp(p->id,data.id)){
		p->lat=data.latitude;
		p->lon=data.longitude;
		p->count_2=0;
		if(distanceEarth(p->lat,p->lon,(p->list).at(0).latitude,(p->list).at(0).longitude)*1000>5){
			(p->list).insertHead(data);
			(p->list).traverse(&be_astray,p,flag);
		}
		else{
			(p->list).insertHead(data);
		}
	}
}



void Event14(L1List<NinjaInfo_t>&nList){
	if (IDList.getSize()==0)
	{
		nList.traverse(&create_id_list);
	}
	Temp*ptr=new Temp();
	ptr->sString=new string[IDList.getSize()];
	bool flag=0;
	L1List<char*>lost_list;
	char* p=new char[10];
	IDList.traverse(&add2array,ptr,flag);
	for(int i=0;i<IDList.getSize();i++){
		for(int j=0;j<10;j++){
			p[j]=ptr->sString[i][j];
		}
		Temp*temp=new Temp(p);
		nList.traverse(&find_astray_ninja,temp,flag);
		if(flag==1){
			char* lost=new char();
			strcpy(lost,p);
			lost_list.push_back(lost);
			flag=0;
		}
		temp->count=0;
		(temp->list).clean();
	}
	if(lost_list.getSize()==0){
		cout<<"-1"<<endl;
	}
	else{
		lost_list.traverse(&print_ninja_astray);
		cout<<endl;
	}
}

   bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList,void*pGData) {
   	cout<<event.code<<": ";
   	if(event.code[0]=='0'){
      	Event0();
   }
   	else if(event.code[0]=='1'&&event.code[1]=='\0'){
       	Event1(nList);
   }
  	else if(event.code[0]=='2'&&event.code[1]=='\0'){
       	Event2(nList);
   }
  	else if(event.code[0]=='3'&&event.code[1]=='\0'){
    	Event3(nList);
	}
	else if(event.code[0]=='4'&&event.code[1]=='\0'){
		Event4(nList);
	}
	else if(event.code[0]=='5'){
		Event5(nList,event);
	}
	else if(event.code[0]=='6'){
		Event6(nList,event);
	}
	else if(event.code[0]=='7'){
		Event7(nList,event);
	}
	else if(event.code[0]=='8'){
		Event8(nList,event);
	}
	else if(event.code[0]=='9'&&event.code[1]=='\0'){
		Event9(nList);
	}
	else if(event.code[0]=='1'&&event.code[1]=='0'){
		Event10(nList);
	}
	else if(event.code[0]=='1'&&event.code[1]=='1'){
		Event11(nList,event);
	}
	else if(event.code[0]=='1'&&event.code[1]=='2'){
		Event12(nList);
	}
	else if(event.code[0]=='1'&&event.code[1]=='4'){
		Event14(nList);
	}
  else{
	  cout << "is an invalid event" << endl;
  }
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}
