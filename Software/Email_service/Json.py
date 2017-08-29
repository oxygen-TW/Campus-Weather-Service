import urllib2
import json

_url = "https://api.thingspeak.com/channels/148353/feeds.json?results=1"

response = urllib2.urlopen(_url)
json_data = response.read()
pre_data = json.loads(json_data)
sec_data = pre_data['feeds']
pre_list = sec_data[0]
data = pre_list
#data = json.loads(pre_data['channel'])

useful_list=[data['field1'],data['field2'],data['field3'],data['field4'],data['created_at']]
print (useful_list)
a=""
a+=useful_list[0]
print (a)

response.close()
