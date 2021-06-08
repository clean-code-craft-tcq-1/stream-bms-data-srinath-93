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
retBmsStatus_en readBmsData(int runTimeIpNo)
{
  retBmsStatus_en bmsStatusRet = ERROR_STATUS;
  FILE * fileToOpen= fopen("./Tx/dataBms.txt","r");
  /* check if file is valid or not */
  if (fileToOpen)
  {
    bmsStatusRet = performBmsDataRead(fileToOpen, runTimeIpNo);
  }
  else
  {
	printf("Could not open file and reporting error status\n");
  }	
  fclose(fileToOpen);
  return bmsStatusRet;
}

retBmsStatus_en performBmsDataRead(FILE * fileToBeRead,int runTimeIpNum)
{
  retBmsStatus_en bmsStatusRet = ERROR_STATUS;
  float dataTemperature = 0.0;
  float dataSoc = 0.0;
  int cntrLoop = 0;
  int tempRunTimeIp = runTimeIpNum;
  bmsTempSocData.numOfData = 0; 
  int runTimeIp = 0;
  for(;fscanf(fileToBeRead, "%f %f\n", &dataTemperature,&dataSoc)!=EOF;cntrLoop++)
  {
    bmsTempSocData.batteryTempearature[cntrLoop] = dataTemperature;
    bmsTempSocData.batterySoc[cntrLoop] = dataSoc;
    /* check validateReadBmsData function */
    runTimeIp = validateReadBmsData(runTimeIpNum,cntrLoop);
    /* when return value is 1, halt requested or max counter value reached */
    if(runTimeIp == 1)
    {
        printf("breaking the loop \n");
        break;
    }
    else if(runTimeIp == 0)
    {
        /* rewinding the file pointer */
        fseek(fileToBeRead,0,SEEK_SET);
//        rewind(fileToBeRead);
        runTimeIpNum += tempRunTimeIp;
    }
    else
    {
      /* Do nothing */
    }
  }
    bmsTempSocData.numOfData = cntrLoop;
    bmsStatusRet= OK_STATUS;
  return bmsStatusRet;  
}

int validateReadBmsData(int runTimeIpdata, int cntrLoop)
{
  int runTimeIp_1 = 0;
  int runTimeIp_2 = 0;
  int retValStatus = 0;
  if(runTimeIpdata==cntrLoop)
  {
    /* entering checkHaltRead function */
    runTimeIp_1 = checkHaltRead();
  }
  runTimeIp_2 = checkStatusRead(runTimeIp_1,runTimeIpdata,cntrLoop);
  retValStatus = runTimeIp_2;
  return retValStatus;
}

int checkHaltRead()
{
  int haltInput = 0;
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
  /* send the updated return value */
  return (haltInput);
}

int checkStatusRead(int runTimeIpStatus,int runTimeIpdata,int cntrLoop)
{
  int retValStatus=2;
  if((runTimeIpStatus == 1)||(cntrLoop > Max_Count(bmsTempSocData.maxDataToStream)))
  {
    /* setting return value for checkReadStatus as 1 denoting halt data stream */
    retValStatus = 1;
  }
  else if(runTimeIpdata == cntrLoop)
  {
    /* setting return value for checkReadStatus as 0 denoting rewind the data stream */
    retValStatus = 0;
  }
  else
  {
    /* do nothing */
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
retBmsStatus_en dataBmsMain(int runTimeIpNum, int maxDataStreamRange)
{
  bmsTempSocData.maxDataToStream = maxDataStreamRange;
  retBmsStatus_en retBmsStatus = ERROR_STATUS;
  retBmsStatus = readBmsData(runTimeIpNum);
  if(retBmsStatus != ERROR_STATUS)
  {
    txBmsData();
  }
  return retBmsStatus;
}
