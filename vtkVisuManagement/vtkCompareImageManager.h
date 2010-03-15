/*=========================================================================

Program:   vtkINRIA3D
Module:    $Id: vtkCompareImageManager.h 608 2008-01-14 08:21:23Z filus $
Language:  C++
Author:    $Author: filus $
Date:      $Date: 2008-01-14 09:21:23 +0100 (Mon, 14 Jan 2008) $
Version:   $Revision: 608 $

Copyright (c) 2007 INRIA - Asclepios Project. All rights reserved.
See Copyright.txt for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _vtk_CompareImageManager_h_
#define _vtk_CompareImageManager_h_

#include "vtkINRIA3DConfigure.h"

#include <vtkObject.h>
#include <vtkImageData.h>
#include <vtkLookupTable.h>
#include <vtkImageCheckerboard.h>
#include <vtkImageMapToWindowLevelColors.h>
//#include <vtkFuseImageFilter.h>
#include <vtkImageBlend.h>

/**
   \class vtkCompareImageManager vtkCompareImageManager.h "vtkCompareImageManager.h"
   \brief takes two input images and outputs a combination of them (grid or fuse)
   \author: Nicolas Toussaint
*/

class VTK_VISUMANAGEMENT_EXPORT vtkCompareImageManager: public vtkObject
{
  
 public:


  enum ComparisonModeIds
  {
    COMPARE_GRID,
    COMPARE_FUSE
  };
  
  
  static vtkCompareImageManager* New();
  vtkTypeRevisionMacro(vtkCompareImageManager, vtkObject);

  vtkGetObjectMacro (Input1, vtkImageData);
  vtkGetObjectMacro (Input2, vtkImageData);

  vtkSetObjectMacro (LUT, vtkLookupTable);
  vtkGetObjectMacro (LUT, vtkLookupTable);

  /** Set the comparison mode (COMPARE_GRID or COMPARE_FUSE) */
  void SetComparisonMode (ComparisonModeIds mode)
  { m_ComparisonMode = mode; }
  
  /** Get the comparison mode */
  ComparisonModeIds GetComparisonMode (void) const
  { return m_ComparisonMode; }

  /** Set the image input 1 */
  void SetInput1 (vtkImageData* im);
  
  /** Set the image input 2 */
  void SetInput2 (vtkImageData* im);
  
  /** Generate the output image (just an update */
  void GenerateData(void);

  /** Reset data */
  void ResetData (void);
  
  /** Specify the Lookup Table to use (not available yet) */
  void SetLUTValues(void);

  /** set thw window and levels */
  void SetWindowLevel (float window1, float level1,
		       float window2, float level2);

  /** Set the divisions in x, y and z axes for the checker */
  void SetNumberOfDivisions (int val1,int val2, int val3)
  {
    m_NGridDivisions[0] = val1;
    m_NGridDivisions[1] = val2;
    m_NGridDivisions[2] = val3;
  }
  /** Set the opacity to use between images in the fusefilter*/
  void SetFuseOpacity (double val)
  { m_FuseOpacity = val; }

  /** Get the opacity of the fusefilter */
  double GetFuseOpacity (void) const
  { return m_FuseOpacity; }

  /** Get the output : combination of the 2 input images */
  vtkImageData* GetOutput (void);
  
 protected:
  
  vtkCompareImageManager();
  ~vtkCompareImageManager();

  void SetProperties(void);

 private:

  vtkImageData*                   Input1;
  vtkImageData*                   Input2;
  vtkImageData*                   Output;
  
  vtkLookupTable*                 LUT;

  vtkImageCheckerboard*           m_CheckerImageFilter;
  vtkImageMapToWindowLevelColors* m_MapToWindowLevelImageFilter1;
  vtkImageMapToWindowLevelColors* m_MapToWindowLevelImageFilter2;
  
  vtkImageBlend*                  m_FuseImageFilter;
  
  int                             m_NGridDivisions[3];
  double                          m_FuseOpacity;
  ComparisonModeIds               m_ComparisonMode;

  bool                            m_IsWindowLevelSet;
  
  

};


#endif



  
