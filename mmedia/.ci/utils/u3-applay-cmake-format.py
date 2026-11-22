# u3-applay-cmake-format.py
# ai-generator  google gemini 
# author        Erashov Anton erashov2026@proton.me
# date          01.01.2026
# copyright     Erashov A.I.
# ai-prompt

import os
import subprocess

def format_files_recursive(start_path):
    """
    Рекурсивно ищет файлы C/C++/ObjC и форматирует их с помощью clang-format.
    """
    # Расширения файлов, которые обычно форматирует clang-format
    extensions = ('.cmake')
    
    # Проверяем, существует ли путь
    if not os.path.exists(start_path):
        print(f"Путь не найден: {start_path}")
        return

    # os.walk рекурсивно обходит директории
    for root, dirs, files in os.walk(start_path):
        for file in files:
            if file.endswith(extensions) or file == "CMakeLists.txt":
                file_path = os.path.join(root, file)
                try:
                    subprocess.run(['cmake-format', '-i', '-c=cmake-format.json', file_path], check=True)
                    print(f"Отформатирован: {file_path}")
                except subprocess.CalledProcessError as e:
                    print(f"Ошибка при форматировании {file_path}: {e}")
                except FileNotFoundError:
                    print("Ошибка: cmake-format не найден. Убедитесь, что он установлен.")
                    return

# --- Пример использования ---
if __name__ == "__main__":
    # Укажите путь к папке с вашими файлами
    target_folder = "./../../" 
    format_files_recursive(target_folder)
    #print("Раскомментируйте строку выше, чтобы запустить.")
