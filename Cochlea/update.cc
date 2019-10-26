#include "cochlea.ih"

void Cochlea::update()
{
  while (bats::SAgentSocketComm::getInstance().hasNextMessage())
  {    
    shared_ptr<Predicate> pred = bats::SAgentSocketComm::getInstance().nextMessage();
    if (pred)
    {
      // for debug -------------------
      d_updated[iVisionBallGT] = false;
      d_updated[iVisionMyOrienGT] = false;
      d_updated[iVisionSelfGT] = false;
      // for debug -------------------

      integrate(pred);
      synthesizeDerivedData();
    }
  }
}
