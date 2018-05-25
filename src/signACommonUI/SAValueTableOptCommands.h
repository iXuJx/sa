﻿#ifndef SAVALUETABLEOPTCOMMANDS_H
#define SAVALUETABLEOPTCOMMANDS_H
#include "SACommonUIGlobal.h"
#include <QUndoCommand>
#include <QItemSelectionModel>
#include <QVariant>
#include <QList>
class SADataTableModel;
class SAAbstractDatas;
class SAVectorDouble;
class SAValueTableOptEditValueCommandPrivateBase;
class SAValueTableOptPasteCommandPrivateBase;
///
/// \brief sa 数值表格操作类命令基类
///
class SA_COMMON_UI_EXPORT SAValueTableOptBaseCommand : public QUndoCommand
{
public:
    SAValueTableOptBaseCommand(SAAbstractDatas* data,QUndoCommand* par = Q_NULLPTR)
        :m_data(data)
    {
    }

    SAAbstractDatas* getDataPtr() const
    {
        return m_data;
    }
private:
    SAAbstractDatas* m_data;
};



///
/// \brief 数值编辑命令
///
/// 数据编辑可以实现数据的修改，以及数据的添加
///
class SA_COMMON_UI_EXPORT SAValueTableOptEditValueCommand : public SAValueTableOptBaseCommand
{
public:
    SAValueTableOptEditValueCommand(SAAbstractDatas* data
                                      , const QVariant& newData
                                       , int row
                                       , int col
                                       , QUndoCommand* par = Q_NULLPTR);
    SAValueTableOptEditValueCommand(SAAbstractDatas* data
                                      , const QVariantList& newDatas
                                       , int row
                                       , int col
                                       , QUndoCommand* par = Q_NULLPTR);
    ~SAValueTableOptEditValueCommand();
    void redo();
    void undo();
    bool isValid() const;
private:
    SAValueTableOptEditValueCommandPrivateBase* d_ptr;
};
#if 0
///
/// \brief 数值追加命令
///
class SA_COMMON_UI_EXPORT SAValueTableOptAppendValueCommand : public SAValueTableOptBaseCommand
{
public:
    SAValueTableOptAppendValueCommand(SAAbstractDatas* data
                                       ,SADataTableModel* model
                                       ,const QVariantList& newDatas
                                       ,int row
                                       ,int col
                                       ,QUndoCommand* par = Q_NULLPTR);
    void redo();
    void undo();
private:
    void appendInVectorPoint();
    void popBackVectorPoint();
    void appendInVectorVariant();
    void popBackVectorVariant();
    void appendInTable();
    void popFromTable();
private:
    QVariantList m_newDatas;
    int m_modelRow;
    int m_modelCol;
    int m_realRow;
    int m_startCol;
    int m_endCol;
};
#endif
////////////////////////////////////////////////////////////////////


///
/// \brief 处理数据表格的复制&粘贴命令
///
/// 并非所有数据都能支持复制粘贴，因此需要使用\sa isValid 进行判断
///
class SA_COMMON_UI_EXPORT SAValueTableOptPasteCommand : public SAValueTableOptBaseCommand
{
public:
    SAValueTableOptPasteCommand(SAAbstractDatas* data
                                     , const QList<QVariantList>& clipboardTextTable
                                     , int startRow
                                     , int startCol
                                     ,QUndoCommand* par = Q_NULLPTR);
    ~SAValueTableOptPasteCommand();
    bool isValid() const;
    void redo();
    void undo();

private:
    SAValueTableOptPasteCommandPrivateBase* d_ptr;
};


#endif // SAVALUETABLEOPTCOMMANDS_H
