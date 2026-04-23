#include<stdio.h>
#include<string.h>

//Declaration of all structures for Location, Data and Resources
struct Location{
    char city[30];
    char state[30];
    char country[30];
}L[30];

struct Data{
    char disaster[20];
    int population;
    int peopleAffected;
    float severity;
}D[30];

struct Resources{
    int waterCans;
    int foodPackets;
    int firstAid;
    int tents;
}R[30];

//Declare global variables for the resources
int water,food,aid,shelter;

//Function to add a particular Location
void AddLocation(int index){
    /*Scanf leaves a new line '\n' in the input buffer after accepting an datatype/character.
    Getchar() flushes the new line and doesnt let next instruction fgets to auto accept newline as an error*/

    getchar();

    printf("Enter City: ");
    //fgets(str,sizeof(str),stdin)
    fgets(L[index].city,30,stdin);
    /*strcspn stands for string character span meaning:
    It returns an index where we find the element specified in " " in a given string*/ 
    L[index].city[strcspn(L[index].city,"\n")] = '\0';

    printf("Enter State: ");
    fgets(L[index].state,30,stdin);
    L[index].state[strcspn(L[index].state,"\n")] = '\0';

    printf("Enter Country: ");
    fgets(L[index].country,30,stdin);
    L[index].country[strcspn(L[index].country,"\n")] = '\0';
}

void AddData(int index){
    int disaster,choice;

    do{
        printf("1:Flood \n2:Earthquake \n3:Fire \n4:Cyclone\n");
        scanf("%d",&disaster);

        switch(disaster){
            case 1: 
                    strcpy(D[index].disaster,"Flood"); 
                    break;
            case 2: 
                    strcpy(D[index].disaster,"Earthquake"); 
                    break;
            case 3: 
                    strcpy(D[index].disaster,"Fire"); 
                    break;
            case 4: 
                    strcpy(D[index].disaster,"Cyclone"); 
                    break;
            default: 
                    printf("Invalid Choice\n");
        }
    }while(disaster<1 || disaster>4);

    printf("Enter Population: ");
    scanf("%d",&D[index].population);

    do{
        printf("1:Enter Severity \n2:Enter People Affected\n");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter Severity (0-10): ");
                scanf("%f",&D[index].severity);
                D[index].peopleAffected = 0.08*D[index].population*D[index].severity;
                break;

            case 2:
                printf("Enter People Affected: ");
                scanf("%d",&D[index].peopleAffected);
                D[index].severity = ((float)D[index].peopleAffected / (float)D[index].population) * 10;
                break;

            default:
                printf("Invalid Option\n");
        }
    }while(choice!=1 && choice!=2);

    printf("Data updated successfully for %s\n",L[index].city);
    printf("Please allocate resources for this Area\n");
}

void Allocation(int index){
    int waterFactor,foodFactor,aidFactor,tentFactor;
    int needWater,needFood,needAid,needTents;

    //Allocation of Resources based on Disaster Type
    if(strcmp(D[index].disaster,"Flood")==0){
        waterFactor = 45; foodFactor = 30; aidFactor = 15; tentFactor = 8;
    }
    else if(strcmp(D[index].disaster,"Earthquake")==0){
        waterFactor = 36; foodFactor = 30; aidFactor = 27; tentFactor = 9;
    }
    else if(strcmp(D[index].disaster,"Fire")==0){
        waterFactor = 39; foodFactor = 25; aidFactor = 29; tentFactor = 5;
    }
    else{
        waterFactor = 48; foodFactor = 30; aidFactor = 18; tentFactor = 8;
    }

    //strcmp(string1,string2) compares string1 and string2 and returns 0 if both are same
    needWater = D[index].peopleAffected/100*waterFactor;
    needFood = D[index].peopleAffected/100*foodFactor;
    needAid = D[index].peopleAffected/100*aidFactor;
    needTents = D[index].peopleAffected/100*tentFactor;

    if(needWater>water || needFood>food || needAid>aid || needTents>shelter){
        printf("Resource shortage detected\n");
    }

    //Use of Ternary opertaors
    //condition? statement if true: statement if false;
    R[index].waterCans = (needWater<=water)?needWater:water;
    R[index].foodPackets = (needFood<=food)?needFood:food;
    R[index].firstAid = (needAid<=aid)?needAid:aid;
    R[index].tents = (needTents<=shelter)?needTents:shelter;

    //water = water - R[index].waterCans;
    water -= R[index].waterCans;
    food -= R[index].foodPackets;
    aid -= R[index].firstAid;
    shelter -= R[index].tents;

    printf("Resources allocated for %s\n",L[index].city);
    printf("Water Cans: %d\n",R[index].waterCans);
    printf("Food Packets: %d\n",R[index].foodPackets);
    printf("First Aid Kits: %d\n",R[index].firstAid);
    printf("Tents: %d\n",R[index].tents);
}

void FillResources(){
    printf("Enter the Reources Pool Amount:\n");
    printf("Water:");
    scanf("%d",&water);
    printf("Food Cans:");
    scanf("%d",&food);
    printf("First Aids:");
    scanf("%d",&aid);
    printf("Tents:");
    scanf("%d",&shelter);
}

void ResourceAvailability(){
    printf("Resources Available\n");
    printf("Water: %d\n",water);
    printf("Food: %d\n",food);
    printf("First Aid: %d\n",aid);
    printf("Tents: %d\n",shelter);
}

void CompleteReport(int index){
    int i;

    //Here %-12s indicates occupy 12 spaces '-' indicates left alignment
    //Used just for decoration purposes
    printf("\n%-15s %-12s %-12s %-15s %-10s %-8s %-8s %-8s\n",
           "City","Disaster","Population","Affected","Severity","Water","Food","Tents");

    for(i=1;i<index;i++){
        printf("%-15s %-12s %-12d %-15d %-10.2f %-8d %-8d %-8d\n", L[i].city,D[i].disaster,D[i].population,D[i].peopleAffected,D[i].severity,R[i].waterCans,R[i].foodPackets,R[i].tents);
    }

    printf("Community Resources Remaining:\n");
    printf("Water: %d\n",water);
    printf("Food: %d\n",food);
    printf("First Aid: %d\n",aid);
    printf("Tents: %d\n",shelter);
}

int main(){
    int option;
    int index=1;

    //Initiate program by entering the pool amount of resources available
    FillResources();

    do{
        if(index==1)
            printf("1:Add Location \n2:Allocate Resources \n3:Resource Availability \n4:Complete Report \n5:Fill Resources \n6:Exit\n");
        else
            printf("1:Add Location \n2:Allocate Resources for %s\n3:Resource Availability \n4:Complete Report \n5:Fill Resources \n6:Exit\n",L[index-1].city);

        scanf("%d",&option);

        //break; is used to avoid execution of other case statements present below
        switch(option){
            case 1:
                AddLocation(index);
                AddData(index);
                index++;
                break;
            case 2:
                Allocation(index-1);
                break;
            case 3:
                ResourceAvailability();
                break;
            case 4:
                CompleteReport(index);
                break;
            case 5:
                FillResources();
                break;
            case 6:
                printf("Exiting Program. Thank You");
                break;
            default:
                printf("Invalid Choice");
        }
    }while(option!=6);

    return 0;
}

