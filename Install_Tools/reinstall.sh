su -l
sudo rm -rf /usr/WeatherServiceClien
sudo cp -r /usr/local/src/Weather-Station/WeatherServiceClient /usr

#Set ssh server
sudo rm -f /etc/ssh/sshd_config
sudo cp /usr/local/src/Weather-Station/WeatherServiceClient/Install_Tools/sshd_config /etc/ssh/
service ssh start
sudo update-rc.d -f ssh defaults
echo "SSH Server default port = 12345"

#install
read -p "Which port is connect to MCU?" port
rm -f /usr/WeatherServiceClient/autorun.sh
echo "sudo python /usr/WeatherServiceClient/Driver.py "$port" /usr/WeatherServiceClient/Data/data.txt" > /usr/WeatherServiceClient/autorun.sh

pip install pyserial
pip install pymysql

cd /usr/WeatherServiceClient
echo Reinstall completed
echo Thank you!


