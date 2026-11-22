# u3-remove-comecrial-parts.py
# ai-generator  google gemini 
# author        Erashov Anton erashov2026@proton.me
# date          30.07.2026
# copyright     Erashov A.I.
# ai-prompt
# Напиши на питоне функцию, которая принимает в качестве аргумента начальный путь к каталогу. 
# Содержимое всех подкаталогов указанного каталога, в которых есть файл с именем u3-folder-with-commercial-part.mark нужно удалить
# кроме файлов с именем u3-folder-with-commercial-part.mark

import os
import subprocess
import shutil

def remove_contents_in_marked_dirs(root_dir: str):
    marker_name = 'u3-folder-with-commercial-part.mark'
    # Обходим каталог снизу вверх, чтобы корректно удалять вложенные структуры
    for dirpath, dirnames, filenames in os.walk(root_dir, topdown=False):
        if marker_name in filenames:
            # Удаляем всё внутри найденного каталога, но не сам каталог
            for item in os.listdir(dirpath):
                item_path = os.path.join(dirpath, item)
                if item != marker_name:
                    if os.path.isfile(item_path) or os.path.islink(item_path):
                        os.unlink(item_path)
                    elif os.path.isdir(item_path):
                        shutil.rmtree(item_path)

# --- Пример использования ---
if __name__ == "__main__":
    # Укажите путь к папке с вашими файлами
    target_folder = "./../../" 
    remove_contents_in_marked_dirs(target_folder)
    