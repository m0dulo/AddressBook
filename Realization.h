#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<iomanip>
#include<vector>
#include<stdlib.h>
#include <string>
#include <vector>
using namespace std;

typedef struct people {//个人信息
    char name[7];
    char Phonenumber[12];
    char QQnumber[10];
    char OrDD[20];
    char address[20];

    people operator=(const people& b)
    {
        people p;
        strcpy(p.name, b.name);
        strcpy(p.Phonenumber, b.Phonenumber);
        strcpy(p.QQnumber, b.QQnumber);
        strcpy(p.OrDD, b.OrDD);
        strcpy(p.address, b.address);
        return p;
    }
}people, *Lperson;

typedef struct Hash_Node {//散列表
                          //int key;
    people P;
    struct Hash_Node *next;
}Hash_Node;

typedef struct BSTree {//二叉排序树
    people P;
    struct BSTree *lchild, *rchild;
}BSTnode;

typedef struct {//QQ号查找的结构体
    int length;
    people P;
}SSTable;

class Realization
{
public:
    Realization();
    ~Realization();


    void createAddressFile(const string& fileName);

    void Init();
    void Add();
    int Getkey(char c);
    void HashInit(Hash_Node *HashTablem[]);
    void Del(char s[]);
    void Alter(char s[]);
    int Getkey2(char *s);
    void NameSearch(char s[]);
    void NameSearch(char s[], vector<people>& pVec);
    void InsertBST(BSTnode* &T, people P);
    void BinarySortTreeInit();
    BSTnode*  SearchBST(BSTnode* T, char s[]);
    void NumberSearch(char s[]);
    void NumberSearch(char s[], vector<people>& pVec);
    void SortQQnumber(int left, int right, vector<people> &ST);
    void QQnumberSearch(char s[]);
    void QQnumberSearch(char s[], vector<people>& pVec);
    void Edit();
    void Search();
    void Manage();

    void setFile(const string& file);


private:
    Hash_Node *HashTable[27];
    Hash_Node *HashTable22[27];
    string m_File;
    BSTnode* TT = NULL;
    int m = 0;
};

