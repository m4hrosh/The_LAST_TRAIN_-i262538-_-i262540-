#include "viewer_iface.h"
#include "util.h"
void printRoomTitle(int floor, int room){
const char* room_names[NUM_FLOORS][ROOMS_PER_FLOOR]={{"Entrance Lobby", "Reception", "Waiting Area", "Utility Room"}, {"Lounge", "Archive", "Lab", "Meeting Room"}, {"Stairwell Annex", "Security Vestibule", "Animal Room", "Control Room"}, {"First Aid Station", "Medical Room", "Maintenence Corridor", "Office"}, {"Security Room", "Training Boarding Platform", "Storage ROom", "Observation Deck"}};
if(floor>=0 && floor<NUM_FLOORS && room>=0 && room<ROOMS_PER_FLOOR){
 cout<<room_names[floor][room];
 }
else{
 cout<<"Unknown Room";
 }
}
void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft){
cout<<endl;
cout<<"----------------------------------------"<<endl;
cout<<"location : F"<<playerFloor+1<<"-R"<<playerRoom+1<<" (";
printRoomTitle(playerFloor, playerRoom);
cout<<")"<<endl;
cout<<"energy   : "<<energy<<" / "<<MAX_ENERGY<<" | time : "<<time<<" | score : "<<score<<" / 520"<<endl;
cout<<"lift 2 emergency trips left : "<<emergencyTripsLeft<<endl;
cout<<"inventory ("<<inventoryCount<<" / "<<MAX_INVENTORY_CAPACITY<<"): ";
if(inventoryCount==0){
 cout<<"empty";
 }
else{
 for(int i=0;i<inventoryCount;i++){
  cout<<"["<<inventory[i]<<" "<<getEntityName(inventory[i])<<"] ";
  }
 }
cout<<endl;
cout<<"----------------------------------------"<<endl;
}
void renderRoomDetails(int floor, int room, const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCount){
cout<<"room F"<<floor+1<<"-R"<<room+1<<" (";
printRoomTitle(floor, room);
cout<<") contains:"<<endl;
if(entityCount<=0){
 cout<<"  - nothing visible here"<<endl;
 return;
 }
for(int i=0;i<entityCount;i++){
 char sym=roomEntities[floor][room][i];
 cout<<"  - ["<<sym<<"] "<<getEntityName(sym)<<endl;
 }
}
void renderAsciiBuilding(int playerFloor, int playerRoom){
cout<<endl;
cout<<"=== FACILITY BLUEPRINT ([P] = Player) ==="<<endl;
for(int f=NUM_FLOORS-1;f>=0;f--){
 cout<<"Floor "<<f+1<<": ";
 for(int r=0;r<ROOMS_PER_FLOOR;r++){
  if(f==playerFloor && r==playerRoom){
   cout<<"[ P ]";
   }
  else{
   cout<<"[R"<<r+1<<" ]";
   }
  if(r<ROOMS_PER_FLOOR-1){
   if(f==4 && r==0) cout<<"-D-";
   else if(f==4 && r==1) cout<<"-D-";
   else if(f==4 && r==2) cout<<"-W-";
   else if(f==3 && r==0) cout<<"-W-";
   else if(f==3 && r==1) cout<<"-#-";
   else if(f==3 && r==2) cout<<"-D-";
   else if(f==2 && r==0) cout<<"-L-";
   else if(f==2 && r==1) cout<<"-W-";
   else if(f==2 && r==2) cout<<"-D-";
   else if(f==1 && r==0) cout<<"-D-";
   else if(f==1 && r==1) cout<<"-L1-";
   else if(f==1 && r==2) cout<<"-D-";
   else if(f==0 && r==0) cout<<"-W-";
   else if(f==0 && r==1) cout<<"-L1-";
   else if(f==0 && r==2) cout<<"-D-";
   }
 }
 cout<<endl;
 }
cout<<"stairs: S1(F1-R1<->F2-R1), S2(F2-R1<->F3-R1), S3(F4-R1<->F5-R1)"<<endl;
cout<<"lifts : L1(F1<->F2 at R2/R3), L2(F2-R4<->F4-R4<->F5-R4)"<<endl;
}
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]){
cout<<endl;
cout<<"=== MISSION OBJECTIVES ==="<<endl;
if(objectives[OBJ_MASTER_KEY]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Find Master Key (<)"<<endl;

if(objectives[OBJ_CLUE_4]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Discover Clue Digit 4"<<endl;

if(objectives[OBJ_CLUE_2]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Discover Clue Digit 2"<<endl;

if(objectives[OBJ_CLUE_7]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Discover Clue Digit 7"<<endl;

if(objectives[OBJ_CABINET_UNLOCKED]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Unlock Cabinet (Code 427)"<<endl;

if(objectives[OBJ_TRAIN_KEY]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Aquire Train Key (K)"<<endl;

if(objectives[OBJ_FUSE_INSTALLED]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Install Fuse (*) at Control Panel"<<endl;

if(objectives[OBJ_LIFT_PASS]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Collect Lift Pass (()"<<endl;

if(objectives[OBJ_PASSENGER_RESCUED]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Rescue Injured Passenger (!)"<<endl;

if(objectives[OBJ_CAT_SECURED]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Secure Stranded Cat (~)"<<endl;

if(objectives[OBJ_TRAIN_PREPARED]==true) cout<<"[X]";
else cout<<"[ ] ";
cout<<"Prepare & Board Train at F5-R2"<<endl;
}
// Terminal UI and dashboard rendering using primitive parameters
