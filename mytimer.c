
#include <stdio.h>
#include <assert.h>
#include <bcc/bcc.h>
#include <drv/timer.h>


static volatile uint32_t cnt;
void myhandler(void *arg, int source)
{
    cnt++;    
    printf("Elapsed time: %d\n",cnt);
}

int mytimer_init(int tnum)
{
    struct timer_priv *tdev;
    struct timer_priv *tsubdev;
    int busintline = 0;
    int irqintnum = 0;
    
    tdev = timer_open(tnum);
    assert(tdev);
    busintline = timer_get_devreg(tnum)->interrupt;
    irqintnum = bcc_int_map_get(busintline);
    if(irqintnum == -1)
    {
        irqintnum = busintline;
    }

    timer_set_scaler_reload(tdev, 0xff);
    timer_set_scaler(tdev, 0xff);

    tsubdev = timer_sub_open(tdev, 1);
    assert(tsubdev);
    timer_set_ctrl(tsubdev, 0);
    timer_set_reload(tsubdev, 1000);

    return irqintnum;

}
int main(void)
{
    int intnum = 0;
    int tnum = 0;
    void *isr;

    timer_autoinit();
    intnum = mytimer_init(tnum);
    if(intnum < 0)
    {
        printf("It failed to intialize a timer\n");
        return BCC_FAIL;
        
    }
    cnt = 0;
    isr = bcc_isr_register(intnum, myhandler, NULL);   
    assert(isr);
    
    bcc_int_unmask(intnum);

    return BCC_OK;
}