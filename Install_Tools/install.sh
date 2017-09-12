sudo cp -r WeatherServiceClient /usr
#sudo cp /home/WeatherServiceClient/crontab /etc
#sudo chmod +x /etc/crontab
#sudo crontab /etc/crontab

#install

read -p "Which port is connect to MCU?" port
echo "sudo python /usr/WeatherServiceClient/mainDriver.py "$port" /usr/WeatherServiceClient/Data/data.txt" > /usr/WeatherServiceClient/autorun.sh

cd /tmp
wget https://pypi.python.org/packages/source/p/pyserial/pyserial-3.0.1.tar.gz#md5=c8521e49f8852196aac39431e0901703
tar zxvf pyserial-3.0.1.tar.gz
cd pyserial-3.0.1/
python setup.py install
pip install pymysql

cd /usr/WeatherServiceClient
echo Install completed
echo Thank you!


