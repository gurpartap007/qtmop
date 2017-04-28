
#ifndef PRERECORDED_H
#define PRERECORDED_H
#include "PIS_global.h"
#include "qt_headers.h"
#include "ui_prerecorded.h"
#include <QDesktopWidget>

namespace Ui {
class PreRecorded;
}

class PIS_VIEWSHARED_EXPORT PreRecorded : public QWidget
{
    Q_OBJECT

public:
    explicit PreRecorded(QWidget *parent = 0);
    ~PreRecorded();
    QSortFilterProxyModel *proxyModel;

signals:
    void playclicked(int *);

private slots:
    void on_play_clicked();
    void on_pushButton_clicked();
protected:
    void showEvent(QShowEvent *e);

private:
    Ui::PreRecorded *ui;
};

#endif // PRERECORDED_H
