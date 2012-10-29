/****************************************************
 *  LineTracer.h                                         
 *  Created on: 2012/05/05 8:31:07                      
 *  Implementation of the Class LineTracer       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#if !defined(EA_6FB55B53_C0F0_4250_B6B0_BC28A0A336D7__INCLUDED_)
#define EA_6FB55B53_C0F0_4250_B6B0_BC28A0A336D7__INCLUDED_

#include "ColorJudgement.h"
#include "BalanceRunner.h"
#include "LightSensor.h"


// ‘®«‚ğ•Û‚·‚é‚½‚ß‚Ì\‘¢‘Ì‚Ì’è‹`
typedef struct LineTracer
{
	ColorJudgement *colorJudgement;
	BalanceRunner *balanceRunner;
	LightSensor *lightSensor;
	S32 diff[2];
	F32 integral;
} LineTracer;

// ŒöŠJ‘€ì
void LineTracer_init(LineTracer* this);
void LineTracer_trace(LineTracer* this, int forword);

#endif /*!defined(EA_6FB55B53_C0F0_4250_B6B0_BC28A0A336D7__INCLUDED_)*/

