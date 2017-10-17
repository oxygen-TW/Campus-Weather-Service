su -l
sudo apt-get update
sudo apt-get upgrade

#Set Firewall
sudo apt-get -y install ufw
ufw allow 12345/tcp
ufw allow http/tcp
ufw allow ftp/tcp
ufw enable

#Check dependences
apt-get -y install python-pip ftp openssh-server sysv-rc-confgit python3 python git-core

#Get Weather Service Client
cd /usr/local/src
git clone https://github.com/oxygen-TW/Weather-Station.git
cd Weather-Station
sh /usr/local/src/Weather-Station/Install_Tools/install.sh


