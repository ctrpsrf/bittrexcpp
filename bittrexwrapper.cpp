#include "bittrexwrapper.h"

bittrexwrapper::bittrexwrapper(QString Key="", QString Secret="")
{
    API_Key = Key;
    API_Secret = Secret;
    mngr = new QNetworkAccessManager();
}

QString bittrexwrapper::privateQuery(QString method, std::vector<QString> params)
{
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    __uint64_t nonce = seconds;
    QEventLoop eventLoop;
    QString paramToUrl = "";
    foreach (QString item, params) {
        paramToUrl += item + "&";
    }
    QString uri = "https://bittrex.com/api/v1.1/account/getbalances?apikey=" + API_Key +"&nonce="+QString::number(nonce) + "&" + paramToUrl;
    QNetworkRequest requ = QNetworkRequest(QUrl(uri));
    QString sign = QString::fromStdString(getHMAC2(API_Secret.toStdString(), uri.toStdString()));
    requ.setRawHeader("apisign", sign.toUtf8());
    QNetworkReply*  reply=mngr->get(requ);

    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError){
        QString strReply = (QString)reply->readAll();
        return strReply;
    }
    else {
        QString tmpNull = "Error: Connection is not available.";
        return tmpNull;
    }
}

QString bittrexwrapper::publicQueryNonParam(QString method){
    QEventLoop eventLoop;
    QNetworkRequest requ = QNetworkRequest(QUrl("https://bittrex.com/api/v1.1/public/" + method));
    QNetworkReply* reply = mngr->get(requ);
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError){
        QString strReply = (QString)reply->readAll();
        return strReply;
    }
    else {
        QString tmpNull = "Eror: Connection is not available.";
        return tmpNull;
    }
}

std::__cxx11::string bittrexwrapper::getHMAC2(std::__cxx11::string keyParam, std::__cxx11::string message)
{
    char key[10000];
    char data[10000];
    strcpy(key, keyParam.c_str());
    strncpy(data, message.c_str(), sizeof(data));

    unsigned char* digest;


    digest = HMAC(EVP_sha512(), key, strlen(key), (unsigned char*) data, strlen(data), NULL, NULL);
    char mdString[SHA512_DIGEST_LENGTH];
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        sprintf(&mdString[i * 2], "%02x", (unsigned int) digest[i]);

    std::string output = mdString;
    return output;
}

QString bittrexwrapper::publicQueryWithParam(QString method, std::vector<QString> params)
{
    QEventLoop eventLoop;
    QString paramToUrl = "";
    foreach (QString item, params) {
        paramToUrl += item + "&";
    }
    QNetworkRequest requ = QNetworkRequest(QUrl("https://bittrex.com/api/v1.1/public/" + method + "?" + paramToUrl));
    QNetworkReply* reply = mngr->get(requ);
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError){
        QString strReply = (QString)reply->readAll();
        return strReply;
    }
    else {
        QString tmpNull = "Eror: Connection is not available";
        return tmpNull;
    }
}


QString bittrexwrapper::getMarkets()
{
    return publicQueryNonParam("getmarkets");
}

QString bittrexwrapper::getCurrencies()
{
    return publicQueryNonParam("getcurrencies");
}

QString bittrexwrapper::getTicker(QString market)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    return publicQueryWithParam("getticker", tmp);
}

QString bittrexwrapper::getMarketSummaries()
{
    return publicQueryNonParam("getmarketsummaries");
}

QString bittrexwrapper::getMarketSummary(QString market)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    return publicQueryWithParam("getmarketsummary", tmp);
}

QString bittrexwrapper::getOrderBook(QString market, QString type)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    tmp.push_back("type=" + type);
    return publicQueryWithParam("getorderbook", tmp);
}

QString bittrexwrapper::getMarketHistory(QString market)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    return publicQueryWithParam("getmarkethistoryr", tmp);
}

QString bittrexwrapper::buyLimit(QString market, QString quantity, QString rate)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    tmp.push_back("quantity="+quantity);
    tmp.push_back("rate=" + rate);
    return privateQuery("buylimit", tmp);
}

QString bittrexwrapper::sellLimit(QString market, QString quantity, QString rate)
{
    std::vector<QString> tmp;
    tmp.push_back("market="+market);
    tmp.push_back("quantity="+quantity);
    tmp.push_back("rate=" + rate);
    return privateQuery("selllimit", tmp);
}

QString bittrexwrapper::cancelOrder(QString uuid)
{
    std::vector<QString> tmp;
    tmp.push_back("uuid="+uuid);
    return privateQuery("cancel", tmp);
}

QString bittrexwrapper::getOpenOrders(QString market)
{
    std::vector<QString> tmp;
    if (market.length()) {
        tmp.push_back("market="+market);
    }
    return privateQuery("getopenorders", tmp);
}

QString bittrexwrapper::getBalances()
{
    std::vector<QString> tmp;
    return privateQuery("getbalances", tmp);
}

QString bittrexwrapper::getBalance(QString currency)
{
    std::vector<QString> tmp;
    tmp.push_back("currency="+currency);
    return privateQuery("getbalance", tmp);
}

QString bittrexwrapper::getDepositAddress(QString currency)
{
    std::vector<QString> tmp;
    tmp.push_back("currency="+currency);
    return privateQuery("getdepositaddress", tmp);
}

QString bittrexwrapper::getOrder(QString uuid)
{
    std::vector<QString> tmp;
    tmp.push_back("uuid="+uuid);
    return privateQuery("getorder", tmp);
}

QString bittrexwrapper::getOrderHistory(QString market)
{
    std::vector<QString> tmp;
    return privateQuery("getorderhistory", tmp);
}

QString bittrexwrapper::getWithdrawalHistory(QString currency)
{
    std::vector<QString> tmp;
    if (currency.length()) {
        tmp.push_back("currency="+currency);
    }
    return privateQuery("getwithdrawalhistory", tmp);
}

QString bittrexwrapper::getDepositHistory(QString currency)
{
    std::vector<QString> tmp;
    if (currency.length()) {
        tmp.push_back("currency="+currency);
    }
    return privateQuery("getdeposithistory", tmp);
}
