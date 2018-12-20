#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Address.h"
#include "LogDlg.h"

class QStandardItemModel;
class QSortFilterProxyModel;
class Realization;


struct AddressItem
{
    QString name;
    QString phone;
    QString qq;
    QString ordd;
    QString address;
};

class Address : public QMainWindow
{
    Q_OBJECT

public:
    Address(QWidget *parent = Q_NULLPTR);
    ~Address();


private:
    bool createNewAddress(const QString& fileName);
    bool openAddress(const QString& fileName);
    void loadAddressFile(const QString& fileName);
    void changeLogMode(const QString& usr,const LogMode& mode);

    void initUi();
    void initTable();

    void readAddressFileInfo(const QString& fileName,QVector<AddressItem>& infoVec);

    void delRows();
    QModelIndexList deleteRepeatList(QModelIndexList indexList);

    void searchMode();
    void allMode();

    void searchAddress(const QString& info, QVector<AddressItem>& infoVec);

    void adminMode();
    void oprMode();
    void unknownMode();

private slots:
    void logSlot();
    void searchSlot();
    void newSlot();
    void selectSolt();

    void delSlot();
    void addSlot();
    void saveSlot();

private:
    Ui::AddressClass ui;
    QString m_SelectAddressFile;
    LogMode m_LogMode;

    QStandardItemModel* m_pListModel;
    QSortFilterProxyModel* m_pProxyModel;
};
