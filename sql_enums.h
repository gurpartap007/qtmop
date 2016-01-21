#ifndef SQL_ENUMS_H
#define SQL_ENUMS_H
namespace  Annuciation_device_type_table
{
enum
{
    Route,
    Path_code,
    Stop_code,
    Device_code,
    Message_code,
    Page,
    Page_duration,synchronization_device,
    Segment_data,
    Segment_sequence

};
}
namespace path_master_table
{
enum
{
    Route,
    Path,
    Path_description,
    Path_code,
    Source_stop_code,
    Destination_stop_code,
    Total_Distance
};


}
enum
{
  SOURCE_NAME,
  DESTINATION_NAME
};
namespace TRAINS_SELECTION {
enum
{
TRAIN_NO,
TRAIN_NAME
};
}
namespace TABLE_TRAIN_NUMBER
{
enum
{
    TRAIN_NO,
    TRAIN_NAME_ENG=11
};
}
#endif // SQL_ENUMS_H

