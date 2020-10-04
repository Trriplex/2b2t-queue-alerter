import requests
from plyer import notification
import time

while True:
    x = requests.get('https://www.2b2t.io/api/queue?last=true')
    q = int(x.text.split(',')[1].replace(']',''))

    if q < 200:
        notification.notify(
            title='2b2t queue is '+str(q),
            message='now go to 2b2t.org !',
            app_icon=None,
            timeout=5,
        )

    time.sleep(120)
