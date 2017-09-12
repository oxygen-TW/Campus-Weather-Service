sudo apt-get update
sudo apt-get upgrade

#Set Firewall
sudo apt-get install ufw
ufw allow 12345/tcp
ufw allow http/tcp
ufw allow ftp/tcp
ufw enable

#Get Weather Service Client
apt-get install git python3
cd /home
git clone https://github.com/oxygen-TW/Weather-Station.git
cd Weather-Station
sh install.sh


