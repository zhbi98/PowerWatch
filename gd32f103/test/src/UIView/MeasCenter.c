
#include "MeasCenter.h"

float avgsum = 0.0;
float avgv = 0.0;
char  avgt = 1;
float mAh = 0.0;
float mWh = 0.0;
char  t = 0;
lv_timer_t * updataTimer = NULL;

void measCenterUpdate()
{
    unsigned char buf[10];

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", ina226_data.voltageVal / 1000);
    lv_label_set_text_fmt(MeasSence.mainShow.lableValue1, "%s", buf);

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", avgv);
    lv_label_set_text_fmt(MeasSence.mainShow.lableValue2, "%s", buf);

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", ina226_data.Shunt_Current);
    lv_label_set_text_fmt(MeasSence.sidebar.labelValue1, "%s", buf);

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", ina226_data.Power);
    lv_label_set_text_fmt(MeasSence.sidebar.labelValue2, "%s", buf);

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", mAh);
    lv_label_set_text_fmt(MeasSence.sidebar.labelValue3, "%s", buf);

    memset(buf, '\0', 10);
    sprintf(buf, "%05.2f", mWh);
    lv_label_set_text_fmt(MeasSence.sidebar.labelValue4, "%s", buf);
}

void timerUpdateCreate()
{
	if (updataTimer == NULL) {
        updataTimer = lv_timer_create(measCenterUpdate, 1000, NULL);
    }
}
