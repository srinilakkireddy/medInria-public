#ifndef medDbControllerFactory_h__
#define medDbControllerFactory_h__

#include "medCoreExport.h"
#include <dtkCore/dtkAbstractFactory.h>
#include <QtCore>

class medAbstractDbController;
class medDbControllerFactoryPrivate;

/**
 * Factory that creates concrete instances of medDatabaseControllers
 */
class MEDCORE_EXPORT medDbControllerFactory : public dtkAbstractFactory
{
  Q_OBJECT

public:
  /**
   * @brief This function pointer designates functions allocating memory
   *
  */
  typedef medAbstractDbController*(*medDbControllerCreator)(void);

  /**
   * @brief Type designating the internal has table containing the creator functions.
   *
  */
  typedef QHash<QString, medDbControllerCreator> medDbControllerCreatorHash;

public:
  /**
   * @brief Gets an instance of the factory.
   *
   * @param void
   * @return medDbControllerFactory * Factory instance
  */
  static medDbControllerFactory * instance(void);
  
  /**
   * @brief Registers a new widget type, and its creator function.
   *
   * @param type name of the controller.
   * @param func creator function
   * @return bool true if type was not registered already, false if it exists.
  */
  bool registerDbController (const QString& type, medDbControllerCreator func);


public slots:
  /**
   * @brief Creates a new controller.
   * When setting the typename, the factory tries to find this in the hash, 
   * otherwise or if not found it will try to return the first one that was registered
   * @param type the type to instantiate
   * @return medSettingsWidget * the newly allocated widget.
  */
  medAbstractDbController * createDbController(QString type = "");

protected:
  /**
   * @brief Constructor, not to be used by users.
   *
   * Use the instance() method instead to get a singleton.
   *
   * @param void
  */
  medDbControllerFactory(void);

  /**
   * @brief Destructor, not to be used by users.
   *
   * The singleton will be deleted at application closing time.
   *
   * @param void
  */
  ~medDbControllerFactory(void);

private:

  static medDbControllerFactory* s_instance; 

  medDbControllerFactoryPrivate* d;
};

#endif 