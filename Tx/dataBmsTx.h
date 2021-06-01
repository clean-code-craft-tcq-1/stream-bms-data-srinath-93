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
}batteryReading_st;

/* Function declaration */
retBmsStatus_en dataBmsMain();
retBmsStatus_en readBmsData();
retBmsStatus_en txBmsData();
