
#ifndef __ELEC_H__
#define __ELEC_H__

// 0.1s/1h = 0.1s/3600s
#define ELEC_TIME (0.1f / 3600)

struct elec_calc_t {
    float mah;
    float mwh;
    float time;
    unsigned char status;
};

extern struct elec_calc_t elec;

extern void set_elec_status(unsigned char status);
extern unsigned char get_elec_status();
extern float get_elec_calc_mah();
extern float get_elec_calc_mwh();
extern float get_elec_calc_time();
extern void elec_calc_clear();
extern void elec_calc_hanlder(float current, float power);

#endif
