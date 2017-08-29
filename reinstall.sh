sudo rm -rf /usr/WeatherServiceClient
sudo rm -f /etc/crontab

sudo cp -r WeatherServiceClient /usr
sudo mv RPi\ software/crontab /etc
sudo chmod +x /etc/crontab
sudo crontab /etc/crontab

read -p "Which port is connect to MCU?" port
read -p "Where do you want to save weather data?" _file

if [ -d $_file ]; then
    echo "sudo python /usr/WeatherStationClient/mainDriver.py "$port" "$_file > /usr/WeatherStationClient/autorun.sh

	echo Install completed
	echo Thank you!
else
    echo "Directory "$_file" does not exists."
fi

