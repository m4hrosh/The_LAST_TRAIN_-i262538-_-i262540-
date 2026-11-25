#include "util.h"
#include <cstring>
using namespace std;

void make_lower_case(char* text)
{
int i=0;
while (text[i]!='\0')
{
if (text[i]>=65 && text[i]<=90)
{
text[i]=text[i]+32;
}
i+=1;
}
}
int keep_in_range(int value, int low, int high)
{
if (value<low)
{
return low;
}
if (value>high)
{
return high;
}
return value;
}
bool extract_room_coords(const char* input, int* floor_out, int* room_out)
{
if (input==0)
{
return false;
}
if (strlen(input)!=5)
{
return false;
}
if (input[0]=='f' && input[2]=='-' && input[3]=='r')
{
int f=input[1]-'0';
int r=input[4]-'0';
if (f>=1 && f<=total_floors && r>=1 && r<=rooms_per_floor)
{
*floor_out=f;
*room_out=r;
return true;
}
}
return false;
}
void add_item_to_bag(char inventory[][max_item_name], int* count, const char* item_name)
{
strncpy(inventory[*count], item_name, max_item_name - 1);
inventory[*count][max_item_name - 1] = '\0';
*count = *count + 1;
}
bool check_item_in_bag(const char inventory[][max_item_name], int count, const char* item_name)
{
int i;
for (i=0; i<count; i++)
{
if (strcmp(inventory[i], item_name)==0)
{
return true;
}
}
return false;
}
