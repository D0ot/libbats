/*
 *  Little Green BATS (2008-2013), AI department, University of Groningen
 *
 *  Authors: 	Sander van Dijk (sgdijk@ai.rug.nl)
 *		Drew Noakes (drew@drewnoakes.com)
 *		Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *		Jeroen Kuijpers (jkuypers@gmail.com)
 *
 *  Date: 	August 17, 2013
 *
 *  Website:	https://github.com/sgvandijk/libbats
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#ifndef BATS_UNUMPCSELECTOR_HH
#define BATS_UNUMPCSELECTOR_HH

#include "../pcselector.hh"
#include "../../AgentModel/agentmodel.hh"

namespace bats
{
  /** Uniform number based player class selector implementation
   *
   * With this implementation, the agent's player class is simply
   * equal to its uniform number.
   */
  class UnumPCSelector : public PCSelector
  {
  public:
    friend class Singleton<PCSelector>;
    
    virtual unsigned getPlayerClass() { return SAgentModel::getInstance().getUnum(); }

  private:
    UnumPCSelector() {}
    UnumPCSelector(UnumPCSelector const&); //NI
    UnumPCSelector operator=(UnumPCSelector const&); //NI
      
  };
}

#endif
