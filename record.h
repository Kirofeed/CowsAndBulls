#ifndef RECORD_H
#define RECORD_H

#include <QString>

struct Record {
    QString name;
    int score; // Чем меньше score, тем лучше результат

    bool operator<(const Record &other) const {
        return score < other.score;
    }
};

#endif // RECORD_H


