/**
 * \file GyotoJet.h
 * \brief Simple jet model with kappa-distribution
 * synchrotron emission from Pandya et al. (2016)
 *
 * This class implements a jet defined as the volume contained
 * between the two conical surfaces defined by angles jetInnerOpeningAngle_
 * and jetOuterOpeningAngle_, with apex located on the black hole rotation
 * axis at altitude jetBaseHeight_ in units of M.
 *
 * The Lorentz factor is assumed constant at gammaJet_.
 * The electron number density at the base of the jet is baseNumberDensity_cgs_,
 * its z-evolution is dedictated by mass conservation.
 * The electron temperature is baseTemperature_, its z-evolution is assumed
 * to follow a power law z^temperatureSlope_. The magnetic field
 * amplitude is defined by the magnetic-to-particles equipartition ratio,
 * magneticParticlesEquipartitionRatio_.
 * 
 * The jet emits synchrotron radiation, assuming that the electrons
 * follow a kappa distribution, ie the smooth gluing of a thermal
 * distribution at low electron Lorentz factor, to a power-law distribution
 * at high electron Lorentz factor. This distribution, as well as the
 * resulting emission and absorption coefficients are taken from:
 * Pandya et al., ApJ, 822, 34 (2016), section 5.3.3
 */

/*
    Copyright 2017-2018 Frederic Vincent

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

#ifndef __GyotoJet_H_ 
#define __GyotoJet_H_ 

#include <iostream>
#include <fstream>
#include <iomanip>

namespace Gyoto{
  namespace Astrobj { class Jet; }
}

#include <GyotoStandardAstrobj.h>
#include <GyotoKappaDistributionSynchrotronSpectrum.h>

/**
 * \class Gyoto::Astrobj::Jet
 * \brief Simple jet model with kappa-distribution
 * synchrotron emission from Pandya et al. (2016)
 *
 * This class implements a jet defined as the volume contained
 * between the two conical surfaces defined by angles jetInnerOpeningAngle_
 * and jetOuterOpeningAngle_, with apex located on the black hole rotation
 * axis at altitude jetBaseHeight_ in units of M.
 * 
 * The Lorentz factor is assumed constant at gammaJet_.
 * The electron number density at the base of the jet is baseNumberDensity_cgs_,
 * its z-evolution is dedictated by mass conservation.
 * The electron temperature is baseTemperature_, its z-evolution is assumed
 * to follow a power law z^temperatureSlope_. The magnetic field
 * amplitude is defined by the magnetic-to-particles equipartition ratio,
 * magneticParticlesEquipartitionRatio_.
 *
 * The jet emits synchrotron radiation, assuming that the electrons
 * follow a kappa distribution, ie the smooth gluing of a thermal
 * distribution at low electron Lorentz factor, to a power-law distribution
 * at high electron Lorentz factor. This distribution, as well as the
 * resulting emission and absorption coefficients are taken from:
 * Pandya et al., ApJ, 822, 34 (2016), section 5.3.3
 */

class Gyoto::Astrobj::Jet
: public Astrobj::Standard,
  public Hook::Listener
{
  friend class Gyoto::SmartPointer<Gyoto::Astrobj::Jet>;
 private:
  SmartPointer<Spectrum::KappaDistributionSynchrotron> spectrumKappaSynch_;
  double jetOuterOpeningAngle_; ///< Jet outer opening angle (rad)
  double jetInnerOpeningAngle_; ///< Jet inner opening angle (rad)
  double jetBaseHeight_; ///< Height of the base of the jet (z value, M units)
  double gammaJet_; ///< Constant Lorentz factor in jet
  double baseNumberDensity_cgs_; ///< electron nb density at jet base (cgs)
  double baseTemperature_; ///< electron temperature at jet base (K)
  double temperatureSlope_; ///< electron temperature \propto z^temperatureSlope_
  double magneticParticlesEquipartitionRatio_; ///< P<SUB>magn</SUB>/(n<SUB>e</SUB> m<SUB>p</SUB> c<SUP>2</SUP>)

  // Constructors - Destructor
  // -------------------------
 public:
  GYOTO_OBJECT;
  GYOTO_OBJECT_THREAD_SAFETY;
  
  Jet(); ///< Standard constructor
  
  Jet(const Jet& ) ;///< Copy constructor
  virtual Jet* clone () const; ///< Cloner
  
  virtual ~Jet() ;                        ///< Destructor
  
  // Accessors
  // ---------
 public:
  void jetOuterOpeningAngle(double ang);
  double jetOuterOpeningAngle() const;
  void jetInnerOpeningAngle(double ang);
  double jetInnerOpeningAngle() const;
  void jetBaseHeight(double hh);
  double jetBaseHeight() const;
  void gammaJet(double gam);
  double gammaJet() const;
  double baseNumberDensity() const;
  double baseNumberDensity(std::string const &unit) const;
  void baseNumberDensity(double ne);
  void baseNumberDensity(double dens, std::string const &unit);
  void baseTemperature(double tt);
  double baseTemperature()const;
  void temperatureSlope(double ss);
  double temperatureSlope()const;
  void magneticParticlesEquipartitionRatio(double rr);
  double magneticParticlesEquipartitionRatio()const;
  void kappaIndex(double index);
  double kappaIndex()const;

 public:
  using Generic::metric;
  virtual void metric(SmartPointer<Metric::Generic>);
    
  virtual double emission(double nu_em, double dsem,
			  double c_ph[8],double c_obj[8]=NULL) const;
  virtual double operator()(double const coord[4]) ;
  virtual void radiativeQ(double Inu[], double Taunu[], 
			  double nu_em[], size_t nbnu,
			  double dsem, double coord_ph[8],
			  double coord_obj[8]=NULL) const ;
  virtual void getVelocity(double const pos[4], double vel[4]) ;

};

#endif
