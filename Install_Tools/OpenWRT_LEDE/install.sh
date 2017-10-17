read -p "Which is your detector type?" type

opkg update
opkg install git python python3 python-pip unzip kmod-usb-serial kmod-usb-serial-ftdi
pip install --upgrade pip
pip install pyserial
pip install pymysql
git clone https://github.com/oxygen-TW/Weather-Station.git
wget http://weather.nhsh.tp.edu.tw/download/driver/$type
unzip driver-$type
cd driver-$type

mkdir /usr/WeatherServiceClient/
mkdir /usr/WeatherServiceClient/Data/
cp database.py Driver.py /usr/WeatherServiceClient/

read -p "Which port is connect to MCU?[usually /dev/ttyUSB0] " port
echo "" > /usr/WeatherServiceClient/autorun.sh #clear
echo "python /usr/WeatherServiceClient/Driver.py "$port" /usr/WeatherServiceClient/Data/data.txt" > /usr/WeatherServiceClient/autorun.sh