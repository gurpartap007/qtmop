
#ifndef ROUTE_SELECTION_H
#define ROUTE_SELECTION_H
#include "PIS_global.h"
#include "qt_headers.h"
#include "ui_route_selection.h"
#include "PIS_Structs.h"
#include "sqlqueries.h"
#include "externs.h"

#define DB_FILE_PATH        "/home/apaul/working_route.txt"
#define DB_DUP_FILE_PATH    "/home/apaul/working_route_DUP.txt"

namespace Ui {
class route_selection;
}


class PIS_VIEWSHARED_EXPORT route_selection : public QWidget
{
    Q_OBJECT

public:
    explicit route_selection(QWidget *parent = 0);
    ~route_selection();

    QSortFilterProxyModel *proxyModel;
    QFont  *table_view_font;

signals:
    void lineedit_filter(QString value);
    void route_selected(qint64 option,void *);

public slots:
    void key_process(QString);
    void lineedit_filtering(QString value);
    void configure_database();
    void create_working_route_log(void);
    void updateLine();
    void upload_database_file(QString);
    int selectCurrentRoute(QString trainNo);

private slots:
    void on_lineEdit_returnPressed();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void updateDatabaseVersion();

private:
    Ui::route_selection *ui;
//    driverID ID;
};

#endif // ROUTE_SELECTION_H
