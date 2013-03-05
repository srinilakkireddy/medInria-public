#ifndef MEDQUICKACCESSMENU_H
#define MEDQUICKACCESSMENU_H

#include "medGuiExport.h"
#include <medHomepageButton.h>

#include <QtGui>

class MEDGUI_EXPORT medQuickAccessMenu : public QWidget
{
  Q_OBJECT
public:
    medQuickAccessMenu ( bool vertical, QWidget* parent = 0, Qt::WindowFlags f = 0 );
    
    void reset(bool optimizeLayout);
    
    void updateCurrentlySelectedRight();
    void updateCurrentlySelectedLeft();
    void updateSelected (QString workspace);
    
    void switchToCurrentlySelected ();
    
protected:
  /**
   *  emit the hideMenu() signal when the widget lost the focus
   */
  void focusOutEvent(QFocusEvent * event);
    
    void mouseMoveEvent (QMouseEvent * event);
    
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    
    void createHorizontalQuickAccessMenu();
    void createVerticalQuickAccessMenu();
    
    void onMouseMovedInWidget(unsigned int identifier);
    
signals:
    void hideMenu(void);
    void switchToHomepageArea(void);
    void switchToBrowserArea(void);
    void showWorkspace(QString);

private:
    int currentSelected;
    
    QList <medHomepagePushButton *> buttonsList;
    
    //! Frame for alt-tab like shortcut access menu
    QFrame *backgroundFrame;
};

#endif // MEDQUICKACCESSMENU_H
