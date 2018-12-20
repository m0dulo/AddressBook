#include "Address.h"
#include <QDebug>
#include "LogDlg.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "Realization.h"

#define ADDRESS_FILE_SUFFIX ".txt"


const int SEARCH_MODE_NAME = 0;
const int SEARCH_MODE_PHONE = 1;
const int SEARCH_MODE_QQ = 2;


Address::Address(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    initUi();

    connect(ui.m_pLogPb, SIGNAL(clicked()), this, SLOT(logSlot()));
    connect(ui.m_pSearchPb, SIGNAL(clicked()), this, SLOT(searchSlot()));
    connect(ui.m_pNewPb, SIGNAL(clicked()), this, SLOT(newSlot()));
    connect(ui.m_pSelectPb, SIGNAL(clicked()), this, SLOT(selectSolt()));
    connect(ui.m_pDelPb, SIGNAL(clicked()), this, SLOT(delSlot()));
    connect(ui.m_pSavePb, SIGNAL(clicked()), this, SLOT(saveSlot()));
    connect(ui.m_pAddPb, SIGNAL(clicked()), this, SLOT(addSlot()));
}

Address::~Address()
{
}

bool Address::createNewAddress(const QString& fileName)
{
    qDebug() << QString("In newSlot");

    Realization().createAddressFile(fileName.toStdString());

    return true;
}
void Address::readAddressFileInfo(const QString& fileName,QVector<AddressItem>& infoVec)
{
    AddressItem item;

    ifstream InFile(fileName.toStdString(), ios::in | ios::binary); //输出全部信息

    people P;
    InFile.read((char*)&P, sizeof(P));
    while (InFile.good())
    {
        //cout << endl << setw(6) << P.name << "   " << setw(6) << P.Phonenumber << "   " << setw(6)
            //<< P.QQnumber << "   " << right << setw(15) << P.OrDD << "   " << right << setw(15) << P.address << endl;

        item.name = QString::fromLocal8Bit(P.name);
        item.phone = QString::fromLocal8Bit(P.Phonenumber);
        item.qq = QString::fromLocal8Bit(P.QQnumber);
        item.ordd = QString::fromLocal8Bit(P.OrDD);
        item.address = QString::fromLocal8Bit(P.address);

        infoVec.append(item);

        InFile.read((char*)&P, sizeof(P));
    }
    InFile.close();

}

void Address::delRows()
{
    QModelIndexList indexList1 = ui.m_pInfoTv->selectionModel()->selectedIndexes();
    while (!indexList1.isEmpty())
    {
        QModelIndexList indexList = deleteRepeatList(indexList1);
        QModelIndex index = indexList.first();
        m_pListModel->removeRow(index.row());
        indexList1 = ui.m_pInfoTv->selectionModel()->selectedIndexes();
    }
}


QModelIndexList Address::deleteRepeatList(QModelIndexList indexList)
{
    QModelIndex index, newIndex;
    QModelIndexList newIndexList;
    foreach(index, indexList)
    {
        if (newIndex.row() != index.row())
        {
            newIndex = index;
            newIndexList.append(newIndex);
        }
    }
    return newIndexList;
}

void Address::searchMode()
{
    ui.m_pAddPb->setEnabled(false);
    ui.m_pSavePb->setEnabled(false);
    ui.m_pDelPb->setEnabled(false);
}

void Address::allMode()
{
    ui.m_pAddPb->setEnabled(true);
    ui.m_pSavePb->setEnabled(true);
    ui.m_pDelPb->setEnabled(true);
}


//here????????????????????????????
void Address::searchAddress(const QString& info, QVector<AddressItem>& infoVec)
{
    vector<people> pVec;

    Realization real;
    real.setFile(m_SelectAddressFile.toStdString());

    int index = ui.m_pSearchModeCb->currentIndex();
    char searchAray[100];
    strncpy(searchAray, info.toLocal8Bit(), sizeof(searchAray));
    switch (index)
    {
    case SEARCH_MODE_NAME:
        real.NameSearch(searchAray, pVec);
        break;
    case SEARCH_MODE_QQ:
        real.QQnumberSearch(searchAray, pVec);
        break;
    case SEARCH_MODE_PHONE:
        real.NumberSearch(searchAray, pVec);
        break;
    }

    AddressItem itm;
    qDebug() << QString("Find num:%1").arg(pVec.size());
    for (int i = 0;i < pVec.size();++i)
    {

        itm.name = QString::fromLocal8Bit(pVec.at(i).name);
        itm.phone = QString::fromLocal8Bit(pVec.at(i).Phonenumber);
        itm.qq = QString::fromLocal8Bit(pVec.at(i).QQnumber);
        itm.ordd = QString::fromLocal8Bit(pVec.at(i).OrDD);
        itm.address = QString::fromLocal8Bit(pVec.at(i).address);

        infoVec.append(itm);
    }
}


bool Address::openAddress(const QString& fileName)
{
    QVector<AddressItem> infoVec;
    readAddressFileInfo(fileName,infoVec);

    m_pListModel->removeRows(0, m_pListModel->rowCount());


    QStandardItem* tmp_item;
    int cnt = 0;
    for (int i = 0;i < infoVec.size();++i)
    {
        tmp_item = new QStandardItem(infoVec.at(i).name);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 0, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).phone);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 1, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).qq);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 2, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).ordd);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 3, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).address);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 4, tmp_item);


        cnt++;
    }

    return true;
}

void Address::loadAddressFile(const QString& fileName)
{
    if (openAddress(fileName))
    {
        m_SelectAddressFile = fileName;
        ui.m_pFileLe->setText(m_SelectAddressFile);
    }
    else
    {
        qDebug() << QString("In loadAddressFile:load file[%1] fail").arg(fileName);
    }
}

void Address::changeLogMode(const QString& usr, const LogMode& mode)
{
    switch (mode)
    {
    case LOG_MODE_ADMIN:
        ui.m_pUsrInfoLa->setText(QString::fromLocal8Bit("当前用户：%1 权限：编辑&&浏览").arg(usr));
        adminMode();
        break;
    case LOG_MODE_OPR:
        ui.m_pUsrInfoLa->setText(QString::fromLocal8Bit("当前用户：%1 权限：浏览").arg(usr));
        oprMode();
        break;
    default:
        ui.m_pUsrInfoLa->setText(QString::fromLocal8Bit("当前用户：未知 权限：未知"));
        unknownMode();
    }
}
void Address::adminMode()
{
    ui.m_pAddPb->setEnabled(true);
    ui.m_pSavePb->setEnabled(true);
    ui.m_pDelPb->setEnabled(true);
    ui.m_pNewPb->setEnabled(true);
    ui.m_pSearchPb->setEnabled(true);
    ui.m_pSelectPb->setEnabled(true);
}

void Address::oprMode()
{
    ui.m_pAddPb->setEnabled(false);
    ui.m_pSavePb->setEnabled(false);
    ui.m_pDelPb->setEnabled(false);
    ui.m_pNewPb->setEnabled(false);
    ui.m_pSearchPb->setEnabled(true);
    ui.m_pSelectPb->setEnabled(true);
}

void Address::unknownMode()
{
    ui.m_pAddPb->setEnabled(false);
    ui.m_pSavePb->setEnabled(false);
    ui.m_pDelPb->setEnabled(false);
    ui.m_pNewPb->setEnabled(false);
    ui.m_pSearchPb->setEnabled(false);
    ui.m_pSelectPb->setEnabled(false);
}
void Address::initUi()
{
    initTable();
    unknownMode();
}

void Address::initTable()
{
    m_pListModel = new QStandardItemModel(this);
    m_pListModel->setColumnCount(5);
    m_pListModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
    m_pListModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("手机"));
    m_pListModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("QQ"));
    m_pListModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("学校"));
    m_pListModel->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("地址"));


    m_pProxyModel = new QSortFilterProxyModel(this);
    m_pProxyModel->setSourceModel(m_pListModel);

    ui.m_pInfoTv->setModel(m_pProxyModel);
    ui.m_pInfoTv->resizeRowsToContents();
    ui.m_pInfoTv->horizontalHeader()->setStretchLastSection(true);
    ui.m_pInfoTv->setAlternatingRowColors(true);
    ui.m_pInfoTv->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Address::logSlot()
{
    LogDlg dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        m_LogMode = dlg.getLogMode();
        QString usr = dlg.getUsrName();
        changeLogMode(usr,m_LogMode);
    }
}


void Address::searchSlot()
{
    QString info = ui.m_pSearchInfoLe->text();
    if (info.isEmpty())
    {
        loadAddressFile(m_SelectAddressFile);
        allMode();

        return;
    }
    
    QVector<AddressItem> infoVec;
    searchAddress(info,infoVec);

    m_pListModel->removeRows(0, m_pListModel->rowCount());

    QStandardItem* tmp_item;
    int cnt = 0;
    for (int i = 0; i < infoVec.size(); ++i)
    {
        tmp_item = new QStandardItem(infoVec.at(i).name);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 0, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).phone);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 1, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).qq);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 2, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).ordd);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 3, tmp_item);

        tmp_item = new QStandardItem(infoVec.at(i).address);
        tmp_item->setTextAlignment(Qt::AlignCenter);
        m_pListModel->setItem(cnt, 4, tmp_item);

        cnt++;
    }



    searchMode();
}

void Address::newSlot()
{
    qDebug() << QString("In newSlot");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), ".", ADDRESS_FILE_SUFFIX);
    if (fileName.isEmpty())
    {
        return;
    }

    QString fullName;
    if (!fileName.endsWith(ADDRESS_FILE_SUFFIX))
    {
        fullName = fileName + ADDRESS_FILE_SUFFIX;
    }
    else
    {
        fullName = fileName;
    }
    

    if (QFile(fullName).exists())
    {
        QMessageBox msgBox(QMessageBox::Warning, QString::fromLocal8Bit("警告"),
            QString::fromLocal8Bit("文件已存在，请输入其他文件名"), 0, this);
        msgBox.addButton(QString::fromLocal8Bit("确定"), QMessageBox::AcceptRole);
        if (msgBox.exec() == QMessageBox::AcceptRole);
        return;
    }


    if (createNewAddress(fullName))
    {
        QMessageBox msgBox(QMessageBox::Warning, QString::fromLocal8Bit("提示"),
            QString::fromLocal8Bit("通讯录文件新建成功，并切换为该文件"), 0, this);
        msgBox.addButton(QString::fromLocal8Bit("确定"), QMessageBox::AcceptRole);
        if (msgBox.exec() == QMessageBox::AcceptRole);
        loadAddressFile(fullName);
        return;
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, QString::fromLocal8Bit("提示"),
            QString::fromLocal8Bit("通讯录文件新建失败"), 0, this);
        msgBox.addButton(QString::fromLocal8Bit("确定"), QMessageBox::AcceptRole);
        if (msgBox.exec() == QMessageBox::AcceptRole);
        return;
    }
}

void Address::selectSolt()
{
    qDebug() << QString("In selectSolt");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select File"), ".", tr("Text File (*%1)").arg(ADDRESS_FILE_SUFFIX));
    if (!fileName.isEmpty())
    {
        loadAddressFile(fileName);
    }
}

void Address::delSlot()
{
    delRows();
}

void Address::addSlot()
{
    QStandardItem* tmp_item;
    int cnt = m_pListModel->rowCount();

    tmp_item = new QStandardItem("");
    tmp_item->setTextAlignment(Qt::AlignCenter);
    m_pListModel->setItem(cnt, 0, tmp_item);

    tmp_item = new QStandardItem("");
    tmp_item->setTextAlignment(Qt::AlignCenter);
    m_pListModel->setItem(cnt, 1, tmp_item);

    tmp_item = new QStandardItem("");
    tmp_item->setTextAlignment(Qt::AlignCenter);
    m_pListModel->setItem(cnt, 2, tmp_item);

    tmp_item = new QStandardItem("");
    tmp_item->setTextAlignment(Qt::AlignCenter);
    m_pListModel->setItem(cnt, 3, tmp_item);

    tmp_item = new QStandardItem("");
    tmp_item->setTextAlignment(Qt::AlignCenter);
    m_pListModel->setItem(cnt, 4, tmp_item);

    ui.m_pInfoTv->scrollToBottom();
}

void Address::saveSlot()
{
    ofstream OutFile(m_SelectAddressFile.toStdString(), ios::out | ios::binary);
   //clear the file
    OutFile.clear();

    people P;
    QString info;
    QModelIndex index;
    for (int i = 0;i < m_pListModel->rowCount();++i)
    {
        memset(P.name,0,sizeof(P.name));
        index = m_pListModel->index(i, 0);
        info = m_pListModel->data(index).toString();
        strncpy(P.name, info.toLocal8Bit(), sizeof(P.name));

        memset(P.Phonenumber, 0, sizeof(P.Phonenumber));
        index = m_pListModel->index(i, 1);
        info = m_pListModel->data(index).toString();
        strncpy(P.Phonenumber, info.toLocal8Bit(), sizeof(P.Phonenumber));

        memset(P.QQnumber, 0, sizeof(P.QQnumber));
        index = m_pListModel->index(i, 2);
        info = m_pListModel->data(index).toString();
        strncpy(P.QQnumber, info.toLocal8Bit(), sizeof(P.QQnumber));

        memset(P.OrDD, 0, sizeof(P.OrDD));
        index = m_pListModel->index(i, 3);
        info = m_pListModel->data(index).toString();
        strncpy(P.OrDD, info.toLocal8Bit(), sizeof(P.OrDD));

        memset(P.address, 0, sizeof(P.address));
        index = m_pListModel->index(i, 4);
        info = m_pListModel->data(index).toString();
        strncpy(P.address, info.toLocal8Bit(), sizeof(P.address));

        OutFile.write((char*)&P, sizeof(P));
    }
}
