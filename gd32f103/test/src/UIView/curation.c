
#include "curation.h"

const unsigned char * unit_list[][UNIT_MAX] = {
    {"mV",   "V"},
    {"mA",   "A"},
    {"mW",   "W"},
    {"mAh", "Ah"},
    {"mWh", "Wh"},
};

const unsigned char * fmt_list[] = {
    "%5.3f", /* Example:1.000 */
    "%5.2f", /* Example:10.00 */
    "%5.1f", /* Example:100.0 */
    "%5.0f", /* Example:1000. */
};

struct data_curation_t curation;

void data_curation_handler(float origin_data, unsigned char curation_type)
{
    float last_data = origin_data;

    memset(curation.value_buf, '\0', 10);
    memset(curation.unint_buf, '\0', 4);
    curation.unit_id = 0;

    while (last_data >= 1000.0) {
        last_data = (float)(last_data / 1000.0);
        curation.unit_id++;
    }

    if ((last_data >= 0.0) && (last_data < 10.0)) {
        snprintf(
            curation.value_buf, 
            10, 
            fmt_list[0], 
            last_data
        );
    } else if ((last_data >= 10.0) && (last_data < 100.0)) {
        snprintf(
            curation.value_buf, 
            10, 
            fmt_list[1], 
            last_data
        );
    } else if ((last_data >= 100.0) && (last_data < 1000.0)) {
        snprintf(
            curation.value_buf, 
            10, 
            fmt_list[2], 
            last_data
        );
    } else if ((last_data >= 1000.0) && (last_data < 10000.0)) {
        snprintf(
            curation.value_buf, 
            10, 
            fmt_list[3], 
            last_data
        );
    }

    snprintf(
        curation.unint_buf, 
        4, 
        "%s", 
        unit_list[curation_type][curation.unit_id]
    );
}
