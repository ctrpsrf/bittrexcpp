# Bittrex wrapper on C++
A simple wrapper for the Biеtrex exchange. Written in C ++ using QT libraries.

Libraries:
  - <QNetworkAccessManager>
  - OpenSSL
  - <QEventLoop>

### AvailableMethod
Description of methods read on [bittrex](https://bittrex.com/Home/Api).
Each method return <QString> containing the response from the exchangeю
  - getMarkets()
  - getCurrencies();
  - getTicker(QString market);
  - getMarketSummaries();
  - getMarketSummary(QString market);
  - getOrderBook(QString market, QString type);
  - getMarketHistory(QString market);
  - buyLimit(QString market, QString quantity, QString rate);
  - sellLimit(QString market, QString quantity, QString rate);
  - cancelOrder(QString uuid);
  - getOpenOrders(QString market);
  - getBalances();
  - getBalance(QString currency);
  - getDepositAddress(QString currency);
  - getOrder(QString uuid);
  - getOrderHistory(QString market);
  - getWithdrawalHistory(QString currency);
  - getDepositHistory(QString currency);


### Example for use

```sh
    bittrexwrapper *mybit = new bittrexwrapper(API_Key, API_Secret);
    QString strReply = mybit->getBalances();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["result"].toArray();
    curToSell.clear();
    ui->listWidget_2->clear();
    ui->listWidget_4->clear();
    foreach (const QJsonValue & value, jsonArray) {

        QJsonObject obj = value.toObject();
        currenciesToSell tmp;

        tmp.name = obj["Currency"].toString();
        tmp.amount = obj["Available"].toDouble();
        curToSell.push_back(tmp);
        if (tmp.amount && tmp.name != "BTC" && tmp.name != "ETH" && tmp.name != "USDT") {
            ui->listWidget_2->addItem("BTC-" + tmp.name + ": " + QString::number(tmp.amount));
            ui->listWidget_2->addItem("ETH-" + tmp.name + ": " + QString::number(tmp.amount));
            ui->listWidget_2->addItem("USDT-" + tmp.name + ": " + QString::number(tmp.amount));
        }
        if (tmp.amount) {
            ui->listWidget_4->addItem(tmp.name + ": " + QString::number(tmp.amount));
            ui->listWidget_6->addItem(tmp.name + ": " + QString::number(tmp.amount));
        }
    }

```
