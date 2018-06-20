import urllib.request
import json

response = urllib.request.urlopen(
    'https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=rdec-key-123-45678-011121314')
data = response.read()
# print(data.decode('utf-8'))

encodedjson = json.loads(data)

for item in encodedjson["records"]["location"]:
    print (item["locationName"]) #注意此處用法