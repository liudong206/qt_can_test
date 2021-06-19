#include <iostream>
#include "BUS_QEV_Act.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

namespace vehicle
{
namespace qev
{
void vehicle_acticvity::VehicleParsingFunc(uint64_t InstanceId)
{
    struct timeval ctime;
    CAN_Data_Assignment(ECUTempDate);
#if 1
    thread t(key_control_fun_,&ECUTempDate);
    t.detach();
#endif
    while(true)
    {
        int i = 0;
        usleep(20000);
    	//usleep(200);
        gettimeofday(&ctime, NULL);
        vector<CanBusDataParam> VehSample;
        VehSample.push_back(canDataParm);
        if(0 == VehSample.size())
        {
//            VehicleProxy->CanDataRxEvent.Cleanup();
            //continue;
        }
        for(auto Sample : VehSample)
        {
            VehicleData.seq = Sample.seq;
            VehicleData.timeStamp.second = ctime.tv_sec;
            VehicleData.timeStamp.nsecond = ctime.tv_usec;
            for(auto Elem : Sample.elementList)
            {
                printf("Elem.canId %X\n",Elem.canId);
                if(Veh_UP_MESSAGE_TAB.find(Elem.canId) == Veh_UP_MESSAGE_TAB.end())
                {
                    continue;
                }
                printf("Elem.data %d %d %d %d %d %d %d %d\n",Elem.data[0],Elem.data[1],Elem.data[2],Elem.data[3],Elem.data[4],Elem.data[5],Elem.data[6],Elem.data[7]);
                CAN_Data_Abstract_Func(Elem.data,&(VehicleData.VehInfo),Veh_UP_MESSAGE_TAB,INTELMODE,Elem.canId);
            }

        }
    #if 1
        CAN_Data_Package_Func(&ECUTempDate,canDataParm, vehicle::qev::Veh_DOWN_MESSAGE_TAB, INTELMODE, 1);
    #endif
        printf("!!!!!!!!!!!!!!!!!!VehicleData.VehInfo.DrivingModeFeedBack: %f\n",VehicleData.VehInfo.DrivingModeFeedBack);
        printf("!!!!!!!!!!!!!!!!!!VehicleData.VehInfo.TargetAccelerated: %f\n",VehicleData.VehInfo.TargetAccelerated);
        printf("!!!!!!!!!!!!!!!!!!VehicleData.VehInfo.TargetSteerAngle: %f\n",VehicleData.VehInfo.TargetSteerAngle);

    }
}


void vehicle_acticvity::CAN_Data_Assignment(Veh_Sub_Info &ECUTempDate)
{
#if 1
    int drivingstatus = 1;
	/*临时关闭*/
    if(1 == drivingstatus)
    {
        ECUTempDate.AutomaticDriveControlStatus = 0;
        ECUTempDate.DrivingModeReg = 0x0;
        ECUTempDate.DrivingModeFeedBack = 0x2;
        ECUTempDate.TargetAccelerated = 0x0;
        ECUTempDate.TargetSteerAngle = 0x0;
		count ++;
		if(count > 15) count = 0;
        ECUTempDate.RollingCount_32E = count;  //OX32E
        std::cout << "################################ drivingstatus = 111111111111111########################################" << std::endl;
    }
#endif

}


void vehicle_acticvity::CAN_Data_Package_Func(void* srcdata,CanBusDataParam &canDataParm, std::map<uint32_t,vector<table_info_t>> table, uint8_t mode, uint8_t seq)
{
    uint8_t i,j = 0;
    i = 0;
    struct timeval ctime;
    vector<uint8_t> Tempdata;
    uint64_t tempdata = 0;
    uint64_t tempdata_test = 0;
    uint64_t Sum = 0;
    uint64_t checksum = 0;
    gettimeofday(&ctime, NULL);
    canDataParm.seq = seq;
    canDataParm.elementList.resize(table.size());
    Tempdata.resize(8);
    for(auto tab : table)
    {
        Sum = 0;
        tempdata = 0;
        //checksum = 0;//liudong
        canDataParm.elementList[i].canId = tab.first;
        canDataParm.elementList[i].validLen = 8;
        canDataParm.elementList[i].timeStamp.second = ctime.tv_sec;
        canDataParm.elementList[i].timeStamp.nsecond = ctime.tv_usec;
        vector<table_info_t> stab;
        stab = tab.second ;
        if(stab.size() > 0)
        {
			for(int j = 0; j < stab.size(); j++)
			{
				::table_info_t t;
				t.Bit_end.insloc = stab[j].Bit_end.insloc;
				t.Bit_end.outloc = stab[j].Bit_end.outloc;
				t.Bit_start.insloc = stab[j].Bit_start.insloc;
				t.Bit_start.outloc = stab[j].Bit_start.outloc;
				t.Length = stab[j].Length;
				t.alpa = stab[j].alpa;
				t.beta = stab[j].beta;
				t.vloc = stab[j].vloc;
                tempdata = static_cast<uint64_t>((*(UNIF_VAR_T *)(((uint64_t)(srcdata)) + t.vloc) - t.beta)/t.alpa);
                //AutoDrivingMsg3CheckSum(tab.first,tempdata,t.Bit_start.insloc,checksum,j,stab);/*liudong*/
				tempdata = DPACK(tempdata,t.Bit_start.outloc,t.Bit_start.insloc);
                uint8_t tranf = LSHIFTBIT(t.Bit_start.outloc,t.Bit_start.insloc);
                Sum += tempdata;
			}
	        if(!mode)
	        {
	            INTELPACK(Tempdata,Sum);
	        }
	        if(mode)
	        {
	            MOTORPACK(Tempdata,Sum);
	        }
	        AutoDrivingMsg3CheckSum(Tempdata);
            canDataParm.elementList[i].data = Tempdata;
	        printf("i: %d ,canDataParm->elementList[i].canId: %X \n", i, canDataParm.elementList[i].canId);
	        printf("i: %d ,canDataParm->elementList[i].data: %X %X %X %X %X %X %X %X\n", i, canDataParm.elementList[i].data[0], canDataParm.elementList[i].data[1], canDataParm.elementList[i].data[2],
	        canDataParm.elementList[i].data[3], canDataParm.elementList[i].data[4], canDataParm.elementList[i].data[5], canDataParm.elementList[i].data[6], canDataParm.elementList[i].data[7]);
	        }
        i++;
    }
}
void vehicle_acticvity::AutoDrivingMsg3CheckSum(vector<uint8_t> &data)/*liudong*/
{
   uint32_t checksum = 0;
   for (int i = 0; i < 7; i++){
       checksum += data[i];
   }
   checksum = checksum ^ 0xff;
   data[7] = checksum;
}

void vehicle_acticvity::CAN_Data_Abstract_Func(vector<uint8_t>& srcdata, void* dstdata, std::map<uint32_t,vector<table_info_t>> table, uint8_t mode, uint32_t CANId)
{
    uint64_t CanVar = 0xFFFFFFFFFFFFFFFF;
    uint64_t IntVar = 0xFFFFFFFFFFFFFFFF;
    if((nullptr == dstdata)||(0 == srcdata.size())||(table.find(CANId) == table.end()))
    {
        return;
    }
    CanVar = (!mode) ? (INTELCAST(srcdata)) : (MOTORCAST(srcdata));
   //  printf("CanVar %lld\n",CanVar);
    auto tab = table.find(CANId)->second;
    for (auto t : tab)
    {
        IntVar = (CanVar & ((uint64_t)(DPICK(t.Bit_start.outloc, t.Bit_start.insloc, t.Bit_end.outloc, t.Bit_end.insloc)))) >> LSHIFTBIT(t.Bit_start.outloc, t.Bit_start.insloc);
        *(UNIF_VAR_T *)(((uint64_t)(dstdata)) + t.vloc) = (t.alpa * ((UNIF_VAR_T)(IntVar))) + t.beta;
    }
}


}
} // namespace vehicle

extern void *key_control_fun(void* args)
{
    vehicle::qev::Veh_Sub_Info ecu_tempDate;
    char c = '0';
    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,,please enter key:"<<std::endl;
    while (true) {
        c = getchar();
        if(c == 'w'){
            ecu_tempDate.TargetAccelerated = ecu_tempDate.TargetAccelerated + 0.1;
        }
        else if(c == 's'){
            ecu_tempDate.TargetAccelerated = ecu_tempDate.TargetAccelerated + 0.1;
        }
        else if(c == 'a') {
            ecu_tempDate.TargetSteerAngle = ecu_tempDate.TargetSteerAngle + 10;
        }
        else if(c == 'd'){
            ecu_tempDate.TargetSteerAngle = ecu_tempDate.TargetSteerAngle - 10;
        }
        else {
            printf("key error");
        }
        usleep(20000);
    }

}
extern int key_control_fun_(vehicle::qev::Veh_Sub_Info *ECUTempDate)
{
    //byd::vehicle::qev::Veh_Sub_Info ecu_tempDate;
    int c = 0;
    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<please enter key:"<<std::endl;
    std::cout<<"ecu_tempDate.TargetAccelerated"<<ECUTempDate->TargetAccelerated<<std::endl;
    std::cout<<"ecu_tempDate.TargetSteerAngle"<<ECUTempDate->TargetSteerAngle<<std::endl;
while(1)
{
    std::cout<<"Before enter key"<<std::endl;
    c = getch();
    std::cout<<"After enter key"<<std::endl;
    if(c == 119){
        ECUTempDate->TargetAccelerated = ECUTempDate->TargetAccelerated + 0.1;//w
    }
    else if(c == 115){
        ECUTempDate->TargetAccelerated = ECUTempDate->TargetAccelerated + 0.1;//s
    }
    else if(c == 97) {
        ECUTempDate->TargetSteerAngle = ECUTempDate->TargetSteerAngle + 10;//a
        std::cout<<"ecu_tempDate.TargetSteerAngle"<<ECUTempDate->TargetSteerAngle<<std::endl;
    }
    else if(c == 100){
        ECUTempDate->TargetSteerAngle = ECUTempDate->TargetSteerAngle - 10;//d
    }
    else if(c == 13){
        printf("key enter");
    }
    else {
        printf("key error");
    }
    usleep(20000);

    //break;
}
    return 0;
}
extern int getch()
{
    int c=0;
    struct termios org_opts, new_opts;
    int res=0;
    //保留终端原来设置
    res=tcgetattr(STDIN_FILENO, &org_opts);
    assert(res==0);
    //从新设置终端参数
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c=getchar();
    //恢复中断设置
    res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
    return c;
}
