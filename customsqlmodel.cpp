#include "customsqlmodel.h"
#include <QColor>

CustomSqlModel::CustomSqlModel(QObject *parent)
{

}

QVariant CustomSqlModel::data(const QModelIndex &index, int role) const
{
    //data返回指定项和角色的值。
    QVariant value = QSqlQueryModel::data(index,role);

    //isValid:不是无效id时(无效代表没在元对象系统注册)。DisplayRole以文本形式呈现数据。
    if(value.isValid() && role == Qt::DisplayRole){
        if(index.column() == 0){
            return value.toString().prepend('#'); //将字符串前置到该字符串的开头，并返回对该字符串的引用。
        }else if(index.column() == 2){
            //return value.toString().toUpper(); //返回该字符串的大写副本。
            return value.toString().prepend('*');
        }

    }

    //ForegroundRole前景画笔(通常为文本颜色)，用于用默认委托呈现的项。
    if(role == Qt::ForegroundRole && index.column() == 1){
        //fromValue返回一个包含value副本的QVariant。返回蓝色。
        return QVariant::fromValue(QColor(Qt::blue));
    }
    return value;
}


