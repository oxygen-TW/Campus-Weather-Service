su -l
sudo cp -r WeatherServiceClient /usr

#Set ssh server
sudo cp sshd_config /etc/ssh/
service ssh start
sudo update-rc.d -f ssh defaults
echo "SSH Server default port = 12345"

#install
read -p "Which port is connect to MCU?" port
echo "sudo python /usr/WeatherServiceClient/Driver.py "$port" /usr/WeatherServiceClient/Data/data.txt" > /usr/WeatherServiceClient/autorun.sh

pip install pyserial
pip install pymysql

cd /usr/WeatherServiceClient
echo Install completed
echo Thank you!

