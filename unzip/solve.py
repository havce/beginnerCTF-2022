import zipfile
import os
i = 999
while i >= 0:
    with zipfile.ZipFile(f'flag{i}.zip', 'r') as zip_ref:
        zip_ref.extractall('./')
    os.remove(f'flag{i}.zip')
    i-=1