#include <stdio.h>
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
  int loopCntr = 0;
  printf("Recorded BMS Data \nBattery Temperature \t\t\t Battery StateOfCharge\n");
  while(loopCntr < bmsTempSocData.numOfData)
  {
    printf("Battery Temperature[%d] -> %f \t\t Battery StateOfCharge[%d] -> %f\n",loopCntr,bmsTempSocData.batteryTempearature[loopCntr],loopCntr,bmsTempSocData.batterySoc[loopCntr]);
    loopCntr++;
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
retBmsStatus_en readBmsData(int runTimeIpNum)
{
  retBmsStatus_en bmsStatusRet = ERROR_STATUS;
  float dataTemperature = 0.0;
  float dataSoc = 0.0;
  int cntrLoop = 0;
  int tempRunTimeIp = runTimeIpNum;
  bmsTempSocData.numOfData = 0; 
  int runTimeIp = 0;
  
  FILE * fileToBeRead= fopen("./Tx/dataBms.txt","r");
  if (fileToBeRead)
  {
    for(;fscanf(fileToBeRead, "%f %f\n", &dataTemperature,&dataSoc)!=EOF;cntrLoop++)
    {
      bmsTempSocData.batteryTempearature[cntrLoop] = dataTemperature;
      bmsTempSocData.batterySoc[cntrLoop] = dataSoc;
      if((runTimeIpNum==cntrLoop)&&(runTimeIp==0))
      {
        /* entering checkHaltRead function */
        runTimeIp = checkHaltRead(cntrLoop);
        printf("checkHaltRead return value in file is %d \n",runTimeIp);
        /* when return value is 1, halt requested or max counter value reached */
        if(runTimeIp == 1)
        {
          break;
        }
        else
        {
          fseek(fileToBeRead, 0, SEEK_END);
          /*\n File pointer rewind \n*/
          runTimeIpNum += tempRunTimeIp;
        }
      }
    }
    bmsTempSocData.numOfData = cntrLoop;
    bmsStatusRet= OK_STATUS;
  }
  fclose(fileToBeRead);
  return bmsStatusRet;
}

int checkHaltRead(int loopCounter)
{
  int haltInput = 0;
  int retValStatus = 0;
  FILE * fileCheckHalt= fopen("./Tx/haltBmsRead.txt","r");
    if(fileCheckHalt)
    {
    /* provide input to the file as 1 to stop the data read else provide 0 */
      while(fscanf(fileCheckHalt, "%d\n", &haltInput)!=EOF)
      {
        printf("Input provided in file is %d \n",haltInput);
      }
    }
    else
    {
      printf("\ncould not open the file\n");
    }
  fclose(fileCheckHalt);
  retValStatus = checkStatusRead(haltInput,loopCounter);
  printf("checkStatusRead return value in file is %d \n",retValStatus);
  return (haltInput&retValStatus);
}

int checkStatusRead(int runTimeIpStatus, int cntrLoop)
{
  int retValStatus=0;
  if((runTimeIpStatus == 1)||(cntrLoop >= 1000))
  {
    /* setting return value for checkReadStatus as 1 */
    retValStatus = 1;
  }
  return retValStatus;
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
retBmsStatus_en dataBmsMain(int runTimeIpNum)
{
  retBmsStatus_en retBmsStatus = ERROR_STATUS;
  retBmsStatus = readBmsData(runTimeIpNum);
  if(retBmsStatus != ERROR_STATUS)
  {
    txBmsData();
  }
  return retBmsStatus;
}
