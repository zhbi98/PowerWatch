
#include "wdog.h"

void wdog_init(void)
{
    // enable IRC40K
    rcu_osci_on(RCU_IRC40K);
    // wait till IRC40K is ready
    while (rcu_osci_stab_wait(RCU_IRC40K) != SUCCESS) {

    }
    // confiure FWDGT counter clock: 40KHz(IRC40K) / 128 = 0.3125 KHz
    fwdgt_config(2 * 500 * 3, FWDGT_PSC_DIV128);    //12λ
    // After 9.6 seconds to generate a reset
    fwdgt_enable();
}
