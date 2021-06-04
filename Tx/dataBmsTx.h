#ifndef DATABMSTX_H_
#define DATABMSTX_H_

/* Macro Declaration */
#define ARRINDEXSIZE 50

/* Enum declarations */
typedef enum
{
  OK_STATUS,
  ERROR_STATUS
}retBmsStatus_en;

/* Structure declarations */
typedef struct
{
  float batteryTempearature[ARRINDEXSIZE];
  float batterySoc[ARRINDEXSIZE];
  int numOfData;
}batteryReading_st;

/* Function declaration */
retBmsStatus_en dataBmsMain(int runTimeIpNum);
retBmsStatus_en readBmsData(int runTimeIpNum);
int checkHaltRead(int runTimeIpNum, int loopCounter);
void txBmsData(void);

#endif  /* DATABMSTX_H_ */
