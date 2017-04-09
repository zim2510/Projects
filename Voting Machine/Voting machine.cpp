#include <bits/stdc++.h>

using namespace std;

map <string, int> markafill;
map <string, int> uname;
char winner[150];
int mx = 0;
int vphase = 0;
int rp = 0;
int almt;



struct candidate
{
    char name[150];
    char uname[25];
    char pass[25];
    int age;
    int voted;
    int votecnt;
    char marka[25];
    candidate * next;
};

struct voter
{
    char name[150];
    char uname[25];
    char pass[25];
    int age;
    int voted;
    voter * next;
};

voter * voterlist = (voter*) malloc(sizeof(voter));
candidate * candidatelist = (candidate*) malloc(sizeof(candidate));


void result()
{
    candidate * lcandidatelist = candidatelist;
    while(lcandidatelist->next!=NULL){
        lcandidatelist = lcandidatelist->next;
        if(lcandidatelist->votecnt>mx){
            mx = lcandidatelist->votecnt;
            strcpy(winner, lcandidatelist->name);
        }
    }
    printf("\nTHE WINNER IS: %s\n", winner);
}


void vote()
{

    if(vphase==0) {printf("Voting session has not started yet.\n"); return;}
    if(vphase==2) {printf("Voting session expired\n"); return;}
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("***WARNING: YOU HAVE TO VOTE IN THIS SESSION. OR YOU ARE NOT GONNA BE ABLE TO VOTE LATER***\n\n");
    candidate * list = candidatelist;
    int cnt = 0;
    while(list->next != NULL){
        list = list->next;
        printf("%d. %s\n   %s\n\n", ++cnt, list->marka, list->name);
    }

    if(cnt==0) printf("NO CANDIDATE FOUND\n");

    while(cnt!=0){
        int selection;
        scanf("%d", &selection);
        if(selection>cnt) printf("WRONG SELECTION\n");
        else{
            cnt = 0;
            list = candidatelist;
            while(list->next != NULL){
                list = list->next;
                cnt++;
                if(cnt==selection){
                    list->votecnt++;
                    printf("Voting successful\n\n");
                    return;
                }
            }
        }
    }
}

void addvoter(voter * lvoterlist)
{
    printf("\n-------------------------------------ADD VOTER-------------------------------------------------");
    while(lvoterlist->next!=NULL) lvoterlist = lvoterlist->next;
    lvoterlist->next = (voter*) malloc(sizeof(voter));
    printf("\nNAME: ");
    scanf(" %[^\n]", (lvoterlist->next)->name);
    printf("\nAGE: ");
    scanf("%d", &(lvoterlist->next)->age);
    if(lvoterlist->next->age<almt){
        printf("You're too young to be a voter.\n");
        free(lvoterlist->next);
        lvoterlist->next = NULL;
        return;
    }
    printf("\nUsername: ");
    scanf(" %s", (lvoterlist->next)->uname);
    printf("\nPassword: ");
    scanf(" %[^\n]", (lvoterlist->next)->pass);
    lvoterlist->next->voted = 0;
    lvoterlist->next->next = NULL;
    printf("\nNew voter ID successfully added\n");
    return;
}

void addcandidate(candidate * candidatelist)
{
    printf("\n----------------------------------ADD CANDIDATE------------------------------------------------");
    while(candidatelist->next!=NULL) candidatelist = candidatelist->next;
    candidatelist->next = (candidate*) malloc(sizeof(candidate));
    printf("\nNAME: ");
    scanf(" %[^\n]", candidatelist->next->name);
    printf("\nAGE: ");
    if(candidatelist->next->age<almt){
        printf("You're too young to be a voter.\n");
        free(candidatelist->next);
        candidatelist->next = NULL;
        return;
    }
    scanf("%d", &candidatelist->next->age);
    printf("\nUsername: ");
    scanf(" %s", candidatelist->next->uname);
    printf("\nPassword: ");
    scanf(" %[^\n]", candidatelist->next->pass);
    printf("\nLogo: ");
    scanf(" %[^\n]", candidatelist->next->marka);
    candidatelist->next->voted = 0;
    candidatelist->next->votecnt = 0;
    candidatelist->next->next = NULL;
    printf("\nNew candidate ID successfully added\n");
    return;
}

void logadmin()
{
    printf("\n-----------------------------------------ADMIN LOGIN--------------------------------------------\n");
    printf("Username: ");
    char uname[25];
    scanf(" %s", uname);
    printf("\n\nPassword: ");
    char pass[25];
    scanf(" %s", pass);
    if(!strcmp(uname, "admin") && !strcmp(pass, "sinp")){
        printf("\nLogin Successful\n");
        printf("1. Start Voting Session\n2. Stop Voting Session\n");
        int selection;
        scanf("%d", &selection);
        if(selection==1){
            if(vphase==0){
                printf("\nVoting session started successfully\n");
                vphase = 1;
            }
            else printf("\nVoting session can't be started. It's either over or running\n");
        }
        if(selection==2){
            if(vphase==1){
                printf("\nVoting session stopped successfully\n");
                vphase = 2;
                result();
            }
            else printf("\nVoting session can't be stopped. It's either over or hasn't started yet\n");
        }

    }
    else printf("USERID or PASSWORD didn't match\n");
}

void logvoter(voter * lvoterlist)
{
    printf("\n-----------------------------------------VOTER LOGIN-------------------------------------------\n");
    printf("Username: ");
    char uname[25];
    scanf(" %s", uname);
    printf("Password: ");
    char pass[25];
    scanf(" %s", pass);

    int flag = 0;

    while(1){
        if(lvoterlist->next != NULL) lvoterlist = lvoterlist->next;
        //printf("%s %s\n", lvoterlist->uname, lvoterlist->pass);
        if(!strcmp(lvoterlist->uname, uname) && !strcmp(lvoterlist->pass, pass)){
            flag = 1;
            break;
        }
        if(lvoterlist->next == NULL){
            printf("NO MATCH FOUND\n");
            return;
        }
    }

    if(flag){
        printf("\nLogin Successful");
        while(1){
            printf("\n1. Cast vote\n2. Change Password\n3. Logout\n");
            int choice;
            scanf("%d", &choice);
            if(choice==1){
                if(lvoterlist->voted==0) vote();
                else printf("YOU HAVE ALREADY VOTED\n");
                if(vphase) lvoterlist->voted = 1;
            }
            else if(choice==2){
                char newpass[25];
                printf("New Password: ");
                scanf(" %[^\n]", newpass);
                strcpy(lvoterlist->pass, newpass);
                printf("Password successfully changed\n");
            }
            else if(choice==3) return;
            else printf("WRONG CHOICE\n");
        }

    }

}

void logcandidate(candidate * lcandidatelist)
{
    printf("\n--------------------------------------CANDIDATE LOGIN-----------------------------------------\n");
    printf("Username: ");
    char uname[25];
    scanf(" %s", uname);
    printf("Password: ");
    char pass[25];
    scanf(" %s", pass);

    int flag = 0;

    while(1){
        if(lcandidatelist->next != NULL) lcandidatelist = lcandidatelist->next;
        //printf("%s %s\n", lcandidatelist->uname, lcandidatelist->pass);
        if(!strcmp(lcandidatelist->uname, uname) && !strcmp(lcandidatelist->pass, pass)){
            flag = 1;
            break;
        }
        if(lcandidatelist->next == NULL){
            printf("NO MATCH FOUND\n");
            return;
        }
    }

    if(flag){
        printf("\nLogin Successful\n");
        while(1){
            printf("1. Cast vote\n2. See results\n3. Change password\n4. Logout\n");
            int choice;
            scanf("%d", &choice);
            if(choice==1){
                    if(lcandidatelist->voted==0) vote();
                    else printf("YOU HAVE ALREADY VOTED\n");
                    if(vphase) lcandidatelist->voted = 1;
                }
                else if(choice==2){
                    if(vphase!=2) printf("Voting session hasn't ended yet.\n");
                    if(vphase==2)printf("You've got %d votes.\n", lcandidatelist->votecnt);
                    if(vphase==2) printf("Winner: %s\nVote count: %d\n", winner, mx);
                }
                else if(choice==3){
                    char newpass[25];
                    printf("New Password: ");
                    scanf(" %[^\n]", newpass);
                    strcpy(lcandidatelist->pass, newpass);
                    printf("Password successfully changed\n");
                }
                else if(choice==4) return;
                else printf("WRONG CHOICE\n");
        }
    }
}

void login()
{
    while(1){
        printf("\n----------------------------------------LOGIN-------------------------------------------------\n");
        printf("1. Voter Login\n2. Candidate Login\n3. Admin Login\n0. Previous menu\n");
        int selection;
        scanf("%d", &selection);
        if(selection==1){
            logvoter(voterlist);
        }
        else if(selection==2){
            logcandidate(candidatelist);
        }
        else if(selection==3){
            logadmin();
        }
        else if(selection==0){
            return;
        }
    }
}


void registration()
{
    while(1){
        printf("\n-----------------------------------REGISTRATION----------------------------------------------\n");
        if(vphase==1) {printf("REGISTRATION IS CLOSED\n"); return;}
        printf("1. Voter Registration\n2. Candidate Registration\n0. Previous menu\n");
        int selection;
        scanf("%d", &selection);
        if(selection==1){
            addvoter(voterlist);
        }
        else if(selection==2){
            addcandidate(candidatelist);
        }
        else if(selection==0){
            return;
        }
    }
}

int main()
{
    candidatelist->next = NULL;
    voterlist->next = NULL;
    printf("SET AGE LIMIT: \n");
    scanf("%d", &almt);

    while(1){
        printf("--------------------------------------VOTING MACHINE------------------------------------------\n");
        printf("1. Registration\n2. Login\n3. Exit\n");
        int selection;
        scanf("%d", &selection);
        if(selection==1){
            registration();
        }
        else if(selection==2){
            login();
        }
        else if(selection==3) return 0;
        else printf("WRONG SELECTION\n\n\n");
    }
}

