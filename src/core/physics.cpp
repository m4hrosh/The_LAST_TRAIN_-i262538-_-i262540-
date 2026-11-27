#include "physics.h"
#include "switches.h"
#include "util.h"

bool isDirectlyConnected(int fromF, int fromR, int toF, int toR, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR-1], char& outConnType) 
{
outConnType = CONN_NONE;
if (fromF<0 || fromF>= NUM_FLOORS || toF<0 || toF>= NUM_FLOORS || fromR<0 || fromR>= ROOMS_PER_FLOOR || toR<0 || toR>= ROOMS_PER_FLOOR) {
return false;
}
if (fromF== toF && fromR== toR) {
return false;
}
if (fromF== toF) {
int diff = toR-fromR;
if (diff== 1 || diff== -1) {
int conn_index;
if (fromR<toR) {
conn_index = fromR;
} else {
conn_index = toR;
}
if ((fromF== 0 || fromF== 1) && conn_index== 1) {
outConnType = CONN_DOOR;
return true;
}
char conn = horizontalConn[fromF][conn_index];
outConnType = conn;
if (conn== CONN_DOOR || conn== CONN_WINDOW || conn== CONN_LOCKED_DOOR) {
return true;
}
}
return false;
}
if (fromR== 0 && toR== 0) {
 if ((fromF== 0 && toF== 1) || (fromF== 1 && toF== 0)) {
 outConnType = 'S';
 return true;
 }
 if ((fromF== 1 && toF== 2) || (fromF== 2 && toF== 1)) {
 outConnType = 'S';
 return true;
 }
 if ((fromF== 3 && toF== 4) || (fromF== 4 && toF== 3)) {
 outConnType = 'S';
 return true;
 }
}
if ((fromR== 1 || fromR== 2) && (toR== 1 || toR== 2)) {
 if (canUseLift1(fromF, toF)== true) {
 outConnType = '1';
 return true;
 }
}
if (fromR== 3 && toR== 3) {
bool valid_from = (fromF== 1 || fromF== 3 || fromF== 4);
bool valid_to = (toF== 1 || toF== 3 || toF== 4);
if (valid_from== true && valid_to== true) {
outConnType = '2';
return true;
}
}
return false;
}

bool canTraverse(int targetFloor, int targetRoom, char connType, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft, bool lift2Operational)
{
if (targetFloor<0 || targetFloor>= NUM_FLOORS || targetRoom<0 || targetRoom>= ROOMS_PER_FLOOR) {
return false;
}
if (connType== CONN_DOOR || connType== CONN_WINDOW || connType== 'S') {
return true;
}
if (connType== CONN_LOCKED_DOOR) {
return unlockFloor3Door(inventory, inventoryCount);
}
if (connType== '1') {
 if (targetFloor== 0 || targetFloor== 1) {
 return true;
 }
 return false;
}
if (connType== '2') {
 if (targetFloor== 1 || targetFloor== 3 || targetFloor== 4) {
  if (lift2Operational== true || emergencyTripsLeft>0) {
  return true;
  }
 }
 return false;
}
return false;
}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime) 
{
energy = clampInt(energy + deltaEnergy, 0, MAX_ENERGY);
time = clampInt(time + deltaTime, 0, 100);
}

void applyScoreDelta(int& score, int deltaScore) {
score+= deltaScore;
if (score<0) {
score = 0;
}
}

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol) {
for (int i = 0; i<inventoryCount; i++) {
 if (inventory[i]== itemSymbol) {
 return true;
 }
}
return false;
}

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
 if (inventoryCount>= MAX_INVENTORY_CAPACITY) {
 return false;
 }
 inventory[inventoryCount] = itemSymbol;
 inventoryCount += 1;
 return true;
}

bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
int found_index = -1;
for (int i = 0; i<inventoryCount; i++) {
 if (inventory[i]== itemSymbol) {
 found_index = i;
 break;
 }
}
if (found_index== -1) {
return false;
}
for (int i = found_index; i<inventoryCount-1; i++) {
inventory[i] = inventory[i+1];
}
inventoryCount -=1;
inventory[inventoryCount] = ENT_NONE;
return true;
}
