#ifndef DATABMSTX_H_
#define DATABMSTX_H_

/* Macro Declaration */
#define ARRINDEXSIZE 512
#define Max_Count(x) x*5 /* maintaining lesser than array index value */

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
int checkHaltRead(void);
int checkStatusRead(int runTimeIpStatus, int cntrLoop);
int validateReadBmsData(int runTimeIpdata, int cntrLoop);
void txBmsData(void);

#endif  /* DATABMSTX_H_ */
