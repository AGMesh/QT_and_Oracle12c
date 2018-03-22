#ifndef COMBOBOXITEMDELEGATE_H
#define COMBOBOXITEMDELEGATE_H

#include <QtCore/QPointer>

#include <QtWidgets/QStyledItemDelegate>

class QAbstractItemModel;

class ComboBoxItemDelegate : public QStyledItemDelegate {
    Q_OBJECT

    public:
        explicit ComboBoxItemDelegate(QObject *parent = Q_NULLPTR);
        virtual ~ComboBoxItemDelegate() {}

        QAbstractItemModel *model() const;
        void setModel(QAbstractItemModel *model);

        int modelKeyColumn() const;
        void setModelKeyColumn(int column);

        int modelViewColumn() const;
        void setModelViewColumn(int column);

        virtual QString displayText(const QVariant &value
            , const QLocale &locale) const;

        virtual QWidget *createEditor(QWidget *parent
            , const QStyleOptionViewItem &option
            , const QModelIndex &index) const;

        virtual void setModelData(QWidget *editor
            , QAbstractItemModel *model
            , const QModelIndex &index) const;

    private:
        int _model_key_column, _model_view_column;

        QPointer<QAbstractItemModel> _model;

};

#endif