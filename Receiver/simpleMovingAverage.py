def calculateAvg(bms_data):
    temperature_values = []
    soc_values = []
    final_display_list = {}

    for i in range(-5, 0, 1):
        temperature_values.append(float(bms_data[i][0][1]))
        soc_values.append(float(bms_data[i][1][1]))

    soc_values.sort()
    temperature_values.sort()
    final_display_list['temperature'] = temperature_values
    final_display_list['soc'] = soc_values
    displayOutput(final_display_list)
    
def displayOutput(bms_data):
    print('Max Temperature:', bms_data['temperature'][-1])
    print('Min Temperature:', bms_data['temperature'][0])
    print('Average Temperature:', average(bms_data['temperature']))
    print('Max SOC:', bms_data['soc'][-1])
    print('Min SOC:', bms_data['soc'][0])
    print('Average SOC:', average(bms_data['soc']))
    
def average(list):
    return round(sum(list) / len(list), 2)
