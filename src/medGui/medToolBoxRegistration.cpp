/* medToolBoxRegistration.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 19 09:06:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  5 09:37:36 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 186
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "medDropSite.h"
#include "medToolBoxRegistration.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>

#include <medCore/medDataManager.h>
#include <medCore/medViewManager.h>

#include <QtGui>

class medToolBoxRegistrationPrivate
{
public:
    medDropSite *processDropSiteFixed;
    medDropSite *processDropSiteMoving;
};

medToolBoxRegistration::medToolBoxRegistration(QWidget *parent) : medToolBox(parent), d(new medToolBoxRegistrationPrivate)
{
    // Process page

    QWidget *processPage = new QWidget;
    
    d->processDropSiteFixed  = new medDropSite(processPage);
    d->processDropSiteFixed->setText("Fixed");

    d->processDropSiteMoving = new medDropSite(processPage);
    d->processDropSiteMoving->setText("Moving");

    QHBoxLayout *processDropSiteLayout = new QHBoxLayout;
    processDropSiteLayout->addWidget(d->processDropSiteFixed);
    processDropSiteLayout->addWidget(d->processDropSiteMoving);

    QPushButton *processRunButton = new QPushButton("Run", processPage);

    QVBoxLayout *processLayout = new QVBoxLayout(processPage);
    processLayout->addLayout(processDropSiteLayout);
    processLayout->addWidget(processRunButton);

    connect(processRunButton, SIGNAL(clicked()), this, SLOT(run()));

    // Layout page

    QWidget *layoutPage = new QWidget;

    QPushButton *layoutButtonCompare = new QPushButton("Compare", layoutPage);
    layoutButtonCompare->setCheckable(true);
    layoutButtonCompare->setChecked(false);

    QPushButton *layoutButtonFuse = new QPushButton("Fuse", layoutPage);
    layoutButtonFuse->setCheckable(true);
    layoutButtonFuse->setChecked(false);

    QButtonGroup *layoutButtonGroup = new QButtonGroup(layoutPage);
    layoutButtonGroup->addButton(layoutButtonCompare);
    layoutButtonGroup->addButton(layoutButtonFuse);
    layoutButtonGroup->setExclusive(true);

    QSlider *layoutFuseSlider = new QSlider(Qt::Horizontal, layoutPage);

    QHBoxLayout *layoutButtonLayout = new QHBoxLayout;
    layoutButtonLayout->addWidget(layoutButtonCompare);
    layoutButtonLayout->addWidget(layoutButtonFuse);

    QVBoxLayout *layoutLayout = new QVBoxLayout(layoutPage);
    layoutLayout->addLayout(layoutButtonLayout);
    layoutLayout->addWidget(layoutFuseSlider);

    connect(layoutButtonCompare, SIGNAL(clicked()), this, SIGNAL(setupLayoutCompare()));
    connect(layoutButtonFuse, SIGNAL(clicked()), this, SIGNAL(setupLayoutFuse()));

    // /////////////////////////////////////////////////////////////////
    // Setup
    // /////////////////////////////////////////////////////////////////

    medToolBoxTab *tab = new medToolBoxTab(this);
    tab->addTab(processPage, "Process");
    tab->addTab(layoutPage, "Layout");

    this->setTitle("Registration");
    this->setWidget(tab);
}

medToolBoxRegistration::~medToolBoxRegistration(void)
{
    delete d;

    d = NULL;
}

void medToolBoxRegistration::run(void)
{
    dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create("itkProcessRegistration");

    if(!process) {
        qDebug() << "No itkProcessRegistration process available";
        return;
    }

    qDebug() << d->processDropSiteFixed->index();
    qDebug() << d->processDropSiteMoving->index();
    
    dtkAbstractData *fixedData = medDataManager::instance()->data(d->processDropSiteFixed->index());

    if(!fixedData) {
        qDebug() << "Unable to retrieve fixed image";
        // return;
    }

    dtkAbstractData *movingData = medDataManager::instance()->data(d->processDropSiteMoving->index());

    if(!movingData) {
        qDebug() << "Unable to retrieve moving image";
        // return;
    }

    dtkAbstractView *fixedView = medViewManager::instance()->views(d->processDropSiteFixed->index()).first();

    if(!fixedView) {
        qDebug() << "Unable to retrieve fixed view";
        // return;
    }

    dtkAbstractView *movingView = medViewManager::instance()->views(d->processDropSiteMoving->index()).first();

    if(!movingView) {
        qDebug() << "Unable to retrieve moving view";
        // return;
    }

    fixedView->link(movingView);

    Q_UNUSED(process);
    Q_UNUSED(fixedData);
    Q_UNUSED(movingData);
    Q_UNUSED(fixedView);
    Q_UNUSED(movingView);
}