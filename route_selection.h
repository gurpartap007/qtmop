#ifndef ROUTE_SELECTION_H
#define ROUTE_SELECTION_H

#include <QWidget>
#include "header.h"
#include "keyboard.h"
#include "train_route.h"
#include "database.h"
#include <QXmlStreamWriter>

/** @brief Route selection window to provide input from keyboard and select train route.
    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */

namespace Ui {
class route_selection;
}
/**  Route  selection window to provide input from keyboard and select train route.
 *  @author Gurpartap Singh
 *  @date December 23 2015
 * */
class route_selection : public QWidget
{
    Q_OBJECT

public:
    explicit route_selection(QWidget *parent = 0);
    keyboard *train_selection_keyboard;/**<android style qwerty keyboard to input train route info. **/
    QSqlTableModel *master_trains_model;
    QSqlTableModel *slave_trains_model;
    QSqlTableModel *dummy_model;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel; 

    database *train_database;/**< mysql database of train routes and trains numbers and their types **/
    train_route *current_route;/**< All information about current selected train route like trains,types of messages**/
    ~route_selection();

public slots:
    /**
     * @brief this function set the text in user input box by reading values from keyboard.
     * @param value single character entered by the user.
     */
    void settext(char value);
    /**
     * @brief Shows the current route selected by user which exist in main database.
     */
    void route_window();
    void select_train_route_with_sorting();
    void route_data_to_relevant_channels();

private slots:
    /**
     * @brief  when back button is clicked the control goes to homescreen.
     */
    void on_backButton_clicked();
    void on_linedit_clicked();
    void lineedit_filtering(QString value);
    void on_tableView_clicked();

signals:
    /**
     * @brief This signal is emited when train route entered by the user matched with Database and valid.
     */
    void train_selected(bool);
    void change_numeric_keypad();
    void lineedit_filter(QString value);

private:
    Ui::route_selection *ui;
    QString train_name;
};

#endif // ROUTE_SELECTION_H
