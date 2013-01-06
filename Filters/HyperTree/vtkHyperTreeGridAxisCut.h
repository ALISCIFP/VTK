/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkHyperTreeGridAxisCut.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkHyperTreeGridAxisCut - Axis aligned hyper tree grid cut
//
// .SECTION Description
// Cut along an axis aligned plane. Only works for 3D grids.
// Produces disjoint (no point sharing) quads for now.
// NB: If cut plane contains inter-cell boundaries, the output will contain
// superimposed faces as a result.
//
// .SECTION See Also
// vtkHyperTreeGrid
//
// .SECTION Thanks
// This class was written by Philippe Pebay and Charles Law, Kitware 2012
// This work was supported in part by Commissariat a l'Energie Atomique (CEA/DIF)

#ifndef __vtkHyperTreeGridAxisCut_h
#define __vtkHyperTreeGridAxisCut_h

#include "vtkFiltersHyperTreeModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class vtkPoints;
class vtkCellArray;
class vtkHyperTreeGrid;

class VTKFILTERSHYPERTREE_EXPORT vtkHyperTreeGridAxisCut : public vtkPolyDataAlgorithm
{
public:
  static vtkHyperTreeGridAxisCut* New();
  vtkTypeMacro( vtkHyperTreeGridAxisCut, vtkPolyDataAlgorithm );
  void PrintSelf( ostream&, vtkIndent );

  // Description:
  // Normal axis: 0=X, 1=Y, 2=Z
  // Position of plane: Axis constant.
  vtkSetMacro(PlaneNormalAxis, int);
  vtkGetMacro(PlaneNormalAxis, int);
  vtkSetMacro(PlanePosition, double);
  vtkGetMacro(PlanePosition, double);

protected:
  vtkHyperTreeGridAxisCut();
  ~vtkHyperTreeGridAxisCut();

  int PlaneNormalAxis;
  double PlanePosition;

  virtual int RequestData( vtkInformation*, vtkInformationVector**, vtkInformationVector* );
  virtual int FillInputPortInformation( int, vtkInformation* );

  void ProcessTrees();
  void RecursiveProcessTree( void* );
  void ProcessLeaf3D( void* );
  void AddFace( vtkIdType inId, double* origin, double* size,
                double offset0, int axis0, int axis1, int axis2 );

  vtkHyperTreeGrid* Input;
  vtkPolyData* Output;
  vtkPoints* Points;
  vtkCellArray* Cells;

private:
  vtkHyperTreeGridAxisCut(const vtkHyperTreeGridAxisCut&);  // Not implemented.
  void operator=(const vtkHyperTreeGridAxisCut&);  // Not implemented.
};

#endif