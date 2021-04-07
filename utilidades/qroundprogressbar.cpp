/*
 * QRoundProgressBar - a circular progress bar Qt widget.
 *
 * Sintegrial Technologies (c) 2015-now
 *
 * The software is freeware and is distributed "as is" with the complete source codes.
 * Anybody is free to use it in any software projects, either commercial or non-commercial.
 * Please do not remove this copyright message and remain the name of the author unchanged.
 *
 * It is very appreciated if you produce some feedback to us case you are going to use
 * the software.
 *
 * Please send your questions, suggestions, and information about found issues to the
 *
 * sintegrial@gmail.com
 *
 */


#include "qroundprogressbar.h"

#include <QtGui/QPainter>


QRoundProgressBar::QRoundProgressBar(QWidget *parent) :
    QWidget(parent),
    m_min(0), m_max(100),
    m_value(25),
    m_nullPosition(PositionTop),
    m_barStyle(StyleDonut),
    m_outlinePenWidth(1),
    m_dataPenWidth(1),
    m_rebuildBrush(false),
    m_format("%d"),
    m_decimals(1),
    m_updateFlags(UF_PERCENT),
    //m_gradientData(NULL),
    m_unit("")
{
}

void QRoundProgressBar::setRange(double min, double max)
{
    try {
        m_min = min;
        m_max = max;

        if (m_max < m_min)
            qSwap(m_max, m_min);

        if (m_value < m_min)
            m_value = m_min;
        else if (m_value > m_max)
            m_value = m_max;

        if (!m_gradientData.isEmpty())
            m_rebuildBrush = true;

        update();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setMinimum(double min)
{
    try {
         setRange(min, m_max);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setMaximum(double max)
{
    try {
         setRange(m_min, max);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setValue(double val)
{
    try {
        if (m_value != val)
        {
            if (val < m_min)
                m_value = m_min;
            else if (val > m_max)
                m_value = m_max;
            else
                m_value = val;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setValue(int val)
{
    try {
         setValue(double(val));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setNullPosition(double position)
{
    try {
        if (position != m_nullPosition)
        {
            m_nullPosition = position;

            if (!m_gradientData.isEmpty())
                m_rebuildBrush = true;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setBarStyle(QRoundProgressBar::BarStyle style)
{
    try {
        if (style != m_barStyle)
        {
            m_barStyle = style;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setOutlinePenWidth(double penWidth)
{
    try {
        if (penWidth != m_outlinePenWidth)
        {
            m_outlinePenWidth = penWidth;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setDataPenWidth(double penWidth)
{
    try {
        if (penWidth != m_dataPenWidth)
        {
            m_dataPenWidth = penWidth;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setDataColors(const QGradientStops &stopPoints)
{
    try {
        if (stopPoints != m_gradientData)
        {
            m_gradientData = stopPoints;
            m_rebuildBrush = true;

            update();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setFormat(const QString &format)
{
    try {
        if (format != m_format)
        {
            m_format = format;

            valueFormatChanged();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::resetFormat()
{
    try {
        m_format = QString(); //QString::null;

        valueFormatChanged();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setDecimals(int count)
{
    try {
        if (count >= 0 && count != m_decimals)
        {
            m_decimals = count;

            valueFormatChanged();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::setUnit(QString unit)
{
    try {
         m_unit = unit;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::paintEvent(QPaintEvent* /*event*/)
{
    try {
        double outerRadius = qMin(width(), height());
        QRectF baseRect(1, 1, outerRadius-2, outerRadius-2);

        QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied);

        QPainter p(&buffer);
        p.setRenderHint(QPainter::Antialiasing);

        // data brush
        rebuildDataBrushIfNeeded();

        // background
        drawBackground(p, buffer.rect());

        // base circle
        drawBase(p, baseRect);

        // data circle
        double arcStep = 360.0 / (m_max - m_min) * m_value;
        drawValue(p, baseRect, m_value, arcStep);

        // center circle
        double innerRadius(0);
        QRectF innerRect;
        calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
        drawInnerBackground(p, innerRect);

        // text
        drawText(p, innerRect, innerRadius, m_value);

        // finally draw the bar
        p.end();

        QPainter painter(this);
        painter.fillRect(baseRect, palette().window()); //painter.fillRect(baseRect, palette().background()); //
        painter.drawImage(0,0, buffer);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::drawBackground(QPainter &p, const QRectF &baseRect)
{
    try {
         p.fillRect(baseRect, palette().window()); //p.fillRect(baseRect, palette().background()); //
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::drawBase(QPainter &p, const QRectF &baseRect)
{
    try {
        switch (m_barStyle)
        {
        case StyleDonut:
            p.setPen(QPen(palette().shadow().color(), m_outlinePenWidth));
            p.setBrush(palette().base());
            p.drawEllipse(baseRect);
            break;

        case StylePie:
            p.setPen(QPen(palette().base().color(), m_outlinePenWidth));
            p.setBrush(palette().base());
            p.drawEllipse(baseRect);
            break;

        case StyleExpand:
            p.setPen(QPen(palette().base().color(), m_outlinePenWidth));
            p.setBrush(palette().base());
            p.drawEllipse(baseRect);
            break;

        case StyleLine:
            p.setPen(QPen(palette().base().color(), m_outlinePenWidth));
            p.setBrush(Qt::NoBrush);
            p.drawEllipse(baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2));
            break;

        default:;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }

}

void QRoundProgressBar::drawValue(QPainter &p, const QRectF &baseRect, double value, double arcLength)
{
    try {
        // nothing to draw
        if (value == m_min)
            return;

        // for expand style
        if(m_barStyle == StyleExpand){
            p.setBrush(palette().highlight());
            p.setPen(QPen(palette().highlight().color(), m_dataPenWidth));
            float radius = (baseRect.height() / 2) / arcLength;
            p.drawEllipse(baseRect.center(), radius, radius);
            return;
        }
        // for Line style
        if (m_barStyle == StyleLine)
        {
            p.setPen(QPen(palette().highlight().color(), m_dataPenWidth));
            p.setBrush(Qt::NoBrush);
            p.drawArc(baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2),
                      m_nullPosition * 16,
                      -arcLength * 16);
            return;
        }

        // for Pie and Donut styles
        QPainterPath dataPath;
        dataPath.setFillRule(Qt::WindingFill);

        // pie segment outer
        dataPath.moveTo(baseRect.center());
        dataPath.arcTo(baseRect, m_nullPosition, -arcLength);
        dataPath.lineTo(baseRect.center());

        p.setBrush(palette().highlight());
        p.setPen(QPen(palette().shadow().color(), m_dataPenWidth));
        p.drawPath(dataPath);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    try {
        // for Line style
        if (m_barStyle == StyleLine)
        {
            innerRadius = outerRadius - m_outlinePenWidth;
        }
        else    // for Pie and Donut styles
        {
            innerRadius = outerRadius * 0.75;
        }

        double delta = (outerRadius - innerRadius) / 2;
        innerRect = QRectF(delta, delta, innerRadius, innerRadius);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::drawInnerBackground(QPainter &p, const QRectF &innerRect)
{
    try {
        if (m_barStyle == StyleDonut)
        {
            p.setBrush(palette().alternateBase());
            p.drawEllipse(innerRect);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::drawText(QPainter &p, const QRectF &innerRect, double innerRadius, double value)
{
    try {
        if (m_format.isEmpty())
            return;

        // !!! to revise
        QFont f(font());
        //f.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)m_decimals * 0.08)));
        f.setPixelSize(18);
        p.setFont(f);

        QRectF textRect(innerRect);
        p.setPen(palette().text().color());
        p.drawText(textRect, Qt::AlignCenter, valueToText(value));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString QRoundProgressBar::valueToText(double value) const
{
    try {
        QString textToDraw(m_format);
        //&
        if (m_updateFlags == UF_VALUE){
            textToDraw.replace("%v", QString::number(value, 'f', m_decimals));
            textToDraw = textToDraw + "\n" + m_unit;
        }

        if (m_updateFlags == UF_PERCENT)
        {
            double procent = (value - m_min) / (m_max - m_min) * 100.0;
            textToDraw.replace("%p", QString::number(procent, 'f', m_decimals));
        }

        if (m_updateFlags == UF_MAX)
            textToDraw.replace("%m", QString::number(m_max - m_min + 1, 'f', m_decimals));

        if(m_updateFlags == UF_DATA)
        {
            textToDraw.replace("%d", QString::number(value)); //textToDraw.replace("%d", QString::number(value, 'd', 0));
            textToDraw = textToDraw + "\n" + m_unit;
        }

        return textToDraw;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void QRoundProgressBar::valueFormatChanged()
{
    try {
        m_updateFlags = 0;

        if (m_format.contains("%v"))
            m_updateFlags |= UF_VALUE;

        if (m_format.contains("%p"))
            m_updateFlags |= UF_PERCENT;

        if (m_format.contains("%m"))
            m_updateFlags |= UF_MAX;

        if(m_format.contains("%d"))
            m_updateFlags |= UF_DATA;

        update();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void QRoundProgressBar::rebuildDataBrushIfNeeded()
{
    try {
        if (m_rebuildBrush)
        {
            m_rebuildBrush = false;

            QConicalGradient dataBrush;
            dataBrush.setCenter(0.5,0.5);
            dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);

            // invert colors
            for (int i = 0; i < m_gradientData.count(); i++)
            {
                dataBrush.setColorAt(1.0 - m_gradientData.at(i).first, m_gradientData.at(i).second);
            }

            // angle
            dataBrush.setAngle(m_nullPosition);

            QPalette p(palette());
            p.setBrush(QPalette::Highlight, dataBrush);
            setPalette(p);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}




