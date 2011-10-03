/* medToolBoxFiltering.cpp ---
 *
 * @author Clément Philipot <clement.philipot@inria.fr>
 *
 */

#include "medToolBoxFiltering.h"
#include "medToolBoxFilteringCustom.h"

#include <medToolBoxFactory.h>
#include <medDropSite.h>

#include <medCore/medDataManager.h>

#include <dtkCore/dtkAbstractData.h>



class medToolBoxFilteringPrivate
{
public:
    QComboBox    *chooseFilter;
    QPushButton *saveInDatabaseButton;
//    QPushButton *saveToDiskButton;
    medToolBoxFilteringCustom *customToolBox;
    dtkAbstractData *inputData;
    medDataIndex index;
};

medToolBoxFiltering::medToolBoxFiltering(QWidget *parent) : medToolBox(parent), d(new medToolBoxFilteringPrivate)
{
    QWidget *displayWidget = new QWidget(this);

    d->saveInDatabaseButton = new QPushButton(tr("Store in Database"),this);

//    d->saveToDiskButton = new QPushButton(tr("Save to Disk"),this);

    d->chooseFilter = new QComboBox(this);
    d->chooseFilter->addItem(tr("Choose filter"));

    QVBoxLayout *filterLayout = new QVBoxLayout(displayWidget);
    filterLayout->addWidget(d->saveInDatabaseButton);
//    filterLayout->addWidget(d->saveToDiskButton);
    filterLayout->addWidget(d->chooseFilter);

    foreach(QString toolbox, medToolBoxFactory::instance()->filteringToolBoxes())
        d->chooseFilter->addItem(toolbox, toolbox);

    connect(d->chooseFilter, SIGNAL(activated(const QString&)), this, SLOT(onToolBoxChosen(const QString&)));
    connect(d->saveInDatabaseButton,SIGNAL(clicked()), this, SLOT(onSavedImage()));


    this->setTitle(tr("Filtering View"));
    this->addWidget(displayWidget);

    d->customToolBox = NULL;
    d->inputData = NULL;
}

medToolBoxFiltering::~medToolBoxFiltering()
{
    delete d;
    d = NULL;
}

medToolBoxFilteringCustom* medToolBoxFiltering::customToolbox(void)
{

    return d->customToolBox;
}

dtkAbstractData*  medToolBoxFiltering::data()
{
    return d->inputData;
}

void medToolBoxFiltering::onToolBoxChosen(const QString& id)
{
    medToolBoxFilteringCustom *toolbox = medToolBoxFactory::instance()->createCustomFilteringToolBox(id);

    if(!toolbox) {
        qDebug() << "Unable to instanciate" << id << "toolbox";
        return;
    }

    toolbox->setFilteringToolBox(this);
    //get rid of old toolBox
    if (d->customToolBox)
    {
        emit removeToolBox(d->customToolBox);
        delete d->customToolBox;
    }
    d->customToolBox = toolbox;
    emit addToolBox(toolbox);

    connect(d->customToolBox,SIGNAL(success()),this,SIGNAL(processFinished()));
}


void medToolBoxFiltering::onInputSelected(const medDataIndex& index)
{
    if (!index.isValid())
        return;

    d->inputData = medDataManager::instance()->data(index).data();

    if (!d->inputData)
        return;
}

void medToolBoxFiltering::clear(void)
{
    if (d->customToolBox)
        d->customToolBox->clear();

    d->inputData = NULL;
    d->index = medDataIndex();
}

void medToolBoxFiltering::setDataIndex(medDataIndex index)
{
    d->index = index;
}

void medToolBoxFiltering::onSavedImage(void)
{
    medDataManager::instance()->storeNonPersistentSingleDataToDatabase(d->index);
}