def calculateAvg(list_temp,list_soc):
    final_display_list = {}
    list_temp.sort()
    list_soc.sort()
    final_display_list['temperature'] = list_temp
    final_display_list['soc'] =list_soc
    print(final_display_list)
    displayOutput(final_display_list)
def displayOutput(bms_data):
    print('Max Temperature:', bms_data['temperature'][-1])
    print('Min Temperature:', bms_data['temperature'][0])
    print('Max SOC:', bms_data['soc'][-1])
    print('Min SOC:', bms_data['soc'][0])
    print('Average of last five values of temperature and soc', averageLastFive(bms_data['temperature'],bms_data['soc']))
    
def averageLastFive(list_temp,list_soc):
    sum_temp = 0
    sum_soc = 0
    for i in range(-1,-6,-1):
        sum_temp += list_temp[i]
        sum_soc += list_soc[i]
        return sum_temp/5,sum_soc/5
