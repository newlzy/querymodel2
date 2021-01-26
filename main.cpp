#include <QApplication>
#include <QTableView>
#include "createConnection.h"
#include <stdlib.h>
#include <QSql>
#include <QSqlQueryModel> //为SQL结果集提供了一个只读数据模型
#include "editablesqlmodel.h"
#include "customsqlmodel.h"

void initializeModel(QSqlQueryModel *model){
    model->setQuery("select * from person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("名字"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("地区"));
}

QTableView* createView(QSqlQueryModel *model, const QString &title = ""){
    QTableView *view = new QTableView;
    view->setModel(model);
    static int offset = 0;

    view->setWindowTitle(title);
    view->move(200 + offset, 200+offset); //窗口移动
    offset += 20;
    view->show();

    return view;
}

int main(int argc, char *argv[]){

    QApplication app(argc,argv);
    if(!createConnection())
        return EXIT_FAILURE;

    QSqlQueryModel plainModel; //只读数据模型
    EditableSqlModel editableModel; //自定义模型，继承QSqlQueryModel
    CustomSqlModel customModel; //自定义样式呈现数据

    initializeModel(&plainModel);
    initializeModel(&editableModel);
    initializeModel(&customModel);

    createView(&plainModel, QObject::tr("只读数据模型"));
    createView(&editableModel, QObject::tr("自定义1"));
    createView(&customModel, QObject::tr("自定义2"));

    return app.exec();

}
