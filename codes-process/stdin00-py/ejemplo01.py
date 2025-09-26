import sys

contador = 0
for linea in sys.stdin:
    l = linea.strip()
    campo = l.split(';')[0]

    if contador % 2 == 0:
        print("stdout:" + campo, file=sys.stdout)
    else:
        print("stderr" + campo, file=sys.stderr)

    contador += 1




'''
datos = open("permisos.csv", "r")
lineas = datos.readlines()[1:]

for linea in lineas:
    l = linea.strip()
    campo = l.split(';')[7]
    print(campo)
'''


