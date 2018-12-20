#include "Realization.h"




const char PPnumber[20][3] = { { '1','3','9' },{ '1','3','8' } ,{ '1','3','7' } ,{ '1','5','1' },
{ '1','5','5' },{ '1','8','2' } ,{ '1','8','1' } ,{ '1','8','7' },
{ '1','5','7' },{ '1','4','7' } ,{ '1','3','0' } ,{ '1','9','0' },
{ '1','4','8' },{ '1','3','6' } ,{ '1','3','5' } ,{ '1','7','7' },
{ '1','7','8' },{ '1','8','9' } ,{ '1','9','2' } ,{ '1','5','2' } };
const char Organization[20][11] = { { "��ʦ��" },{ "������ѧ" },{ "������" },{ "���̴�" },
{ "�㽭��ѧ" },{ "��ҽ��" },{ "̨���ѧ" },{ "�ຣ��ѧ" },
{ "��۴�ѧ" },{ "������ѧ" },{ "��ɽ��ѧ" },{ "�廪��ѧ" },
{ "�人��ѧ" },{ "ͬ�ô�ѧ" },{ "ɽ����ѧ" },{ "������ѧ" },
{ "���ݴ�ѧ" },{ "���ϴ�ѧ" },{ "���ݴ�ѧ" },{ "�Ͽ���ѧ" } };
const char AddressT[20][11] = { { "����·" },{ "����·" },{ "����·" },{ "��������" },
{ "�����" },{ "��־���" },{ "�����" },{ "ͨ����" },
{ "��ֱ��" },{ "��԰��" },{ "һ����" },{ "���Ǻ쳡" },
{ "ѧ��·" },{ "������" },{ "�������" },{ "������" },
{ "���˴��" },{ "�Ĳ���" },{ "��ƽ·" },{ "�ĸ���" } };


Realization::Realization()
{
    for (int i = 0;i < 27;++i)
    {
        HashTable[i] = NULL;
        HashTable22[i] = NULL;
    }
}

Realization::~Realization()
{
}

void Realization::createAddressFile(const string& fileName)
{
    ofstream OutFile(fileName, ios::out | ios::binary);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 2000; i++) {
        people P;
        long Nnumber;
        while (1) {                                  //�����������
            Nnumber = rand() % 10;
            while (Nnumber < 3 || Nnumber > 5) {
                Nnumber = rand() % 10;
            }
            int m;
            char c;
            for (m = 0; m < Nnumber; m++)
            {
                int num = rand() % 25;
                c = num + 'a';
                P.name[m] = c;
            }
            P.name[m] = '\0'; break;
        }

        int mm;      //������ɵ绰��
        int n = rand() % 20;
        for (int i = 0; i < 3; i++) {
            P.Phonenumber[i] = PPnumber[n][i];
        }
        for (mm = 3; mm < 11; mm++)
            _itoa(rand() % 10, &P.Phonenumber[mm], 10);
        P.Phonenumber[mm] = '\0';

        int mmm;        //�������QQ��
        for (mmm = 0; mmm < 9; mmm++)
        {
            _itoa((rand() % 9) + 1, &P.QQnumber[mmm], 10);
        }
        P.QQnumber[mmm] = '\0';


        strcpy(P.OrDD, Organization[n]);
        strcpy(P.address, AddressT[n]);

        OutFile.write((char*)&P, sizeof(P));
    }
    cout << "�Ѳ���100���������" << endl;
}

void Realization::Init()//����ͨѶ¼�������ļ�
{
    ofstream OutFile(m_File, ios::out | ios::binary);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10000; i++) {
        people P;
        long Nnumber;
        while (1) {                                  //�����������
            Nnumber = rand() % 10;
            while (Nnumber < 3 || Nnumber > 5) {
                Nnumber = rand() % 10;
            }
            int m;
            char c;
            for (m = 0; m < Nnumber; m++)
            {
                int num = rand() % 25;
                c = num + 'a';
                P.name[m] = c;
            }
            P.name[m] = '\0'; break;
        }

        int mm;      //������ɵ绰��
        int n = rand() % 20;
        for (int i = 0; i < 3; i++) {
            P.Phonenumber[i] = PPnumber[n][i];
        }
        for (mm = 3; mm < 11; mm++)
            _itoa(rand() % 10, &P.Phonenumber[mm], 10);
        P.Phonenumber[mm] = '\0';

        int mmm;        //�������QQ��
        for (mmm = 0; mmm < 9; mmm++)
        {
            _itoa((rand() % 9) + 1, &P.QQnumber[mmm], 10);
        }
        P.QQnumber[mmm] = '\0';


        strcpy(P.OrDD, Organization[n]);
        strcpy(P.address, AddressT[n]);

        OutFile.write((char*)&P, sizeof(P));
    }
    cout << "�Ѳ���һ����������" << endl;
    cout << "������Ҫ��ӵ�����" << endl;
    cout << "������Ҫ��������ݸ���" << endl;
    int mmmm;
    people p;
    cin >> mmmm;
    for (int i = 1; i <= mmmm; i++) {
        cout << "�������" << i << "������" << endl;
        cin >> p.name >> p.Phonenumber >> p.QQnumber >> p.OrDD >> p.address;
        OutFile.write((char*)&p, sizeof(p));
    }
    OutFile.close();

    //ifstream InFile(m_File, ios::in | ios::binary); //���ȫ����Ϣ

    //people P;
    //InFile.read((char*)&P, sizeof(P));
    //while (InFile.good()) {
    //    cout << endl << setw(6) << P.name << "   " << setw(6) << P.Phonenumber << "   " << setw(6)
    //        << P.QQnumber << "   " << right << setw(15) << P.OrDD << "   " << right << setw(15) << P.address << endl;
    //    InFile.read((char*)&P, sizeof(P));
    //}
    //InFile.close();
    return;
}
void Realization::Add()//���Ӽ�¼
{
    ofstream OutFile(m_File, ios::app);
    //ofstream OutFileAdd("PersoninformationAdd.txt", ios::app);
    cout << "������Ҫ��ӵ�����" << endl;
    cout << "������Ҫ��������ݸ���" << endl;
    int mmmm;
    people p;
    cin >> mmmm;
    for (int i = 1; i <= mmmm; i++) {
        cout << "�������" << i << "������" << endl;
        cin >> p.name >> p.Phonenumber >> p.QQnumber >> p.OrDD >> p.address;
        //OutFileAdd.write((char*)&p, sizeof(p));
        OutFile.write((char*)&p, sizeof(p));
    }
    OutFile.close();
    //OutFileAdd.close();
    ifstream InFile(m_File, ios::in | ios::binary); //���ȫ����Ϣ

    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) {
        cout << endl << setw(6) << P.name << "   " << setw(6) << P.Phonenumber << "   " << setw(6)
            << P.QQnumber << "   " << right << setw(15) << P.OrDD << "   " << right << setw(15) << P.address << endl;
        InFile.read((char*)&P, sizeof(P));
    }
    InFile.close();
    cout << "��׷��!" << endl;
    return;
}

int Realization::Getkey(char c)// ��ȡ�ؼ��� 1
{
    return c % 'a';
}
void Realization::HashInit(Hash_Node *HashTablem[])//ɢ�б���
{
    ifstream InFile(m_File, ios::in | ios::binary);
    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) 
    {
        Hash_Node *node = new Hash_Node;
        int hashvalue = Getkey(P.name[0]);
        //node->P = P;

        strcpy(node->P.name, P.name);
        strcpy(node->P.Phonenumber, P.Phonenumber);
        strcpy(node->P.QQnumber, P.QQnumber);
        strcpy(node->P.OrDD, P.OrDD);
        strcpy(node->P.address, P.address);
        //cout << "In HashInit:name-"<< node->P.name << endl;
        node->next = NULL;
        node->next = HashTablem[hashvalue];
        HashTablem[hashvalue] = node;

        InFile.read((char*)&P, sizeof(P));
    }
    InFile.close();
}
void Realization::Del(char s[])//ɾ����¼
{
    HashInit(HashTable22);
    int hashvalue = Getkey(s[0]);
    bool flag = false;
    people PP[100]; int i = 1;
    Hash_Node* np = HashTable22[hashvalue];
    for (; np != NULL; np = np->next)
    {
        if (!strcmp(np->P.name, s)) {
            cout << i << " " << setw(6) << np->P.name << "   " << setw(6) << np->P.Phonenumber << "   " << setw(6)
                << np->P.QQnumber << "   " << right << setw(15) << np->P.OrDD << "   " << right << setw(15) << np->P.address << endl;
            PP[i] = np->P; i++;
            flag = true;
        }
    }
    if (flag) {
        cout << "��ѡ��Ҫɾ��������" << endl;
        int n; cin >> n;
        Hash_Node* np = HashTable22[hashvalue];
        Hash_Node* q = np;
        if ((strcmp(np->P.Phonenumber, PP[n].Phonenumber) == 0)) {
            np = np->next;
            HashTable22[hashvalue] = np;
            delete(q);
        }
        else {
            np = np->next;

            for (; np != NULL; np = np->next)
            {
                if ((strcmp(np->P.Phonenumber, PP[n].Phonenumber) == 0)) {
                    q->next = np->next;
                    delete(np); cout << "��ɾ��!" << endl; break;
                }
                else {
                    q = np;
                }
            }
        }
    }
    else {
        cout << "δ�ҵ�����!" << endl;
        return;
    }
    ofstream OutFile(m_File, ios::trunc | ios::binary);
    people phaha;
    for (int i = 0; i < 26; i++) {
        Hash_Node* np = HashTable22[i];
        for (; np != NULL; np = np->next)
        {
            phaha = np->P;
            OutFile.write((char*)&phaha, sizeof(phaha));
        }
    }
    OutFile.close();
    ifstream InFile(m_File, ios::in | ios::binary); //���ȫ����Ϣ

    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) {
        cout << setw(6) << P.name << "   " << setw(6) << P.Phonenumber << "   " << setw(6)
            << P.QQnumber << "   " << right << setw(15) << P.OrDD << "   " << right << setw(15) << P.address << endl;
        InFile.read((char*)&P, sizeof(P));
    }
    Hash_Node *q2 = NULL;
    Hash_Node *p2 = HashTable22[0];
    if (p2->next != NULL)p2 = p2->next;
    else memset(HashTable22, NULL, sizeof(HashTable22));
    for (int i = 1; i < 27; i++) {
        while (p2) {
            q2 = p2->next;
            free(p2);
            p2 = q2;
        }
        p2 = HashTable22[i];
    }
    memset(HashTable22, NULL, sizeof(HashTable22));
    InFile.close();
}
void Realization::Alter(char s[])//�޸ļ�¼
{
    HashInit(HashTable22);
    int hashvalue = Getkey(s[0]);
    bool flag = false;
    people PP[100]; int i = 1;
    Hash_Node* np = HashTable22[hashvalue];
    for (; np != NULL; np = np->next)
    {
        if (!strcmp(np->P.name, s)) {
            cout << i << " " << setw(6) << np->P.name << "   " << setw(6) << np->P.Phonenumber << "   " << setw(6)
                << np->P.QQnumber << "   " << right << setw(15) << np->P.OrDD << "   " << right << setw(15) << np->P.address << endl;
            PP[i] = np->P; i++;
            flag = true;
        }
    }
    if (flag) {
        cout << "��ѡ��Ҫ�޸ĵ�����" << endl;
        int n; cin >> n;
        Hash_Node* np = HashTable22[hashvalue];
        Hash_Node* q = np;
        people p;
        cout << "������Ҫ�滻������" << endl; cin >> p.name >> p.Phonenumber >> p.QQnumber >> p.OrDD >> p.address;
        if ((strcmp(np->P.Phonenumber, PP[n].Phonenumber) == 0)) {
            np->P = p; cout << "���޸�!" << endl;
        }
        else {
            np = np->next;

            for (; np != NULL; np = np->next)
            {
                if ((strcmp(np->P.Phonenumber, PP[n].Phonenumber) == 0)) {
                    np->P = p; cout << "���޸�!" << endl; break;
                }
                else {
                    q = np;
                }
            }
        }
    }
    else {
        cout << "δ�ҵ�����!" << endl;
        return;
    }
    ofstream OutFile(m_File, ios::trunc | ios::binary);
    people phaha;
    for (int i = 0; i < 26; i++) {
        Hash_Node* np = HashTable22[i];
        for (; np != NULL; np = np->next)
        {
            phaha = np->P;
            OutFile.write((char*)&phaha, sizeof(phaha));
        }
    }
    OutFile.close();
    ifstream InFile(m_File, ios::in | ios::binary); //���ȫ����Ϣ

    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) {
        cout << setw(6) << P.name << "   " << setw(6) << P.Phonenumber << "   " << setw(6)
            << P.QQnumber << "   " << right << setw(15) << P.OrDD << "   " << right << setw(15) << P.address << endl;
        InFile.read((char*)&P, sizeof(P));
    }
    Hash_Node *q2 = NULL;
    Hash_Node *p2 = HashTable22[0];
    if (p2->next != NULL)p2 = p2->next;
    else memset(HashTable22, NULL, sizeof(HashTable22));
    for (int i = 1; i < 27; i++) {
        while (p2) {
            q2 = p2->next;
            free(p2);
            p2 = q2;
        }
        p2 = HashTable22[i];
    }
    memset(HashTable22, NULL, sizeof(HashTable22));
    InFile.close();
}
int Realization::Getkey2(char *s)  //��ȡ�ؼ���  2
{
    int h = 0;
    for (; *s; s++) {
        h = *s + h * 31;
    }
    return h % 26;
}
void Realization::NameSearch(char s[])//��������
{
    HashInit(HashTable);
    int hashvalue = Getkey(s[0]);
    bool flag = false;
    Hash_Node* np = HashTable[hashvalue];
    for (; np != NULL; np = np->next)
    {
        if (!strcmp(np->P.name, s)) {
            cout << np->P.name << " " << np->P.Phonenumber << " " << np->P.QQnumber << " " << np->P.OrDD << " " << np->P.address << endl;
            flag = true;
        }
    }
    if (flag) {
        Hash_Node *q = NULL;
        Hash_Node *p = HashTable[0];
        if (p->next != NULL)p = p->next;
        else memset(HashTable, NULL, sizeof(HashTable));
        for (int i = 1; i < 27; i++) {
            while (p) {
                q = p->next;
                free(p);
                p = q;
            }
            p = HashTable[i];
        }
        memset(HashTable, NULL, sizeof(HashTable));
        return;
    }
    else {
        cout << "δ�ҵ�����!" << endl;
        memset(HashTable, NULL, sizeof(HashTable));
        return;
    }

}

void Realization::NameSearch(char s[], vector<people>& pVec)
{
    HashInit(HashTable);
    int hashvalue = Getkey(s[0]);
    bool flag = false;
    Hash_Node* np = HashTable[hashvalue];
    people p;
    //cout << "Start NameSearch"<<endl;
    for (; np != NULL; np = np->next)
    {
        //cout << np->P.name << endl;
        if (!strcmp(np->P.name, s)) 
        {
            cout << np->P.name << " " << np->P.Phonenumber << " " << np->P.QQnumber << " " << np->P.OrDD << " " << np->P.address << endl;
            strcpy(p.name, np->P.name);
            strcpy(p.Phonenumber, np->P.Phonenumber);
            strcpy(p.QQnumber, np->P.QQnumber);
            strcpy(p.OrDD, np->P.OrDD);
            strcpy(p.address, np->P.address);
            pVec.push_back(p);
            flag = true;
        }
    }
    //cout << "End NameSearch" << endl;
    if (flag) 
    {
        Hash_Node *q = NULL;
        Hash_Node *p = HashTable[0];
        if (p->next != NULL)
            p = p->next;
        else 
            //memset(HashTable, NULL, sizeof(HashTable));

        for (int i = 1; i < 27; i++) 
        {
            //cout << i << endl;
            while (p) 
            {
                q = p->next;
                free(p);
                p = q;
            }
            p = HashTable[i];
        }
        memset(HashTable, NULL, sizeof(HashTable));
        return;
    }
    else {
        cout << "δ�ҵ�����!" << endl;
        memset(HashTable, NULL, sizeof(HashTable));
        return;
    }
}


void Realization::InsertBST(BSTnode* &T, people P)//��������������
{
    if (!T) {
        BSTnode *B = new BSTnode;
        //B->P = P;
        strcpy(B->P.name, P.name);
        strcpy(B->P.Phonenumber, P.Phonenumber);
        strcpy(B->P.QQnumber, P.QQnumber);
        strcpy(B->P.OrDD, P.OrDD);
        strcpy(B->P.address, P.address);

        B->lchild = B->rchild = NULL;
        T = B;
    }
    else if (strcmp(T->P.Phonenumber, P.Phonenumber) > 0)
        InsertBST(T->lchild, P);
    else if (strcmp(T->P.Phonenumber, P.Phonenumber) < 0)
        InsertBST(T->rchild, P);
}
void Realization::BinarySortTreeInit()//��������������
{
    ifstream InFile(m_File, ios::in | ios::binary);
    if (m != 0) {
        TT = NULL;
        m = 0;
    }
    m++;
    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) {
        InsertBST(TT, P);
        InFile.read((char*)&P, sizeof(P));
    }
    InFile.close();
}
BSTnode*  Realization::SearchBST(BSTnode* T, char s[])//�绰�Ų���
{
    //cout << "In SearchBST" << endl;
    if (!T || strcmp(T->P.Phonenumber, s) == 0)return T;
    else if (strcmp(T->P.Phonenumber, s) > 0)return SearchBST(T->lchild, s);
    else if (strcmp(T->P.Phonenumber, s) < 0)return SearchBST(T->rchild, s);
}
void Realization::NumberSearch(char s[])//�绰�Ų���
{
    BinarySortTreeInit();
    BSTnode* T = SearchBST(TT, s);
    if (T == NULL) {
        cout << "δ�ҵ�����!" << endl; return;
    }
    else {
        cout << T->P.name << " " << T->P.Phonenumber << " " << T->P.QQnumber << " " << T->P.OrDD << " " << T->P.address << endl;
        return;
    }
}

void Realization::NumberSearch(char s[], vector<people>& pVec)
{
    //??????
    BinarySortTreeInit();
    BSTnode* T = SearchBST(TT, s);
    people p;
    if (T == NULL) {
        cout << "δ�ҵ�����!" << endl; return;
    }
    else {
        //cout <<"In NumberSearch:"<< T->P.name << " " << T->P.Phonenumber << " " << T->P.QQnumber << " " << T->P.OrDD << " " << T->P.address << endl;

        strcpy(p.name, T->P.name);
        strcpy(p.Phonenumber, T->P.Phonenumber);
        strcpy(p.QQnumber, T->P.QQnumber);
        strcpy(p.OrDD, T->P.OrDD);
        strcpy(p.address, T->P.address);
        pVec.push_back(p);

        return;
    }
}

void Realization::SortQQnumber(int left, int right, vector<people> &ST)
{
    people p, temp;
    int i, j;
    if (left > right)
        return;
    //temp = ST[left];
    strcpy(temp.name, ST[left].name);
    strcpy(temp.Phonenumber, ST[left].Phonenumber);
    strcpy(temp.QQnumber, ST[left].QQnumber);
    strcpy(temp.OrDD, ST[left].OrDD);
    strcpy(temp.address, ST[left].address);

    i = left; j = right;
    while (i != j) {
        while (strcmp(ST[j].QQnumber, temp.QQnumber) >= 0 && i < j)j--;
        while (strcmp(ST[i].QQnumber, temp.QQnumber) <= 0 && i < j)i++;
        if (i < j) {
            //p = ST[i];
            strcpy(p.name, ST[i].name);
            strcpy(p.Phonenumber, ST[i].Phonenumber);
            strcpy(p.QQnumber, ST[i].QQnumber);
            strcpy(p.OrDD, ST[i].OrDD);
            strcpy(p.address, ST[i].address);

            //ST[i] = ST[j];
            strcpy(ST[i].name, ST[j].name);
            strcpy(ST[i].Phonenumber, ST[j].Phonenumber);
            strcpy(ST[i].QQnumber, ST[j].QQnumber);
            strcpy(ST[i].OrDD, ST[j].OrDD);
            strcpy(ST[i].address, ST[j].address);

            //ST[j] = p;
            strcpy(ST[j].name, p.name);
            strcpy(ST[j].Phonenumber, p.Phonenumber);
            strcpy(ST[j].QQnumber, p.QQnumber);
            strcpy(ST[j].OrDD, p.OrDD);
            strcpy(ST[j].address, p.address);

        }
    }
    //ST[left] = ST[i];
    strcpy(ST[left].name, ST[i].name);
    strcpy(ST[left].Phonenumber, ST[i].Phonenumber);
    strcpy(ST[left].QQnumber, ST[i].QQnumber);
    strcpy(ST[left].OrDD, ST[i].OrDD);
    strcpy(ST[left].address, ST[i].address);

    //ST[i] = temp;
    strcpy(ST[i].name, temp.name);
    strcpy(ST[i].Phonenumber, temp.Phonenumber);
    strcpy(ST[i].QQnumber, temp.QQnumber);
    strcpy(ST[i].OrDD, temp.OrDD);
    strcpy(ST[i].address, temp.address);

    SortQQnumber(left, i - 1, ST);
    SortQQnumber(i + 1, right, ST);
    return;
    /*for (int i = 1; i <= ST.size()-1; i++)
    if(ST[i].QQnumber == "777788888")
    cout <<endl<<endl<<endl<<endl<< setw(6) <<ST[i].name << "   " << setw(6) << ST[i].Phonenumber << "   " << setw(6)
    << ST[i].QQnumber << "   " << right << setw(15) << ST[i].OrDD << "   " << right << setw(15) << ST[i].address << endl<<endl<<endl<<endl;
    else
    cout << endl << setw(6) << ST[i].name << "   " << setw(6) << ST[i].Phonenumber << "   " << setw(6)
    << ST[i].QQnumber << "   " << right << setw(15) << ST[i].OrDD << "   " << right << setw(15) << ST[i].address << endl;

    */
}
void Realization::QQnumberSearch(char s[])//QQ�Ų���
{
    ifstream InFile(m_File, ios::in | ios::binary);
    vector<people> ST;
    people P = { "abcd","12345678945","123456789","��ʦ��","ѧ��·" };
    ST.push_back(P);
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good()) {
        ST.push_back(P);
        InFile.read((char*)&P, sizeof(P));
    }
    InFile.close();
    SortQQnumber(1, ST.size() - 1, ST);
    int low = 1; int high = ST.size() - 1; int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(s, ST[mid].QQnumber) == 0) {
            cout << ST[mid].name << " " << ST[mid].Phonenumber << " "
                << ST[mid].QQnumber << " " << ST[mid].OrDD << " " << ST[mid].address << endl;
            return;
        }
        else if (strcmp(s, ST[mid].QQnumber) < 0)high = mid - 1;
        else low = mid + 1;
    }
    cout << "δ�ҵ�����!" << endl;
    return;
}

void Realization::QQnumberSearch(char s[], vector<people>& pVec)
{
    ///?????
    //cout << "In QQnumberSearch" << endl;
    ifstream InFile(m_File, ios::in | ios::binary);
    vector<people> ST;
    people P = { "abcd","12345678945","123456789","��ʦ��","ѧ��·" };
    ST.push_back(P);
    InFile.read((char*)&P, sizeof(P));
    people p1;
    while (InFile.good()) 
    {
        //cout << P.QQnumber << endl;
        ST.push_back(P);
        InFile.read((char*)&P, sizeof(P));
    }
    //cout << "In QQnumberSearch:after read file" << endl;
    InFile.close();
    //cout << "In QQnumberSearch:2" << endl;
    SortQQnumber(1, ST.size() - 1, ST);
    //cout << "In QQnumberSearch:3" << endl;
    int low = 1; int high = ST.size() - 1; int mid;
    while (low <= high) 
    {
        //cout << "In QQnumberSearch:in while" << endl;
        mid = (low + high) / 2;
        if (strcmp(s, ST[mid].QQnumber) == 0) 
        {
            //cout << ST[mid].name << " " << ST[mid].Phonenumber << " "
                //<< ST[mid].QQnumber << " " << ST[mid].OrDD << " " << ST[mid].address << endl;

            strcpy(p1.name, ST[mid].name);
            strcpy(p1.Phonenumber, ST[mid].Phonenumber);
            strcpy(p1.QQnumber, ST[mid].QQnumber);
            strcpy(p1.OrDD, ST[mid].OrDD);
            strcpy(p1.address, ST[mid].address);
            pVec.push_back(p1);

            return;
        }
        else if (strcmp(s, ST[mid].QQnumber) < 0)
            high = mid - 1;
        else 
            low = mid + 1;
    }
    cout << "δ�ҵ�����!" << endl;
    return;
}

void Realization::Edit()
{
    bool flag = true;
    int n;
    people p;
    char *s = new char[15];
    while (flag) {
        cout << " ͨѶ¼�༭��ϵͳ " << endl << endl;
        cout << "1------����ͨѶ¼��¼���¼" << endl;
        cout << "2------���Ӽ�¼" << endl;
        cout << "3------ɾ����¼" << endl;
        cout << "4------�޸ļ�¼" << endl;
        cout << "5------�������˵�" << endl;
        cin >> n;
        switch (n) {
        case 1:Init(); break;
        case 2:Add(); break;
        case 3:cout << "������Ҫɾ�������ݵ�����" << endl; cin >> s; Del(s); break;
        case 4:cout << "������Ҫ�޸ĵ����ݵ�����" << endl; cin >> s;
            Alter(s); break;
        case 5:flag = false; break;
        default: cout << "�����������������" << endl; break;
        }
    }
    return;
}
void Realization::Search()
{
    bool flag = true;
    int n;
    char *s = new char[15];
    while (flag) {
        cout << "ͨѶ¼������ϵͳ" << endl << endl;
        cout << "1------���������ң�ɢ�б���ң�" << endl;
        cout << "2------���绰�Ų��ң��������������ң�" << endl;
        cout << "3------��QQ�Ų��ң����ֲ��ң�" << endl;
        cout << "4--------�������˵�" << endl;
        cin >> n;
        switch (n) {
        case 1:cout << "������Ҫ���ҵ�����" << endl; cin >> s; NameSearch(s); break;
        case 2:cout << "������Ҫ���ҵĵ绰��" << endl; cin >> s; NumberSearch(s); break;
        case 3:cout << "������Ҫ���ҵ�QQ��" << endl; cin >> s; QQnumberSearch(s); break;
        case 4:flag = false; break;
        default: cout << "�����������������" << endl; break;
        }
    }
    return;
}
void Realization::Manage()
{
    bool flag = true;
    int n;
    while (flag) {
        cout << "ͨѶ¼����ϵͳ" << endl << endl;
        cout << "1------ͨѶ¼�༭" << endl;
        cout << "2------ͨѶ¼����" << endl;
        cout << "3---------�˳�" << endl;
        cin >> n;
        switch (n) {
        case 1:Edit(); break;
        case 2:Search(); break;
        case 3:flag = false; break;
        default: cout << "�����������������!" << endl << endl; break;
        }
    }
    cout << "���˳�!" << endl;
}

void Realization::setFile(const string& file)
{
    m_File = file;
}

//int main()
//{
//    Manage();
//    return 0;
//}
