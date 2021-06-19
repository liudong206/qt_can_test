#include "veh_can_table.h"
namespace vehicle
{
namespace qev
{
#if 1
/*********************EV****************************/
 /*下发控车的报文0x32E*/
vector<table_info_t> Veh_ECU_II_SUB_MESSAGE_TAB = {
     {{1, 0}, {1, 7}, 8, 0.05, -5, VEHVLOC(TargetAccelerated)},
     {{2, 0}, {2, 7}, 8, 0.05, -5, VEHVLOC(axvCvComfortBandUpperValue)},
     {{3, 0}, {3, 7}, 8, 0.05, -5, VEHVLOC(axvCvComfortBandLowerValue)},
     {{4, 0}, {4, 6}, 7, 0.2, 0.0, VEHVLOC(aDtUpperLimitAxvCv)},
     {{4, 7}, {4, 7}, 1, 1.0, 0.0, VEHVLOC(CANX32E_47_Resvered)},
     {{5, 0}, {5, 6}, 7, -0.2, 0.0, VEHVLOC(aDtLowerLimitAxvCv)},//
     {{5, 7}, {5, 7}, 1, 1.0, 0.0, VEHVLOC(ACC_DriveOffReq)},
     {{6, 0}, {6, 0}, 1, 1.0, 0.0, VEHVLOC(ACC_DecToStopReq)},
     {{6, 1}, {6, 1}, 1, 1.0, 0.0, VEHVLOC(ACC_MinimumBreaking)},
     {{6, 2}, {6, 2}, 1, 1.0, 0.0, VEHVLOC(BreakPreferred)},
     {{6, 3}, {6, 5}, 3, 1.0, 0.0, VEHVLOC(AutomaticDriveControlStatus)},
     {{6, 6}, {6, 7}, 2, 1.0, 0.0, VEHVLOC(RequestESP_VLCModeClose)},
     {{7, 0}, {7, 3}, 4, 1.0, 0.0, VEHVLOC(RollingCount_32E)},
     {{7, 4}, {7, 7}, 4, 1.0, 0.0, VEHVLOC(CANX32E_74_77_Resvered)},
     {{8, 0}, {8, 7}, 8, 1.0, 0.0, VEHVLOC(AutonomousDrivingMsg3cheksum)}
};

 /*下发控车的报文0x32F*/
vector<table_info_t> Veh_ECU_III_SUB_MESSAGE_TAB = {
     {{1, 0}, {2, 7}, 16, 0.0004882, -16.0, VEHVLOC(CAN0X32F_10_27)},
     {{3, 0}, {3, 1}, 2, 1.0, 0.0, VEHVLOC(CAN0X32F_30_31)},
     {{3, 2}, {3, 2}, 1, 1.0, 0.0, VEHVLOC(CAN0X32F_32)},
     {{3, 3}, {3, 3}, 1, 1.0, 0.0, VEHVLOC(CAN0X32F_33)},
     {{3, 4}, {3, 4}, 1, 1.0, 0.0, VEHVLOC(CAN0X32F_34)},
     {{3, 5}, {3, 6}, 2, 1.0, 0.0, VEHVLOC(CAN0X32F_35_36)},
     {{3, 7}, {3, 7}, 1, 1.0, 0.0, VEHVLOC(CAN0X32F_37)},
     {{4, 0}, {4, 3}, 4, 1.0, 0.0, VEHVLOC(CAN0X32F_40_43)},
     {{4, 4}, {4, 7}, 4, 1.0, 0.0, VEHVLOC(CAN0X32F_44_47)},
     {{5, 0}, {6, 7}, 16, 1.0, 0.0, VEHVLOC(CAN0X32F_50_67)},
     {{7, 0}, {7, 3}, 4, 1.0, 0.0, VEHVLOC(CAN0X32F_70_73)},
     {{7, 4}, {7, 7}, 4, 1.0, 0.0, VEHVLOC(CAN0X32F_74_77)},
     {{8, 0}, {8, 7}, 8, 1.0, 0.0, VEHVLOC(CAN0X32F_80_87)}
};

 /*下发控车的报文0x3A3*/
vector<table_info_t> Veh_ECU_I_SUB_MESSAGE_TAB = {
      {{1, 0}, {1, 1}, 2, 1.0, 0.0, VEHVLOC(DrivingModeReg)},
     {{1, 2}, {1, 3}, 2, 1.0, 0.0, VEHVLOC(LampAutoGearSwitch)},
      {{1, 4}, {1, 4}, 1, 1.0, 0.0, VEHVLOC(TurnLeftLampSwitch)},
     {{1, 5}, {1, 5}, 1, 1.0, 0.0, VEHVLOC(TurnRightLampSwitch)},
     {{1, 6}, {1, 6}, 1, 1.0, 0.0, VEHVLOC(DangerAlarmLightSwitch)},
     {{1, 7}, {1, 7}, 1, 1.0, 0.0, VEHVLOC(BreakLightBCM)},
     {{2, 0}, {3, 7}, 16, 0.1, -780, VEHVLOC(TargetSteerAngle)},
     {{4, 2}, {4, 3}, 2, 1.0, 0.0, VEHVLOC(EPBtargetStatus)},
     {{4, 4}, {4, 7}, 4, 1.0, 0.0, VEHVLOC(WipertargetGera)},
     {{5, 0}, {5, 2}, 3, 1.0, 0.0, VEHVLOC(TargetGear)},
     {{5, 3}, {5, 4}, 2, 1.0, 0.0, VEHVLOC(DrivingModeFeedBack)},
      {{6, 0}, {7, 1}, 10, 1.0, 0.0, VEHVLOC(TargetSteerAngleSpeed)}
};


/*上报的报文*///0x34c
vector<table_info_t> Veh_EPS_SUB_MESSAGE_TAB = {
     {{1, 0}, {1, 0}, 1, 1.0, 0.0, VEHVLOC(Angle_Status)},
     {{2, 0}, {3, 7}, 16, -0.104, 811.2, VEHVLOC(SteeringWheelAngle)},
     {{4, 0}, {4, 1}, 2, 1.0, 0.0, VEHVLOC(EPS_Status)},/*liu dong*/
     {{4, 1}, {4, 2}, 2, 1.0, 0.0, VEHVLOC(AutomaticDrivingPermission)}
};

/*上报的报文*/
std::map<uint32_t,vector<table_info_t>> Veh_UP_MESSAGE_TAB = {
    {0x34C, Veh_EPS_SUB_MESSAGE_TAB},

    {0x32E, Veh_ECU_II_SUB_MESSAGE_TAB},
    {0x32F, Veh_ECU_III_SUB_MESSAGE_TAB},
    {0x3A3, Veh_ECU_I_SUB_MESSAGE_TAB},
};


/*下发控车的报文*/
std::map<uint32_t,vector<table_info_t>> Veh_DOWN_MESSAGE_TAB = {
     {0x32E, Veh_ECU_II_SUB_MESSAGE_TAB},
     {0x32F, Veh_ECU_III_SUB_MESSAGE_TAB},
     {0x3A3, Veh_ECU_I_SUB_MESSAGE_TAB},
 };
#endif


/**/
}
}
