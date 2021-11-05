from PIL import Image
# pip install pillow
import sys
# input:
# python check.py <difficulty> <test_id>

# puedes agregar el flag -i para que 
# solo se impriman los tests fallidos


# checkea si 2 imagenes son iguales
# según la ruta
def check_dif(route_1, route_2):
    im1 = Image.open(route_1)
    im2 = Image.open(route_2)
    if list(im1.getdata()) == list(im2.getdata()):
        return True
    else:
        return False

n_querys = {}
for i in range (1, 7):
    n_querys[("Easy", i)] = 5 + 2 * i
    n_querys[("Medium", i)] = 100 + i * 30
    n_querys[("Hard", i)] = 220 + i * 30
    n_querys[("Lunatic", i)] = 220 + i * 30

# dificultad
dif = sys.argv[1]

# numero del test
test_id = sys.argv[2]

all = True
try:
    flag = sys.argv[3]
    if flag == "-i":
        all = False

except:
    pass


# contamos los tests incorrectos
counter = 0

# cantidad total de querys
total_querys = n_querys[(dif, int(test_id))]

#imprimimos un mensaje de inicio
print("");
print(" ---------CHECKING-----------\n")

# iteramos por las imagenes para ver si están correctas
for i in range(0, total_querys):
    route_1 = f"solutions/{dif}/out_{test_id}_{i}.png"
    route_2 = f"output/{dif}/out_{test_id}_{i}.png"

    out_string = "  query " + str(i) + ":"

    if check_dif(route_1, route_2):
        if all:
            blank_space = 13 - len(out_string)
            print(out_string + " " * blank_space + "C")
    else:
        counter += 1;
        blank_space = 13 - len(out_string)
        print(out_string + " " * blank_space + "Incorrect")

# imprimimos el resumen
print("")
print(" ---------SUMMARY------------")
print("")
print(f"    Correct:    {total_querys - counter}/{total_querys}")
print(f"    Incorrect:  {counter}")
