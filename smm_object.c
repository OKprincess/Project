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

/*
static char smmFoodCard [MAX_CHARNAME] =
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
    "sing_a_song",
    "After_Graduate?",
    "What_do_you_want_to_do_at_home?",
    "Talk_about_programming_class.",
    "Introduce_your_favorite_restaurnt."
};
*/

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
