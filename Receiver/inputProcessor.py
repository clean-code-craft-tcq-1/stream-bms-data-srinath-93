import simpleMovingAverage

def getBMSData():
    while(True):
        bms_details = input()
        list_temp,list_soc = formatInputStream(bms_details)
        if len(list_temp) >= 5 and len(list_soc) >=5:
            simpleMovingAverage.calculateAvg(list_temp,list_soc)
    
def dataValidation(bms_details):
    length = len(bms_details)
    if length <5:
        print('please input more than 5 values')
        exit
    return True

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
    if(dataValidation(bms_details)==True):
        list_temp,list_soc = parameterSeperation(bms_details)
        return list_temp,list_soc
    
getBMSData()
