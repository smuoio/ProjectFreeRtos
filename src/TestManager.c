/**
 * \file TestManager.c
 * \brief the file manages all tests created for the SCADA
 */
#include <stdio.h>
#include "TestManager.h"
#include "TestManager_impl.h"
#include "OwnBusPublic.h"
#include "OwnBus.h"


/**
* \brief state machine used to call the tests
*/
typedef void (*TestId)(void);

/**
* \brief static tab of functions used to write the data from CCUT packet
*/
 const TestId _jumpTestTabFun[] = {TestCheck,
		                           TestCheckInput,
		                           TestDummy
 };

 const TestId _FeedbackTest13Poles[] = {Test_10Line, TestDummy};

void TestManager(void)
{
	const uint16_t TestId = 0x1U;

	//check which connector is under test
	{
		//printf("ii = %d\n", ii);
		//static uint8_t *lindex;
		//lindex = GetDataRx(TestId);
		uint8_t *data;
		data = GetDataRx(TestId);//(unsigned char *)(getOwnBusStruct()->buspacketrx.DataRx[TestId]);
		_FeedbackTest13Poles[LookUpTable(data/*GetDataRx(TestId)*/)]();
	}
}

uint8_t LookUpTable( uint8_t *index)
{
	const uint8_t Tab[15] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0,0x01,0x01,0x01,0x01};
	return(Tab[*index]);
}
