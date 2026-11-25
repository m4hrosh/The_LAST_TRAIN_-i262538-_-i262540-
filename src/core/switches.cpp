#include "switches.h"
#include "util.h"
using namespace std;

bool canUseLift1(int fromFloor, int toFloor){
if((fromFloor==0 && toFloor==1) || (fromFloor==1 && toFloor==0)){
 return true;
 }
return false;
}
bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft){
if(fromFloor==toFloor){
 return false;
 }
bool valid_from=false;
bool valid_to=false;
if(fromFloor==1 || fromFloor==3 || fromFloor==4){
 valid_from=true;
 }
if(toFloor==1 || toFloor==3 || toFloor==4){
 valid_to=true;
 }
if(valid_from==false || valid_to==false){
 return false;
 }
if(lift2Operational==true){
 return true;
 }
if(emergencyTripsLeft>0){
 return true;
 }
return false;
}
bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount){
bool has_key=hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
return has_key;
}
bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& score){
if (objectives[OBJ_FUSE_INSTALLED]==true){
 return false;
 }
bool has_fuse=hasItem(inventory, inventoryCount, ENT_FUSE);
if(has_fuse==false){
 return false;
 }
removeItem(inventory, inventoryCount, ENT_FUSE);
objectives[OBJ_FUSE_INSTALLED]=true;
applyScoreDelta(score, SCORE_INSTALL_FUSE);
if(objectives[OBJ_LIFT_PASS]==true){
 objectives[OBJ_LIFT2_ACTIVE]=true;
 }
return true;
bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES]){
if (objectives[OBJ_CLUE_4]==false || objectives[OBJ_CLUE_2]==false || objectives[OBJ_CLUE_7]==false){
 return false;
 }
bool match=stringEquals(enteredCode, "427");
return match;
}

// Door lock mechanics, lifts, and cabinet verification without structures
