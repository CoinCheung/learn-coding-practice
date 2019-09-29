
pipreqs ./
sudo docker run -v "$(pwd):/src/" cdrx/pyinstaller-windows pyinstaller main.py
sudo docker run -v "$(pwd):/src/" cdrx/pyinstaller-windows "apt-get update -y && apt-get install -y python3-dev python3-setuptools python3-pip && python3 -m pip install -r requirements.txt && pyinstaller --clean -y --dist ./dist/windows --workpath /tmp *.spec
