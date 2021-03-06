/**
 * \file GyotoMinkowski.h
 * \brief The Minkowski flat-space metric
 * 
 * Use &lt;Cartesian&gt; or &lt;/Spherical&gt; to select the coordinate system
 * kind.
 */

/*
    Copyright 2014 Thibaut Paumard

    This file is part of Gyoto.

    Gyoto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Gyoto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Gyoto.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __GyotoMinkowski_H_
#define __GyotoMinkowski_H_

#include <GyotoMetric.h>

namespace Gyoto {
  namespace Metric { class Minkowski; }
}

/**
 * \class Gyoto::Metric::Minkowski
 * \brief The Minkowski flat-space metric
 * 
 * Use &lt;Cartesian&gt; or &lt;/Spherical&gt; to select the coordinate system
 * kind.
 */

class Gyoto::Metric::Minkowski
: public Gyoto::Metric::Generic
{
  friend class Gyoto::SmartPointer<Gyoto::Metric::Minkowski>;

 private:
  
 public:
  // Those are mere wrappers arround Generic::coordKind(), useful for
  // declaring a boolen property using the macro GYOTO_PROPERTY_BOOL:
  void spherical(bool);
  bool spherical() const;
  // This is the bare minimum of what a Metric class must implement:
  GYOTO_OBJECT;
  Minkowski();
  virtual Minkowski* clone() const ;

  void gmunu(double g[4][4], const double x[4]) const ;
  int christoffel(double dst[4][4][4], const double x[4]) const ;

  // Those two are implemented as examples.
  double gmunu(const double x[4], int mu, int nu) const ;
  double christoffel(const double coord[4],
		     const int alpha, const int mu, const int nu) const ;
  void observerTetrad(std::string const obskind,
		      double const pos[4], double fourvel[4],
		      double screen1[4], double screen2[4], 
		      double screen3[4]) const;
};

#endif
