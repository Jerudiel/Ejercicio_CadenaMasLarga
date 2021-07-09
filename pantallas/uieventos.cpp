#include "uieventos.h"

UiEventos::UiEventos(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("color: white;");
        this->monitor = monitor;

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        tableView = new QTableWidget(this);
        tableView->setGeometry(QRect(10, 5, 1000, 480));
        tableView->setStyleSheet("QWidget {background-color: black ;font: 75 9pt 'Futura Md BT';} "
                                 "QTableWidget { gridline-color: #fffff8; font-size: 10pt;}"
                                 "QHeaderView::section { background-color: #646464; padding: 2px; "
                                 "font-size: 10pt; border-style: none; border-bottom: 1px solid #fffff8; "
                                 "border-right: 1px solid #fffff8;} "
                                 "QHeaderView::section:horizontal { border-top: 1px solid #fffff8;} "
                                 "QHeaderView::section:vertical { border-left: 1px solid #fffff8;}");
        tableView->setObjectName("tableView");
        tableView->setRowCount(15);
        tableView->setColumnCount(5);
        tableView->setHorizontalHeaderLabels({"TIPO", "MODO ", "DESCRIPCION", "FECHA", "HORA"});

        QHeaderView *header = tableView->horizontalHeader();
        header->setDefaultSectionSize(235);

        header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        header->setSectionResizeMode(2, QHeaderView::Stretch);
        header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
        header->setSectionResizeMode(4, QHeaderView::ResizeToContents);

        numero_eventos = 0;
        numero_scrolls = 0;
        contador_scrolls = 0;
        numero_eventos_mostrados = 15;
        numero_mas_eventos = 5;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiEventos::paintEvent(QPaintEvent* /*event*/)
{
    try {
        QStyleOption * opt = new QStyleOption;
        opt->initFrom(this);
        QPainter * p = new QPainter(this);
        this->style()->drawPrimitive(QStyle::PE_Widget, opt, p, this);
        p->end();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiEventos::bajar(){
    try {
        //qDebug() << "bajar";
        if(contador_scrolls < numero_scrolls){
            contador_scrolls += 1;
            //qDebug() << "bajar if : " + QString::number(contador_scrolls);
            int temp = numero_eventos_mostrados + (numero_mas_eventos * contador_scrolls) - 1;
            if(temp > numero_eventos - 1){
                temp = numero_eventos - 1;
                //qDebug() << "bajar if if: " + QString::number(temp);
            }
            //qDebug() << "bajar if if final : " + QString::number(temp);
            tableView->scrollToItem(tableView->item(temp,0), QAbstractItemView::PositionAtBottom);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiEventos::subir(){
    try {
        if(contador_scrolls > 0){
            contador_scrolls -= 1;
            int temp = numero_eventos_mostrados + (numero_mas_eventos * contador_scrolls) - 1;

            tableView->scrollToItem(tableView->item(temp,0), QAbstractItemView::PositionAtBottom);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiEventos::obtener_numero_scrolls(){
    try {
        int temp = numero_eventos - 15;
        if(temp > 0){
            int temp2 = temp/2;
            if(temp %5 > 0){
                temp2++;
            }
            numero_scrolls = temp2;
        }
        else{
            numero_scrolls = 0;
        }
        //qDebug() << "obtener_numero_scrolls: " + QString::number(numero_scrolls);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiEventos::cargar_datos(){
    try {
         QStringList eventos = monitor->consul->obtener_eventos();
         tableView->setRowCount(0);
         tableView->setHorizontalHeaderLabels({"TIPO", "MODO ", "DESCRIPCION", "FECHA", "HORA"});

         //int total = eventos.size() -1;

         //invertir orden de la lista
         QStringList *neo_eventos = new QStringList;
         for(int k= eventos.size()-1; k>=0; k--){
             neo_eventos->append(eventos.at(k));
         }
         //
         //el siguiente for recorre las filas - elemento en lista
         for(int row_number=0; row_number < neo_eventos->size() ;row_number++){
             int indice = row_number; // se quita porque ya no hay reversa en lista total - row_number;
             tableView->insertRow(indice);
             numero_eventos = indice;
             //el siguiente for es para recorrer por el string con los datos del event
             QStringList row_data = neo_eventos->at(indice).split(",");
             for(int column_number = 0; column_number < row_data.size() ;column_number++){
                 QTableWidgetItem *item = new QTableWidgetItem(row_data.at(column_number));
                 item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                 //qDebug() << "item- indice: " + QString::number(indice) + ", column_number: " + QString::number(column_number) + " , data: " + row_data.at(column_number);
                 tableView->setItem(indice, column_number, item);
                 QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
                 sizePolicy.setHorizontalStretch(0);
                 sizePolicy.setVerticalStretch(0);
                 sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
                 tableView->setSizePolicy(sizePolicy);
             }
         }
         numero_eventos += 1;
         obtener_numero_scrolls();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

