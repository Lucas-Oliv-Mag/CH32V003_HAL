#ifndef PFIC_src
#define PFIC_src


#include <Peripherics/inc/PFIC.h>

#define PFIC_SECURE_MODE_FLAG (unsigned int)0xFFU


void IRQ_enable(IRQ_t IRQ){

    if(IRQ > 38 || IRQ < 0){return;}

    if(IRQ < 32){
     REG_PFIC_IENR1 |= (1<<IRQ);

    }else{
     REG_PFIC_IENR2 |= (1<<(IRQ - 32));
    }
   

}


void IRQ_Disable(IRQ_t IRQ){

    if(IRQ < 32){
     REG_PFIC_IRER1 |= (1<<IRQ);

    }else{
     REG_PFIC_IRER2 |= (1<<(IRQ - 32));
    }

}




void IRQ_SetPriority(IRQ_t IRQn, Priority_t Priority) {

unsigned int* Register_pointer = ((unsigned int*)(PFIC_IPRIORx_BASE + ((IRQn/8)*4)));

   unsigned int shift = (IRQn % 8) * 4;

   *Register_pointer &= ~(0xf<<shift);

   *Register_pointer |= (Priority<<shift);

}



unsigned int Secure_mode_set(Secure_t Mode){

 static unsigned int Backup = (unsigned int)0x00U;
 static unsigned int Flag   = (unsigned int)0x00U;

 if(Mode == SECURE_MODE_ON)
 {
  Backup = REG_PFIC_ITHRESDR;
  REG_PFIC_ITHRESDR = Extreme_Priority;
  Flag = PFIC_SECURE_MODE_FLAG;
  return (unsigned int)0x00U;
 }
 
  if(Mode == SECURE_MODE_OFF && Flag == PFIC_SECURE_MODE_FLAG)
 {
    REG_PFIC_ITHRESDR = Backup;
    Flag = (unsigned int)0x00U;
    return (unsigned int)0x00U;
 }else{ return (unsigned int)0x01U;}
}


void PFIC_Priority(Priority_t Minus_Priority){

  REG_PFIC_ITHRESDR = Minus_Priority;

}



/**
 * @brief Inicia a ISR inserida em IRQ, simulando uma interrupcao verdadeira.
 * 
 * @param IRQ 
 */
void IRQ_Append(IRQ_t IRQ){

    if(IRQ > 38 || IRQ < 0){return;}

    if(IRQ < 32){
     REG_PFIC_IPSR1 |= (1<<IRQ);

    }else{
     REG_PFIC_IPSR2 |= (1<<(IRQ - 32));
    }


}








#endif