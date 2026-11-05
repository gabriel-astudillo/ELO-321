#!/usr/bin/env python3
import sys
import os
from PIL import Image

def convert_to_ppm_p3(input_path, output_path, divisor=16):
    if not os.path.exists(input_path):
        print(f"Error: El archivo de entrada '{input_path}' no existe.", file=sys.stderr)
        sys.exit(1)

    # Abrir la imagen y convertir a modo RGB estándar de 3 canales
    img = Image.open(input_path).convert('RGB')
    orig_w, orig_h = img.size

    # Calcular la nueva altura divisible exactamente por el divisor (16)
    new_h = (orig_h // divisor) * divisor
    if new_h == 0:
        new_h = divisor  # Evitar dimensiones nulas en imágenes muy pequeñas

    # Calcular el nuevo ancho manteniendo la relación de aspecto original
    new_w = int(round(orig_w * (new_h / orig_h)))

    # Redimensionar usando remuestreo Lanczos para alta calidad
    img_resized = img.resize((new_w, new_h), Image.Resampling.LANCZOS)
    pixels = img_resized.load()

    # Escribir manualmente en formato PPM P3 (ASCII) respetando el límite de línea
    with open(output_path, 'w', encoding='ascii') as f:
        # Encabezado PPM P3
        f.write("P3\n")
        f.write(f"# Generado por convert_ppm_p3.py (H divisible por {divisor})\n")
        f.write(f"{new_w} {new_h}\n")
        f.write("255\n")

        # Matriz de píxeles en texto plano
        for y in range(new_h):
            row_tokens = []
            for x in range(new_w):
                r, g, b = pixels[x, y]
                row_tokens.extend([str(r), str(g), str(b)])
            
            # Escribir la fila en bloques de hasta 15 valores por línea (~60-70 caracteres)
            chunk_size = 15
            for i in range(0, len(row_tokens), chunk_size):
                f.write(" ".join(row_tokens[i:i + chunk_size]) + "\n")

    print(f"Conversión exitosa:")
    print(f"  Entrada : {input_path} ({orig_w}x{orig_h})")
    print(f"  Salida  : {output_path} ({new_w}x{new_h}) -> Altura divisible por {divisor} ({new_h} % {divisor} = {new_h % divisor})")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Uso: python3 {sys.argv[0]} <imagen_entrada.[jpg|png]> <salida.ppm> [divisor (default: 16)]")
        sys.exit(1)

    div = int(sys.argv[3]) if len(sys.argv) > 3 else 16
    convert_to_ppm_p3(sys.argv[1], sys.argv[2], div)

