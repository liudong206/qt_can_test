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

#ifndef BUS_QEV_ACT_H
#define BUS_QEV_ACT_H
#include <math.h>
/*临时关闭*/
//#include <ros/ros.h>
#include <array>
#include <string>
#include <map>
#include <inttypes.h>
#include <thread>
#include <string.h>
#include <stdio.h>
#include <termios.h> //操作终端
#include <unistd.h>
#include <assert.h>

#include "veh_can_table.h"
#include "CAN_Abstract_Struct.h"


const unsigned int CAN_NUM = 12;

namespace vehicle
{
namespace qev
{
class vehicle_acticvity
{
public:
    vehicle_acticvity(){}
    ~vehicle_acticvity(){}
    //std::unique_ptr<std::thread> VehicleProcess;
    Veh_Info VehicleData;
	int index = 0;

	void CAN_Data_Assignment(Veh_Sub_Info &ECUTempDate);
    /*****************************************************************************
     函 数 名  :  PackageMehodCanData
     功能描述  : 拼接下发MCU的CAN包，vector中包含40帧
                              需基于业务需求自行实现
     输入参数  : CanBusDataParam& canData
     返 回 值  : 无
     修改历史  : NA
    *****************************************************************************/
    void PackageMethodCanData(CanBusDataParam &canDataParm);
    uint8_t alivecounter;
    uint8_t can_3A3_date[8];
    uint8_t can_32E_date[8];
    // Event组包
    CanBusDataParam canDataParm;
    Veh_Sub_Info ECUTempDate;
    void VehicleParsingFunc(uint64_t InstanceId);


private:
    int m_channelId;
    // instance ID
    int m_instance;

	int count = 0;

    string ActName;

    void VehicleRosPublish();
    // Event下发组包
    void CAN_Data_Package_Func(void* srcdata,CanBusDataParam &canDataParm, std::map<uint32_t,vector<table_info_t>> table, uint8_t mode, uint8_t seq);   
    void AutoDrivingMsg3CheckSum(vector<uint8_t> &data);
    void CAN_Data_Abstract_Func(vector<uint8_t>& srcdata, void* dstdata, std::map<uint32_t,vector<table_info_t>> table, uint8_t mode, uint32_t CANId);
};

}
} // namespace vehicle
extern void *key_control_fun(void* args);
extern int key_control_fun_(vehicle::qev::Veh_Sub_Info *ECUTempDate);
extern int getch();
#endif
