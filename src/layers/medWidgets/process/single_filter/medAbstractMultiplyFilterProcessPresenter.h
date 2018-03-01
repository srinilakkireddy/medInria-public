/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2018. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medAbstractSingleFilterOperationDoubleProcessPresenter.h>
#include <medProcessPresenterFactory.h>
#include <medAbstractMultiplyFilterProcess.h>

#include <medWidgetsExport.h>

class MEDWIDGETS_EXPORT medAbstractMultiplyFilterProcessPresenter: public medAbstractSingleFilterOperationDoubleProcessPresenter
{
    Q_OBJECT
public:
    medAbstractMultiplyFilterProcessPresenter(medAbstractMultiplyFilterProcess *parent)
        : medAbstractSingleFilterOperationDoubleProcessPresenter(parent)
    {}
    virtual medAbstractMultiplyFilterProcess* process() const = 0;
};

MED_DECLARE_PROCESS_PRESENTER_FACTORY(medAbstractMultiplyFilterProcess, MEDWIDGETS_EXPORT)
