#include "fusswindow.h"
#include <QQmlEngine>
#include <QQmlContext>

int FussWindow::shadowThick()
{
    return m_shadowThick;
}
void FussWindow::setShadowThick(int thick)
{
    m_shadowThick = thick;
    emit shadowThickChanged();
}

QObject* FussWindow::layoutComponent()
{
    return m_layoutComponent;
}

void FussWindow::setLayoutComponent(QObject* layoutComponent)
{
    clientContent = static_cast<QQuickItem*>(this->rootObject()->findChild<QObject*>("fusswin_clientContent"));
    m_layoutComponent = static_cast<QQuickItem*>(layoutComponent);
    m_layoutComponent->setParent(clientContent);
    m_layoutComponent->setParentItem(clientContent);
}

QObject* FussWindow::titleMenu()
{
    return m_layoutComponent;
}

void FussWindow::setTitleMenu(QObject* titleMenu)
{
    if(titleMenu==NULL)
    {
        setShowTitleMenu(false);
        return;
    }
    menuButton = static_cast<QQuickItem*>(this->rootObject()->findChild<QObject*>("fusswin_menuButton"));
    m_titleMenu = static_cast<QQuickItem*>(titleMenu);
    menuButton->setProperty("menu",QVariant::fromValue(m_titleMenu));
    setShowTitleMenu(true);
}

bool FussWindow::showTitleMenu()
{
    return m_showTitleMenu;
}

void FussWindow::setShowTitleMenu(bool showTitleMenu)
{
    m_showTitleMenu = showTitleMenu;
    emit showTitleMenuChanged();
}
bool FussWindow::showMaxButton()
{
    return m_showMaxButton;
}

void FussWindow::setShowMaxButton(bool showMaxButton)
{
    m_showMaxButton = showMaxButton;
    emit showMaxButtonChanged();
}

FussWindow::FussWindow(QQuickView *parent):QQuickView(parent)
{
    this->engine()->rootContext()->setContextProperty("fuss_win",this);
    this->setSource(QUrl("qrc:/theme/MyWindow.qml"));
    this->setFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint);
    this->setColor(Qt::transparent);
    if(this->minimumHeight()==0)
        this->setMinimumHeight(180);
    if(this->minimumWidth()==0)
        this->setMinimumWidth(300);

    QPoint p = this->mapToGlobal(this->cursor().pos());
    oldCursorScreenX = p.x();
    oldCursorScreenY = p.y();
    beginMove = false;
    beginResize = false;
}

FussWindow::~FussWindow()
{
}

Qt::CursorShape FussWindow::getCursorType(int x, int y)
{
    int buttonswidth=122;
    if(titleMenu()==NULL)
        buttonswidth -=30;
    if(!showMaxButton())
        buttonswidth -=30;
    if(x>=this->width()-(buttonswidth+this->shadowThick())&&x<this->width()-5&&y<32+this->shadowThick()&&y>5)
    {
        cursorInArea = Fuss::ButtonArea;
        return Qt::ArrowCursor;
    }
    if(this->windowState()==Qt::WindowNoState)//正常状态才可以拖拉调节窗口大小
    {
        if(x<10&&y<10)
        {
            cursorInArea = Fuss::LeftTopResizeArea;
            return Qt::SizeFDiagCursor;
        }
        if(x>this->width()-10&&y>this->height()-10)
        {
            cursorInArea = Fuss::RightBottomResizeArea;
            return Qt::SizeFDiagCursor;
        }
        if(x>this->width()-10&&y<10)
        {
            cursorInArea = Fuss::RightTopResizeArea;
            return Qt::SizeBDiagCursor;
        }
        if(x<10&&y>this->height()-10)
        {
            cursorInArea = Fuss::LeftBottomResizeArea;
            return Qt::SizeBDiagCursor;
        }
        if(x<6)
        {
            cursorInArea = Fuss::LeftResizeArea;
            return Qt::SizeHorCursor;
        }
        if(x>this->width()-6)
        {
            cursorInArea = Fuss::RightResizeArea;
            return Qt::SizeHorCursor;
        }
        if(y<6)
        {
            cursorInArea = Fuss::TopResizeArea;
            return Qt::SizeVerCursor;
        }
        if(y>this->height()-6)
        {
            cursorInArea = Fuss::BottomResizeArea;
            return Qt::SizeVerCursor;
        }
    }

    cursorInArea = Fuss::CustomerArea;
    if(this->windowState()==Qt::WindowNoState&&y<40||this->windowState()==Qt::WindowMaximized&&y<35)
        cursorInArea = Fuss::TitleBarArea;
    return Qt::ArrowCursor;
}

void FussWindow::mousePressEvent(QMouseEvent * event)
{
    QQuickView::mousePressEvent(event);    
    if(event->button()==Qt::LeftButton)
    {
        oldCursorScreenX = event->globalX();
        oldCursorScreenY = event->globalY();
        getCursorType(event->x(),event->y());
        if(cursorInArea>0&&cursorInArea<9)//边框，拖动改变窗体大小区域
        {
            beginResize = true;
        }
        else if(cursorInArea==Fuss::TitleBarArea)//标题栏
        {
            beginMove = true;
        }
    }
}

void FussWindow::mouseMoveEvent(QMouseEvent * event)
{
    if(!beginResize&&!beginMove)
    {
        Qt::CursorShape cursorType = getCursorType(event->x(),event->y());
        this->setCursor(cursorType);
        QQuickView::mouseMoveEvent(event);
    }
    QPoint winOldPosition = this->position();
    int winOldWidth = this->width();
    int winOldHeight = this->height();
    int winNewWidth = this->width();
    int winNewHeight = this->height();
    int winNewX = winOldPosition.x();
    int winNewY = winOldPosition.y();
    int offsetX = event->globalX()-oldCursorScreenX;
    int offsetY = event->globalY()-oldCursorScreenY;
    if(beginResize)
    {
        switch (cursorInArea)
        {
        case Fuss::LeftTopResizeArea:
            winNewX = winOldPosition.x()+offsetX;
            winNewY = winOldPosition.y()+offsetY;
            winNewWidth = winOldWidth-offsetX;
            winNewHeight = winOldHeight-offsetY;
            break;
        case Fuss::TopResizeArea:
            winNewY = winOldPosition.y()+offsetY;
            winNewHeight = winOldHeight-offsetY;
            break;
        case Fuss::RightTopResizeArea:
            winNewY = winOldPosition.y()+offsetY;
            winNewWidth = winOldWidth+offsetX;
            winNewHeight = winOldHeight-offsetY;
            break;
        case Fuss::RightResizeArea:
            winNewWidth = winOldWidth+offsetX;
            break;
        case Fuss::RightBottomResizeArea:
            winNewWidth = winOldWidth+offsetX;
            winNewHeight = winOldHeight+offsetY;
            break;
        case Fuss::BottomResizeArea:
            winNewHeight = winOldHeight+offsetY;
            break;
        case Fuss::LeftBottomResizeArea:
            winNewX = winOldPosition.x()+offsetX;
            winNewWidth = winOldWidth-offsetX;
            winNewHeight = winOldHeight+offsetY;
            break;
        case Fuss::LeftResizeArea:
            winNewX = winOldPosition.x()+offsetX;
            winNewWidth = winOldWidth-offsetX;
            break;
        default:
            break;
        }
        if(winNewWidth<=this->minimumWidth()||winNewWidth>=this->maximumWidth())
            winNewX=winOldPosition.x();
        if(winNewHeight<=this->minimumHeight()||winNewHeight>=this->maximumHeight())
            winNewY=winOldPosition.y();
        this->setPosition(winNewX,winNewY);
        if(winNewWidth>this->minimumWidth()&&winNewWidth<this->maximumWidth())
            this->setWidth(winNewWidth);
        if(winNewHeight>this->minimumHeight()&&winNewHeight<this->maximumHeight())
            this->setHeight(winNewHeight);

        oldCursorScreenX = event->globalX();
        oldCursorScreenY = event->globalY();
        return;
    }
    if(beginMove)
    {
        if(this->windowState()==Qt::WindowMaximized&&offsetY>0)
        {
            setShadowThick(5);
            this->showNormal();
            this->setPosition(event->globalX()-this->width()/2,event->globalY()-offsetY-5);
        }
        else if(this->windowState()==Qt::WindowNoState)
        {
            if(event->globalY()==0)
            {
                if(!showMaxButton()) return;
                setShadowThick(0);
                this->showMaximized();
            }
            else
            {
                this->setPosition(winOldPosition.x()+offsetX,winOldPosition.y()+offsetY);
                oldCursorScreenX = event->globalX();
                oldCursorScreenY = event->globalY();
            }
        }
        return;
    }    
}

void FussWindow::mouseReleaseEvent(QMouseEvent * event)
{
    QQuickView::mouseReleaseEvent(event);
    beginMove = false;
    beginResize = false;
}

void FussWindow::mouseDoubleClickEvent(QMouseEvent * event)
{
    QQuickView::mouseDoubleClickEvent(event);
    getCursorType(event->x(),event->y());
    if(cursorInArea==Fuss::TitleBarArea)//标题栏
    {
        if(!showMaxButton()) return;
        if(this->windowState()==Qt::WindowNoState)
        {
            setShadowThick(0);
            this->showMaximized();
        }
        else if(this->windowState()==Qt::WindowMaximized)
        {
            setShadowThick(5);
            this->showNormal();
        }
    }
}
