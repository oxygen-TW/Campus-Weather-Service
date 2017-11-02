
sudo cp -r /usr/local/src/Campus-Weather-Service/WeatherServiceClient /usr

#Set ssh server
sudo rm -f /etc/ssh/sshd_config
sudo cp /usr/local/src/Campus-Weather-Service/WeatherServiceClient/sshd_config /etc/ssh/
service ssh start
sudo update-rc.d -f ssh defaults
echo "SSH Server default port = 12345"

#install
read -p "Which port is connect to MCU?" port
echo "" > /usr/WeatherServiceClient/autorun.sh #clear
echo "sudo python /usr/WeatherServiceClient/Driver.py "$port" /usr/WeatherServiceClient/Data/data.txt" > /usr/WeatherServiceClient/autorun.sh

pip install pyserial
pip install pymysql

cd /usr/WeatherServiceClient
echo Install completed
echo Thank you!
echo "Notice! Please set crontab service by yourself!!!!!"
echo "If you skip this step, device will not upload data itself!"
echo "You also could set auto-update.sh in crontab, it can update automatically!"
read -n 1 -p "Press any key to start crontab -e"

crontab -e


