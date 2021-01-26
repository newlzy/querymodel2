#ifndef EDITABLESQLMODEL_H
#define EDITABLESQLMODEL_H

#include <QSqlQueryModel> //为sql结果集提供一个只读模型

class EditableSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    EditableSqlModel(QObject *parent = nullptr);

    //返回给定索引的项标志。
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    //将索引处的项的角色数据设置为值。
    bool setData(const QModelIndex &index,const QVariant &value,int role) override;

private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();


};

#endif // EDITABLESQLMODEL_H
