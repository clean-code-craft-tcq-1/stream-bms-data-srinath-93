def calculateAvg(list_temp,list_soc):
    final_display_list = {}
    list_temp.sort()
    list_soc.sort()
    final_display_list['temperature'] = list_temp
    final_display_list['soc'] =list_soc
    print(final_display_list)
    displayOutput(final_display_list)
    
def calculateMin(bms_data,param):
    return min(bms_data[param])
def calculateMax(bms_data,param):
    return max(bms_data[param])

def displayOutput(bms_data):
    print('Max Temperature:', calculateMax(bms_data,'temperature'))
    print('Min Temperature:', calculateMin(bms_data,'temperature'))
    print('Max SOC:', calculateMax(bms_data,'soc'))
    print('Min SOC:', calculateMin(bms_data,'soc'))
    print('Average of last five values of temperature', averageLastFive(bms_data['temperature']))
    print('Average of last five values of soc', averageLastFive(bms_data['soc']))
    
def averageLastFive(bms_param_list):
    sum_list = 0
    length = len(bms_param_list)
    if length !=0:
        for i in range(-1,-6,-1):
            sum_list += bms_param_list[i]
        return sum_list/5
    else:
        return "Length of the list is Zero"
