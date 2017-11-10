#include "utils.h"
#include <QUrl>
#include <set>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

QString Utils::UrlToPath(const QString &url)
{
    return QUrl(url).toLocalFile();
}

QStringList splitOnWords(const QString &text)
{
    QStringList result;
    QString word;
    std::set<QChar> allowedChars{'\'', '-'};
    for(int i = 0; i < text.length(); ++i)
    {
        const auto& ch = text[i];
        if(ch.isLetter() || (!word.isEmpty() && allowedChars.find(ch) != allowedChars.end()))
        {
            word += ch;
        }
        else
        {
            if(!word.isEmpty())
            {
                result.push_back(word);
                word.clear();
            }
        }
    }
    return result;
}
