#include "ikgaitgenerator.ih"

VectorXd IKGaitGenerator::doStep()
{
  AgentModel& am = SAgentModel::getInstance();

  // Determine the direction the hip will move to
  VectorXd hipMove = d_stage == 0 ?
    -(d_curStep.rEnd - d_curStep.rStart) :
    -(d_curStep.lEnd - d_curStep.lStart);

  cout << "hipmove: " << hipMove.transpose() << endl;

  // Determine desired ankle positions
  Vector3d lAnklePos(0, 0, 0);
  Vector3d rAnklePos(0, 0, 0);

  double alpha = fmod(d_phase, M_PI) / M_PI;
  double hipAngle = 0;

  // Stance foot still moves in opposite direction. Swing foot up
  // and forward. If turning, turn hip when foot opposite to turn
  // direction is stance foot (ie, turning right: turn out when
  // standing on left).

  // stage = 0: swing left
  if (d_stage == 0)
  {
    rAnklePos = d_curStep.rStart - alpha * hipMove;

    lAnklePos = 
      (1.0 - alpha) * d_curStep.lStart +
      alpha * d_curStep.lEnd;
    lAnklePos.z() = sin(alpha * M_PI) * d_ellipseHeight + d_curStep.offsetZ;

    hipAngle = d_curStep.turn > 0 ?
      (1.0 - alpha) * d_curStep.hipAngle :
      alpha * d_curStep.hipAngle;
  }
  // stage = 1: swing right
  else
  {
    lAnklePos = d_curStep.lStart - alpha * hipMove;

    rAnklePos =
      (1.0 - alpha) * d_curStep.rStart +
      alpha * d_curStep.rEnd;
    rAnklePos.z() = sin(alpha * M_PI) * d_ellipseHeight + d_curStep.offsetZ;

    hipAngle = d_curStep.turn < 0 ?
      (1.0 - alpha) * d_curStep.hipAngle :
      alpha * d_curStep.hipAngle;
  }
  
  cout << lAnklePos.transpose() << ", " << rAnklePos.transpose() << endl;

  // Determine desired joint angles

  VectorXd jointAngles = am.getJointAngles();

  VectorXd lAngles = am.jointAnglesForAnklePosition(lAnklePos, Types::LEFT, hipAngle);
  VectorXd rAngles = am.jointAnglesForAnklePosition(rAnklePos, Types::RIGHT, hipAngle);
  lAngles(0) = rAngles(0) = hipAngle;

  cout << lAngles.transpose() << ", " << rAngles.transpose() << endl;

  fillJointAngles(jointAngles, lAngles, rAngles);

  // Keep arms down
  jointAngles(Types::LARM1) = -.5 * M_PI;
  jointAngles(Types::RARM1) = -.5 * M_PI;

  return jointAngles;
}
