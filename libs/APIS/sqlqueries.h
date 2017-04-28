#ifndef SQLQUERIES_H
#define SQLQUERIES_H
//#include "qt_headers.h"
typedef enum
{
    ROUTE_CODE,
    PATH_CODE,
    JOURNEY_TIME,
    JOURNEY_DISTANCE,
    DEPARTURE_TIME,
    ARRIVAL_TIME,
    TRAIN_NAME_ENG,
    TRAIN_NAME_HIN,
    TRAIN_NAME_REG1,
    TRAIN_NAME_REG2,
    TRAIN_REG_LANG1,
    TRAIN_REG_LANG2,
    STOP_CODE,
    STOP_NAME_ENG,
    STOP_NAME_HIN,
    STOP_NAME_REG1,
    STOP_NAME_REG2,
    STOP_NAME_REG3,
    LAT,
    LONG,
    DISTANCE_FROM_SOURCE,
    JOURNEY_TIME_NXT_STN,
    STN_LEN,
    ENTRY_PERI,
    EXIT_PERI,
    STN_ARRIVAL_TIME,
    STN_HALT_TIME,
    STN_ARRIVAL_DAY,
    PLATFORM,
    REGIONAL_LANG,
    INCLUDED_IN_VIA,
    DB_VERSION
}path_route_table;


typedef enum
{
    STOP_FULL_NAME = 0,
    STP_CODE,
    STOP_REF,
    STOP_DESC,
    LATIT,
    LONGIT,
    HEADING_INFO,
    HEADING_TOL,
    POSITION_TOL,
    DISTANCE_TOL,
    APPR_PERI,
    ENT_PERI,
    EXT_PERI,
    STOP_TYPE
}Stop_Master_Table;

typedef enum
{
    ROUTE_NUMBER,
    PATH_CODE_DISP_TABLE,
    STOP_CODE_DISP_TABLE,
    DEVICE_CODE,
    MESSAGE_CODE,
    PAGE_NUMBER,
    REPEAT_COUNT,
    PAGE_DURATION,
    SECTION_NUMBER,
    X1_COORDINATE,
    X2_COORDINATE,
    Y1_COORDINATE,
    Y2_COORDINATE,
    DISPLAY_MODE,
    SCROLL_RATE,
    SCROLL_DIRECTION,
    FLASHING_MODE,
    FLASH_RATE,
    FONT_ID,
    TEXT,
    TAGS,
    BITMAP_LENGTH,
    BITMAP
}Display_device_table;
typedef enum
{
    ROUTE_SELECTED = 99,

}pis_events;

#define DISPLAY_TYPE    "Display"
#define AAU_TYPE        "AAU"

#define DESTINATION_STOPS_LIST "select * from stop_master_table where stop_type = 'Destination'"

//#define GET_DATA_FROM_STOP_MASTER_TABLE(z) "select *from stop_master_table where stop_code = '" + z + "'"
//#define GET_PATH_CODE_DATA_FROM_PATH_ROUTE_TABLE_FOR_ROUTE(a,b) "select * from path_route_table where Path_code = '" + QString(a) + "'and Route = '" + QString(b) +"' ORDER BY CONVERT(`Distnace_from_source`, UNSIGNED INTEGER) ASC"
//#define GET_PATH_CODE_DATA_FROM_PATH_ROUTE_TABLE(z) "select * from path_route_table where Path_code = '" + z + "'"
//#define GET_DEVICES_AND_MCODE_FOR_MTRIGGER_FOR_STOP(a,b,c,d) "select `Device_code` , `Message_code` from message_configuration_table where Route = '" + QString(a) + "' and Path_code = '" + QString(b) + "'and Stop_code = '" + QString(c) + "'and Message_trigger = '" + QString(d) + "'"
//#define GET_DEVICE_MASTER_TABLE_DEVICE_TYPE(a) "SELECT `device_type` FROM `device_master_table` WHERE `device_code`= '" + a + "'"
//#define GET_MESSAGE_FROM_DISPLAY_TYPE_TABLE(a,b,c,d,e) "select * from `Display_device_type_table` where `Route` = '" + QString(a) + "' and `Path_code` = '" + QString(b) + "'and `Stop_code` = '" + QString(c) + "'and `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Section_number` ASC "
//#define GET_DATA_FROM_DISPLAY_TYPE_TABLE(d,e) "select * from `Display_device_type_table` where `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Section_number` ASC "
//#define GET_MESSAGE_FROM_AAU_TABLE(a,b,c,d,e) "select * from `Annuciation_device_type_table` where `Route` = '" + QString(a) + "' and `Path_code` = '" + QString(b) + "'and `Stop_code` = '" + QString(c) + "' and `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Segment_sequence` ASC "
//#define GET_PRE_RECORDED_MSGS   "select `Device_code` , `Message_code` from  message_configuration_table where `Message_trigger` = 'Manually'"

#define GET_DATA_FROM_STOP_MASTER_TABLE(z) "select *from tbl_StationName where stn_Code = '" + z + "' and reg_Language = 'English'"
#define GET_PATH_CODE_DATA_FROM_PATH_ROUTE_TABLE_FOR_ROUTE(a,b) "select * from tbl_pis_route where `train_number` = '" + QString(a) + "' ORDER BY CONVERT(`distance_source`, UNSIGNED INTEGER) ASC"
#define GET_PATH_CODE_DATA_FROM_PATH_ROUTE_TABLE(z) "select * from path_route_table where Path_code = '" + z + "'"
#define GET_DEVICES_AND_MCODE_FOR_MTRIGGER_FOR_STOP(a,b,c,d) "select `Device_code` , `Message_code` from message_configuration_table where Route = '" + QString(a) + "' and Path_code = '" + QString(b) + "'and Stop_code = '" + QString(c) + "'and Message_trigger = '" + QString(d) + "'"
#define GET_DEVICE_MASTER_TABLE_DEVICE_TYPE(a) "SELECT `device_type` FROM `device_master_table` WHERE `device_code`= '" + a + "'"
#define GET_MESSAGE_FROM_DISPLAY_TYPE_TABLE(a,b,c,d,e) "select * from `Display_device_type_table` where `Route` = '" + QString(a) + "' and `Path_code` = '" + QString(b) + "'and `Stop_code` = '" + QString(c) + "'and `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Section_number` ASC "
#define GET_DATA_FROM_DISPLAY_TYPE_TABLE(d,e) "select * from `Display_device_type_table` where `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Section_number` ASC "
#define GET_MESSAGE_FROM_AAU_TABLE(a,b,c,d,e) "select * from `Annuciation_device_type_table` where `Route` = '" + QString(a) + "' and `Path_code` = '" + QString(b) + "'and `Stop_code` = '" + QString(c) + "' and `Message_code` = '" + d + "' and `Device_code` = '" + e + "' order by `Page` ASC , `Segment_sequence` ASC "
#define GET_PRE_RECORDED_MSGS   "select `Device_code` , `Message_code` from  message_configuration_table where `Message_trigger` = 'Manually'"


#define PATH_MASTER_TABLE "tbl_TrainMaster"
#define PIS_DB_ROUTE_NUM_INDEX          0
#define PIS_DB_TRAIN_NAME_INDEX         10
#define PIS_DB_SRC_STN_INDEX            2
#define PIS_DB_DEST_STN_INDEX           3
#define PIS_DB_TOTAL_DISTANCE_INDEX     6






#define CREATE_BUS_PIS_LOG "CREATE DATABASE IF NOT EXISTS BUS_PIS_LOG;"
#define CREATE_BUS_PIS_LOG_SERVER "CREATE DATABASE BUS_PIS_LOG;"



#define CREATE_TABLE       "CREATE TABLE IF NOT EXISTS log(\
Id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,BusNo VARCHAR(20),\
DriverID VARCHAR(20), Route VARCHAR(10),RouteDBVersion VARCHAR(20),\
SourceStop VARCHAR(30), DestinationStop VARCHAR(30),\
DepartureTime VARCHAR(20), ArrivalTime VARCHAR(20),\
NextStop VARCHAR(30),CurrentTime VARCHAR(30),\
CurrentLatitude VARCHAR(20), CurrentLongitude VARCHAR(20),\
CurrentSpeed VARCHAR(10), Input_1 VARCHAR(1), Input_2 VARCHAR(1),\
Input_3 VARCHAR(1), Input_4 VARCHAR(1),Output_1 VARCHAR(1), Output_2 VARCHAR(1),\
Slave_1 VARCHAR(30), Slave_2 VARCHAR(30), Slave_3 VARCHAR(30),\
Slave_4 VARCHAR(30), Slave_5 VARCHAR(30), Slave_6 VARCHAR(30),\
Slave_7 VARCHAR(30), Slave_8 VARCHAR(30), Slave_9 VARCHAR(30),\
Slave_10 VARCHAR(30), Event VARCHAR(30));"

#define CREATE_SERVER_TABLE       "CREATE TABLE log(\
Id INT IDENTITY,BusNo VARCHAR(20),\
DriverID VARCHAR(20), Route VARCHAR(10),RouteDBVersion VARCHAR(20),\
SourceStop VARCHAR(30), DestinationStop VARCHAR(30),\
DepartureTime VARCHAR(20), ArrivalTime VARCHAR(20),\
NextStop VARCHAR(30),CurrentTime VARCHAR(30),\
CurrentLatitude VARCHAR(20), CurrentLongitude VARCHAR(20),\
CurrentSpeed VARCHAR(10), Input_1 VARCHAR(1), Input_2 VARCHAR(1),\
Input_3 VARCHAR(1), Input_4 VARCHAR(1),Output_1 VARCHAR(1), Output_2 VARCHAR(1),\
Slave_1 VARCHAR(30), Slave_2 VARCHAR(30), Slave_3 VARCHAR(30),\
Slave_4 VARCHAR(30), Slave_5 VARCHAR(30), Slave_6 VARCHAR(30),\
Slave_7 VARCHAR(30), Slave_8 VARCHAR(30), Slave_9 VARCHAR(30),\
Slave_10 VARCHAR(30), Event VARCHAR(30));"

#endif // SQLQUERIES_H

