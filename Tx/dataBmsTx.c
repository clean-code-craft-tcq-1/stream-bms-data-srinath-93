#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dataBmsTx.h"

/* global variable declaration */
batteryReading_st bmsTempSocData;

/*
 **********************************************************************************************************************
 * Service name         : txBmsData
 * Syntax               : void txBmsData(void)
 * param[in]            : None
 * return               : None
 * Description          : Program to print the read battery temperature and soc data to the console
 **********************************************************************************************************************
 */
void txBmsData(void)
{
  int cntrLoop = 0;
  printf("Recorded BMS Data \nBattery Temperature \t\t\t Battery StateOfCharge\n");
  while(cntrLoop < bmsTempSocData.numOfData)
  {
    printf("Battery Temperature[%d] -> %f \t\t Battery StateOfCharge[%d] -> %f\n",cntrLoop,bmsTempSocData.batteryTempearature[cntrLoop],cntrLoop,bmsTempSocData.batterySoc[cntrLoop]);
  }
}

/*
 **********************************************************************************************************************
 * Service name         : readBmsData
 * Syntax               : retBmsStatus_en readBmsData(void)
 * param[in]            : None
 * return               : OK_STATUS, ERROR_STATUS
 * Description          : Program to read battery health that includes temperature, state of charge from a recorded 
                          file
 **********************************************************************************************************************
 */
retBmsStatus_en readBmsData(void)
{
  retBmsStatus_en retBmsStatus;
  float dataTemperature = 0.0;
  float dataSoc = 0.0;
  int cntrLoop = 0;
  bmsTempSocData.numOfData = 0;
  
  FILE * fileToBeRead= fopen("./Tx/dataBms.txt","r");
  if (fileToBeRead)
  {
    for(;fscanf(fileToBeRead, "%f %f\n", &dataTemperature,&dataSoc)!=EOF;cntrLoop++)
    {
      bmsTempSocData.batteryTempearature[cntrLoop] = dataTemperature;
      bmsTempSocData.batterySoc[cntrLoop] = dataSoc;
    }
    bmsTempSocData.numOfData = cntrLoop;
    retBmsStatus= OK_STATUS;
  }
  fclose(fileToBeRead);
  return retBmsStatus;
}

/*
 **********************************************************************************************************************
 * Service name         : dataBmsMain
 * Syntax               : retBmsStatus_en txBmsData(void)
 * param[in]            : None
 * return               : OK_STATUS, ERROR_STATUS
 * Description          : Program to invoke reading of required bms datas and send them to console or reciever
 **********************************************************************************************************************
 */
retBmsStatus_en dataBmsMain(void)
{
  retBmsStatus_en retBmsStatus;
  retBmsStatus = readBmsData();
  if(retBmsStatus != ERROR_STATUS)
  {
    txBmsData();
  }
  return retBmsStatus;
}
