import json
import http.client
def send(temperature, humidity, UV_value, light_value, RainFall):
	params = {'tempature': temperature, 'humidity': humidity, 'UV': UV_value, 'light': light_value, 'rainfall':RainFall}
	headers	 = {"content-type": "application/json"}
	conn = http.client.HTTPConnection('203.72.63.54', "8080")
	conn.request('POST', 'http://203.72.63.54:8080/api', json.dumps(params), headers)
	response = conn.getresponse()
	data = response.read()
	print (data.decode("utf-8"))
	conn.close()

send(17,25,38,44,52)