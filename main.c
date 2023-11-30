//
//  main.c
//  SMMarble
//
//  Created by SoJuongOK on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"

#define MAX_NODE    100

//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;       // 플레이어 몇명


// -----------------------player를 구조체로 선언하기-----------------------------
typedef struct player{
    int     energy;
    int     position;
    char    name[MAX_CHARNAME];
    int     accumCredit;        // 누적학점
    int     flag_graduate;      // player을 졸업 조건여부 따지기 위함
} player_t;

static player_t cur_player[MAX_PLAYER];


/*
static int player_energy[MAX_PLAYER];   // energy최대로
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME];  // 2차원 배열로
*/
// ------------------------------------------------------------------------------

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif

// ============================플레이어 상태 출력 함수====================================
void printPlayerStatus(void)
{
    int i;
    
    for (i=0; i<player_nr; i++)
    {
        printf("%s : credit %i, energy %i, position %i\n",
               cur_player[i].name,
               cur_player[i].accumCredit,
               cur_player[i].energy,
               cur_player[i].position);
    }
    
}
// ==================================================================================


// ===============================player 생성 함수======================================
void generatePlayers(int n, int initEnergy)
{
    int i;
    //n time loop
    for(i=0; i<n; i++)
    {
        //input name
        printf("Input player %i's name :",i);      // player이름 입력하라고 출력
        scanf("%s", cur_player[i].name);    // i번째 player의 이름 저장
        fflush(stdin);
        
        //set position
        cur_player[i].position = 0;
        
        // set energy
        cur_player[i].energy = initEnergy;
        cur_player[i].accumCredit = 0;
        cur_player[i].flag_graduate = 0;
    }
}
// ======================================================================================


// ================================주사위 굴리기=============================================
int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
#if 0
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}

// =======================================================================================

// =====================
//action code when a player stays at a node
void actionNode(int player)
{
    int type = smmObj_getNodeType(cur_player[player].position);
    
    switch(type)
    {
        //case lecture:
        case SMMNODE_TYPE_LECTURE:
            cur_player[player].accumCredit += smmObj_getNodeCredit(cur_player[player].position);
            cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);
            break;
            
        default:
            break;
    }
}
// ===================================================================================

// ========================앞으로 가라====================
void goForward(int player, int step)
{
     cur_player[player].position += step;
     
     printf("%s go to node %i (name: %s)\n",
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(cur_player[player].position));
}
// ===========================================================================

// ================================================ MAIN 함수 ===================================================

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn=0;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");      // 파일에서 받아오기
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy);
        if (type == SMMNODE_TYPE_HOME)
            initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    for (i = 0;i<board_nr;i++)
        printf("node %i : %s, %i(%s), credit %i, energy %i\n",
               i, smmObj_getNodeName(i), smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),
               smmObj_getNodeCredit(i), smmObj_getNodeEnergy(i));
    printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
    #if 0
    //2. food card config
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while () //read a food parameter set
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    
    //3. festival card config
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while () //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
#endif
    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf("intput player number: ");
        scanf("%d", &player_nr);
        fflush(stdin);                  // 원하는 입력만 받고 비우기
    }
    while (player_nr < 0 || player_nr > MAX_PLAYER);
    
    generatePlayers(player_nr, initEnergy);
    // player 상태를 for문으로 확인해보기
    
#if 0
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while () //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        //printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        
        
        //4-3. go forward
        //goForward();

        //4-4. take action at the destination node of the board
        //actionNode();
        
        //4-5. next turn
        
    }
    #endif

    return 0;
}
