import json

str = "{\"type\":\"General\", \"Temp\":10, \"Humi\":20}"
data = json.loads(str)

print (data['type'])