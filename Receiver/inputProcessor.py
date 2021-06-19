import simpleMovingAverage
import sys
def getBMSData():
    list_temp = []
    list_soc = []
    for i in sys.stdin:
        list_temp,list_soc = formatInputStream(i)
    print(list_temp)
    if len(list_temp) >= 5 and len(list_soc) >=5:
       simpleMovingAverage.calculateAvg(list_temp,list_soc)
    

def parameterSeperation(bms_details):
    dict_query = {}
    list_temp = []
    list_soc = []
    print(bms_details)
    for i in bms_details:
        try:
            key, val = i.split("=", 1)
            dict_query.update({key:float(val)})
            if key == 'Temperature':
                list_temp.append(dict_query['Temperature'])
            else:
                list_soc.append(dict_query['StateOfCharge'])
        except ValueError:
            continue
    return list_temp,list_soc

def formatInputStream(bms_details):
    bms_details = bms_details.replace('\n',',')
    bms_details = bms_details.replace(' ' ,'')
    bms_details = bms_details.split(',')
    list_temp,list_soc = parameterSeperation(bms_details)
    return list_temp,list_soc
    
getBMSData()
