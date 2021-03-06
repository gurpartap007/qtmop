#ifndef SQL_ENUMS_H
#define SQL_ENUMS_H
typedef unsigned char ubyte;
typedef char sbyte;
typedef	unsigned short uinteger;
typedef	int sinteger;
typedef	unsigned long uword;
typedef	long int sword;
typedef	const unsigned char urombyte;
typedef	const char srombyte;
typedef	const unsigned short uromint;
typedef	const int sromint;
typedef urombyte *const uromptr;
typedef srombyte *const sromptr;
typedef unsigned char *const uramptr;
typedef sbyte *const sramptr;
typedef long double lword;
namespace Time {
enum{
    HOURS,
    MINUTES,
    SECONDS
};
}
namespace  TrainNumber
{
enum
{
    TRAIN_NO,
    SRC_STN_SNO,
    DEST_STN_SNO,
    VIA_STN_SNO,
    RETURN_TRAIN_NO,
    JRNY_DISTANCE,
    ARR_TIME,
    DEP_TIME,
    TOTAL_STATION_ROUTE,
    NO_OF_COACHES,
    SLOW_FAST,
    TRAN_NAME_ENGLISH,
    TRAN_NAME_HINDI,
    TRAN_NAME_REGIONAL,
    TRAN_LANGUAGE,
    RAILWAYS,
    DB_VERSION,
    SDB_VERSION,
    TRAIN_SNO,
    LADIES_TRAIN_STATUS
};
}

namespace Configuration
{
enum
{
    SLAVE,
    LADIES_SPECIAL,
    PLATFORM,
    ANNOUNCEMENT,
    TIME_DISPLAY,
    PASSWORD,
    TRAIN_SPEED,
    HEAD_CODE_SCHEME,
    HEAD_CODE_UPDATE,
    GENERAL_MSG_UPDATE,
    GENERAL_MSG_DISPLAY,
    REGIONAL_LANG_ORDER,
    ICD_DISPLAY,
    COACH_COUNT,
    HANDICAP_COACH1,
    HANDICAP_COACH2,
    WELCOME_REPEAT_COUNT,
    WELCOME_ENABLE,
    WELCOME_TIME,
    WELCOME_VOICE,
    DEPARTURE_REPEAT,
    DEPARTURE_ENABLE,
    DEPARTURE_TIME,
    DEPARTURE_VOICE,
    DEPARTURE_DISTANCE,
    APPROACH_REPEAT,
    APPROACH_ENABLE,
    APPROACH_TIME,
    APPROACH_VOICE,
    APPROACH_DISTANCE,
    ARRIVAL_REPEAT,
    ARRIVAL_ENABLE,
    ARRIVAL_TIME,
    ARRIVAL_VOICE,
    ARRIVAL_DISTANCE,
    FAEWELL_REPEAT,
    FAREWELL_ENABLE,
    FAREWELL_TIME,
    FAREWELL_VOICE,
    ZONE,
    WELCOME_COLOR,
    DEPARTURE_COLOR,
    ARRIVAL_COLOR,
    APPRO_COLOR,
    FAREWELL_COLOR,
    ENABLE_MSG_ID
};
}

namespace StationName
{
enum
{
    STATION_CODE,
    STATION_NAME,
    STN_LANGID,
    EXTRA1,
    EXTRA2,
    EXTRA3,
    EXTRA4,
    EXTRA5,
    EXTRA6,
    DB_VERSION,
    RAILWAYS,
    SDB_VERSION
};
}

namespace StationCode
{
enum
{
    STATION_CODE,
    LATITUDE,
    LONGITUDE,
    STATION_LENGTH,
    LANGUAGE_ID,
    EXTRA1,
    EXTRA2,
    EXTRA3,
    EXTRA4,
    EXTRA5,
    DB_VERSION,
    RAILWAYS,
    SDB_VERSION,
    STN_CODE_SEQ_NUMBER
};
}
namespace  SlaveRoute
{
enum
{
    TRAIN_NUMBER,
    MASTER_ROUTE,
    ARRIVAL_TIME,
    DEPARTURE_TIME,
    RAILWAYS,
    TRAIN_STATUS,
    LADIES_TRN_STATUS,
    DESCRIPTION,
    SERIAL_NUM
};
}

namespace RouteMaster
{
enum
{
    TRAIN_SNO,
    STN_CODE,
    DEP_TRIGGERING,
    ARR_TRIGGERING,
    APP_TRIGGERING,
    ARR_HRS,
    WAIT_TIME,
    SLOW_FAST,
    PLATFORM_DIRECTION,
    DISTANCE_FRM_SOURCE,
    RAILWAYS,
    DB_VERSION,
    SDB_VERSION,
    LADIES_TRAINS_STATUS
};
}

namespace Trip
{
enum
{
    RAILWAYS,
    COACH_NUMBER,
    UNIT_NUMBER,
    DATE,
    TIME,
    TRN_NUMBER,
    ROUTE_NAME,
    STATION_NAME,
    STATION_LAT,
    STATION_LONG,
    AP_TIME,
    AP_DISTANCE,
    AP_SPEED,
    AP_LAT,
    AP_LONG,
    ARR_TIME,
    ARR_DISTANCE,
    ARR_SPEED,
    ARR_LAT,
    ARR_LONG,
    DEP_TIME,
    DEP_DISTANCE,
    DEP_SPEED,
    DEP_LAT,
    DEP_LONG
};
}

#endif // SQL_ENUMS_H

