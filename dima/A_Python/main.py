import sqlite3
import json
from flask import Flask

app = Flask(__name__)
f = open('stolen.json')
params = json.load(f)
f.close()
filename, things, least_value = params['filename'], params['things'], params['least_value']


@app.route('/steal')
def steal():
    connection = sqlite3.connect(filename)
    cursor = connection.cursor()
    cursor.execute('SELECT * FROM Stolen')
    stolen = cursor.fetchall()
    connection.close()
    stolen = [{'thing': el[1], 'whom': el[2], 'when': el[3]} for el in stolen if
              any([el2 in el[1] for el2 in things]) and el[4] >= least_value]
    return sorted(stolen, key=lambda x: x['thing'])


if __name__ == '__main__':
    app.run(port=8080)
