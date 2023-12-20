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


char* smmObj_getTypeName(int type)
{
    return (char*)smmNodeName[type];
}

typedef enum smmObjGrade {
    smmObjGrade_Ap = 0,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;

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

char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->name;
}

int smmObj_getNodeType(int node_nr)
{
    return smm_node[node_nr].type;
}

int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit;
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}

#if 0


//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

#endif
