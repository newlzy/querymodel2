#include "editablesqlmodel.h"
#include <QtSql>
#pragma execution_character_set("utf-8")

EditableSqlModel::EditableSqlModel(QObject *parent):QSqlQueryModel(parent)
{

}

//返回给定索引的项标志
Qt::ItemFlags EditableSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if(index.column() == 1 || index.column() == 2)
        flags |= Qt::ItemIsEditable; //可以被编辑

    return flags;
}

//将索引处的项的角色数据设置为值。
bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column() < 1 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(),0);
    int id = data(primaryKeyIndex).toUInt();

    clear(); //清除模型并释放任何获取的资源。

    bool ok;
    if(index.column() == 1){
        ok = setFirstName(id,value.toString()); //更新person表的”名称“列
    }else
        ok = setLastName(id,value.toString()); //更新person表的“地区”列

    refresh(); //查询数据库表，设置标题
    return ok;
}

//修改person表的”名称“列
bool EditableSqlModel::setFirstName(int personId, const QString &firstName)
{
    QSqlQuery query;
    //准备执行更新sql
    query.prepare("update person set firstname = ? where id = ?");
    //使用位置值绑定时，将值val添加到值列表中。addBindValue()调用的顺序决定了一个值将在准备好的查询中绑定到哪个占位符。exec()调用后，占位符将被数据库中的数据覆盖。
    query.addBindValue("666");
    query.addBindValue(personId);
    return query.exec();
}

//修改person表的“地区”列
bool EditableSqlModel::setLastName(int personId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update person set lastname = ? where id = ?");
    query.addBindValue("999");
    query.addBindValue(personId);
    return query.exec();
}

//查询数据库表，设置标题
void EditableSqlModel::refresh()
{
    //重置模型并将数据提供程序设置为给定的查询。
    setQuery("select * from person");

    //将指定角色的水平标题设置为值。
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("地区"));
}




