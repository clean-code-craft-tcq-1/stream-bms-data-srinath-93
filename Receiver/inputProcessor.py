import simpleMovingAverage

def getBMSData():
    final_bms_data = []
    while(True):
        bms_details = input()
        bms_details = simpleMovingAverage.formatInputStream(bms_details)
        final_bms_data.append(bms_details)
        if len(final_bms_data) >= 5:
            simpleMovingAverage.calculateAvg(final_bms_data)
def formatInputStream(bms_details):
    bms_details = bms_details.replace('Battery Temperature[.+','temperature')
    bms_details = bms_details.replace('Battery StateOfCharge[.+','soc')
    bms_details = bms_details.replace('->', '=')
    bms_details = bms_details.replace(' ', '')
    bms_details = bms_details.split('\t')
    bms_details[0] = bms_details[0].split('=')
    bms_details[1] = bms_details[1].split('=')
    return bms_details
  
getBMSData()
