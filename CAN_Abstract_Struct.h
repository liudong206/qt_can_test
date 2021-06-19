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
#ifndef CAN_ABSTRACT_STRUCT_H
#define CAN_ABSTRACT_STRUCT_H

typedef double             UNIF_VAR_T;
typedef unsigned char      uint8_t;     //无符号8位数
typedef signed   char      int8_t;      //有符号8位数
typedef unsigned short int uint16_t;    //无符号16位数
typedef signed   short int int16_t;     //有符号16位数
typedef unsigned int       uint32_t;    //无符号32位数
typedef signed   int       int32_t;     //有符号32位数
typedef unsigned long int  uint64_t;    //无符号64位数
typedef signed   long int  int64_t;     //有符号64位数
typedef float              float32;     //单精度浮点数
typedef double             float64;     //双精度浮点数


#define MRRMODE 0
#define SRRMODE 1
#define VEHMODE 2

#define INTELMODE 0
#define MOTORMODE 1

#define BITLOC(m, n) {m, n}
#define VdstLOC(type,n) (uint64_t)(&(((type *)((void*)(0)))->n))

#define DATA2UINT64(m) ((uint64_t)(m[0]))+(((uint64_t)(m[1]))<<8)+(((uint64_t)(m[2]))<<16)+(((uint64_t)(m[3]))<<24)+(((uint64_t)(m[4]))<<32)+(((uint64_t)(m[5]))<<40)+(((uint64_t)(m[6]))<<48)+(((uint64_t)(m[7]))<<56)
#define BITREVERSE(var) (((var&0x01)<<7)+((var&0x02)<<5)+((var&0x04)<<3)+((var&0x08)<<1)+((var&0x10)>>1)+((var&0x20)>>3)+((var&0x40)>>5)+((var&0x80)>>7))

#define DCAST(m,index) (((uint64_t)m[index])<<(index*8))
#define RDCAST(m,index) (((uint64_t)BITREVERSE(m[index]))<<(index*8))

#define INTELCAST(m) DCAST(m,0)+DCAST(m,1)+DCAST(m,2)+DCAST(m,3)+DCAST(m,4)+DCAST(m,5)+DCAST(m,6)+DCAST(m,7)
#define MOTORCAST(m) RDCAST(m,0)+RDCAST(m,1)+RDCAST(m,2)+RDCAST(m,3)+RDCAST(m,4)+RDCAST(m,5)+RDCAST(m,6)+RDCAST(m,7)

#define SCAST(m,d) m[0] = (uint8_t)(d&0x00000000000000FF);\
m[1] = (uint8_t)((d&0x000000000000FF00)>>8);              \
m[2] = (uint8_t)((d&0x0000000000FF0000)>>16);             \
m[3] = (uint8_t)((d&0x00000000FF000000)>>24);             \
m[4] = (uint8_t)((d&0x000000FF00000000)>>32);             \
m[5] = (uint8_t)((d&0x0000FF0000000000)>>40);             \
m[6] = (uint8_t)((d&0x00FF000000000000)>>48);             \
m[7] = (uint8_t)((d&0xFF00000000000000)>>56);             \

#define RSCAST(m,d) m[0] = BITREVERSE((uint8_t)(d&0x00000000000000FF));\
m[1] = BITREVERSE((uint8_t)((d&0x000000000000FF00)>>8));              \
m[2] = BITREVERSE((uint8_t)((d&0x0000000000FF0000)>>16));             \
m[3] = BITREVERSE((uint8_t)((d&0x00000000FF000000)>>24));             \
m[4] = BITREVERSE((uint8_t)((d&0x000000FF00000000)>>32));             \
m[5] = BITREVERSE((uint8_t)((d&0x0000FF0000000000)>>40));             \
m[6] = BITREVERSE((uint8_t)((d&0x00FF000000000000)>>48));             \
m[7] = BITREVERSE((uint8_t)((d&0xFF00000000000000)>>56));             \

#define INTELPACK(m,d) SCAST(m,d)
#define MOTORPACK(m,d) RSCAST(m,d)

#define LSHIFTBIT(m,n) (8*(m-1)+n)
#define RSHIFTBIT(m,n) (64-(8*(m-1)+n+1))
#define DPICK(osd,isd,oed,ied) ((((0xFFFFFFFFFFFFFFFF>>(LSHIFTBIT(osd,isd)))<<(LSHIFTBIT(osd,isd)))<<RSHIFTBIT(oed,ied))>>RSHIFTBIT(oed,ied))
#define DPACK(data,osd,isd) (data<<(LSHIFTBIT(osd,isd)))

#define CHECKSUM_DPACK(data,isd) (data<<isd)/*liudong*/

typedef struct _BIT_LOC_T
{
    uint8_t outloc;
    uint8_t insloc;
} bit_loc_t;

typedef struct _TABLE_T
{
    bit_loc_t Bit_start;
    bit_loc_t Bit_end;
    uint8_t Length;
    float alpa;
    float beta;
    uint64_t vloc;
} table_info_t;

#endif
