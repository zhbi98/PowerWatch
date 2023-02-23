
#ifndef __CURATION_H__
#define __CURATION_H__

#define UNIT_MAX 2

enum curation_type {
    FMT_VOLTAGE = 0,
    FMT_CURRENT = 1,
    FMT_POWER   = 2,
    FMT_MAH     = 3,
    FMT_MWH     = 4,
};

struct data_curation_t {
    unsigned char value_buf[10];
    unsigned char unit_buf[4];
    unsigned char unit_id;
};

extern const unsigned char * unit_list[][UNIT_MAX];
extern const unsigned char * fmt_list[];
extern struct data_curation_t curation;

extern void data_curation_handler(float origin_data, unsigned char curation_type);

#endif
