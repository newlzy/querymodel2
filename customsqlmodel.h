#ifndef CUSTOMSQLMODEL_H
#define CUSTOMSQLMODEL_H

#include <QSqlQueryModel> //提供了一个只读数据模型。

//自定义样式呈现数据
class CustomSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    CustomSqlModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

};

#endif // CUSTOMSQLMODEL_H
