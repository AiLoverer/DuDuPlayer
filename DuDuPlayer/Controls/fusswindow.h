#ifndef FUSSWINDOW_H
#define FUSSWINDOW_H

#include "fnamespace.h"
#include <QQuickView>
#include <QtQuick/QQuickItem>

class FussWindow : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(int shadowThick READ shadowThick WRITE setShadowThick NOTIFY shadowThickChanged)
    Q_PROPERTY(QObject* layoutComponent READ layoutComponent WRITE setLayoutComponent NOTIFY layoutComponentChanged)
    Q_PROPERTY(bool showTitleMenu READ showTitleMenu WRITE setShowTitleMenu NOTIFY showTitleMenuChanged)
    Q_PROPERTY(bool showMaxButton READ showMaxButton WRITE setShowMaxButton NOTIFY showMaxButtonChanged)
    Q_PROPERTY(QObject* titleMenu READ titleMenu WRITE setTitleMenu NOTIFY titleMenuChanged)

public:
    FussWindow(QQuickView *parent = 0);
    ~FussWindow();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);

signals:
    void shadowThickChanged();
    void layoutComponentChanged();
    void showTitleMenuChanged();
    void showMaxButtonChanged();
    void titleMenuChanged();

public slots:
    int shadowThick();
    void setShadowThick(int thick);

    QObject* layoutComponent();
    void setLayoutComponent(QObject* layoutComponent);

    QObject* titleMenu();
    void setTitleMenu(QObject* titleMenu);

    bool showTitleMenu();
    void setShowTitleMenu(bool showTitleMenu);

    bool showMaxButton();
    void setShowMaxButton(bool showMaxButton);

private:
    QQuickItem * clientContent;
    QQuickItem * menuButton;
    QQuickItem * m_layoutComponent;
    QQuickItem * m_titleMenu;
    bool m_showTitleMenu = false;
    bool m_showMaxButton = true;

    int m_shadowThick = 5;
    int oldCursorScreenX;
    int oldCursorScreenY;
    bool beginMove;
    Qt::CursorShape getCursorType(int x,int y);
    bool beginResize;
    Fuss::FussWindowArea cursorInArea;

};

#endif // FUSSWINDOW_H

