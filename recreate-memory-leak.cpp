#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class PollClient : public QObject
{
public:
    PollClient(const QUrl &url)
        : m_request(url)
    {
        request();
    }
public slots:
    void request()
    {
        assert(m_reply == nullptr);

        qDebug() << "GET" << m_request.url();

        m_reply = nm.get(m_request);

        connect(m_reply, &QNetworkReply::finished, this, [&]() {
            if (m_reply->error() != QNetworkReply::NoError) {
                qWarning() << m_reply->errorString();
            }
            m_reply->deleteLater();
            m_reply = nullptr;
            QMetaObject::invokeMethod(this, &PollClient::request, Qt::QueuedConnection);
        });
    }

private:
    QNetworkAccessManager nm;
    QNetworkRequest m_request;
    QNetworkReply *m_reply = nullptr;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qWarning() << "No URL supplied";
        return -1;
    }

    qDebug() << "Starting polling client...";
    QString url(argv[1]);
    PollClient requester(url);
    return app.exec();
}
