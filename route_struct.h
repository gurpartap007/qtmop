#ifndef ROUTE_STRUCT_H
#define ROUTE_STRUCT_H
#define DIG_STN_NAME 32
#define DIG_STN_CODE 6
#define DIG_TRAIN_NUM 6
typedef enum
{
    ARRIVAL,
    DEPARTURE,
    APPROACHING
}ROUTE_STATES;
struct station_name_struct
{
    unsigned char eng[DIG_STN_NAME];
    unsigned char hin[DIG_STN_NAME];
    unsigned char reg1[DIG_STN_NAME];
};

union station_name_union
{
    struct station_name_struct name;
    unsigned char names[3][DIG_STN_NAME];
};


typedef struct gps_position
{
    struct coordinate_struct
    {
        float latitude;
        float longitude;
    }coordintes;
    float distance;
}GPS_POS;

union route_status_flags
{
    struct route_flags
    {
        bool position_identified;
        bool distance_processed;
        bool inside_peri;
        bool outside_peri;
        bool right_angle;
        bool welcome_message_generated;
        bool trip_formatted;
    }bits;
};

struct status_struct
{
    union route_status_flags flags;
    unsigned char next_halting_stn;
    unsigned char next_stn;
    float prev_dist;
    unsigned long distance_to_next_halt;
    unsigned char state;
    unsigned char distance[6];
};

union status_bits
       {
    struct bits_structure
    {
        bool station_dep_generated;
        bool station_arr_generated;
        bool station_appr_generated;
        bool station_dep_generate;
        bool station_arr_generate;
        bool station_appr_generate;
        bool station_skipped;
    }bits;
    unsigned char flags;
};
struct train_struct
{

    unsigned char train_num[DIG_TRAIN_NUM];
    union station_name_union src;
    union station_name_union des;
    union station_name_union mid;
     union station_name_union current_station;
    unsigned int journ_dist;
    unsigned int journ_time;
    unsigned char src_stn_code[DIG_STN_CODE];
    unsigned char mid_stn_code[DIG_STN_CODE];
    unsigned char des_stn_code[DIG_STN_CODE];
    unsigned char no_of_stns;
    unsigned char dep_time_hrs;
    unsigned char dep_time_min;
    unsigned char arr_time_hrs;
    unsigned char arr_time_min;
    unsigned char reg_lang1_code;
    unsigned char coach_count;
    unsigned char slow_fast;
};
struct stn_info_struct
{
    GPS_POS loc; // latitude longitude
    unsigned long distance_from_previous_station;
    unsigned int arrival_peri; // arrival periphery
    unsigned int departure_peri; //departure periphery
    unsigned int approaching_peri; //approaching periphery
    unsigned int track_distance_from_curr_pt;
    unsigned int stn_id;
    unsigned char stn_code[DIG_STN_CODE];
    unsigned char wait_time;
    struct bits_struct
    {
        bool fast_train;
        bool pf_left;
        bool appr;
        bool arr;
        bool dep;
    }bits;
    union status_bits status;
};
typedef struct route_struct
{
    struct stn_info_struct stn[96];
    struct train_struct train;
    struct status_struct status;
}route;





#endif // ROUTE_STRUCT_H

