#include <QtWidgets/QComboBox>

#include "comboboxitemdelegate.h"

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , _model_key_column(0), _model_view_column(0) {}

QAbstractItemModel *ComboBoxItemDelegate::model() const {
    return _model;
}

void ComboBoxItemDelegate::setModel(QAbstractItemModel *model) {
    _model = model;
}

int ComboBoxItemDelegate::modelKeyColumn() const {
    return _model_key_column;
}

void ComboBoxItemDelegate::setModelKeyColumn(int column) {
    _model_key_column = column;
}

int ComboBoxItemDelegate::modelViewColumn() const {
    return _model_view_column;
}

void ComboBoxItemDelegate::setModelViewColumn(int column) {
    _model_view_column = column;
}

QString ComboBoxItemDelegate::displayText(const QVariant &value
    , const QLocale &locale) const {

    Q_UNUSED(locale);

    if(_model.isNull()) return QString();

    while(_model->canFetchMore(QModelIndex()))
        _model->fetchMore(QModelIndex());

    QModelIndexList indexes
        = _model->match(_model->index(0,_model_key_column)
            , Qt::DisplayRole, value, 1, Qt::MatchExactly);

    if(indexes.isEmpty()) return QString();

    QModelIndex index
        = _model->index(indexes.first().row(), _model_view_column);

    return (index.isValid()) ? _model->data(index).toString() : QString();
}

QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent
    , const QStyleOptionViewItem &option, const QModelIndex &index) const {

    //if(_model.isNull()) return;

    while(_model->canFetchMore(QModelIndex()))
        _model->fetchMore(QModelIndex());

    QComboBox *cbox = new QComboBox(parent);
    cbox->setGeometry(option.rect);
    cbox->setModel(_model);
    cbox->setModelColumn(_model_view_column);

    QModelIndexList indexes
        = _model->match(_model->index(0,_model_key_column)
            , Qt::DisplayRole, index.data(), 1, Qt::MatchExactly);

    if(!indexes.isEmpty())
        cbox->setCurrentIndex(indexes.first().row());

    return cbox;
}

void ComboBoxItemDelegate::setModelData(QWidget *editor
    , QAbstractItemModel *model, const QModelIndex &index) const {

    if(_model.isNull()) return;

    QComboBox *cbox = qobject_cast<QComboBox*>(editor);
    if(cbox == Q_NULLPTR) return;

    while(_model->canFetchMore(QModelIndex()))
        _model->fetchMore(QModelIndex());

    QModelIndex model_index
        = _model->index(cbox->currentIndex(), _model_key_column);

    if(model_index.isValid())
        model->setData(index, model_index.data());
}
