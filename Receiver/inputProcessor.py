import simpleMovingAverage
import sys
def getBMSData():
    temp_val = []
    soc_val = []
    for i in sys.stdin:
        list_temp,list_soc = formatInputStream(i)
        temp_val.extend(list_temp)
        soc_val.extend(list_soc)
    if len(temp_val) >= 5 and len(soc_val) >=5:
       simpleMovingAverage.calculateAvg(temp_val,soc_val)
    

def parameterSeperation(bms_details):
    dict_query = {}
    list_temp = []
    list_soc = []
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
    bms_details = bms_details.replace('\n','')
    bms_details = bms_details.replace(' ' ,'')
    bms_details = bms_details.split(',')
    list_temp,list_soc = parameterSeperation(bms_details)
    return list_temp,list_soc
    
getBMSData()
