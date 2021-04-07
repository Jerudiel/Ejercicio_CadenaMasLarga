#ifndef UIQWIDGETMENUGRAFICA_H
#define UIQWIDGETMENUGRAFICA_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QSizePolicy>

class UiQWidgetMenuGrafica : public QWidget
{
    Q_OBJECT
public:
    explicit UiQWidgetMenuGrafica(QWidget *parent = nullptr);
    QString estiloBotonA;
    QString estiloBotonI;
    QHBoxLayout * horizontalLayout;
    QPushButton * btncontrolgrafica;
    QFont * fuente;
    QSizePolicy * sizePolicy;
    QPushButton * btntipografica;
    bool estadomostrargrafica;
    bool estadotipografica;
    int btnsel;

    void retranslateUi();
    void ocultar();
    void mostrar();
    bool cambiar_mostrar_grafica();
    bool cambiar_tipo_grafica();
    int seleccionar_boton();

signals:

};

#endif // UIQWIDGETMENUGRAFICA_H
