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
    /**
     * 加速度上限值
     * 加速度控制量的容差上限值，加速度取值范围[-5,3][m/s2]，目标设置为0.1，主要影响加速度跨零点的控制性能
     */
    UNIF_VAR_T axvCvComfortBandUpperValue;
    /**
     * 加速度下限值
     * 加速度控制量的容差下限值，加速度取值范围[-5,3][m/s2]，目标设置为-0.1，主要影响加速度跨零点的控制性能
     */
    UNIF_VAR_T axvCvComfortBandLowerValue;
    /**
     * 最大允许目标加速度梯度
     * 影响目标加速度上升斜率，加速度梯度取值范围[0,16][m/s3]
     */
    UNIF_VAR_T aDtUpperLimitAxvCv;
    UNIF_VAR_T CANX32E_47_Resvered;
    /**
     * 最小允许目标加速度梯度
     * 影响目标减速度下降斜率，加速度梯度取值范围[-16,0][m/s3]
     */
    UNIF_VAR_T aDtLowerLimitAxvCv;
    /**
     * 起步请求
     * 0x0:no request  0x1:request
     * 1、若发0x1，ESP会以一种方式释放制动压力，可以通过标定优化起步舒适度
     * 2、若发0x0，ESP会以另外一种方式泄压
     * 一般建议起步时发1，车速大于5km/h后停止发送
     */
    UNIF_VAR_T ACC_DriveOffReq;
    /**
     * 停车请求
     * 0x0:no request  0x1:request
     * 1、若发0x1，在接近停止时会对减速度进行平稳处理
     */
    UNIF_VAR_T ACC_DecToStopReq;
    /**
     * 最小制动请求
     * 0x0:no demand  0x1:demand
     * 1、若发0x1，会按照加速度容差的上限值进行处理
     */
    UNIF_VAR_T ACC_MinimumBreaking;
    /**
     * 预制动请求
     * 0x0:no demand  0x1:demand
     * 需紧急制动时提前600ms发送0x1（在需要-5m/s2时提前发送）
     * 1、若不发送，ESP会等待电机反馈扭矩降至最小扭矩（电控系统发出）时才会启动液压制动；
     * 2、若发送，ESP会在内部目标扭矩降至最小扭矩之后就启动，而不会等待电机扭矩实际输出降至最小扭矩
     */
    UNIF_VAR_T BreakPreferred;
    /**
     * 自动驾驶状态控制
     * 0x0:无人驾驶关闭状态  0x1:预留 0x2:预留  0x3:无人功能开启状态  0x4:Brake-Onlymode（延迟制动，系统退出依然保持制动）  0x5:Override（超车时发送）  0x6:车辆处于静止状态时发送  0x7:Failure mode 0x6
     * 1）需要保持持续发送
     * 2) 0,1,2都处理成无人驾驶关闭
     * 3）0x4，不响应加速控制，只能进行刹车控制
     * 4）0x5，当接收到电控发出的驾驶员请求扭矩大于自动驾驶请求扭矩的标志位信号时发出
     * 5）0x6，要求保持静止
     * 6）0x7，上位机出错发出，ESP收到后会进行降级处理
     */
    UNIF_VAR_T AutomaticDriveControlStatus;
    /**
     * 模式关闭请求
     * 0x0:soft off  0x1:退出无人驾驶 0x2:immediate off  0x3:保持无人驾驶
     * 1）只有在AutomaticDriveControlStatus是0,1,2,7时才会起作用
     * 2) 0是缓慢释放制动压力
     * 3）1是中速释放压力
     * 4）2是立即释放压力
     * 5）若AutomaticDriveControlStatus发的是0等值时，若还是发3，实际会按照2执行
     */
    UNIF_VAR_T RequestESP_VLCModeClose;

    UNIF_VAR_T RollingCount_32E;
    UNIF_VAR_T CANX32E_74_77_Resvered;
    UNIF_VAR_T AutonomousDrivingMsg3cheksum;


/*0x32F控车报文ID*/ /*Receiver ESP*/
    UNIF_VAR_T CAN0X32F_10_27;
    UNIF_VAR_T CAN0X32F_30_31;
    UNIF_VAR_T CAN0X32F_32;
    UNIF_VAR_T CAN0X32F_33;
    UNIF_VAR_T CAN0X32F_34;
    UNIF_VAR_T CAN0X32F_35_36;
    UNIF_VAR_T CAN0X32F_37;
    UNIF_VAR_T CAN0X32F_40_43;
    UNIF_VAR_T CAN0X32F_44_47;
    UNIF_VAR_T CAN0X32F_50_67;
    UNIF_VAR_T CAN0X32F_70_73;
    UNIF_VAR_T CAN0X32F_74_77;
    UNIF_VAR_T CAN0X32F_80_87;

/*0x3A3控车报文ID*/
    /**
     * 驾驶模式请求
     * 0x0:Invalid  0x1:开启自动驾驶模式 0x2:关闭自动驾驶模式  0x3:Reserved
     */
    UNIF_VAR_T DrivingModeReg;
    /**
     * 大灯自动开启控制标志位
     * 0x0:无效  0x1:AUTO档 0x2:非AUTO档  0x3:Reserved
     */
    UNIF_VAR_T LampAutoGearSwitch;
    /**
     * 左转向灯开关
     * 0x0:关闭  0x1:打开
     */
    UNIF_VAR_T TurnLeftLampSwitch;
    /**
     * 右转向灯开关
     * 0x0:关闭  0x1:打开
     */
    UNIF_VAR_T TurnRightLampSwitch;
    /**
     * 紧急告警灯
     * 0x0:关闭  0x1:打开
     */
    UNIF_VAR_T DangerAlarmLightSwitch;
    /**
     * 制动灯，用ESP系统进行行车制动不能直接触发制动灯，需要分开控制
     * 0x0:关闭  0x1:打开
     */
    UNIF_VAR_T BreakLightBCM;
    /**
     * 目标方向盘角度
     * 实际限制±500度，精度为0.1度，
     */
    UNIF_VAR_T TargetSteerAngle;
    /**
     * 目标EPB状态
     * 0x0:无效  0x1:拉起 0x2:释放  0x3:Reserved
     */
    UNIF_VAR_T EPBtargetStatus;
    /**
     * 目标雨刮档位
     * 0x0:预留  0x1:OFF档位 0x2:点刮短按  0x3:点刮长按  0x4:间隙1档  0x5:间隙2档  0x6:间隙3档  0x7:间隙4档  0x8:慢刮  0x9:快刮
     */
    UNIF_VAR_T WipertargetGera;
    /**
     * 目标档位
     * 0x0:无效  0x1:P档  0x2:R档  0x3:N档  0x4:D档
     */
    UNIF_VAR_T TargetGear;
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
            TargetAccelerated(0.0),axvCvComfortBandUpperValue(0.0),axvCvComfortBandLowerValue(0.0),aDtUpperLimitAxvCv(0.0),CANX32E_47_Resvered(0.0),aDtLowerLimitAxvCv(0.0),ACC_DriveOffReq(0.0),ACC_DecToStopReq(0.0),ACC_MinimumBreaking(0.0),BreakPreferred(0.0),AutomaticDriveControlStatus(0.0),RequestESP_VLCModeClose(0.0),RollingCount_32E(0.0),CANX32E_74_77_Resvered(0.0),AutonomousDrivingMsg3cheksum(0.0),
            CAN0X32F_10_27(0.0),CAN0X32F_30_31(0.0),CAN0X32F_32(0.0),CAN0X32F_33(0.0),CAN0X32F_34(0.0),CAN0X32F_35_36(0.0),CAN0X32F_37(0.0),CAN0X32F_40_43(0.0),CAN0X32F_44_47(0.0),CAN0X32F_50_67(0.0),CAN0X32F_70_73(0.0),CAN0X32F_74_77(0.0),CAN0X32F_80_87(0.0),
            DrivingModeReg(0.0),LampAutoGearSwitch(0.0),TurnLeftLampSwitch(0.0),TurnRightLampSwitch(0.0),DangerAlarmLightSwitch(0.0),BreakLightBCM(0.0),TargetSteerAngle(0.0),EPBtargetStatus(0.0),WipertargetGera(0.0),TargetGear(0.0),DrivingModeFeedBack(3.0),TargetSteerAngleSpeed(0.0),
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
