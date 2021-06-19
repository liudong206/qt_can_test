/**
 * @file Veh_CAN_Table.h
 * @author liudong
 * @brief
 * @version V0.2.1
 * @date 2020-12-26
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef VEH_CAN_TABLE_H
#define VEH_CAN_TABLE_H

#include "CAN_Abstract_Struct.h"
#include <map>
#include <vector>

using namespace std;

#define VEHVLOC(n) VdstLOC(vehicle::qev::Veh_Sub_Info,n)

namespace vehicle
{
namespace qev
{
#if 1
/*********************EV****************************/
typedef struct _Veh_Sub_Info{
/*0x32E控车报文ID*/ /*Receiver ESP*/
    /**
     * 目标加速度
     * 发送目标加速度，实际加速度控制范围[-5,3][m/s2]
     */
    UNIF_VAR_T TargetAccelerated;
    UNIF_VAR_T RollingCount_32E;
    UNIF_VAR_T AutonomousDrivingMsg3cheksum;


/*0x32F控车报文ID*/ /*Receiver ESP*/
    UNIF_VAR_T CAN0X32F_10_27;
   
/*0x3A3控车报文ID*/
    /**
     * 驾驶模式请求
     * 0x0:Invalid  0x1:开启自动驾驶模式 0x2:关闭自动驾驶模式  0x3:Reserved
     */
    UNIF_VAR_T DrivingModeReg;
   
    /**
     * 目标方向盘角度
     * 实际限制±500度，精度为0.1度，
     */
    UNIF_VAR_T TargetSteerAngle;
    
    /**
     * 驾驶模式反馈
     * 0x0:Invalid  0x1:自动驾驶模式 0x2:正常驾驶模式  0x3:Reserved
     */
    UNIF_VAR_T DrivingModeFeedBack;
    /**
     * 目标方向盘角速度
     * 单位【°/s】，一般设置范围50°/s到400°/s
     */
    UNIF_VAR_T TargetSteerAngleSpeed;


/*0x34c*/
    /**
     * 角度状态
     * 0x0:Invalid  0x1:开启自动驾驶模式 0x2:关闭自动驾驶模式  0x3:Reserved
     */
    UNIF_VAR_T Angle_Status;
    UNIF_VAR_T SteeringWheelAngle;
    UNIF_VAR_T EPS_Status;
    UNIF_VAR_T AutomaticDrivingPermission;



    /**/
    _Veh_Sub_Info() :
            TargetAccelerated(0.0),RollingCount_32E(0.0),AutonomousDrivingMsg3cheksum(0.0),
            CAN0X32F_10_27(0.0),
            DrivingModeReg(0.0),TargetSteerAngle(0.0),DrivingModeFeedBack(3.0),TargetSteerAngleSpeed(0.0),
            Angle_Status(0.0),SteeringWheelAngle(0.0),EPS_Status(0.0),AutomaticDrivingPermission(0.0){}
} Veh_Sub_Info;

extern vector<table_info_t> Veh_EPS_SUB_MESSAGE_TAB;    //0x34c
extern std::map<uint32_t,vector<table_info_t>> Veh_UP_MESSAGE_TAB;

/**/
extern vector<table_info_t> Veh_ECU_I_SUB_MESSAGE_TAB;
extern vector<table_info_t> Veh_ECU_II_SUB_MESSAGE_TAB;
extern vector<table_info_t> Veh_ECU_III_SUB_MESSAGE_TAB;
extern std::map<uint32_t,vector<table_info_t>> Veh_DOWN_MESSAGE_TAB;
/**/
#endif


typedef struct _Systemtime{
    float second;
    float nsecond;
}Systemtime;


typedef struct _Veh_Info{
    uint8_t seq;
    Systemtime timeStamp;
    Veh_Sub_Info VehInfo;
    _Veh_Info() : seq(0)
    {
        timeStamp.second = 0;
        timeStamp.nsecond = 0;
    }
}Veh_Info;


typedef struct _Element {
    Systemtime timeStamp;
    uint32_t canId;
    uint8_t validLen;
    vector<uint8_t> data;
}Element;

typedef struct _CanBusDataParam {
    uint8_t seq;
    vector<Element> elementList;
}CanBusDataParam;


}
} // namespace vehicle


#endif // VEH_CAN_TABLE_H
