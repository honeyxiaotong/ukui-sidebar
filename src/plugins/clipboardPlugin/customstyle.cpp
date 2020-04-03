#include "customstyle.h"
#include <QWidget>

#include <QStyleOption>
#include <QPainter>

#include <QDebug>

CustomStyle::CustomStyle(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{
}

void CustomStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void CustomStyle::drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::drawItemPixmap(painter, rectangle, alignment, pixmap);
}

void CustomStyle::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    return QProxyStyle::drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole);
}

/// 我们重写button的绘制方法，通过state和当前动画的状态以及value值改变相关的绘制条件
/// 这里通过判断hover与否，动态的调整painter的透明度然后绘制背景
/// 需要注意的是，默认控件的绘制流程只会触发一次，而动画需要我们在一段时间内不停绘制才行，
/// 要使得动画能够持续，我们需要使用QWidget::update()在动画未完成时，
/// 手动更新一次，这样button将在一段时间后再次调用draw方法，从而达到更新动画的效果
///
/// 需要注意绘制背景的流程会因主题不同而产生差异，所以这一部分代码在一些主题中未必正常，
/// 如果你需要自己实现一个主题，这同样是你需要注意和考虑的点
void CustomStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == PE_PanelButtonCommand) {
        qDebug()<<"draw pe button";
        if (widget) {
            bool isPressed = false;
            bool isHover = false;
            if (!option->state.testFlag(State_Sunken)) {
                if (option->state.testFlag(State_MouseOver)) {
                    isHover = true;
                }
            } else {
                isPressed = true;
            }

            QStyleOption opt = *option;
            if (isHover) {
                QColor color(107,142,235,255);
                opt.palette.setColor(QPalette::Highlight, color);

            }
            if (isPressed) {
                QColor color(50,87,202,255);
                opt.palette.setColor(QPalette::Highlight, color);
            }
            if (!isHover && !isPressed) {
                QColor color(61, 107, 229, 255);
                opt.palette.setColor(QPalette::Button,color);
            }
            return QProxyStyle::drawPrimitive(element, &opt, painter, widget);
        }
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

QPixmap CustomStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl CustomStyle::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

QRect CustomStyle::itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::itemPixmapRect(rectangle, alignment, pixmap);
}

QRect CustomStyle::itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
{
    return QProxyStyle::itemTextRect(metrics, rectangle, alignment, enabled, text);
}

int CustomStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::pixelMetric(metric, option, widget);
}

/// 我们需要将动画与widget一一对应起来，
/// 在一个style的生命周期里，widget只会进行polish和unpolish各一次，
/// 所以我们可以在polish时将widget与一个新的动画绑定，并且对应的在unpolish中解绑定
void CustomStyle::polish(QWidget *widget)
{
    return QProxyStyle::polish(widget);
}

void CustomStyle::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void CustomStyle::polish(QPalette &palette)
{
    return QProxyStyle::polish(palette);
}

void CustomStyle::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

void CustomStyle::unpolish(QApplication *application)
{
    return QProxyStyle::unpolish(application);
}

QSize CustomStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
}

QIcon CustomStyle::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette CustomStyle::standardPalette() const
{
    return QProxyStyle::standardPalette();
}

int CustomStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

QRect CustomStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QRect CustomStyle::subElementRect(QStyle::SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}
