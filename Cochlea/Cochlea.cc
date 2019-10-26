#include "cochlea.ih"

Cochlea::Cochlea()
  : d_hearMessage(-1, 0, ""),
    d_frpFix(true)
{
  d_infoMap["GS"            ] = iGameState;
  d_infoMap["unum"          ] = iUnum;
  d_infoMap["team"          ] = iTeam;
  d_infoMap["t"             ] = iGameTime;
  d_infoMap["pm"            ] = iPlayMode;
  d_infoMap["ax"            ] = iAxis        ;
  d_infoMap["ax1"           ] = iAxis1       ;
  d_infoMap["ax2"           ] = iAxis2       ;
  d_infoMap["B"             ] = iVisionBall  ;
  d_infoMap["L"             ] = iVisionLine  ;
  d_infoMap["F1L"           ] = iVisionFlag1L;
  d_infoMap["F1R"           ] = iVisionFlag1R;
  d_infoMap["F2L"           ] = iVisionFlag2L;
  d_infoMap["F2R"           ] = iVisionFlag2R;
  d_infoMap["G1L"           ] = iVisionGoal1L;
  d_infoMap["G1R"           ] = iVisionGoal1R;
  d_infoMap["G2L"           ] = iVisionGoal2L;
  d_infoMap["G2R"           ] = iVisionGoal2R;
  d_infoMap["mypos"         ] = iVisionSelfGT;
  d_infoMap["ballpos"       ] = iVisionBallGT;
  d_infoMap["myorien"       ] = iVisionMyOrienGT;
  d_infoMap["HJ"            ] = iHJ          ;
  d_infoMap["HJT"           ] = iHJT         ;
  d_infoMap["head1"         ] = iHeadJoint1;
  d_infoMap["head2"         ] = iHeadJoint2;
  d_infoMap["larm1"         ] = iLArmJoint1;
  d_infoMap["larm2"         ] = iLArmJoint2;
  d_infoMap["larm3"         ] = iLArmJoint3  ;
  d_infoMap["larm4"         ] = iLArmJoint4  ;
  d_infoMap["lleg1"         ] = iLLegJoint1  ;
  d_infoMap["lleg2"         ] = iLLegJoint2;
  d_infoMap["lleg3"         ] = iLLegJoint3;
  d_infoMap["lleg4"         ] = iLLegJoint4  ;
  d_infoMap["lleg5"         ] = iLLegJoint5  ;
  d_infoMap["lleg6"         ] = iLLegJoint6  ;
  d_infoMap["n"             ] = iName        ;
  d_infoMap["now"           ] = iNow         ;
  d_infoMap["rarm1"         ] = iRArmJoint1  ;
  d_infoMap["rarm2"         ] = iRArmJoint2  ;
  d_infoMap["rarm3"         ] = iRArmJoint3  ;
  d_infoMap["rarm4"         ] = iRArmJoint4  ;
  d_infoMap["rt"            ] = iRate        ;
  d_infoMap["rate1"         ] = iRate1       ;
  d_infoMap["rate2"         ] = iRate2       ;
  d_infoMap["tq"            ] = iTorque      ;
  d_infoMap["rleg1"         ] = iRLegJoint1  ;
  d_infoMap["rleg2"         ] = iRLegJoint2  ;
  d_infoMap["rleg3"         ] = iRLegJoint3  ;
  d_infoMap["rleg4"         ] = iRLegJoint4  ;
  d_infoMap["rleg5"         ] = iRLegJoint5  ;
  d_infoMap["rleg6"         ] = iRLegJoint6  ;
  d_infoMap["step"          ] = iStep        ;
  d_infoMap["time"          ] = iTime        ;
  d_infoMap["UJ"            ] = iUJ          ;
  d_infoMap["See"           ] = iVision      ;
  d_infoMap["GYR"           ] = iGyro        ;
  d_infoMap["torsogyro"     ] = iTorsoGyro   ;
  d_infoMap["TCH"           ] = iTouch       ;
  d_infoMap["lf"            ] = iFootLeft    ;
  d_infoMap["rf"            ] = iFootRight   ;
  d_infoMap["val"           ] = iVal         ;
  d_infoMap["FRP"           ] = iForceResistancePerceptor;
  d_infoMap["c"             ] = iContact;
  d_infoMap["f"             ] = iForce;
  d_infoMap["P"             ] = iP;
  d_infoMap["hear"          ] = iHear;
  d_infoMap["head"]           = iBodyHead;
  d_infoMap["rlowerarm"]      = iBodyRLowerArm;
  d_infoMap["llowerarm"]      = iBodyLLowerArm;
  d_infoMap["rfoot"]          = iBodyRFoot;
  d_infoMap["lfoot"]          = iBodyLFoot;
  d_infoMap["ACC"]            = iAcc;
  d_infoMap["a"]              = iAccA;

  _debugLevel1("Cochlea info size: " << d_infoMap.size() << ", iInfoID=" << iInfoID);
  //assert(d_infoMap.size() ==  iInfoID); Fails as long as infoMpa is wrong

  d_playModeMap["BeforeKickOff"]     = Types::BEFORE_KICKOFF;
  d_playModeMap["KickOff_Left"]      = Types::KICKOFF_LEFT;
  d_playModeMap["KickOff_Right"]     = Types::KICKOFF_RIGHT;
  d_playModeMap["PlayOn"]            = Types::PLAY_ON;
  d_playModeMap["free_kick_left"]    = Types::FREEKICK_LEFT;
  d_playModeMap["free_kick_right"]   = Types::FREEKICK_RIGHT;
  d_playModeMap["Goal_Left"]         = Types::GOAL_LEFT;
  d_playModeMap["Goal_Right"]        = Types::GOAL_RIGHT;
  d_playModeMap["goal_kick_left"]    = Types::GOAL_KICK_LEFT;
  d_playModeMap["goal_kick_right"]   = Types::GOAL_KICK_RIGHT;
  d_playModeMap["corner_kick_left"]  = Types::CORNER_KICK_LEFT;
  d_playModeMap["corner_kick_right"] = Types::CORNER_KICK_RIGHT;
  d_playModeMap["KickIn_Left"]       = Types::KICKIN_LEFT;
  d_playModeMap["KickIn_Right"]      = Types::KICKIN_RIGHT;

  for (unsigned i = 0; i < iInfoID; ++i)
    d_timestamps[i] = d_dt[i] = 0;

  d_opponentTeamName = "";

  Eigen::Matrix4d mat;
  mat.setZero();
  d_selfTransform = Eigen::Affine3d(mat);
}
