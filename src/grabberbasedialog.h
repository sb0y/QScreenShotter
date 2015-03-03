#ifndef GRABBERBASEDIALOG_H
#define GRABBERBASEDIALOG_H

#include <QObject>
#include <QDialog>
#include "grabberbase.h"

class grabberBaseDialog : public QDialog, public grabberBase
{
    Q_OBJECT
public:
    explicit grabberBaseDialog();
    virtual ~grabberBaseDialog();

signals:

public slots:
};

#endif // GRABBERBASEDIALOG_H
