//
//  smm_node.c
//  SMMarble
//
//  Created by SoJuongOK on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100


static char smmNodeName [MAX_NODETYPE][MAX_CHARNAME] =
{
    "lecture",
    "restaurant",
    "laboratory",
    "home",
    "gotoLab",
    "foodChance",
    "festival"
};

static char smmFoodCard [14][MAX_CHARNAME] =
{
    "chicken",
    "beer",
    "tanghulu",
    "ramen",
    "gamja",
    "cupbab",
    "zazang",
    "schoolfood",
    "pasta",
    "pizza",
    "hamburger",
    "sandwich",
    "yogart",
    "bibim"
};

static char smmFestival [][MAX_CHARNAME] =
{
    "sing a song",
    "After GArduate?",
    "What do you want to do at home?",
    "Talk about programming class.",
    "Introduce your favorite restaurnt."
};

// ========================게임 보드의 구조체화====================================

// 1. 구조체 형식 정의 (typedef struct문법 활용)-------------------------
typedef struct smmObject {
    char name[MAX_CHARNAME];
    smmObjType_e objType;
    int type;
    int credit;
    int energy;
    smmObjGrade_e grade;
} smmObject_t;  // type을 뜻하는 의미에서

typedef struct smmFestival{
    char fes[MAX_CHARNAME];
    
} smmFestival_name;

typedef enum smmFood {
    chicken     = 0,
    beer        = 1,
    tanghulu    = 2,
    ramen       = 3,
    gamja       = 4,
    cupbab      = 5,
    zazang      = 6,
    schoolfood  = 7,
    pasta       = 8,
    pizza       = 9,
    hamburger   = 10,
    sandwich    = 11,
    yogart      = 12,
    bibim       = 13
} smmFood_e;

// 2. 구조체 배열 변수 정의------------------------------------------------
// smmObject_t smm_node[MAX_NODE];     // struct안해도 ㄱㅊ

// 지우는 것 보다 남겨두기(컴파일은 X)
/*
static char     smmObj_name[MAX_NODE][MAX_CHARNAME];
static int      smmObj_type[MAX_NODE];
static int      smmObj_credit[MAX_NODE];
static int      smmObj_energy[MAX_NODE];
*/
//static smmObject_t smm_node[MAX_NODE];

// 3. 관련 함수 변경-------------------------------------------------------
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
{
    smmObject_t* ptr;
    
    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
    
    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;
    
    return ptr;
}

char* smmObj_getTypeName(int type)
{
    return (char*)smmNodeName[type];
}

// 노드이름
char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->name;
}

// 노드타입
int smmObj_getNodeType(int* type)
{
    smmObject_t* ptr = (smmObject_t*)type;
    
    return ptr -> objType;
    //return smm_node[node_nr].type;
}

// node credit받기
int smmObj_getNodeCredit(int* credit)
{
    smmObject_t* ptr = (smmObject_t*)credit;
    
    return ptr -> credit;
    //return smm_node[node_nr].credit;
}

// node 에너지 받기
int smmObj_getNodeEnergy(int* energy)
{
    smmObject_t* ptr = (smmObject_t*)energy;
    
    return ptr -> energy;
    //return smm_node[node_nr].energy;
}

// grade 받기
int smmObj_getNodeGrade(int* grade)
{
    smmObject_t* ptr = (smmObject_t*)grade;
    
    return ptr -> grade;
}


