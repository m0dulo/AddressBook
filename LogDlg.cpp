#include "LogDlg.h"
#include <QDebug>

LogDlg::LogDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    m_LogMode = LOG_MODE_UNKNOWN;

    connect(ui.m_pLogPb, SIGNAL(clicked()), this, SLOT(logSlot()));
}

LogDlg::~LogDlg()
{
}

QString LogDlg::getUsrName()
{
    return ui.m_pUsrNameLe->text();
}

void LogDlg::logSlot()
{
    ui.m_pTipLa->clear();

    QString usr = ui.m_pUsrNameLe->text();
    QString pwd = ui.m_pPwdLe->text();

    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

    qDebug() << QString("In logSlot:usr[%1],pwd[%2]").arg(usr).arg(pwd);

    if ((usr == USR_NAME_ADMIN) && (md5 == PASSWORD_ADMIN))
    {
        m_LogMode = LOG_MODE_ADMIN;
    }
    else if ((usr == USR_NAME_OPR) && (md5 == PASSWORD_OPR))
    {
        m_LogMode = LOG_MODE_OPR;
    }
    else
    {
        m_LogMode = LOG_MODE_UNKNOWN;
        ui.m_pTipLa->setText(QString::fromLocal8Bit("用户名或密码错误，请重新输入"));
        return;
    }

    this->accept();
}
