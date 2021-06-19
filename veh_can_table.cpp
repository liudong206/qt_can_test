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
     {{7, 0}, {7, 3}, 4, 1.0, 0.0, VEHVLOC(RollingCount_32E)},
     {{8, 0}, {8, 7}, 8, 1.0, 0.0, VEHVLOC(AutonomousDrivingMsg3cheksum)}
};

 /*下发控车的报文0x32F*/
vector<table_info_t> Veh_ECU_III_SUB_MESSAGE_TAB = {
     {{1, 0}, {2, 7}, 16, 0.0004882, -16.0, VEHVLOC(CAN0X32F_10_27)},
};

 /*下发控车的报文0x3A3*/
vector<table_info_t> Veh_ECU_I_SUB_MESSAGE_TAB = {
      {{1, 0}, {1, 1}, 2, 1.0, 0.0, VEHVLOC(DrivingModeReg)},
     {{2, 0}, {3, 7}, 16, 0.1, -780, VEHVLOC(TargetSteerAngle)},
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
