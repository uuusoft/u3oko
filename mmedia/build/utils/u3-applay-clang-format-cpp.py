# u3-applay-clang-format-cpp.py
# generator   gemini google
# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2026
# copyright   Erashov A.I.
# Напиши на питоне функцию, которая принимает в качестве аргумента начальный путь к файлам. 
# Для каждого файла рекурсивно, вызови clang-format, передавая в качестве аргумента путь к файлу.

import os
import subprocess

def format_files_recursive(start_path):
    """
    Рекурсивно ищет файлы C/C++/ObjC и форматирует их с помощью clang-format.
    """
    # Расширения файлов, которые обычно форматирует clang-format
    extensions = ('.cpp', '.c', '.h', '.hpp', '.cc', '.cxx', '.m', '.mm')
    
    # Проверяем, существует ли путь
    if not os.path.exists(start_path):
        print(f"Путь не найден: {start_path}")
        return

    # os.walk рекурсивно обходит директории
    for root, dirs, files in os.walk(start_path):
        for file in files:
            if file.endswith(extensions):
                file_path = os.path.join(root, file)
                try:
                    # Вызов clang-format -i (inplace, форматирование на месте)
                    # Если clang-format не в PATH, укажите полный путь к нему
                    subprocess.run(['clang-format', '-i', '--style=file:./../../../.clang-format', file_path], check=True)
                    print(f"Отформатирован: {file_path}")
                except subprocess.CalledProcessError as e:
                    print(f"Ошибка при форматировании {file_path}: {e}")
                except FileNotFoundError:
                    print("Ошибка: clang-format не найден. Убедитесь, что он установлен.")
                    return

# --- Пример использования ---
if __name__ == "__main__":
    # Укажите путь к папке с вашими файлами
    target_folder = "./../../" 
    format_files_recursive(target_folder)
    #print("Раскомментируйте строку выше, чтобы запустить.")
