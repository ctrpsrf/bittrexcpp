#ifndef BITTREXWRAPPER_H
#define BITTREXWRAPPER_H
#include <QObject>
#include <QString>
#include <QSsl>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <hmac_sha512.h>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <vector>
class bittrexwrapper
{
private:
    QString API_Key, API_Secret;
public:
    QNetworkAccessManager *mngr;
    bittrexwrapper(QString Key, QString Secret);
    QString getMarkets();
    QString getCurrencies();
    QString getTicker(QString market);
    QString getMarketSummaries();
    QString getMarketSummary(QString market);
    QString getOrderBook(QString market, QString type);
    QString getMarketHistory(QString market);
    QString buyLimit(QString market, QString quantity, QString rate);
    QString sellLimit(QString market, QString quantity, QString rate);
    QString cancelOrder(QString uuid);
    QString getOpenOrders(QString market);
    QString getBalances();
    QString getBalance(QString currency);
    QString getDepositAddress(QString currency);
    QString getOrder(QString uuid);
    QString getOrderHistory(QString market);
    QString getWithdrawalHistory(QString currency);
    QString getDepositHistory(QString currency);
    QString publicQueryNonParam(QString method);
    std::string getHMAC2(std::string keyParam, std::string message);
    QString publicQueryWithParam(QString method, std::vector<QString> params);
    QString privateQuery(QString method, std::vector<QString> params);
};

#endif // BITTREXWRAPPER_H
