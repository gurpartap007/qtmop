#ifndef PIS_STRUCTS_H
#define PIS_STRUCTS_H
#include "qt_headers.h"
#include "PIS_global.h"
#define	DIG_STN_CODE						(uinteger)6
#define	DIG_MAX_ROUTE_NUM_LEN				(uinteger)8
#define	DIG_MAX_PATH_DESC_LEN				(uinteger)96
#define	DIG_MAX_PATH_CODE_LEN				(uinteger)6
#define	MAX_DEV_CODE_LEN                    (uinteger)6
#define	MAX_DEV_DESC_LEN                    (uinteger)96
#define MAX_DEVICES_IN_SYSTEM               (uinteger)20
#define	DIG_BUS_NAME						(uinteger)48
#define	DIG_STN_NAME						(uinteger)96
#define DIG_STN_TYPE                        (uinteger)20
#define	MAX_STNS_PER_BUS    				(uinteger)96
#define	STX_STR								"STX"
#define	ETX_STR								"ETX"
#define	L_STX								(uinteger)(sizeof(STX_STR)-1)
#define	L_FR_LEN							(uinteger)5
#define	L_DEV_ID							(uinteger)5
#define	L_DEV_PORT							(uinteger)2
#define	L_FUNC_CODE							(uinteger)3
#define	L_DATA								(uinteger)900
#define	L_DATA_BIG							(uinteger)(9*1024)
#define	L_CRC								(uinteger)7
#define	L_ETX								(uinteger)(sizeof(ETX_STR)-1)
#define	L_FRAME_INIT						(uinteger)(L_STX+L_FR_LEN+L_SRC_ID+L_DEST_ID+L_FUNC_CODE)
#define	L_FRAME_LEN(DATA)					(uinteger)(L_STX+L_FR_LEN+L_SRC_ID+L_DEST_ID+L_FUNC_CODE+DATA+L_CRC+L_ETX)
#define	L_DATA_LEN(FRAME)					(uinteger)(FRAME-L_STX-L_FR_LEN-L_SRC_ID-L_DEST_ID-L_FUNC_CODE-L_CRC-L_ETX)
#define TOTAL_NO_OF_SECTION                 6
#define TOTAL_NO_OF_PAGES                   10

#define	KNOTS_TO_KMS_FACTOR					(float)1.852
#define MAX_RETRY_COUNT                     1
//#######################################################################################
//				 DATABASE RELATED STRUCTURES
//#######################################################################################
struct path_header_struct
{
     char Route[DIG_MAX_ROUTE_NUM_LEN];
     char LinkRoute[DIG_MAX_ROUTE_NUM_LEN];
     char Description[4][DIG_MAX_PATH_DESC_LEN];
     char Code[DIG_MAX_PATH_CODE_LEN];
     char Source_Stop[DIG_STN_CODE];
     char Source_station_name[4][DIG_STN_NAME];
     char Via_stop[DIG_STN_CODE];
     char VIA_station_name[4][DIG_STN_NAME];
     char Destination_Stop[DIG_STN_CODE];
     char Destination_station_name[4][DIG_STN_NAME];
     char welcome_message[4][100];
     char to[4][10];
     char via[4][10];
     char comma[4][10];
     unsigned char no_of_stns;
     float distance;
     struct time_struct
     {
         ubyte hrs;
         ubyte min;
     }time;
};

union events_defined_union
{
    struct
    {
        uinteger route_selection:1;
        uinteger journey_start:1;
        uinteger door_open:1;
        uinteger door_close:1;
        uinteger emergency:1;
        uinteger engineboot:1;
        uinteger stoparrival:1;
        uinteger stopapproaching:1;
        uinteger stopdeparture:1;
        uinteger journeyend:1;
        uinteger extras:6;
    }bits;
    uinteger flags;
};

struct stop_info_struct
{
    char Code[DIG_STN_CODE];
    char station_name[5][DIG_STN_NAME];
    char station_type[DIG_STN_TYPE];
    int reference;
    float latit;
    float longit;
    float heading_info;
    float heading_tolerance;
    float position_tolerance_lat;
    float position_tolerance_long;
    float distance_tolerance;
    float distance_frm_src;
    uinteger entry_peri;
    uinteger exit_peri;
    uinteger arrival_day;
    uinteger regional_lngugage;
    uinteger approaching_peri;
    float gps_distance_from_curr_loc;
    float gps_distance_from_prev_loc;
    float distance_from_curr_loc;
    float distance_from_prev_loc;
    union events_defined_union events;
    uinteger included_in_via_list;
    struct time_struct
    {
        unsigned char hrs;
        unsigned char min;
    }arrival_time;
};
#define	STOP_INFO_STRUCT						sizeof(struct stop_info_struct)

union stop_info_union
{
    struct stop_info_struct info;
    unsigned char bytes[STOP_INFO_STRUCT];
};
#define	STOP_INFO_UNION							sizeof(union stop_info_union)

//#######################################################################################
//				ROUTE RELATED STRUCTURES
//#######################################################################################
union route_status_union
{
    struct
    {
        unsigned inside_peri:1;
        unsigned outside_peri:1;
        unsigned approaching_peri:1;
        unsigned station_arrival:1;
        unsigned station_departure:1;
        unsigned station_approaching:1;
        unsigned new_gps_data:1;
        unsigned route_info_avail:1;
        unsigned bus_tracked:1;
        unsigned dist_processed:1;
        unsigned outage_rec:1;
        unsigned right_angle:1;
    }bits;
    uword word;
};
struct route_params
{
    struct time_struct
    {
        unsigned char hrs;
        unsigned char min;
         unsigned char sec;
    }start_time;
    struct date_struct
    {
        unsigned char day;
        unsigned char mon;
         unsigned char yrs;
    }start_date;
    ubyte audio;
    QString event;
    QString late_run;
    ubyte alarm;
    double kilometrage;
    QString fault;
};
struct PIS_VIEWSHARED_EXPORT path_struct
{
    sinteger Curr_stop;
    sinteger Next_stop;
    sinteger Prev_stop;
    struct path_header_struct Header;
    union stop_info_union Stops[MAX_STNS_PER_BUS];
    union route_status_union status;
    struct route_params params;
};
extern struct path_struct route_path;

#endif // PIS_STRUCTS_H
