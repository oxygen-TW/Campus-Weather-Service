import urllib2

_url = "https://api.thingspeak.com/channels/148353/feeds.json?results=1"

response = urllib2.urlopen(_url)
data = response.read()
print (data)