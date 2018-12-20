#pragma once

#include <QDialog>
#include <QCryptographicHash>
#include "ui_LogDlg.h"

const QString USR_NAME_ADMIN = "Admin";
const QString PASSWORD_ADMIN = "e3afed0047b08059d0fada10f400c1e5";

const QString USR_NAME_OPR = "Nor";
const QString PASSWORD_OPR = "5f61fcb6e17f7a46a46a47c7977c90c1";


enum LogMode
{
    LOG_MODE_UNKNOWN = 0,
    LOG_MODE_ADMIN,
    LOG_MODE_OPR
};


class LogDlg : public QDialog
{
    Q_OBJECT

public:
    LogDlg(QWidget *parent = Q_NULLPTR);
    ~LogDlg();
    
    LogMode getLogMode()
    {
        return m_LogMode;
    }

    QString getUsrName();

private slots:
    void logSlot();

private:
    Ui::LogDlg ui;
    LogMode m_LogMode;
};
